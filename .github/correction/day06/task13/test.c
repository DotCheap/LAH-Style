#include "test.h"

int my_str_isnum(char const *str);

int main(void)
{
    CHECK_INT(my_str_isnum(""), 1);
    CHECK_INT(my_str_isnum("0"), 1);
    CHECK_INT(my_str_isnum("42"), 1);
    CHECK_INT(my_str_isnum("0123456789"), 1);
    CHECK_INT(my_str_isnum("42a"), 0);
    CHECK_INT(my_str_isnum("-42"), 0);
    CHECK_INT(my_str_isnum("+1"), 0);
    CHECK_INT(my_str_isnum("/"), 0);
    CHECK_INT(my_str_isnum(":"), 0);
    CHECK_INT(my_str_isnum("4\n"), 0);
    TEST_END();
}
