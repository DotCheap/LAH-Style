. "$CORR/lib/test_lib.sh"

if ! tar tzf task07/task06.tgz > content.txt 2> tar.log; then
    cat tar.log
    fail "task07/task06.tgz n'est pas une archive tar compressée avec gzip"
    finish
fi
sed -i -e 's|^\./||' -e 's|^task06/||' -e 's|/$||' content.txt
for p in "Professors/Paul Karrer" "1920s/1927" \
    "Solvay Conferences on Physics/Electrons and photons/participants/N. Bohr" \
    "Solvay Conferences on Chemistry/Isotopes/chair"; do
    grep -qxF "$p" content.txt || fail "l'archive ne contient pas « $p »"
done
finish
