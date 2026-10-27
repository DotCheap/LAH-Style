#include "test.h"

int my_print_comb(void);

int main(void)
{
    CHECK_INT(my_print_comb(), 0);
    test_nl();
    TEST_END();
}
