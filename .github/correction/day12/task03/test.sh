. "$CORR/lib/test_lib.sh"

check_makefile grep grep || finish
check_symbols_in grep/grep "open read write close malloc free"
mkdir -p data
printf 'root:x:0:0\nlooneytunes:x:1000:100:looney tunes\nbin:x:2:2\nlooney\n' > data/passwd
printf 'http 80/tcp\nhttps 443/tcp\nssh 22/tcp\n' > data/services
seq 1 30000 > data/gros

check_same "grep looney data/passwd" "grep -F -- looney data/passwd" "./grep/grep looney data/passwd"
check_same "grep http data/services" "grep -F -- http data/services" "./grep/grep http data/services"
check_same "grep 'x:2' data/passwd" "grep -F -- 'x:2' data/passwd" "./grep/grep 'x:2' data/passwd"
check_same "grep 2999 data/gros" "grep -F -- 2999 data/gros" "./grep/grep 2999 data/gros"
check_same "grep http data/services data/passwd" \
    "grep -F -- http data/services data/passwd" "./grep/grep http data/services data/passwd"
check_same "grep tcp (entrée standard)" "grep -F -- tcp < data/services" "./grep/grep tcp < data/services"
out="$(./grep/grep absent data/passwd 2> /dev/null)"
[ -z "$out" ] || fail "grep absent data/passwd ne doit rien afficher"
./grep/grep http data/inexistant > /dev/null 2> "$STDERR"
status=$?
grep -q "No such file or directory" "$STDERR" \
    || fail "grep http data/inexistant doit afficher « No such file or directory » sur la sortie d'erreur"
[ "$status" -eq 84 ] || fail "grep http data/inexistant : code de retour $status, attendu 84"
finish
