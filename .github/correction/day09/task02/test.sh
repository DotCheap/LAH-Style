. "$CORR/lib/test_lib.sh"

# Toutes les fonctions exposées par la libmy doivent être prototypées dans my.h.
mkdir -p objs
for f in lib/my/*.c; do
    gcc -Iinclude -c "$f" -o "objs/$(basename "${f%.c}").o" 2> /dev/null
done
if ! compgen -G "objs/*.o" > /dev/null; then
    fail "aucun fichier de lib/my/ ne compile"
    finish
fi
missing=""
for fn in $(nm --defined-only objs/*.o | awk '$2 == "T" { print $3 }' | sort -u); do
    grep -Eq "[^A-Za-z0-9_]${fn}[[:space:]]*\(" include/my.h || missing="$missing $fn"
done
[ -n "$missing" ] && fail "fonction(s) de la libmy absente(s) de include/my.h :$missing"
if ! printf '#include "my.h"\nint main(void) { return 0; }\n' \
        | gcc -Wall -Wextra -Werror -Iinclude -x c - -o /dev/null 2> my_h.log; then
    cat my_h.log
    fail "include/my.h ne compile pas"
fi
if ! printf '#include "my.h"\n#include "my.h"\nint main(void) { return 0; }\n' \
        | gcc -Iinclude -x c - -o /dev/null 2> /dev/null; then
    fail "include/my.h ne supporte pas une double inclusion (garde #ifndef manquante ?)"
fi
finish
