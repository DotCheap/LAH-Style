#include "test.h"

int my_compute_power_rec(int nb, int p);

int main(void)
{
    CHECK_INT(my_compute_power_rec(2, 0), 1);
    CHECK_INT(my_compute_power_rec(0, 0), 1);
    CHECK_INT(my_compute_power_rec(0, 5), 0);
    CHECK_INT(my_compute_power_rec(2, 10), 1024);
    CHECK_INT(my_compute_power_rec(3, 3), 27);
    CHECK_INT(my_compute_power_rec(-2, 3), -8);
    CHECK_INT(my_compute_power_rec(-3, 2), 9);
    CHECK_INT(my_compute_power_rec(7, 1), 7);
    CHECK_INT(my_compute_power_rec(2, 30), 1073741824);
    CHECK_INT(my_compute_power_rec(5, -1), 0);
    CHECK_INT(my_compute_power_rec(2, 31), 0);
    CHECK_INT(my_compute_power_rec(10, 10), 0);
    CHECK_INT(my_compute_power_rec(46341, 2), 0);
    TEST_END();
}
