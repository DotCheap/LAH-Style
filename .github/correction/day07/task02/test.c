#include "test.h"

char *my_strcat(char *dest, char const *src);

int main(void)
{
    char dest[32] = "Bonjour";
    char empty[8] = "";

    CHECK(my_strcat(dest, " tout") == dest);
    CHECK_STR(dest, "Bonjour tout");
    CHECK_STR(my_strcat(dest, ""), "Bonjour tout");
    CHECK_STR(my_strcat(dest, " le monde"), "Bonjour tout le monde");
    CHECK_STR(my_strcat(empty, "abc"), "abc");
    TEST_END();
}
