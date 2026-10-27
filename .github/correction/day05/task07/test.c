#include <limits.h>
#include "test.h"

int my_find_prime_sup(int nb);

int main(void)
{
    CHECK_INT(my_find_prime_sup(2), 2);
    CHECK_INT(my_find_prime_sup(3), 3);
    CHECK_INT(my_find_prime_sup(4), 5);
    CHECK_INT(my_find_prime_sup(14), 17);
    CHECK_INT(my_find_prime_sup(0), 2);
    CHECK_INT(my_find_prime_sup(-42), 2);
    CHECK_INT(my_find_prime_sup(INT_MIN), 2);
    CHECK_INT(my_find_prime_sup(1000000), 1000003);
    CHECK_INT(my_find_prime_sup(2147483588), 2147483629);
    CHECK_INT(my_find_prime_sup(2147483630), INT_MAX);
    TEST_END();
}
