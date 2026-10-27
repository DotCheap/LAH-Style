#include <limits.h>
#include "test.h"

int my_getnbr(char const *str);

int main(void)
{
    CHECK_INT(my_getnbr("42"), 42);
    CHECK_INT(my_getnbr("-42"), -42);
    CHECK_INT(my_getnbr("0"), 0);
    CHECK_INT(my_getnbr("0042"), 42);
    CHECK_INT(my_getnbr("+12"), 12);
    CHECK_INT(my_getnbr("+---+--++---+---+---+-42"), -42);
    CHECK_INT(my_getnbr("--42"), 42);
    CHECK_INT(my_getnbr("42a43"), 42);
    CHECK_INT(my_getnbr("-7-8"), -7);
    CHECK_INT(my_getnbr("abc"), 0);
    CHECK_INT(my_getnbr(""), 0);
    CHECK_INT(my_getnbr("2147483647"), INT_MAX);
    CHECK_INT(my_getnbr("-2147483648"), INT_MIN);
    CHECK_INT(my_getnbr("2147483648"), 0);
    CHECK_INT(my_getnbr("-2147483649"), 0);
    CHECK_INT(my_getnbr("11000000000000000000000000042"), 0);
    CHECK_INT(my_getnbr("-1000000000000000000000042"), 0);
    TEST_END();
}
