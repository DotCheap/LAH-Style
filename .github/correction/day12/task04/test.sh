. "$CORR/lib/test_lib.sh"

if ! grep -q '^tests_run[[:space:]]*:' grep/Makefile; then
    fail "pas de règle tests_run dans grep/Makefile"
    finish
fi
if ! make -C cat tests_run > tests.log 2>&1; then
    tail -n 30 tests.log
    fail "make tests_run échoue dans grep/"
fi
finish
