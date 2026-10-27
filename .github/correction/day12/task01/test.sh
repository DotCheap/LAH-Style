. "$CORR/lib/test_lib.sh"

check_makefile cat cat || finish
check_symbols_in cat/cat "open read write close"
mkdir -p data
printf 'Bonjour\ntout le monde\n' > data/f1
printf 'sans saut de ligne' > data/f2
: > data/vide
seq 1 30000 > data/gros
head -c 50000 /dev/urandom > data/binaire

check_same "cat data/f1" "cat data/f1" "./cat/cat data/f1"
check_same "cat data/f2" "cat data/f2" "./cat/cat data/f2"
check_same "cat data/vide" "cat data/vide" "./cat/cat data/vide"
check_same "cat data/gros (≈170 ko)" "cat data/gros" "./cat/cat data/gros"
check_same "cat data/binaire" "cat data/binaire" "./cat/cat data/binaire"
check_same "cat data/f1 data/f2 data/f1" "cat data/f1 data/f2 data/f1" "./cat/cat data/f1 data/f2 data/f1"
check_same "cat sans argument (entrée standard)" "printf 'ab\ncd' | cat" "printf 'ab\ncd' | ./cat/cat"
check_same "cat fichier inexistant" "cat data/absent" "./cat/cat data/absent"
[ -s "$STDERR" ] || fail "cat data/absent doit afficher une erreur sur la sortie d'erreur"
check_same "cat data/f1 data/absent data/f2" "cat data/f1 data/absent data/f2" \
    "./cat/cat data/f1 data/absent data/f2"
./cat/cat data/absent > /dev/null 2>&1
status=$?
[ "$status" -eq 84 ] || fail "cat data/absent : code de retour $status, attendu 84"
finish
