#include <string.h>
#include "mouli.h"

char *my_strcat(char *dest, char const *src);

#define CAT(a, b) CASE("my_strcat(\"" a "\", \"" b "\")") { \
    char dest[64]; \
    memset(dest, 'X', sizeof(dest)); \
    strcpy(dest, a); \
    EXPECT_PTR(my_strcat(dest, b), dest); \
    EXPECT_STR(dest, a b); \
}

int main(void)
{
    CAT("Hello", " World");
    CAT("", "abc");
    CAT("abc", "");
    CAT("", "");
    return 0;
}
