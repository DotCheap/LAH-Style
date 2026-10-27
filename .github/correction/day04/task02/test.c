#include "test.h"

int my_putstr(char const *str);

int main(void)
{
    CHECK_INT(my_putstr("Bonjour"), 0);
    test_nl();
    CHECK_INT(my_putstr(""), 0);
    test_nl();
    CHECK_INT(my_putstr("Hello, World! 123"), 0);
    test_nl();
    CHECK_INT(my_putstr("a\tb"), 0);
    test_nl();
    TEST_END();
}
