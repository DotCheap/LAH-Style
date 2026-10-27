#include "mouli.h"
#include "str_is.h"

int my_str_islower(char const *str);

int main(void)
{
    IS(my_str_islower, "", 1);
    IS(my_str_islower, "abcxyz", 1);
    IS(my_str_islower, "abcXyz", 0);
    IS(my_str_islower, "abc def", 0);
    IS(my_str_islower, "`{", 0);
    return 0;
}
