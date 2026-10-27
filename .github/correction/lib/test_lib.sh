# shellcheck shell=bash
# Fonctions communes aux scripts test.sh (modes program et script).
# Chaque échec affiche une ligne « ÉCHEC : ... » ; finish renvoie le bilan.

FAILED=0
# Fichiers temporaires des tests, hors du dossier courant. STDERR contient la
# sortie d'erreur de la dernière commande lancée par check_output/check_same.
TEST_TMP="$(mktemp -d)"
STDERR="$TEST_TMP/stderr.txt"
trap 'rm -rf "$TEST_TMP"' EXIT

fail() {
    echo "ÉCHEC : $*"
    FAILED=1
}

# check_output DESCRIPTION STATUT_ATTENDU SORTIE_ATTENDUE -- COMMANDE...
# Lance la commande, compare sa sortie standard (sans tenir compte des sauts
# de ligne finaux) et son code de retour. STATUT_ATTENDU peut valoir « any ».
check_output() {
    local desc="$1" want_status="$2" want_out="$3" got_out status
    shift 4
    # Une fonction shell est exportée pour être lancée sous timeout (les
    # variables qu'elle utilise doivent aussi être exportées).
    # shellcheck disable=SC2163
    declare -F "$1" > /dev/null && export -f "$1"
    got_out="$(timeout 5 bash -c '"$@"' _ "$@" 2> "$STDERR"; echo "~$?")"
    if [ "${got_out##*~}" = "124" ]; then
        fail "$desc : trop lent (plus de 5 s) ou boucle infinie"
        return 1
    fi
    status="${got_out##*~}"
    got_out="${got_out%~*}"
    got_out="$(printf '%s' "$got_out")"
    while [ "${got_out%$'\n'}" != "$got_out" ]; do got_out="${got_out%$'\n'}"; done
    while [ "${want_out%$'\n'}" != "$want_out" ]; do want_out="${want_out%$'\n'}"; done
    if [ "$got_out" != "$want_out" ]; then
        fail "$desc : sortie incorrecte"
        echo "  attendu :"
        printf '%s\n' "$want_out" | head -n 10 | sed 's/^/    | /'
        echo "  obtenu :"
        printf '%s\n' "$got_out" | head -n 10 | sed 's/^/    | /'
        return 1
    fi
    if [ "$want_status" != "any" ] && [ "$status" != "$want_status" ]; then
        fail "$desc : code de retour $status, attendu $want_status"
        return 1
    fi
    cat "$STDERR" >&2
}

# check_symbols_in BINAIRE "fonctions autorisées"
# Vérifie les fonctions de la libc importées par un binaire.
check_symbols_in() {
    local bin="$1" allowed="$2" sym bad=""
    local startup="__libc_start_main __cxa_finalize __gmon_start__ _ITM_registerTMCloneTable
        _ITM_deregisterTMCloneTable __stack_chk_fail __errno_location"
    for sym in $(nm -D --undefined-only "$bin" | awk '{ print $2 }' | sed 's/@.*//'); do
        printf '%s\n' $allowed $startup | grep -qxF "$sym" && continue
        bad="$bad $sym"
    done
    if [ -n "$bad" ]; then
        fail "fonction(s) interdite(s) :$bad (autorisées : $allowed)"
        return 1
    fi
}

# check_makefile DOSSIER BINAIRE : make, binaire produit, pas de relink, fclean.
check_makefile() {
    local dir="$1" bin="$2" before after
    if [ ! -f "$dir/Makefile" ]; then
        fail "pas de Makefile dans $dir"
        return 1
    fi
    if ! make -C "$dir" > "$TEST_TMP/make.log" 2>&1; then
        cat "$TEST_TMP/make.log"
        fail "make échoue dans $dir"
        return 1
    fi
    if [ ! -x "$dir/$bin" ]; then
        fail "make ne produit pas le binaire $bin"
        return 1
    fi
    before="$(stat -c %Y "$dir/$bin")"
    sleep 1
    make -C "$dir" > "$TEST_TMP/make.log" 2>&1
    after="$(stat -c %Y "$dir/$bin")"
    # Un relink est une faute, mais on teste quand même le programme.
    [ "$before" != "$after" ] && fail "le Makefile relinke alors que rien n'a changé"
    return 0
}

finish() {
    exit "$FAILED"
}

# check_unit_tests TEST.c FONCTION.c LIGNES_MIN BRANCHES_MIN
# Compile les tests Criterion avec la fonction, les lance, puis vérifie la
# couverture de FONCTION.c (lignes exécutées, branches prises au moins une fois).
check_unit_tests() {
    local test="$1" func="$2" lmin="$3" bmin="$4" name out lines branches
    name="$(basename "${func%.c}")"
    if [ ! -f "$test" ]; then
        fail "$test manquant"
        return 1
    fi
    if [ ! -f "$func" ]; then
        fail "$func manquant (fonction testée par $test)"
        return 1
    fi
    if [ ! -d /usr/include/criterion ] && [ ! -d /usr/local/include/criterion ]; then
        fail "Criterion n'est pas installé (voir install_criterion.sh)"
        return 1
    fi
    out="$PWD/cov_$name"
    mkdir -p "$out/sib"
    # Les autres .c du dossier restent disponibles, comme avec « gcc *.c ».
    local f
    for f in *.c; do
        [ "$f" = "$(basename "$func")" ] && continue
        gcc -Iinclude -c "$f" -o "$out/sib/${f%.c}.o" > /dev/null 2>&1 \
            || rm -f "$out/sib/${f%.c}.o"
    done
    rm -f "$out/sib/libsib.a"
    if compgen -G "$out/sib/*.o" > /dev/null; then
        ar rcs "$out/sib/libsib.a" "$out"/sib/*.o
    else
        ar rcs "$out/sib/libsib.a"
    fi
    if ! gcc --coverage -Iinclude -c "$func" -o "$out/$name.o" > "$out/build.log" 2>&1 \
            || ! gcc -Iinclude -c "$test" -o "$out/test.o" >> "$out/build.log" 2>&1 \
            || ! gcc --coverage "$out/$name.o" "$out/test.o" -o "$out/unit_tests" \
                -L"$out/sib" -lsib -lcriterion >> "$out/build.log" 2>&1; then
        cat "$out/build.log"
        fail "$test ne compile pas"
        return 1
    fi
    if ! (cd "$out" && timeout 10 ./unit_tests > run.log 2>&1); then
        cat "$out/run.log"
        fail "les tests de $test ne passent pas"
        return 1
    fi
    (cd "$out" && gcov -b -o . "$name.o" > gcov.log 2>&1)
    lines="$(awk -F'[:%]' '/^Lines executed/ { print int($2); exit }' "$out/gcov.log")"
    branches="$(awk -F'[:%]' '/^Taken at least once/ { print int($2); exit }' "$out/gcov.log")"
    lines="${lines:-0}"
    grep -q '^No branches' "$out/gcov.log" && branches=100
    branches="${branches:-0}"
    echo "$name : lignes $lines %, branches $branches %"
    if [ "$lines" -lt "$lmin" ]; then
        fail "$name : couverture des lignes $lines %, minimum $lmin %"
        return 1
    fi
    if [ "$branches" -lt "$bmin" ]; then
        fail "$name : couverture des branches $branches %, minimum $bmin %"
        return 1
    fi
}

# check_same DESCRIPTION "COMMANDE DE RÉFÉRENCE" "COMMANDE TESTÉE"
# Compare octet par octet les sorties standard des deux commandes (lancées
# avec bash -c), ainsi que leur réussite ou leur échec.
check_same() {
    local desc="$1" want_status got_status
    bash -c "$2" > "$TEST_TMP/want.out" 2> /dev/null
    want_status=$?
    timeout 5 bash -c "$3" > "$TEST_TMP/got.out" 2> "$STDERR"
    got_status=$?
    if ! cmp -s "$TEST_TMP/want.out" "$TEST_TMP/got.out"; then
        fail "$desc : sortie différente de « $2 »"
        if cmp "$TEST_TMP/want.out" "$TEST_TMP/got.out" 2>&1 | grep -q EOF; then
            echo "  une des deux sorties est plus courte que l'autre"
        else
            echo "  premier octet différent : $(cmp "$TEST_TMP/want.out" "$TEST_TMP/got.out" | awk '{ print $5 }' | tr -d ,)"
        fi
        echo "  attendu ($(wc -c < "$TEST_TMP/want.out") octets) :"
        head -n 5 "$TEST_TMP/want.out" | cut -c1-100 | cat -v | sed 's/^/    | /'
        echo "  obtenu ($(wc -c < "$TEST_TMP/got.out") octets) :"
        head -n 5 "$TEST_TMP/got.out" | cut -c1-100 | cat -v | sed 's/^/    | /'
        return 1
    fi
    if [ "$want_status" -eq 0 ] && [ "$got_status" -ne 0 ]; then
        fail "$desc : code de retour $got_status, attendu 0"
        return 1
    fi
    if [ "$want_status" -ne 0 ] && [ "$got_status" -eq 0 ]; then
        fail "$desc : code de retour 0 alors qu'il y a une erreur"
        return 1
    fi
}

# check_script FICHIER : exécutable et commençant par un shebang.
check_script() {
    [ -x "$1" ] || fail "$1 doit être exécutable (chmod +x)"
    head -n 1 "$1" | grep -q '^#!' || fail "$1 doit commencer par un shebang (#!/bin/bash)"
}

# Données d'exemple au format passwd, écrites dans le fichier $1.
make_passwd() {
    cat > "$1" <<'PASSWD'
martin_a:x:1001:100:alice martin:/home/martin_a:/bin/bash
theo1:x:1002:100:theo dupont:/home/theo1:/bin/bash
dupont_c:x:1003:100:claire dupont:/home/dupont_c:/bin/bash
martinez_b:x:1004:100:bob martinez:/home/martinez_b:/bin/bash
steven1:x:1005:100:steven leroy:/home/steven1:/bin/bash
durand_d:x:1006:100:martin durand:/home/durand_d:/bin/bash
arnaud1:x:1007:100:arnaud petit:/home/arnaud1:/bin/bash
lemartin_e:x:1008:100:eve lemartin:/home/lemartin_e:/bin/bash
pierre-jean:x:1009:100:pierre-jean roux:/home/pierre-jean:/bin/bash
zoe_f:x:1010:100:zoe faure:/home/zoe_f:/bin/bash
abel_g:x:1011:100:abel girard:/home/abel_g:/bin/bash
yann_h:x:1012:100:yann henry:/home/yann_h:/bin/bash
PASSWD
    mkdir -p Day02
    cp "$1" Day02/passwd
}

# build_epitech BINAIRE : construit le programme comme l'autograder Epitech
# (libmy depuis lib/my/*.c, puis gcc *.c -I./include -lmy). Échoue sinon.
build_epitech() {
    local bin="$1" f lib=""
    if compgen -G "lib/my/*.c" > /dev/null; then
        mkdir -p "$TEST_TMP/lib"
        for f in lib/my/*.c; do
            gcc -Iinclude -Ilib/my -c "$f" -o "$TEST_TMP/lib/$(basename "${f%.c}").o" \
                >> "$TEST_TMP/build.log" 2>&1 || break
        done
        ar rcs "$TEST_TMP/lib/libmy.a" "$TEST_TMP"/lib/*.o 2>> "$TEST_TMP/build.log"
        lib="-L$TEST_TMP/lib -lmy"
    fi
    # shellcheck disable=SC2086
    if ! gcc -o "$bin" *.c -Iinclude $lib >> "$TEST_TMP/build.log" 2>&1; then
        grep -v 'warning:' "$TEST_TMP/build.log" | head -n 20
        fail "le programme ne compile pas (gcc -o $bin *.c -I./include -L./lib/my -lmy)"
        return 1
    fi
}
