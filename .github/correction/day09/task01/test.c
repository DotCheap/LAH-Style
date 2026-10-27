#include "test.h"
#include "my_macro_abs.h"

int main(void)
{
    int x = 3;
    int y = 10;

    CHECK_INT(ABS(-5), 5);
    CHECK_INT(ABS(5), 5);
    CHECK_INT(ABS(0), 0);
    CHECK_INT(ABS(x - y), 7);
    CHECK_INT(ABS(-2 + 1), 1);
    CHECK_INT(2 * ABS(-3), 6);
    CHECK_INT(ABS(-3) * 2, 6);
    CHECK_INT(ABS(-x) + 1, 4);
    TEST_END();
}
