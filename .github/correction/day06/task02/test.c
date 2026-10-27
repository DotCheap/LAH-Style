#include "test.h"

char *my_strncpy(char *dest, char const *src, int n);

int main(void)
{
    char dest[16];

    memset(dest, 'X', sizeof(dest));
    CHECK(my_strncpy(dest, "Bonjour", 3) == dest);
    CHECK(memcmp(dest, "BonXXXX", 7) == 0);

    memset(dest, 'X', sizeof(dest));
    my_strncpy(dest, "Bonjour", 7);
    CHECK(memcmp(dest, "BonjourX", 8) == 0);

    memset(dest, 'X', sizeof(dest));
    my_strncpy(dest, "abc", 6);
    CHECK(memcmp(dest, "abc\0\0\0X", 7) == 0);

    memset(dest, 'X', sizeof(dest));
    my_strncpy(dest, "abc", 0);
    CHECK(dest[0] == 'X');

    memset(dest, 'X', sizeof(dest));
    my_strncpy(dest, "", 2);
    CHECK(memcmp(dest, "\0\0X", 3) == 0);
    TEST_END();
}
