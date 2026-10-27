#include "mouli.h"

int my_compute_factorial_it(int nb);

int main(void)
{
    CHECK_INT(my_compute_factorial_it(0), 1);
    CHECK_INT(my_compute_factorial_it(1), 1);
    CHECK_INT(my_compute_factorial_it(5), 120);
    CHECK_INT(my_compute_factorial_it(10), 3628800);
    CHECK_INT(my_compute_factorial_it(12), 479001600);
    CHECK_INT(my_compute_factorial_it(13), 0);
    CHECK_INT(my_compute_factorial_it(42), 0);
    CHECK_INT(my_compute_factorial_it(-1), 0);
    CHECK_INT(my_compute_factorial_it(-2147483647 - 1), 0);
    return 0;
}
