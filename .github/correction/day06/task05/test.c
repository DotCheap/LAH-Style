#include "test.h"

char *my_strstr(char *str, char const *to_find);

int main(void)
{
    char s[] = "Bonjour tout le monde";
    char r[] = "aaab";
    char e[] = "";

    CHECK(my_strstr(s, "jour") == s + 3);
    CHECK(my_strstr(s, "Bonjour") == s);
    CHECK(my_strstr(s, "monde") == s + 16);
    CHECK(my_strstr(s, "o") == s + 1);
    CHECK(my_strstr(s, "") == s);
    CHECK(my_strstr(s, "absent") == NULL);
    CHECK(my_strstr(s, "mondes") == NULL);
    CHECK(my_strstr(r, "aab") == r + 1);
    CHECK(my_strstr(e, "") == e);
    CHECK(my_strstr(e, "a") == NULL);
    TEST_END();
}
