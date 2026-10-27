. "$CORR/lib/test_lib.sh"

FUNCTIONS="my_putchar my_isneg my_put_nbr my_swap my_putstr my_strlen my_getnbr
    my_sort_int_array my_compute_power_rec my_compute_square_root my_is_prime
    my_find_prime_sup my_strcpy my_strncpy my_revstr my_strstr my_strcmp
    my_strncmp my_strupcase my_strlowcase my_strcapitalize my_str_isalpha
    my_str_isnum my_str_islower my_str_isupper my_str_isprintable my_showstr
    my_showmem my_strcat my_strncat"

rm -f lib/my/*.o lib/my/libmy.a
if ! (cd lib/my && bash build.sh) > build.log 2>&1; then
    cat build.log
    fail "lib/my/build.sh échoue"
    finish
fi
if [ ! -f lib/my/libmy.a ]; then
    fail "build.sh ne crée pas lib/my/libmy.a"
    finish
fi
defined="$(nm --defined-only lib/my/libmy.a | awk '$2 == "T" { print $3 }')"
missing=""
for f in $FUNCTIONS; do
    printf '%s\n' $defined | grep -qxF "$f" || missing="$missing $f"
done
[ -n "$missing" ] && fail "fonction(s) absente(s) de libmy.a :$missing"
printf '%s\n' write __stack_chk_fail _GLOBAL_OFFSET_TABLE_ $defined > allowed.txt
bad="$(nm -u lib/my/libmy.a | awk 'NF >= 2 { print $2 }' | sort -u | grep -vxFf allowed.txt)"
[ -n "$bad" ] && fail "fonction(s) interdite(s) dans libmy.a : $(echo $bad)"
finish
