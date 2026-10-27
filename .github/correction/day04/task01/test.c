#include <limits.h>
#include "test.h"

void my_swap(int *a, int *b);

int main(void)
{
    int a = 1;
    int b = 2;
    int c = INT_MIN;
    int d = INT_MAX;
    int e = 42;

    my_swap(&a, &b);
    CHECK_INT(a, 2);
    CHECK_INT(b, 1);
    my_swap(&c, &d);
    CHECK_INT(c, INT_MAX);
    CHECK_INT(d, INT_MIN);
    my_swap(&e, &e);
    CHECK_INT(e, 42);
    TEST_END();
}
