#include "mouli.h"
#include "str_is.h"

int my_str_isupper(char const *str);

int main(void)
{
    IS(my_str_isupper, "", 1);
    IS(my_str_isupper, "ABCXYZ", 1);
    IS(my_str_isupper, "ABCxYZ", 0);
    IS(my_str_isupper, "ABC DEF", 0);
    IS(my_str_isupper, "@[", 0);
    return 0;
}
