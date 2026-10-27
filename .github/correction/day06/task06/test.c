#include "test.h"

int my_strcmp(char const *s1, char const *s2);

static int sign(int n)
{
    return (n > 0) - (n < 0);
}

#define CHECK_CMP(a, b) \
    CHECK_INT(sign(my_strcmp(a, b)), sign(strcmp(a, b)))

int main(void)
{
    CHECK_CMP("abc", "abc");
    CHECK_CMP("abc", "abd");
    CHECK_CMP("abd", "abc");
    CHECK_CMP("ab", "abc");
    CHECK_CMP("abc", "ab");
    CHECK_CMP("", "");
    CHECK_CMP("", "a");
    CHECK_CMP("a", "");
    CHECK_CMP("Abc", "abc");
    CHECK_CMP("\200", "a");
    CHECK_CMP("a", "\377");
    TEST_END();
}
