#include "test.h"

int my_strlen(char const *str);

int main(void)
{
    char long_str[5001];

    memset(long_str, 'x', 5000);
    long_str[5000] = '\0';
    CHECK_INT(my_strlen(""), 0);
    CHECK_INT(my_strlen("a"), 1);
    CHECK_INT(my_strlen("Bonjour"), 7);
    CHECK_INT(my_strlen("Hello\0World"), 5);
    CHECK_INT(my_strlen(long_str), 5000);
    TEST_END();
}
