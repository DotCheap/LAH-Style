. "$CORR/lib/test_lib.sh"

build_epitech rush2 || finish
textes="$TEST_DIR/../textes"

# Dernière ligne de la sortie pour un long texte typique de chaque langue.
for lang in English French German Spanish; do
    file="$textes/$(echo "$lang" | tr 'A-Z' 'a-z').txt"
    check_output "./rush2 <texte en $lang> a e" 0 "=> $lang" \
        -- bash -c "./rush2 \"\$(cat '$file')\" a e | tail -n 1"
done
finish
