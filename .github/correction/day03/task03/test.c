#include "test.h"

int my_print_digits(void);

int main(void)
{
    CHECK_INT(my_print_digits(), 0);
    test_nl();
    TEST_END();
}
