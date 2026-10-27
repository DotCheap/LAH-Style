. "$CORR/lib/test_lib.sh"

# Le Makefile doit tout faire seul : on retire build.sh et les produits.
rm -f lib/my/build.sh lib/libmy.a lib/my/libmy.a lib/my/*.o include/my.h
if ! make -C lib/my > make.log 2>&1; then
    cat make.log
    fail "make échoue dans lib/my/"
    finish
fi
[ -f lib/libmy.a ] || fail "le Makefile ne copie pas libmy.a dans lib/"
[ -f include/my.h ] || fail "le Makefile ne copie pas my.h dans include/"
if [ -f lib/libmy.a ] && [ -z "$(nm --defined-only lib/libmy.a 2> /dev/null | awk '$2 == "T"')" ]; then
    fail "lib/libmy.a ne contient aucune fonction"
fi
if ! make -C lib/my clean > make.log 2>&1; then
    cat make.log
    fail "make clean échoue"
fi
compgen -G "lib/my/*.o" > /dev/null && fail "make clean ne supprime pas les .o"
finish
