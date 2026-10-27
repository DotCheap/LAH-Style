#include "test.h"

int count_valid_queens_placements(int n);

int main(void)
{
    int const expected[] = {1, 0, 0, 2, 10, 4, 40, 92, 352, 724};

    for (int n = 1; n <= 10; n++)
        CHECK_INT(count_valid_queens_placements(n), expected[n - 1]);
    TEST_END();
}
