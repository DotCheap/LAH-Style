#include "mouli.h"

int my_print_alpha(void);

int main(void)
{
    CHECK_OUT_NL(my_print_alpha(), "abcdefghijklmnopqrstuvwxyz");
    return 0;
}
