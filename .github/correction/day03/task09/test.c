#include "test.h"

int my_print_combn(int n);

int main(void)
{
    int values[] = {1, 2, 3, 9, 10};

    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        CHECK_INT(my_print_combn(values[i]), 0);
        test_nl();
    }
    TEST_END();
}
