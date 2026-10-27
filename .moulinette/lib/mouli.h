/*
** Moulinette de la piscine - mini framework de tests unitaires.
**
** Chaque CASE s'execute dans un processus fils : un segfault ou une boucle
** infinie dans le code teste n'empeche pas les autres cas de s'executer.
*/

#ifndef MOULI_H_
    #define MOULI_H_

int mouli_fork(char const *desc);
int mouli_done(void);
void mouli_capture(void);
char const *mouli_stdout(void);
char const *mouli_stderr(void);
void mouli_fail(char const *fmt, ...);
void mouli_expect_int(char const *what, long long got, long long expected);
void mouli_expect_sign(char const *what, long long got, long long expected);
void mouli_expect_ptr(char const *what, void const *got, void const *expected);
void mouli_expect_offset(char const *what, char const *got, char const *base,
    char const *expected);
void mouli_expect_str(char const *what, char const *got, char const *expected);
void mouli_expect_true(char const *what, int cond);
void mouli_expect_out(char const *expected);
void mouli_expect_out_nl(char const *expected);
void mouli_expect_out_ws(char const *expected);
void mouli_expect_err(char const *expected);
char *mouli_strdup(char const *str);

    #define CASE(desc) \
    for (int mouli_c_ = mouli_fork(desc); mouli_c_; mouli_c_ = mouli_done())

    #define EXPECT(cond) mouli_expect_true(#cond, (cond))
    #define EXPECT_INT(got, exp) \
    mouli_expect_int(#got, (long long)(got), (long long)(exp))
    #define EXPECT_SIGN(got, exp) \
    mouli_expect_sign(#got, (long long)(got), (long long)(exp))
    #define EXPECT_PTR(got, exp) mouli_expect_ptr(#got, (got), (exp))
    #define EXPECT_STR(got, exp) mouli_expect_str(#got, (got), (exp))

    #define CHECK_INT(expr, exp) CASE(#expr) EXPECT_INT(expr, exp)
    #define CHECK_SIGN(expr, exp) CASE(#expr) EXPECT_SIGN(expr, exp)
    #define CHECK_STR(expr, exp) CASE(#expr) EXPECT_STR(expr, exp)
    #define CHECK_OUT(stmt, exp) \
    CASE(#stmt) { mouli_capture(); stmt; mouli_expect_out(exp); }
    #define CHECK_OUT_NL(stmt, exp) \
    CASE(#stmt) { mouli_capture(); stmt; mouli_expect_out_nl(exp); }

#endif
