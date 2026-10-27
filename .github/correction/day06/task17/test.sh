. "$CORR/lib/test_lib.sh"

check_unit_tests tests/test_my_str_isalpha.c my_str_isalpha.c 100 80
check_unit_tests tests/test_my_str_islower.c my_str_islower.c 100 80
check_unit_tests tests/test_my_str_isprintable.c my_str_isprintable.c 100 80

finish
