#include "mouli.h"

int my_compute_square_root(int nb);

int main(void)
{
    CHECK_INT(my_compute_square_root(0), 0);
    CHECK_INT(my_compute_square_root(1), 1);
    CHECK_INT(my_compute_square_root(4), 2);
    CHECK_INT(my_compute_square_root(5), 0);
    CHECK_INT(my_compute_square_root(144), 12);
    CHECK_INT(my_compute_square_root(-4), 0);
    CHECK_INT(my_compute_square_root(2147395600), 46340);
    CHECK_INT(my_compute_square_root(2147483647), 0);
    return 0;
}
