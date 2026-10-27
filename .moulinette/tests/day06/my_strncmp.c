#include <string.h>
#include "mouli.h"

int my_strncmp(char const *s1, char const *s2, int n);

#define NCMP(a, b, n) CHECK_SIGN(my_strncmp(a, b, n), strncmp(a, b, n))

int main(void)
{
    NCMP("abc", "abc", 3);
    NCMP("abc", "abd", 3);
    NCMP("abc", "abd", 2);
    NCMP("abd", "abc", 5);
    NCMP("abc", "abcd", 3);
    NCMP("abc", "abcd", 4);
    NCMP("abcd", "abc", 10);
    NCMP("xyz", "abc", 0);
    NCMP("", "", 1);
    NCMP("", "a", 1);
    return 0;
}
