. "$CORR/lib/test_lib.sh"

check_unit_tests tests/test_my_strncpy.c my_strncpy.c 60 40
check_unit_tests tests/test_my_revstr.c my_revstr.c 60 40

finish
