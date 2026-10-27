. "$CORR/lib/test_lib.sh"

check_script find_sh.sh
script="$PWD/find_sh.sh"
mkdir -p essai/sous/profond && cd essai || finish
touch a.sh sous/b.sh sous/profond/c.sh d.txt e.sh.bak f.shx
# Avec ou sans chemin, avec ou sans l'extension .sh : seuls les noms comptent.
check_output "find_sh.sh" any "$(printf '%s\n' a b c)" \
    -- bash -c "bash '$script' | sed -e 's|.*/||' -e 's|\.sh\$||' | LC_ALL=C sort"
finish
