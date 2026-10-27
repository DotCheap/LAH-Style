. "$CORR/lib/test_lib.sh"

[ -x task03/midLS ] || fail "task03/midLS doit être exécutable"
midls="$PWD/task03/midLS"
mkdir -p essai/zeta essai/alpha essai/.cache && cd essai || finish
touch beta gamma .cache_file delta
check_output "midLS" any "alpha/, beta, delta, gamma, zeta/" -- bash "$midls"
finish
