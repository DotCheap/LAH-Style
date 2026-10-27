#include "mouli.h"

int my_getnbr_base(char const *str, char const *base);

int main(void)
{
    CHECK_INT(my_getnbr_base("42", "0123456789"), 42);
    CHECK_INT(my_getnbr_base("FF", "0123456789ABCDEF"), 255);
    CHECK_INT(my_getnbr_base("-ff", "0123456789abcdef"), -255);
    CHECK_INT(my_getnbr_base("101", "01"), 5);
    CHECK_INT(my_getnbr_base("--+-101", "01"), -5);
    CHECK_INT(my_getnbr_base("+-+-+10", "0123456789"), 10);
    CHECK_INT(my_getnbr_base("op", "poneyvif"), 8);
    CHECK_INT(my_getnbr_base("0", "01"), 0);
    CHECK_INT(my_getnbr_base("7FFFFFFF", "0123456789ABCDEF"), 2147483647);
    CHECK_INT(my_getnbr_base("-80000000", "0123456789ABCDEF"), -2147483648LL);
    return 0;
}
