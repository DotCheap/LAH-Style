. "$CORR/lib/test_lib.sh"

check_unit_tests tests/test_my_strstr.c my_strstr.c 80 60
check_unit_tests tests/test_my_strncmp.c my_strncmp.c 80 60
check_unit_tests tests/test_my_strcapitalize.c my_strcapitalize.c 80 60

finish
