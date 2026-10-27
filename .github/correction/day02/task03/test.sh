. "$CORR/lib/test_lib.sh"

check_script count_files.sh
script="$PWD/count_files.sh"
mkdir -p essai/sous/profond essai/vide && cd essai || finish
touch a b sous/c sous/profond/d .cache
ln -s a lien
check_output "count_files.sh" any 5 -- bash -c "bash '$script' | tr -d ' \t'"
finish
