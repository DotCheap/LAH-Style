#include "mouli.h"

int my_strlen(char const *str);

int main(void)
{
    CHECK_INT(my_strlen("hello"), 5);
    CHECK_INT(my_strlen(""), 0);
    CHECK_INT(my_strlen("a"), 1);
    CHECK_INT(my_strlen("Epitech\n42 !"), 12);
    return 0;
}
