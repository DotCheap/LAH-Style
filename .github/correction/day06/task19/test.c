#include <limits.h>
#include "test.h"

int my_getnbr_base(char const *str, char const *base);

int main(void)
{
    CHECK_INT(my_getnbr_base("FF", "0123456789ABCDEF"), 255);
    CHECK_INT(my_getnbr_base("-FF", "0123456789ABCDEF"), -255);
    CHECK_INT(my_getnbr_base("101", "01"), 5);
    CHECK_INT(my_getnbr_base("--+-101", "01"), -5);
    CHECK_INT(my_getnbr_base("+-+-42", "0123456789"), 42);
    CHECK_INT(my_getnbr_base("0", "01"), 0);
    CHECK_INT(my_getnbr_base("vn", "poneyvif"), 42);
    CHECK_INT(my_getnbr_base("7fffffff", "0123456789abcdef"), INT_MAX);
    CHECK_INT(my_getnbr_base("-80000000", "0123456789abcdef"), INT_MIN);
    CHECK_INT(my_getnbr_base("80000000", "0123456789abcdef"), 0);
    CHECK_INT(my_getnbr_base("123456789123456789", "0123456789"), 0);
    TEST_END();
}
