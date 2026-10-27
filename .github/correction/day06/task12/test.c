#include "test.h"

int my_str_isalpha(char const *str);

int main(void)
{
    CHECK_INT(my_str_isalpha(""), 1);
    CHECK_INT(my_str_isalpha("abc"), 1);
    CHECK_INT(my_str_isalpha("ABC"), 1);
    CHECK_INT(my_str_isalpha("azAZ"), 1);
    CHECK_INT(my_str_isalpha("Bonjour"), 1);
    CHECK_INT(my_str_isalpha("abc1"), 0);
    CHECK_INT(my_str_isalpha("a\tb"), 0);
    CHECK_INT(my_str_isalpha("42"), 0);
    CHECK_INT(my_str_isalpha("a_b"), 0);
    CHECK_INT(my_str_isalpha("@"), 0);
    CHECK_INT(my_str_isalpha("["), 0);
    CHECK_INT(my_str_isalpha("`"), 0);
    CHECK_INT(my_str_isalpha("{"), 0);
    TEST_END();
}
