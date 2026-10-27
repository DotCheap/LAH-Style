#!/usr/bin/env bash
#
# Liste les dossiers à corriger d'après les fichiers modifiés entre deux
# commits. Utilisé par le workflow pour ne corriger que ce qui a été poussé.
#
# Usage : .github/correction/selection.sh COMMIT_DE_DÉPART COMMIT_D_ARRIVÉE
#
# Affiche :
#   - « tout » si le correcteur lui-même a changé (ou si le commit de départ
#     est inconnu, par exemple au premier push d'une branche) ;
#   - sinon les dossiers concernés, séparés par des espaces (ex. « day03 day06 »),
#     ou rien du tout si aucun rendu ni test n'a changé.

set -u

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
CORR="$ROOT/.github/correction"
base="${1:-}"
head="${2:-HEAD}"

if [ -z "$base" ] || [ -z "${base//0/}" ] \
        || ! git -C "$ROOT" cat-file -e "$base^{commit}" 2> /dev/null; then
    echo "tout"
    exit 0
fi

projects=""
while IFS= read -r file; do
    case "$file" in
        .github/workflows/correction.yml | .github/correction/corriger.sh \
            | .github/correction/selection.sh | .github/correction/lib/*)
            echo "tout"
            exit 0
            ;;
        rendu/*/* | .github/correction/*/*)
            project="${file#rendu/}"
            project="${project#.github/correction/}"
            project="${project%%/*}"
            ;;
        *)
            continue
            ;;
    esac
    # Seuls les dossiers qui ont des tests comptent.
    [ -d "$CORR/$project" ] || continue
    case " $projects " in
        *" $project "*) ;;
        *) projects="$projects $project" ;;
    esac
done < <(git -C "$ROOT" -c core.quotePath=false diff --name-only "$base" "$head")

echo "${projects# }"
