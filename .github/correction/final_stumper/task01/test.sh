. "$CORR/lib/test_lib.sh"

check_makefile . rush3 || finish
check_symbols_in rush3 "read write malloc free"
# Chaque inputs/NN_nom.in est envoyé à ./rush3, qui doit afficher NN_nom.out.
for input in "$TEST_DIR"/inputs/*.in; do
    name="$(basename "${input%.in}")"
    check_output "./rush3 < $name.in" any "$(cat "${input%.in}.out")" -- bash -c "./rush3 < '$input'"
done
finish
