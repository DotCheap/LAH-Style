. "$CORR/lib/test_lib.sh"

[ -x mr_clean ] || fail "mr_clean doit être exécutable par son propriétaire"
clean="$PWD/mr_clean"
mkdir -p essai/sous/dossier && cd essai || finish
touch 'a~' '#b#' 'c#' '#d' 'garder' 'e~f' 'sous/g~' 'sous/dossier/#h#' 'sous/garder~bis'
bash "$clean" > /dev/null 2>&1
for f in 'a~' '#b#' 'sous/g~' 'sous/dossier/#h#'; do
    [ -e "$f" ] && fail "mr_clean ne supprime pas « $f »"
done
for f in 'c#' '#d' 'garder' 'e~f' 'sous/garder~bis'; do
    [ -e "$f" ] || fail "mr_clean supprime « $f » à tort"
done
finish
