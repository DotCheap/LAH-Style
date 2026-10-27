#include <limits.h>
#include "test.h"

int my_is_prime(int nb);

int main(void)
{
    CHECK_INT(my_is_prime(2), 1);
    CHECK_INT(my_is_prime(3), 1);
    CHECK_INT(my_is_prime(17), 1);
    CHECK_INT(my_is_prime(97), 1);
    CHECK_INT(my_is_prime(999983), 1);
    CHECK_INT(my_is_prime(0), 0);
    CHECK_INT(my_is_prime(1), 0);
    CHECK_INT(my_is_prime(4), 0);
    CHECK_INT(my_is_prime(25), 0);
    CHECK_INT(my_is_prime(1000000), 0);
    CHECK_INT(my_is_prime(-7), 0);
    CHECK_INT(my_is_prime(INT_MIN), 0);
    CHECK_INT(my_is_prime(2147483629), 1);
    CHECK_INT(my_is_prime(2147483646), 0);
    CHECK_INT(my_is_prime(INT_MAX), 1);
    TEST_END();
}
