#include "test.h"

int my_strncmp(char const *s1, char const *s2, int n);

static int sign(int n)
{
    return (n > 0) - (n < 0);
}

#define CHECK_NCMP(a, b, n) \
    CHECK_INT(sign(my_strncmp(a, b, n)), sign(strncmp(a, b, n)))

int main(void)
{
    CHECK_NCMP("abc", "abc", 3);
    CHECK_NCMP("abc", "abd", 3);
    CHECK_NCMP("abc", "abd", 2);
    CHECK_NCMP("abd", "abc", 5);
    CHECK_NCMP("ab", "abc", 3);
    CHECK_NCMP("ab", "abc", 2);
    CHECK_NCMP("abc", "ab", 10);
    CHECK_NCMP("xyz", "abc", 0);
    CHECK_NCMP("", "", 1);
    CHECK_NCMP("\200", "a", 1);
    TEST_END();
}
