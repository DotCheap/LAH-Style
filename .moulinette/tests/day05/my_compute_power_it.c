#include "mouli.h"

int my_compute_power_it(int nb, int p);

int main(void)
{
    CHECK_INT(my_compute_power_it(2, 10), 1024);
    CHECK_INT(my_compute_power_it(5, 0), 1);
    CHECK_INT(my_compute_power_it(0, 0), 1);
    CHECK_INT(my_compute_power_it(0, 5), 0);
    CHECK_INT(my_compute_power_it(-3, 3), -27);
    CHECK_INT(my_compute_power_it(-2, 4), 16);
    CHECK_INT(my_compute_power_it(7, 1), 7);
    CHECK_INT(my_compute_power_it(2, -1), 0);
    CHECK_INT(my_compute_power_it(3, 19), 1162261467);
    CHECK_INT(my_compute_power_it(3, 20), 0);
    CHECK_INT(my_compute_power_it(2, 31), 0);
    CHECK_INT(my_compute_power_it(10, 15), 0);
    return 0;
}
