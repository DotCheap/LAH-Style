#include "test.h"

int my_print_revalpha(void);

int main(void)
{
    CHECK_INT(my_print_revalpha(), 0);
    test_nl();
    TEST_END();
}
