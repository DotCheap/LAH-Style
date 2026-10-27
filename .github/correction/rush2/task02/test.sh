. "$CORR/lib/test_lib.sh"

build_epitech rush2 || finish
export textes="$TEST_DIR/../textes"

# freq TEXTE LETTRES... : premières lignes de la sortie, pourcentages compris.
freq() {
    local text="$1"
    shift
    ./rush2 "$(cat "$textes/$text.txt")" "$@" | head -n "$#"
}

check_output "./rush2 <t3> a q e i" 0 \
    "$(printf 'a:3 (6.25%%)\nq:0 (0.00%%)\ne:4 (8.33%%)\ni:6 (12.50%%)')" -- freq t3 a q e i
check_output "./rush2 <t4> t z" 0 "$(printf 't:5 (8.33%%)\nz:2 (3.33%%)')" -- freq t4 t z
finish
