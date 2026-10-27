#include "test.h"

int my_str_islower(char const *str);

int main(void)
{
    CHECK_INT(my_str_islower(""), 1);
    CHECK_INT(my_str_islower("abc"), 1);
    CHECK_INT(my_str_islower("z"), 1);
    CHECK_INT(my_str_islower("bonjour"), 1);
    CHECK_INT(my_str_islower("Abc"), 0);
    CHECK_INT(my_str_islower("abC"), 0);
    CHECK_INT(my_str_islower("a1"), 0);
    CHECK_INT(my_str_islower("`"), 0);
    CHECK_INT(my_str_islower("{"), 0);
    CHECK_INT(my_str_islower("a\tb"), 0);
    TEST_END();
}
