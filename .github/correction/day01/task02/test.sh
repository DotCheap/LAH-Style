. "$CORR/lib/test_lib.sh"

printf 'Z\n' > want.txt
cmp -s want.txt task02/z || fail "cat -e task02/z doit afficher « Z\$ », obtenu « $(cat -e task02/z) »"
finish
