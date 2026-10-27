#include "mouli.h"

int my_find_prime_sup(int nb);

int main(void)
{
    CHECK_INT(my_find_prime_sup(-10), 2);
    CHECK_INT(my_find_prime_sup(0), 2);
    CHECK_INT(my_find_prime_sup(2), 2);
    CHECK_INT(my_find_prime_sup(4), 5);
    CHECK_INT(my_find_prime_sup(7), 7);
    CHECK_INT(my_find_prime_sup(90), 97);
    CHECK_INT(my_find_prime_sup(1000000), 1000003);
    CHECK_INT(my_find_prime_sup(2147483640), 2147483647);
    return 0;
}
