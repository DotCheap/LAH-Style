#include "mouli.h"
#include "str_is.h"

int my_str_isprintable(char const *str);

int main(void)
{
    IS(my_str_isprintable, "", 1);
    IS(my_str_isprintable, "Hello World! ~ 42", 1);
    IS(my_str_isprintable, "Hello\n", 0);
    IS(my_str_isprintable, "\t", 0);
    IS(my_str_isprintable, "\177", 0);
    IS(my_str_isprintable, "\037", 0);
    return 0;
}
