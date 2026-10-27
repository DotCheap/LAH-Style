#include "test.h"

char *my_evil_str(char *str);

int main(void)
{
    char s1[] = "a";
    char s2[] = "ab";
    char s3[] = "abc";
    char s4[] = "abcd";
    char s5[] = "abcdef";
    char s6[] = "";
    char s7[] = "Bonjour tout le monde";

    CHECK(my_evil_str(s1) == s1);
    CHECK_STR(s1, "a");
    CHECK(my_evil_str(s2) == s2);
    CHECK_STR(s2, "ba");
    CHECK_STR(my_evil_str(s3), "cba");
    CHECK_STR(my_evil_str(s4), "dcba");
    CHECK_STR(my_evil_str(s5), "fedcba");
    CHECK_STR(my_evil_str(s6), "");
    CHECK_STR(my_evil_str(s7), "ednom el tuot ruojnoB");
    TEST_END();
}
