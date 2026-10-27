. "$CORR/lib/test_lib.sh"

check_makefile . calc || finish
check_symbols_in calc "read write malloc free exit"

# calc EXPRESSION BASE OPÉRATEURS : lance ./calc sur l'expression.
calc() {
    echo "$1" | ./calc "$2" "$3" "${#1}"
}

check_output "echo '3+6' | ./calc '0123456789' '()+-*/%'" 0 '9' -- calc '3+6' '0123456789' '()+-*/%'
check_output "echo '3v6' | ./calc '0123456789' '{}vwxyz'" 0 '9' -- calc '3v6' '0123456789' '{}vwxyz'
check_output "echo '----++-6*12' | ./calc '0123456789' '()+-*/%'" 0 '-72' -- calc '----++-6*12' '0123456789' '()+-*/%'
check_output "echo '-(12-(4*32))' | ./calc '0123456789' '()+-*/%'" 0 '116' -- calc '-(12-(4*32))' '0123456789' '()+-*/%'
check_output "echo '-(e@-(;*!@))' | ./calc '0A@!;ie& ]' '()+-*/%'" 0 'ee' -- calc '-(e@-(;*!@))' '0A@!;ie& ]' '()+-*/%'
check_output "echo '-(12*(13+15/5*(6/(12+14%(30%5+(10*25)-46)+16)-20)/43)*20)*(-(12-98*42)*(16+63-50/3))' | ./calc '0123456789' '()+-*/%'" 0 '-744629760' -- calc '-(12*(13+15/5*(6/(12+14%(30%5+(10*25)-46)+16)-20)/43)*20)*(-(12-98*42)*(16+63-50/3))' '0123456789' '()+-*/%'
check_output "echo '2+3*4' | ./calc '0123456789' '()+-*/%'" 0 '14' -- calc '2+3*4' '0123456789' '()+-*/%'
check_output "echo '(2+3)*4' | ./calc '0123456789' '()+-*/%'" 0 '20' -- calc '(2+3)*4' '0123456789' '()+-*/%'
check_output "echo '-7/2' | ./calc '0123456789' '()+-*/%'" 0 '-3' -- calc '-7/2' '0123456789' '()+-*/%'
check_output "echo '7%3' | ./calc '0123456789' '()+-*/%'" 0 '1' -- calc '7%3' '0123456789' '()+-*/%'
check_output "echo '123456789123456789123456789*987654321987654321' | ./calc '0123456789' '()+-*/%'" 0 '121932631356500531469135800347203169112635269' -- calc '123456789123456789123456789*987654321987654321' '0123456789' '()+-*/%'
check_output "echo '123456789123456789123456789-987654321987654321*3' | ./calc '0123456789' '()+-*/%'" 0 '123456786160493823160493826' -- calc '123456789123456789123456789-987654321987654321*3' '0123456789' '()+-*/%'
check_output "echo '(123456789123456789123456789+1)/7' | ./calc '0123456789' '()+-*/%'" 0 '17636684160493827017636684' -- calc '(123456789123456789123456789+1)/7' '0123456789' '()+-*/%'
check_output "echo '-123456789123456789123456789%1000' | ./calc '0123456789' '()+-*/%'" 0 '-789' -- calc '-123456789123456789123456789%1000' '0123456789' '()+-*/%'
check_output "echo 'FF+1' | ./calc '0123456789ABCDEF' '()+-*/%'" 0 '100' -- calc 'FF+1' '0123456789ABCDEF' '()+-*/%'
check_output "echo '101*11' | ./calc '01' '()+-*/%'" 0 '1111' -- calc '101*11' '01' '()+-*/%'

export -f calc
# err EXPRESSION : sortie standard et d'erreur de ./calc, avec un délai.
err() {
    timeout 5 bash -c 'calc "$1" 0123456789 "()+-*/%" 2>&1' _ "$1"
}
for expr in '----++-6(12)' '3+' '(3+2' '3++*2'; do
    out="$(err "$expr")"
    status=$?
    [ "$status" -eq 84 ] || fail "echo '$expr' | ./calc : code de retour $status, attendu 84 (erreur de syntaxe)"
    printf '%s' "$out" | grep -q "syntax error" \
        || fail "echo '$expr' | ./calc doit afficher « syntax error », obtenu « $out »"
done
out="$(err '5/0')"
status=$?
[ "$status" -eq 84 ] || fail "echo '5/0' | ./calc : code de retour $status, attendu 84"
printf '%s' "$out" | grep -q "error" || fail "echo '5/0' | ./calc doit afficher « error »"
finish
