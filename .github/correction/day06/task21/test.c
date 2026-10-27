#include "test.h"

int my_showmem(char const *str, int size);

int main(void)
{
    char const data[] = "hey guys show mem is cool you can do some pretty"
        " neat stuff\0\x0f\x1b\x7f\x05.\0\x01\x02\x03\x04\x05\x06\x07\x08\x09"
        "\x0e\x0f\x1b\x7f";

    CHECK_INT(my_showmem(data, 79), 0);
    CHECK_INT(my_showmem("0123456789abcdef", 16), 0);
    CHECK_INT(my_showmem("abc", 3), 0);
    CHECK_INT(my_showmem("", 0), 0);
    TEST_END();
}
