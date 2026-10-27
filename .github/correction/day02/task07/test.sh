. "$CORR/lib/test_lib.sh"

check_script r_tacpy.sh
make_passwd passwd
export LC_ALL=C
for range in "1 3" "2 5" "1 6"; do
    set -- $range
    want="$(sed -n 'n;p' passwd | cut -d: -f1 | rev | sort -r | sed -n "$1,$2p" \
        | paste -sd, - | sed -e 's/,/, /g' -e 's/$/./')"
    check_output "MY_LINE1=$1 MY_LINE2=$2 ./r_tacpy.sh" any "$want" \
        -- env MY_LINE1="$1" MY_LINE2="$2" bash -c "cat passwd | ./r_tacpy.sh"
done
finish
