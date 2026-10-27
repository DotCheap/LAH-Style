#include <string.h>
#include "mouli.h"

char *my_strncat(char *dest, char const *src, int nb);

#define NCAT(a, b, n) CASE("my_strncat(\"" a "\", \"" b "\", " #n ")") { \
    char dest[64]; \
    char exp[64]; \
    memset(dest, 'X', sizeof(dest)); \
    strcpy(dest, a); \
    strcpy(exp, a); \
    strncat(exp, b, n); \
    EXPECT_PTR(my_strncat(dest, b, n), dest); \
    EXPECT_STR(dest, exp); \
}

int main(void)
{
    NCAT("Hello", " World", 3);
    NCAT("Hello", " World", 6);
    NCAT("Hello", " World", 42);
    NCAT("Hello", " World", 0);
    NCAT("", "abc", 2);
    return 0;
}
