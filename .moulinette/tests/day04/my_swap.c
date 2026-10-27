#include "mouli.h"

void my_swap(int *a, int *b);

int main(void)
{
    CASE("my_swap(&a, &b) avec a = 42 et b = -21") {
        int a = 42;
        int b = -21;
        my_swap(&a, &b);
        EXPECT_INT(a, -21);
        EXPECT_INT(b, 42);
    }
    CASE("my_swap(&a, &a)") {
        int a = 7;
        my_swap(&a, &a);
        EXPECT_INT(a, 7);
    }
    return 0;
}
