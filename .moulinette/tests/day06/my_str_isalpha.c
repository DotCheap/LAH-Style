#include "mouli.h"
#include "str_is.h"

int my_str_isalpha(char const *str);

int main(void)
{
    IS(my_str_isalpha, "", 1);
    IS(my_str_isalpha, "Hello", 1);
    IS(my_str_isalpha, "azAZ", 1);
    IS(my_str_isalpha, "Hello World", 0);
    IS(my_str_isalpha, "abc1", 0);
    IS(my_str_isalpha, "@[`{", 0);
    return 0;
}
