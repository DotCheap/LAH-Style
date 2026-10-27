#include "test.h"

char *my_strupcase(char *str);

int main(void)
{
    char s1[] = "Bonjour";
    char s2[] = "hello, world! 42 abcxyz";
    char s3[] = "DEJA EN MAJUSCULES";
    char s4[] = "";
    char s5[] = "@[`{";

    CHECK(my_strupcase(s1) == s1);
    CHECK_STR(s1, "BONJOUR");
    CHECK_STR(my_strupcase(s2), "HELLO, WORLD! 42 ABCXYZ");
    CHECK_STR(my_strupcase(s3), "DEJA EN MAJUSCULES");
    CHECK_STR(my_strupcase(s4), "");
    CHECK_STR(my_strupcase(s5), "@[`{");
    TEST_END();
}
