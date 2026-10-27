#include <limits.h>
#include "test.h"

int my_put_nbr(int nb);

int main(void)
{
    int values[] = {0, 7, -7, 42, -42, 100, 1000000, -987654,
        -2147483647, INT_MAX, INT_MIN};

    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        CHECK_INT(my_put_nbr(values[i]), 0);
        test_nl();
    }
    TEST_END();
}
