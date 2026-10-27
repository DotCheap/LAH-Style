#include "mouli.h"
#include "case_ref.h"

char *my_strlowcase(char *str);

int main(void)
{
    CONV(my_strlowcase, "HELLO WORLD", "hello world");
    CONV(my_strlowcase, "Hey, How Are You? 42WORds", "hey, how are you? 42words");
    CONV(my_strlowcase, "", "");
    CONV(my_strlowcase, "AZ[]`{}@az", "az[]`{}@az");
    return 0;
}
