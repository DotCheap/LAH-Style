#include "test.h"

char *my_strncat(char *dest, char const *src, int nb);

int main(void)
{
    char dest[32] = "Bonjour";
    char other[16] = "ab";

    CHECK(my_strncat(dest, " tout le monde", 5) == dest);
    CHECK_STR(dest, "Bonjour tout");
    CHECK_STR(my_strncat(dest, "!!", 10), "Bonjour tout!!");
    CHECK_STR(my_strncat(dest, "xyz", 0), "Bonjour tout!!");
    memset(other + 3, 'X', sizeof(other) - 3);
    my_strncat(other, "cdef", 2);
    CHECK_STR(other, "abcd");
    TEST_END();
}
