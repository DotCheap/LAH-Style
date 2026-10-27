. "$CORR/lib/test_lib.sh"

ln -sf "$PROG" a.out
check_output "./a.out test \"This is a test\" retest" 0 "./a.out
This is a test
retest
test" -- ./a.out test "This is a test" retest
check_output "./a.out (sans argument)" 0 "./a.out" -- ./a.out
finish
