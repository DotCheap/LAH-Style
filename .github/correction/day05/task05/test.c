#include <limits.h>
#include "test.h"

int my_compute_square_root(int nb);

int main(void)
{
    CHECK_INT(my_compute_square_root(0), 0);
    CHECK_INT(my_compute_square_root(1), 1);
    CHECK_INT(my_compute_square_root(4), 2);
    CHECK_INT(my_compute_square_root(16), 4);
    CHECK_INT(my_compute_square_root(144), 12);
    CHECK_INT(my_compute_square_root(2), 0);
    CHECK_INT(my_compute_square_root(15), 0);
    CHECK_INT(my_compute_square_root(-4), 0);
    CHECK_INT(my_compute_square_root(2147395600), 46340);
    CHECK_INT(my_compute_square_root(INT_MAX), 0);
    TEST_END();
}
