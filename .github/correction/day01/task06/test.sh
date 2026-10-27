. "$CORR/lib/test_lib.sh"

# Liste « type chemin [-> cible] » de task06, sans les fichiers cachés (.gitkeep).
list_tree() {
    find "$1" -mindepth 1 -name '.*' -prune -o -printf '%y %p\t%l\n' \
        | sed -e 's|/*$||' -e 's|\t\(.*[^/]\)/*$| -> \1|' -e 's|\t$||' | LC_ALL=C sort
}
list_tree task06 > got.txt
LC_ALL=C sort "$TEST_DIR/expected.txt" > want.txt
if ! diff want.txt got.txt > diff.txt; then
    fail "l'arborescence de task06 ne correspond pas au sujet"
    grep '^<' diff.txt | head -n 10 | sed 's/^< /  manquant : /'
    grep '^>' diff.txt | head -n 10 | sed 's/^> /  en trop  : /'
    echo "  (git ne garde pas les dossiers vides : ajoutez-y un fichier caché comme .gitkeep)"
fi
broken="$(find task06 -xtype l)"
[ -n "$broken" ] && fail "lien(s) cassé(s) : $(echo $broken)"
finish
