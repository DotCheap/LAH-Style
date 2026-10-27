. "$CORR/lib/test_lib.sh"

check_script how_many_are_we.sh
printf '%s\n' 'abaab_a;tek3;PAR' 'bob_b;tek2;NCY' 'carl_c;tek3;PAR' 'dan_d;tek1;LYN' \
    'eve_e;tek2;NCY' 'fred_f;tek3;PAR' > students.csv
for city in ncy par lyn; do
    want="$(grep -ci ";$city\$" students.csv)"
    check_output "cat students.csv | ./how_many_are_we.sh $city" any "$want" \
        -- bash -c "./how_many_are_we.sh $city < students.csv | tr -d ' \t'"
done
check_output "cat students.csv | ./how_many_are_we.sh (sans argument)" any 6 \
    -- bash -c "./how_many_are_we.sh < students.csv | tr -d ' \t'"
finish
