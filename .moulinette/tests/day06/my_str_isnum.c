#include "mouli.h"
#include "str_is.h"

int my_str_isnum(char const *str);

int main(void)
{
    IS(my_str_isnum, "", 1);
    IS(my_str_isnum, "0123456789", 1);
    IS(my_str_isnum, "-42", 0);
    IS(my_str_isnum, "42a", 0);
    IS(my_str_isnum, "/:", 0);
    return 0;
}
