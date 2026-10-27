. "$CORR/lib/test_lib.sh"

check_script skip.sh
check_output "printf 'l1\\nl2\\nl3\\nl4\\nl5\\n' | ./skip.sh" any "$(printf 'l1\nl3\nl5')" \
    -- bash -c "printf 'l1\nl2\nl3\nl4\nl5\n' | ./skip.sh"
check_output "printf 'seule\\n' | ./skip.sh" any "seule" -- bash -c "printf 'seule\n' | ./skip.sh"
finish
