#include "test.h"

int my_print_comb2(void);

int main(void)
{
    CHECK_INT(my_print_comb2(), 0);
    test_nl();
    TEST_END();
}
