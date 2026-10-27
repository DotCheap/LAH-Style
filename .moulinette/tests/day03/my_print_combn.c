#include "mouli.h"
#include "combn_ref.h"

int my_print_combn(int n);

int main(void)
{
    CHECK_OUT_NL(my_print_combn(1), expected_combn(1));
    CHECK_OUT_NL(my_print_combn(2), expected_combn(2));
    CHECK_OUT_NL(my_print_combn(3), expected_combn(3));
    CHECK_OUT_NL(my_print_combn(5), expected_combn(5));
    CHECK_OUT_NL(my_print_combn(9), expected_combn(9));
    return 0;
}
