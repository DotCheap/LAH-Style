. "$CORR/lib/test_lib.sh"

cd task01 || finish
if [ ! -f test01 ] || [ -L test01 ]; then
    fail "task01/test01 doit être un fichier"
elif [ -s test01 ]; then
    fail "task01/test01 doit être vide"
fi
if [ ! -f test02 ] || [ -L test02 ]; then
    fail "task01/test02 doit être un fichier"
else
    content="$(cat test02)"
    [ "$content" = "If you don't struggle, you don't improve." ] \
        || fail "task01/test02 contient « $content »"
    [ -x test02 ] || fail "task01/test02 doit être exécutable par tous (git ne garde que le bit x)"
fi
if [ ! -L test03 ]; then
    fail "task01/test03 doit être un lien symbolique"
elif [ "$(readlink test03)" != "test02" ]; then
    fail "task01/test03 pointe vers « $(readlink test03) », attendu « test02 »"
fi
finish
