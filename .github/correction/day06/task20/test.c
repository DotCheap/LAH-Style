#include "test.h"

int my_showstr(char const *str);

int main(void)
{
    CHECK_INT(my_showstr("I like \n ponies!"), 0);
    test_nl();
    CHECK_INT(my_showstr("abc"), 0);
    test_nl();
    CHECK_INT(my_showstr(""), 0);
    test_nl();
    CHECK_INT(my_showstr("tab\there"), 0);
    test_nl();
    CHECK_INT(my_showstr("\x01\x1f\x7f"), 0);
    test_nl();
    CHECK_INT(my_showstr("caf\xe9"), 0);
    test_nl();
    TEST_END();
}
