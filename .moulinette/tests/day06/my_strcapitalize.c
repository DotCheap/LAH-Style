#include "mouli.h"
#include "case_ref.h"

char *my_strcapitalize(char *str);

int main(void)
{
    CONV(my_strcapitalize, "hey, how are you? 42WORds forty-two; fifty+one",
        "Hey, How Are You? 42words Forty-Two; Fifty+One");
    CONV(my_strcapitalize, "HELLO WORLD", "Hello World");
    CONV(my_strcapitalize, "", "");
    CONV(my_strcapitalize, "a", "A");
    CONV(my_strcapitalize, "  deux  espaces", "  Deux  Espaces");
    CONV(my_strcapitalize, "l'arbre", "L'Arbre");
    return 0;
}
