#include "test.h"

int my_print_alpha(void);

int main(void)
{
    CHECK_INT(my_print_alpha(), 0);
    test_nl();
    TEST_END();
}
