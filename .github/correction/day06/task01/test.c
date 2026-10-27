#include "test.h"

char *my_strcpy(char *dest, char const *src);

int main(void)
{
    char dest[32];

    memset(dest, 'X', sizeof(dest));
    CHECK(my_strcpy(dest, "Bonjour") == dest);
    CHECK_STR(dest, "Bonjour");
    CHECK(dest[8] == 'X');
    CHECK_STR(my_strcpy(dest, ""), "");
    CHECK(dest[1] == 'o');
    CHECK_STR(my_strcpy(dest, "Hello, World!"), "Hello, World!");
    TEST_END();
}
