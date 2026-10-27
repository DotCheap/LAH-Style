. "$CORR/lib/test_lib.sh"

check_makefile . eval_expr || finish
check_symbols_in eval_expr "write malloc free"
check_output './eval_expr "(3+2)*5"' 0 '25' -- ./eval_expr '(3+2)*5'
check_output './eval_expr "3+2*5"' 0 '13' -- ./eval_expr '3+2*5'
check_output './eval_expr "10-2-3"' 0 '5' -- ./eval_expr '10-2-3'
check_output './eval_expr "100/7/2"' 0 '7' -- ./eval_expr '100/7/2'
check_output './eval_expr "-7/2"' 0 '-3' -- ./eval_expr '-7/2'
check_output './eval_expr "-7%3"' 0 '-1' -- ./eval_expr '-7%3'
check_output './eval_expr "2*(3+(4-1))*2"' 0 '24' -- ./eval_expr '2*(3+(4-1))*2'
check_output './eval_expr "42"' 0 '42' -- ./eval_expr '42'
check_output './eval_expr "1+2-3+4-5+6"' 0 '5' -- ./eval_expr '1+2-3+4-5+6'
check_output './eval_expr "8%3*4"' 0 '8' -- ./eval_expr '8%3*4'
check_output './eval_expr "-(4+2)*3"' 0 '-18' -- ./eval_expr '-(4+2)*3'
check_output './eval_expr "((((1))))+((2))"' 0 '3' -- ./eval_expr '((((1))))+((2))'
check_output './eval_expr "1000000/3/7*2"' 0 '95238' -- ./eval_expr '1000000/3/7*2'
check_output './eval_expr "(7-10)*(2-5)/2"' 0 '4' -- ./eval_expr '(7-10)*(2-5)/2'
check_output './eval_expr (sans argument)' 84 '' -- ./eval_expr
finish
