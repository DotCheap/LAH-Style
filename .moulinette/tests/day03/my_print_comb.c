#include "mouli.h"
#include "combn_ref.h"

int my_print_comb(void);

int main(void)
{
    CHECK_OUT_NL(my_print_comb(), expected_combn(3));
    return 0;
}
