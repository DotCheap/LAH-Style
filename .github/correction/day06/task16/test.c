#include "test.h"

int my_str_isprintable(char const *str);

int main(void)
{
    CHECK_INT(my_str_isprintable(""), 1);
    CHECK_INT(my_str_isprintable("abc"), 1);
    CHECK_INT(my_str_isprintable("~!@#$%^&*()"), 1);
    CHECK_INT(my_str_isprintable("\x20"), 1);
    CHECK_INT(my_str_isprintable("Hello,\x20World!"), 1);
    CHECK_INT(my_str_isprintable("a\tb"), 0);
    CHECK_INT(my_str_isprintable("\n"), 0);
    CHECK_INT(my_str_isprintable("\x7f"), 0);
    CHECK_INT(my_str_isprintable("\x1f"), 0);
    CHECK_INT(my_str_isprintable("\x80"), 0);
    TEST_END();
}
