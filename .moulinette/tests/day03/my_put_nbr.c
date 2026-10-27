#include <limits.h>
#include "mouli.h"

int my_put_nbr(int nb);

int main(void)
{
    CHECK_OUT(my_put_nbr(42), "42");
    CHECK_OUT(my_put_nbr(0), "0");
    CHECK_OUT(my_put_nbr(7), "7");
    CHECK_OUT(my_put_nbr(-7), "-7");
    CHECK_OUT(my_put_nbr(1000000), "1000000");
    CHECK_OUT(my_put_nbr(-2147483647), "-2147483647");
    CHECK_OUT(my_put_nbr(INT_MAX), "2147483647");
    CHECK_OUT(my_put_nbr(INT_MIN), "-2147483648");
    return 0;
}
