#include "test.h"

char *my_revstr(char *str);

int main(void)
{
    char s1[] = "Bonjour";
    char s2[] = "abcd";
    char s3[] = "a";
    char s4[] = "";
    char s5[] = "kayak";

    CHECK(my_revstr(s1) == s1);
    CHECK_STR(s1, "ruojnoB");
    CHECK(my_revstr(s2) == s2);
    CHECK_STR(s2, "dcba");
    CHECK_STR(my_revstr(s3), "a");
    CHECK_STR(my_revstr(s4), "");
    CHECK_STR(my_revstr(s5), "kayak");
    TEST_END();
}
