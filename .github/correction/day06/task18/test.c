#include <limits.h>
#include "test.h"

int my_putnbr_base(int nbr, char const *base);

int main(void)
{
    my_putnbr_base(255, "0123456789ABCDEF");
    test_nl();
    my_putnbr_base(-255, "0123456789ABCDEF");
    test_nl();
    my_putnbr_base(0, "01");
    test_nl();
    my_putnbr_base(5, "01");
    test_nl();
    my_putnbr_base(42, "0123456789");
    test_nl();
    my_putnbr_base(42, "poneyvif");
    test_nl();
    my_putnbr_base(INT_MAX, "0123456789abcdef");
    test_nl();
    my_putnbr_base(INT_MIN, "0123456789");
    test_nl();
    my_putnbr_base(INT_MIN, "01");
    test_nl();
    TEST_END();
}
