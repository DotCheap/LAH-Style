. "$CORR/lib/test_lib.sh"

build_epitech rush2 || finish
check_symbols_in rush2 "write"
export textes="$TEST_DIR/../textes"

# count TEXTE LETTRES... : ne garde que « lettre:nombre » des premières lignes.
count() {
    local text="$1"
    shift
    ./rush2 "$(cat "$textes/$text.txt")" "$@" | head -n "$#" | cut -d' ' -f1
}

check_output "./rush2 <t1> a" 0 "a:4" -- count t1 a
check_output "./rush2 <t1> A" 0 "A:4" -- count t1 A
check_output "./rush2 <t1> j" 0 "j:1" -- count t1 j
check_output "./rush2 <t2> a i" 0 "$(printf 'a:3\ni:4')" -- count t2 a i
check_output "./rush2 <t2> A i I i" 0 "$(printf 'A:3\ni:4\nI:4\ni:4')" -- count t2 A i I i
check_output "./rush2 <t4> z Q x" 0 "$(printf 'z:2\nQ:2\nx:1')" -- count t4 z Q x
check_output "./rush2 (sans argument)" 84 "" -- ./rush2
check_output "./rush2 texte (sans lettre)" 84 "" -- ./rush2 texte
finish
