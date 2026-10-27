#include "test.h"

int my_str_isupper(char const *str);

int main(void)
{
    CHECK_INT(my_str_isupper(""), 1);
    CHECK_INT(my_str_isupper("ABC"), 1);
    CHECK_INT(my_str_isupper("Z"), 1);
    CHECK_INT(my_str_isupper("BONJOUR"), 1);
    CHECK_INT(my_str_isupper("aBC"), 0);
    CHECK_INT(my_str_isupper("ABc"), 0);
    CHECK_INT(my_str_isupper("A1"), 0);
    CHECK_INT(my_str_isupper("@"), 0);
    CHECK_INT(my_str_isupper("["), 0);
    CHECK_INT(my_str_isupper("A\tB"), 0);
    TEST_END();
}
