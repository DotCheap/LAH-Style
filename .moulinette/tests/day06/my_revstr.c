#include "mouli.h"

char *my_revstr(char *str);

#define REV(in, out) CASE("my_revstr(\"" in "\")") { \
    char *s = mouli_strdup(in); \
    EXPECT_PTR(my_revstr(s), s); \
    EXPECT_STR(s, out); \
}

int main(void)
{
    REV("Hello", "olleH");
    REV("", "");
    REV("a", "a");
    REV("ab", "ba");
    REV("Hello World!", "!dlroW olleH");
    return 0;
}
