#include <limits.h>
#include "test.h"

int my_isneg(int n);

int main(void)
{
    int values[] = {0, 21, -21, 1, -1, INT_MAX, INT_MIN};

    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        CHECK_INT(my_isneg(values[i]), 0);
        test_nl();
    }
    TEST_END();
}
