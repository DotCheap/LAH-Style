#include "mouli.h"

int my_showstr(char const *str);

int main(void)
{
    CASE("my_showstr(\"I like \\n ponies!\")") {
        mouli_capture();
        EXPECT_INT(my_showstr("I like \n ponies!"), 0);
        mouli_expect_out("I like \\0a ponies!");
    }
    CHECK_OUT(my_showstr("Hello World"), "Hello World");
    CHECK_OUT(my_showstr(""), "");
    CHECK_OUT(my_showstr("\t\033\177x\001"), "\\09\\1b\\7fx\\01");
    return 0;
}
