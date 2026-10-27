. "$CORR/lib/test_lib.sh"

check_makefile do_op do-op || finish
check_symbols_in do_op/do-op "write malloc free"
cd do_op || finish
check_output "./do-op (sans argument)" 84 "" -- ./do-op
check_output "./do-op 1 +" 84 "" -- ./do-op 1 +
check_output "./do-op 1 + 1" 0 "2" -- ./do-op 1 + 1
check_output "./do-op 42friends - ---20toto12" 0 "62" -- ./do-op 42friends - ---20toto12
check_output "./do-op 6 '*' 7" 0 "42" -- ./do-op 6 '*' 7
check_output "./do-op 7 / 2" 0 "3" -- ./do-op 7 / 2
check_output "./do-op -10 / 3" 0 "-3" -- ./do-op -10 / 3
check_output "./do-op 7 % 3" 0 "1" -- ./do-op 7 % 3
check_output "./do-op 1 p 1" 84 "0" -- ./do-op 1 p 1
check_output "./do-op 1 +toto 1" 0 "2" -- ./do-op 1 +toto 1
check_output "./do-op 1 + toto3" 0 "1" -- ./do-op 1 + toto3
check_output "./do-op toto3 + 4" 0 "4" -- ./do-op toto3 + 4
check_output "./do-op foo plus bar" 84 "0" -- ./do-op foo plus bar
check_output "./do-op 25 / 0" 84 "" -- ./do-op 25 / 0
grep -q "Stop: division by zero" "$STDERR" \
    || fail "./do-op 25 / 0 doit afficher « Stop: division by zero » sur la sortie d'erreur"
check_output "./do-op 25 % 0" 84 "" -- ./do-op 25 % 0
grep -q "Stop: modulo by zero" "$STDERR" \
    || fail "./do-op 25 % 0 doit afficher « Stop: modulo by zero » sur la sortie d'erreur"
finish
