#!/usr/bin/env bash
#
# Correction automatique du travail rendu dans rendu/.
#
# Usage :
#   .github/correction/corriger.sh                 # tout corriger
#   .github/correction/corriger.sh day03           # un jour ou un projet
#   .github/correction/corriger.sh day03/task07    # une tâche
#
# Chaque tâche est décrite par un dossier .github/correction/<projet>/<tâche>/ :
#   config        variables shell (voir plus bas)
#   test.c        programme de test lié aux fichiers rendus (mode function)
#   test.sh       script de test (modes program et script)
#   expected.txt  (optionnel) sortie standard attendue de test.c
#
# Variables de config :
#   MODE       function (défaut) : FILES + test.c compilés ensemble ;
#              program : FILES compilés en un programme, puis test.sh ;
#              script : test.sh lancé dans une copie de rendu/<projet>/.
#   FILES      fichiers rendus, relatifs à rendu/<projet>/ (motifs acceptés)
#   ALLOWED    fonctions externes autorisées
#   LIBMY      yes : construit rendu/<projet>/lib/my/*.c en libmy.a et la lie
#   SIBLINGS   no : n'utilise pas les autres .c du dossier (par défaut, comme
#              chez Epitech, ils sont disponibles via une archive)
#   HELPERS    fichiers de .github/correction/lib/ ajoutés à la compilation
#   RECURSIVE  fonctions qui doivent s'appeler elles-mêmes
#   ITERATIVE  fonctions qui ne doivent pas s'appeler elles-mêmes
#   TIMEOUT    durée maximale du test en secondes (défaut : 10)
#   EXTRA_CFLAGS  options ajoutées à la compilation (ex. -include fichier.h)
#   IGNORE_TRAILING_SPACES  yes : ignore les espaces en fin de ligne dans la
#              comparaison avec expected.txt

set -u
shopt -s nullglob

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
CORR="$ROOT/.github/correction"
RENDU="${RENDU_DIR:-$ROOT/rendu}"
CC="${CC:-gcc}"
CFLAGS="-Wall -Wextra -Werror"
SANITIZE="-fsanitize=address,undefined -fno-omit-frame-pointer -g"
DEFAULT_TIMEOUT=10
# Symboles ajoutés par le compilateur, toujours tolérés.
IMPLICIT_SYMBOLS="__stack_chk_fail _GLOBAL_OFFSET_TABLE_"

export ASAN_OPTIONS="detect_leaks=0:abort_on_error=0"
export UBSAN_OPTIONS="halt_on_error=1:print_stacktrace=1"
export CORR

WORK="$(mktemp -d)"
trap 'rm -rf "$WORK"' EXIT

if [ -t 1 ]; then
    GREEN=$'\e[32m'; RED=$'\e[31m'; GREY=$'\e[90m'; BOLD=$'\e[1m'; RESET=$'\e[0m'
else
    GREEN=""; RED=""; GREY=""; BOLD=""; RESET=""
fi

total=0
rendus=0
valides=0
summary_projects=""
summary_rows=""
summary_details=""

# Vrai si la tâche $1 (ex. day03/task02) est sélectionnée par les arguments.
selected() {
    local id="$1" arg
    [ "$NB_ARGS" -eq 0 ] && return 0
    for arg in "${ARGS[@]}"; do
        arg="${arg%/}"
        [ "$id" = "$arg" ] && return 0
        case "$id" in "$arg"/*) return 0 ;; esac
    done
    return 1
}

# Vrai si la fonction $2 contient un appel à elle-même dans l'objet $1.
calls_itself() {
    objdump -dr "$1" | awk -v f="$2" '
        /^[0-9a-f]+ <[^>]+>:$/ { infn = ($2 == "<" f ">:") ; next }
        infn && $0 ~ ("R_[A-Z0-9_]+[ \t]+" f "([-+]0x[0-9a-f]+)?$") { found = 1 }
        infn && $0 ~ ("call.*<" f ">") { found = 1 }
        END { exit !found }'
}

# Nettoie et tronque un journal pour l'affichage.
excerpt() {
    sed -e '/Shadow bytes around/,$d' \
        -e '/__libc_start\|in _start /d' \
        -e 's/\x1b\[[0-9;]*m//g' \
        -e "s|$WORK/[^ ]*/copy/|rendu/$PROJECT/|g" \
        -e "s|$RENDU/|rendu/|g" -e "s|$ROOT/||g" -e "s|$WORK/[^ :]*/||g" "$1" \
        | head -n 40
}

# Développe FILES dans le dossier $1. Remplit SRC_FILES et MISSING.
expand_files() {
    local dir="$1" pattern patterns matches f
    SRC_FILES=()
    MISSING=""
    read -ra patterns <<< "$FILES"
    for pattern in "${patterns[@]}"; do
        matches=()
        for f in "$dir"/$pattern; do
            [ -e "$f" ] && matches+=("$f")
        done
        if [ "${#matches[@]}" -eq 0 ]; then
            MISSING="$MISSING $pattern"
        else
            SRC_FILES+=("${matches[@]}")
        fi
    done
}

# Compile les .c de $1 (sans sanitizer) dans $2 avec $FLAGS (défaut :
# CFLAGS). Écrit la liste des objets dans OBJS. Échoue au premier fichier
# qui ne compile pas.
compile_plain() {
    local out="$2" f o flags="${FLAGS:-$CFLAGS}"
    shift 2
    OBJS=()
    for f in "$@"; do
        case "$f" in *.c) ;; *) continue ;; esac
        o="$out/$(echo "${f#"$RENDU"/}" | tr '/' '_').o"
        # shellcheck disable=SC2086
        if ! "$CC" $flags $INCLUDES -c "$f" -o "$o" >> "$LOG" 2>&1; then
            return 1
        fi
        OBJS+=("$o")
    done
}

# Construit la libmy de rendu/<projet>/lib/my/ : objets simples dans LIB_OBJS
# (pour l'analyse des symboles) et libmy.a avec sanitizers dans $w/lib.
# Les warnings de la libmy sont tolérés : elle est jugée par sa propre tâche.
build_libmy() {
    local src="$1" w="$2" f main_log="$LOG"
    local lib_sources=("$src"/lib/my/*.c)
    if [ "${#lib_sources[@]}" -eq 0 ]; then
        REASON="libmy introuvable : aucun fichier .c dans lib/my/"
        return 1
    fi
    mkdir -p "$w/lib/plain" "$w/lib/san"
    LOG="$w/lib/build.log"
    if ! FLAGS="-Wall -Wextra" compile_plain "$src" "$w/lib/plain" "${lib_sources[@]}"; then
        LOG="$main_log"
        cat "$w/lib/build.log" >> "$LOG"
        REASON="la libmy (lib/my/) ne compile pas"
        return 1
    fi
    LOG="$main_log"
    LIB_OBJS=("${OBJS[@]}")
    for f in "${lib_sources[@]}"; do
        # shellcheck disable=SC2086
        "$CC" -Wall -Wextra $SANITIZE $INCLUDES -c "$f" \
            -o "$w/lib/san/$(basename "${f%.c}").o" > /dev/null 2>&1 || return 1
    done
    ar rcs "$w/lib/libmy.a" "$w"/lib/san/*.o
    LINK_LIBMY="-L$w/lib -lmy"
}

# Archive les autres .c à la racine de rendu/<projet>/ (hors FILES), comme
# le « gcc *.c » d'Epitech. Ceux qui ne compilent pas sont ignorés.
build_siblings() {
    local src="$1" w="$2" f skip o
    mkdir -p "$w/sib"
    for f in "$src"/*.c; do
        skip=0
        for o in "${SRC_FILES[@]}"; do [ "$f" = "$o" ] && skip=1; done
        [ "$skip" -eq 1 ] && continue
        # shellcheck disable=SC2086
        "$CC" $SANITIZE $INCLUDES -c "$f" -o "$w/sib/$(basename "${f%.c}").o" \
            > /dev/null 2>&1 || rm -f "$w/sib/$(basename "${f%.c}").o"
    done
    set -- "$w"/sib/*.o
    [ "$#" -eq 0 ] && return
    ar rcs "$w/sib/libsib.a" "$@"
    LINK_SIB="-L$w/sib -lsib"
    SIB_DEFINED="$(nm --defined-only "$@" | awk 'NF == 3 { print $3 }')"
}

# Vérifie que les objets ($@) n'appellent que des fonctions autorisées.
check_symbols() {
    local defined undefined forbidden="" sym
    defined="$(nm --defined-only "$@" | awk 'NF == 3 { print $3 }')"
    undefined="$(nm -u "$@" | awk 'NF >= 2 { print $2 }' | sort -u)"
    for sym in $undefined; do
        # shellcheck disable=SC2086
        printf '%s\n' $defined $SIB_DEFINED $ALLOWED $IMPLICIT_SYMBOLS | grep -qxF "$sym" && continue
        forbidden="$forbidden $sym"
    done
    if [ -n "$forbidden" ]; then
        REASON="fonction(s) interdite(s) :$forbidden"
        echo "Fonctions autorisées : ${ALLOWED:-aucune}" >> "$LOG"
        return 1
    fi
}

# Analyse la sortie d'erreur d'un test exécuté avec sanitizers.
check_run() {
    local status="$1" err="$2"
    if [ "$status" -eq 124 ]; then
        REASON="trop lent (plus de ${TIMEOUT}s) ou boucle infinie"
        return 1
    fi
    if grep -q 'ERROR: \(AddressSanitizer\|LeakSanitizer\)' "$err"; then
        REASON="erreur mémoire détectée"
        return 1
    fi
    if grep -q 'runtime error:' "$err"; then
        REASON="comportement indéfini détecté (dépassement d'entier ?)"
        return 1
    fi
    if [ "$status" -gt 128 ]; then
        REASON="crash (signal $((status - 128)))"
        return 1
    fi
}

# Corrige une tâche. Remplit REASON et LOG.
# Code retour : 0 = validée, 1 = échec, 2 = non rendue.
grade() {
    local result
    WARNINGS=0
    grade_task "$1"
    result=$?
    if [ "$WARNINGS" -eq 1 ]; then
        {
            echo "--- warnings refusés par $CFLAGS :"
            cat "$WORK/$1/warnings.log"
        } >> "$LOG"
    fi
    if [ "$WARNINGS" -eq 1 ] && [ "$result" -eq 0 ]; then
        REASON="warnings refusés par -Werror (les tests passent sinon)"
        return 1
    fi
    if [ "$WARNINGS" -eq 1 ] && [ "$result" -eq 1 ]; then
        REASON="$REASON, et warnings refusés par -Werror"
    fi
    return "$result"
}

grade_task() {
    local id="$1" dir="$CORR/$1" src="$RENDU/${1%%/*}" w="$WORK/$1"
    local fn obj found status

    MODE="function"; FILES=""; ALLOWED=""; LIBMY=""; HELPERS=""; SIBLINGS="yes"
    RECURSIVE=""; ITERATIVE=""; TIMEOUT="$DEFAULT_TIMEOUT"
    IGNORE_TRAILING_SPACES=""; EXTRA_CFLAGS=""
    # shellcheck disable=SC1091
    . "$dir/config"
    REASON=""; LOG="$w/log"; LINK_LIBMY=""; LIB_OBJS=(); LINK_SIB=""; SIB_DEFINED=""
    mkdir -p "$w/plain" "$w/build" "$w/run"
    : > "$LOG"
    INCLUDES="-I$src/include -I$src/lib/my -I$CORR/lib $EXTRA_CFLAGS"

    expand_files "$src"
    [ "${#SRC_FILES[@]}" -eq 0 ] && return 2
    if [ -n "$MISSING" ]; then
        REASON="fichier(s) manquant(s) :$MISSING"
        return 1
    fi

    if [ "$MODE" = "script" ]; then
        cp -r "$src" "$w/copy"
        (cd "$w/copy" && DAY="$w/copy" TEST_DIR="$dir" \
            timeout "$TIMEOUT" bash "$dir/test.sh" > "$w/out" 2>&1)
        status=$?
        cat "$w/out" >> "$LOG"
        check_run "$status" "$w/out" || return 1
        if [ "$status" -ne 0 ]; then
            REASON="$(grep -m1 '^ÉCHEC' "$w/out" | sed 's/^ÉCHEC : //')"
            REASON="${REASON:-le test a échoué}"
            return 1
        fi
        return 0
    fi

    # 1. Compilation des fichiers rendus (et de la libmy) avec -Werror.
    if [ "$LIBMY" = "yes" ]; then
        build_libmy "$src" "$w" || return 1
    fi
    local log_size
    log_size="$(wc -c < "$LOG")"
    if ! compile_plain "$src" "$w/plain" "${SRC_FILES[@]}"; then
        # Simples warnings ? On continue sans -Werror pour donner le résultat
        # des tests, mais la tâche restera en échec. Les warnings sont mis de
        # côté et ajoutés à la fin du journal.
        if LOG=/dev/null FLAGS="-Wall -Wextra" \
                compile_plain "$src" "$w/plain" "${SRC_FILES[@]}"; then
            WARNINGS=1
            tail -c +"$((log_size + 1))" "$LOG" > "$w/warnings.log"
            truncate -s "$log_size" "$LOG"
        else
            REASON="ne compile pas"
            return 1
        fi
    fi
    [ "$SIBLINGS" = "yes" ] && build_siblings "$src" "$w"

    # 2. Pas de main (sauf programme), pas de fonction interdite.
    if [ "$MODE" = "function" ] && [ "${#OBJS[@]}" -gt 0 ] \
            && nm --defined-only "${OBJS[@]}" | awk '{ print $3 }' | grep -qx 'main'; then
        REASON="les fichiers rendus ne doivent pas contenir de main"
        return 1
    fi
    if [ "$((${#OBJS[@]} + ${#LIB_OBJS[@]}))" -gt 0 ]; then
        check_symbols "${OBJS[@]}" "${LIB_OBJS[@]}" || return 1
    fi

    # 3. Contraintes récursif / itératif.
    for fn in $RECURSIVE $ITERATIVE; do
        found=0
        for obj in "${OBJS[@]}"; do
            calls_itself "$obj" "$fn" && found=1
        done
        if [[ " $RECURSIVE " == *" $fn "* ]] && [ "$found" -eq 0 ]; then
            REASON="$fn doit être récursive"
            return 1
        fi
        if [[ " $ITERATIVE " == *" $fn "* ]] && [ "$found" -eq 1 ]; then
            REASON="$fn ne doit pas être récursive"
            return 1
        fi
    done

    # 4. Construction du programme de test (avec sanitizers).
    local srcs=() f
    for f in "${SRC_FILES[@]}"; do
        case "$f" in *.c) srcs+=("$f") ;; esac
    done
    for f in $HELPERS; do srcs+=("$CORR/lib/$f"); done
    [ "$MODE" = "function" ] && srcs+=("$dir/test.c")
    # shellcheck disable=SC2086
    if ! "$CC" -Wall -Wextra $SANITIZE $INCLUDES "${srcs[@]}" \
            -o "$w/build/prog" $LINK_SIB $LINK_LIBMY > "$w/build.log" 2>&1; then
        grep -v 'warning:' "$w/build.log" >> "$LOG"
        local dup
        dup="$(grep -o "multiple definition of \`[^']*'" "$w/build.log" | head -n 1 \
            | sed "s/.*\`\(.*\)'/\1/")"
        if [ -n "$dup" ]; then
            REASON="$dup est défini deux fois (fonction fournie à ne pas rendre, ou en double)"
        else
            REASON="erreur à l'édition de liens (prototype ou nom de fonction incorrect ?)"
        fi
        return 1
    fi

    # 5. Exécution.
    if [ "$MODE" = "program" ]; then
        (cd "$w/run" && PROG="$w/build/prog" TEST_DIR="$dir" \
            timeout "$TIMEOUT" bash "$dir/test.sh" > "$w/out" 2>&1)
        status=$?
        cat "$w/out" >> "$LOG"
        check_run "$status" "$w/out" || return 1
        if [ "$status" -ne 0 ]; then
            REASON="$(grep -m1 '^ÉCHEC' "$w/out" | sed 's/^ÉCHEC : //')"
            REASON="${REASON:-sortie incorrecte}"
            return 1
        fi
        return 0
    fi
    (cd "$w/run" && timeout "$TIMEOUT" "$w/build/prog" > "$w/out" 2> "$w/err")
    status=$?
    cat "$w/err" >> "$LOG"
    check_run "$status" "$w/err" || return 1
    if [ "$status" -ne 0 ]; then
        REASON="résultats incorrects"
        return 1
    fi
    if [ "$IGNORE_TRAILING_SPACES" = "yes" ]; then
        sed -i 's/ *$//' "$w/out"
    fi
    if [ -f "$dir/expected.txt" ] && ! cmp -s "$dir/expected.txt" "$w/out"; then
        REASON="sortie incorrecte"
        diff -u --label attendu --label obtenu "$dir/expected.txt" "$w/out" \
            | head -n 30 >> "$LOG"
        return 1
    fi
    return 0
}

ARGS=("$@")
NB_ARGS=$#
mapfile -t TASKS < <(cd "$CORR" && find . -mindepth 3 -maxdepth 3 -name config \
    | sed 's|^\./||; s|/config$||' | sort)

PROJECT=""
p_ok=0; p_ko=0; p_none=0

flush_project() {
    [ -z "$PROJECT" ] && return
    summary_projects="$summary_projects| \`$PROJECT\` | $p_ok | $p_ko | $p_none |"$'\n'
}

for id in "${TASKS[@]}"; do
    selected "$id" || continue
    project="${id%%/*}"
    if [ "$project" != "$PROJECT" ]; then
        flush_project
        echo "${BOLD}== $project ==${RESET}"
        PROJECT="$project"
        p_ok=0; p_ko=0; p_none=0
    fi
    total=$((total + 1))
    grade "$id"
    result=$?
    title=""
    # shellcheck disable=SC1090
    [ -f "$CORR/$id/config" ] && title="$(. "$CORR/$id/config"; echo "${TITLE:-}")"
    label="$id${title:+ ($title)}"
    case "$result" in
        0)
            rendus=$((rendus + 1)); valides=$((valides + 1)); p_ok=$((p_ok + 1))
            echo "  ${GREEN}✔${RESET} $label"
            summary_rows="$summary_rows| \`$id\` | $title | ✅ validée | |"$'\n'
            ;;
        1)
            rendus=$((rendus + 1)); p_ko=$((p_ko + 1))
            echo "  ${RED}✘${RESET} $label : $REASON"
            if [ -s "$LOG" ]; then
                excerpt "$LOG" | sed 's/^/      /'
            fi
            summary_rows="$summary_rows| \`$id\` | $title | ❌ échec | $REASON |"$'\n'
            if [ -s "$LOG" ]; then
                summary_details="$summary_details<details><summary><code>$id</code> $title : $REASON</summary>"$'\n\n'
                summary_details="$summary_details\`\`\`text"$'\n'"$(excerpt "$LOG")"$'\n'"\`\`\`"$'\n\n'"</details>"$'\n'
            fi
            if [ "${GITHUB_ACTIONS:-}" = "true" ]; then
                echo "::error title=$id::$REASON"
            fi
            ;;
        2)
            p_none=$((p_none + 1))
            echo "  ${GREY}· $label (non rendue)${RESET}"
            summary_rows="$summary_rows| \`$id\` | $title | ⬜ non rendue | |"$'\n'
            ;;
    esac
done
flush_project

if [ "$total" -eq 0 ]; then
    echo "Aucune tâche ne correspond à : $*" >&2
    exit 2
fi

echo
echo "${BOLD}Résultat : $valides / $total tâches validées ($rendus rendues).${RESET}"

if [ -n "${GITHUB_STEP_SUMMARY:-}" ]; then
    {
        echo "## Correction : $valides / $total tâches validées"
        echo
        echo "$rendus tâche(s) rendue(s), $((rendus - valides)) en échec."
        echo
        echo "| Projet | ✅ Validées | ❌ Échecs | ⬜ Non rendues |"
        echo "|---|---|---|---|"
        printf '%s' "$summary_projects"
        if [ -n "$summary_details" ]; then
            echo
            echo "### Détail des échecs"
            echo
            printf '%s' "$summary_details"
        fi
        echo
        echo "<details><summary>Toutes les tâches</summary>"
        echo
        echo "| Tâche | Fonction | Résultat | Détail |"
        echo "|---|---|---|---|"
        printf '%s' "$summary_rows"
        echo
        echo "</details>"
    } >> "$GITHUB_STEP_SUMMARY"
fi

[ "$rendus" -eq "$valides" ]
