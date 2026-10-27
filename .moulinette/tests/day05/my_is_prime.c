#include "mouli.h"

int my_is_prime(int nb);

int main(void)
{
    CHECK_INT(my_is_prime(0), 0);
    CHECK_INT(my_is_prime(1), 0);
    CHECK_INT(my_is_prime(2), 1);
    CHECK_INT(my_is_prime(3), 1);
    CHECK_INT(my_is_prime(4), 0);
    CHECK_INT(my_is_prime(17), 1);
    CHECK_INT(my_is_prime(91), 0);
    CHECK_INT(my_is_prime(-7), 0);
    CHECK_INT(my_is_prime(1000003), 1);
    CHECK_INT(my_is_prime(2147483646), 0);
    CHECK_INT(my_is_prime(2147483647), 1);
    return 0;
}
