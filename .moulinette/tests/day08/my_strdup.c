#include "mouli.h"

char *my_strdup(char const *src);

#define DUP(s) CASE("my_strdup(\"" s "\")") { \
    char const *src = s; \
    char *dup = my_strdup(src); \
    EXPECT(dup != src); \
    EXPECT_STR(dup, s); \
}

int main(void)
{
    DUP("Hello World");
    DUP("");
    DUP("a");
    return 0;
}
