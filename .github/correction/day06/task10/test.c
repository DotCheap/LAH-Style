#include "test.h"

char *my_strcapitalize(char *str);

int main(void)
{
    char s1[] = "hey, how are you? 42WORds forty-two; fifty+one";
    char s2[] = "BONJOUR TOUT LE MONDE";
    char s3[] = "a";
    char s4[] = "";
    char s5[] = "  deux  espaces";

    CHECK(my_strcapitalize(s1) == s1);
    CHECK_STR(s1, "Hey, How Are You? 42words Forty-Two; Fifty+One");
    CHECK_STR(my_strcapitalize(s2), "Bonjour Tout Le Monde");
    CHECK_STR(my_strcapitalize(s3), "A");
    CHECK_STR(my_strcapitalize(s4), "");
    CHECK_STR(my_strcapitalize(s5), "  Deux  Espaces");
    TEST_END();
}
