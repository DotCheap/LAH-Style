#include <string.h>
#include "mouli.h"

char *my_strcpy(char *dest, char const *src);

#define CPY(src) CASE("my_strcpy(dest, \"" src "\")") { \
    char dest[64]; \
    memset(dest, 'X', sizeof(dest)); \
    EXPECT_PTR(my_strcpy(dest, src), dest); \
    EXPECT_STR(dest, src); \
}

int main(void)
{
    CPY("Hello World");
    CPY("");
    CPY("a");
    CPY("tab\tet\nretour");
    return 0;
}
