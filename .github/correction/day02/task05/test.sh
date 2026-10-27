. "$CORR/lib/test_lib.sh"

check_script looneytised.sh
make_passwd passwd
want="$(sed -n -e 's/theo1/Wile E. Coyote/g' -e 's/steven1/Daffy Duck/g' \
    -e 's/arnaud1/Porky Pig/g' -e 's/pierre-jean/Marvin the Martian/g' \
    -e '/Wile E. Coyote\|Daffy Duck\|Porky Pig\|Marvin the Martian/p' passwd)"
check_output "cat passwd | ./looneytised.sh" any "$want" -- bash -c "./looneytised.sh < passwd"
finish
