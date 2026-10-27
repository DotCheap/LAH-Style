#include "mouli.h"

char *my_evil_str(char *str);

#define EVIL(in, out) CASE("my_evil_str(\"" in "\")") { \
    char *s = mouli_strdup(in); \
    EXPECT_PTR(my_evil_str(s), s); \
    EXPECT_STR(s, out); \
}

int main(void)
{
    EVIL("a", "a");
    EVIL("ab", "ba");
    EVIL("abc", "cba");
    EVIL("abcd", "dcba");
    EVIL("abcde", "edcba");
    EVIL("abcdef", "fedcba");
    EVIL("", "");
    EVIL("Hello World!", "!dlroW olleH");
    return 0;
}
