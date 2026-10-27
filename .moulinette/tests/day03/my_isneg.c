#include <limits.h>
#include "mouli.h"

int my_isneg(int n);

int main(void)
{
    CHECK_OUT(my_isneg(-42), "N");
    CHECK_OUT(my_isneg(-1), "N");
    CHECK_OUT(my_isneg(0), "P");
    CHECK_OUT(my_isneg(1), "P");
    CHECK_OUT(my_isneg(INT_MAX), "P");
    CHECK_OUT(my_isneg(INT_MIN), "N");
    return 0;
}
