#include "mouli.h"

int count_valid_queens_placements(int n);

int main(void)
{
    CHECK_INT(count_valid_queens_placements(1), 1);
    CHECK_INT(count_valid_queens_placements(2), 0);
    CHECK_INT(count_valid_queens_placements(3), 0);
    CHECK_INT(count_valid_queens_placements(4), 2);
    CHECK_INT(count_valid_queens_placements(5), 10);
    CHECK_INT(count_valid_queens_placements(6), 4);
    CHECK_INT(count_valid_queens_placements(8), 92);
    CHECK_INT(count_valid_queens_placements(10), 724);
    return 0;
}
