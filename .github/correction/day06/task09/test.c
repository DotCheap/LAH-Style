#include "test.h"

char *my_strlowcase(char *str);

int main(void)
{
    char s1[] = "BONJOUR";
    char s2[] = "Hello, World! 42 ABCXYZ";
    char s3[] = "deja en minuscules";
    char s4[] = "";
    char s5[] = "@[`{";

    CHECK(my_strlowcase(s1) == s1);
    CHECK_STR(s1, "bonjour");
    CHECK_STR(my_strlowcase(s2), "hello, world! 42 abcxyz");
    CHECK_STR(my_strlowcase(s3), "deja en minuscules");
    CHECK_STR(my_strlowcase(s4), "");
    CHECK_STR(my_strlowcase(s5), "@[`{");
    TEST_END();
}
