#include <string.h>
#include "mouli.h"

char *my_strncpy(char *dest, char const *src, int n);

static void check_buf(char const *got, char const *exp, int size)
{
    for (int i = 0; i < size; i++)
        if (got[i] != exp[i]) {
            mouli_fail("dest[%d] : attendu 0x%02x, obtenu 0x%02x", i,
                (unsigned char)exp[i], (unsigned char)got[i]);
            return;
        }
}

#define NCPY(src, n) CASE("my_strncpy(dest, \"" src "\", " #n ")") { \
    char dest[32]; \
    char exp[32]; \
    memset(dest, 'X', sizeof(dest)); \
    memset(exp, 'X', sizeof(exp)); \
    strncpy(exp, src, n); \
    EXPECT_PTR(my_strncpy(dest, src, n), dest); \
    check_buf(dest, exp, sizeof(dest)); \
}

int main(void)
{
    NCPY("HelloWorld", 5);
    NCPY("Hello", 6);
    NCPY("Hello", 10);
    NCPY("Hello", 0);
    NCPY("", 4);
    NCPY("abc", 3);
    return 0;
}
