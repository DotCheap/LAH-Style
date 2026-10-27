#include <stdlib.h>
#include "test.h"

char *my_strdup(char const *src);

int main(void)
{
    char const *src = "Bonjour tout le monde";
    char *copy = my_strdup(src);
    char *empty = my_strdup("");

    CHECK(copy != NULL && copy != src);
    CHECK_STR(copy, src);
    CHECK(empty != NULL);
    CHECK_STR(empty, "");
    if (copy != NULL) {
        copy[0] = 'b';
        CHECK_STR(src, "Bonjour tout le monde");
    }
    free(copy);
    free(empty);
    TEST_END();
}
