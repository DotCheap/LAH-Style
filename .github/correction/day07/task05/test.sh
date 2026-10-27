. "$CORR/lib/test_lib.sh"

ln -sf "$PROG" a.out
check_output "./a.out test \"This is a test\" retest" 0 "retest
This is a test
test
./a.out" -- ./a.out test "This is a test" retest
check_output "./a.out (sans argument)" 0 "./a.out" -- ./a.out
finish
