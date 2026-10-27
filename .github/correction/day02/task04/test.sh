. "$CORR/lib/test_lib.sh"

check_script gotta_catch_them_all.sh
make_passwd passwd
check_output "cat passwd | ./gotta_catch_them_all.sh martin" any 2 \
    -- bash -c "./gotta_catch_them_all.sh martin < passwd | tr -d ' \t'"
check_output "cat passwd | ./gotta_catch_them_all.sh dup" any 2 \
    -- bash -c "./gotta_catch_them_all.sh dup < passwd | tr -d ' \t'"
check_output "cat passwd | ./gotta_catch_them_all.sh zzz" any 0 \
    -- bash -c "./gotta_catch_them_all.sh zzz < passwd | tr -d ' \t'"
finish
