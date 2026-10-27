#include "mouli.h"
#include "case_ref.h"

char *my_strupcase(char *str);

int main(void)
{
    CONV(my_strupcase, "hello world", "HELLO WORLD");
    CONV(my_strupcase, "Hey, How Are You? 42WORds", "HEY, HOW ARE YOU? 42WORDS");
    CONV(my_strupcase, "", "");
    CONV(my_strupcase, "az[]`{}@AZ", "AZ[]`{}@AZ");
    return 0;
}
