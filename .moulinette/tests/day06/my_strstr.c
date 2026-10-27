#include <string.h>
#include "mouli.h"

char *my_strstr(char *str, char const *to_find);

#define STR(hay, needle) CASE("my_strstr(\"" hay "\", \"" needle "\")") { \
    char *s = mouli_strdup(hay); \
    mouli_expect_offset("valeur de retour", my_strstr(s, needle), s, \
        strstr(s, needle)); \
}

int main(void)
{
    STR("Hello World", "World");
    STR("Hello World", "o");
    STR("Hello World", "Hello");
    STR("Hello World", "xyz");
    STR("Hello World", "");
    STR("", "");
    STR("", "a");
    STR("aaab", "aab");
    STR("abc", "abcd");
    STR("Hello World", "World!");
    return 0;
}
