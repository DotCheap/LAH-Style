. "$CORR/lib/test_lib.sh"

[ -x push_that.sh ] || fail "push_that.sh doit être exécutable"
head -n 1 push_that.sh | grep -q '^#!.*bash' || fail "push_that.sh doit commencer par un shebang bash"
script="$PWD/push_that.sh"
export GIT_AUTHOR_NAME=test GIT_AUTHOR_EMAIL=test@example.com
export GIT_COMMITTER_NAME=test GIT_COMMITTER_EMAIL=test@example.com
git init -q --bare remote.git
git clone -q remote.git clone 2> /dev/null
cd clone || finish
git checkout -q -b main
echo bonjour > fichier.txt
mkdir -p dossier && echo salut > dossier/autre.txt
timeout 20 bash "$script" "mon message" > ../push.log 2>&1 < /dev/null
log="$(git --git-dir=../remote.git log --all --format=%s 2> /dev/null)"
if [ -z "$log" ]; then
    cat ../push.log
    fail "aucun commit n'a été poussé sur le dépôt distant"
else
    printf '%s\n' "$log" | grep -qx "mon message" \
        || fail "le commit poussé n'a pas pour message « mon message » (obtenu : $log)"
    files="$(git --git-dir=../remote.git ls-tree -r --name-only --all 2> /dev/null; \
        git --git-dir=../remote.git ls-tree -r --name-only "$(git --git-dir=../remote.git rev-parse --all | head -n 1)")"
    printf '%s\n' "$files" | grep -qx "dossier/autre.txt" \
        || fail "tous les fichiers du dossier n'ont pas été ajoutés"
fi
finish
