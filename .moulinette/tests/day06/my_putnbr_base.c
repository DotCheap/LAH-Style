#include "mouli.h"

int my_putnbr_base(int nbr, char const *base);

int main(void)
{
    CHECK_OUT(my_putnbr_base(42, "0123456789"), "42");
    CHECK_OUT(my_putnbr_base(255, "0123456789ABCDEF"), "FF");
    CHECK_OUT(my_putnbr_base(-255, "0123456789abcdef"), "-ff");
    CHECK_OUT(my_putnbr_base(5, "01"), "101");
    CHECK_OUT(my_putnbr_base(0, "01"), "0");
    CHECK_OUT(my_putnbr_base(8, "poneyvif"), "op");
    CHECK_OUT(my_putnbr_base(2147483647, "0123456789ABCDEF"), "7FFFFFFF");
    CHECK_OUT(my_putnbr_base(-2147483647 - 1, "0123456789ABCDEF"), "-80000000");
    CHECK_OUT(my_putnbr_base(-2147483647 - 1, "0123456789"), "-2147483648");
    return 0;
}
