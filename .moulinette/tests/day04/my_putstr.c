#include "mouli.h"

int my_putstr(char const *str);

int main(void)
{
    CHECK_OUT(my_putstr("hello world"), "hello world");
    CHECK_OUT(my_putstr(""), "");
    CHECK_OUT(my_putstr("a\nb\tc"), "a\nb\tc");
    return 0;
}
