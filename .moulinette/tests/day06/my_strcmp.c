#include <string.h>
#include "mouli.h"

int my_strcmp(char const *s1, char const *s2);

#define CMP(a, b) CHECK_SIGN(my_strcmp(a, b), strcmp(a, b))

int main(void)
{
    CMP("abc", "abc");
    CMP("abc", "abd");
    CMP("abd", "abc");
    CMP("abc", "abcd");
    CMP("abcd", "abc");
    CMP("", "");
    CMP("", "a");
    CMP("a", "");
    CMP("A", "a");
    CMP("\200", "a");
    return 0;
}
