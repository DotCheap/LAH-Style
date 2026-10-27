#include "test.h"

int my_compute_factorial_rec(int nb);

int main(void)
{
    CHECK_INT(my_compute_factorial_rec(0), 1);
    CHECK_INT(my_compute_factorial_rec(1), 1);
    CHECK_INT(my_compute_factorial_rec(2), 2);
    CHECK_INT(my_compute_factorial_rec(5), 120);
    CHECK_INT(my_compute_factorial_rec(10), 3628800);
    CHECK_INT(my_compute_factorial_rec(12), 479001600);
    CHECK_INT(my_compute_factorial_rec(13), 0);
    CHECK_INT(my_compute_factorial_rec(42), 0);
    CHECK_INT(my_compute_factorial_rec(-1), 0);
    CHECK_INT(my_compute_factorial_rec(-42), 0);
    TEST_END();
}
