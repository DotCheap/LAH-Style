#include "test.h"

int my_compute_power_it(int nb, int p);

int main(void)
{
    CHECK_INT(my_compute_power_it(2, 0), 1);
    CHECK_INT(my_compute_power_it(0, 0), 1);
    CHECK_INT(my_compute_power_it(0, 5), 0);
    CHECK_INT(my_compute_power_it(2, 10), 1024);
    CHECK_INT(my_compute_power_it(3, 3), 27);
    CHECK_INT(my_compute_power_it(-2, 3), -8);
    CHECK_INT(my_compute_power_it(-3, 2), 9);
    CHECK_INT(my_compute_power_it(7, 1), 7);
    CHECK_INT(my_compute_power_it(2, 30), 1073741824);
    CHECK_INT(my_compute_power_it(5, -1), 0);
    CHECK_INT(my_compute_power_it(2, 31), 0);
    CHECK_INT(my_compute_power_it(10, 10), 0);
    CHECK_INT(my_compute_power_it(46341, 2), 0);
    TEST_END();
}
