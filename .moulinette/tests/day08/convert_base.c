#include "mouli.h"

char *convert_base(char const *nbr, char const *base_from, char const *base_to);

int main(void)
{
    CHECK_STR(convert_base("101", "01", "0123456789"), "5");
    CHECK_STR(convert_base("255", "0123456789", "0123456789ABCDEF"), "FF");
    CHECK_STR(convert_base("-ff", "0123456789abcdef", "01"), "-11111111");
    CHECK_STR(convert_base("0", "0123456789", "01"), "0");
    CHECK_STR(convert_base("42", "0123456789", "0123456789"), "42");
    CHECK_STR(convert_base("2147483647", "0123456789", "0123456789abcdef"), "7fffffff");
    CHECK_STR(convert_base("op", "poneyvif", "0123456789"), "8");
    return 0;
}
