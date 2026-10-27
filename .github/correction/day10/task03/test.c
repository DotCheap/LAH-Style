#include "test.h"

int my_sort_word_array(char **tab);

int main(void)
{
    char *b = "banane";
    char *a = "abricot";
    char *c = "cerise";
    char *upper = "Zebre";
    char *a2 = "abricot";
    char *tab[] = {b, a, c, upper, a2, NULL};
    char *one[] = {a, NULL};
    char *empty[] = {NULL};

    CHECK_INT(my_sort_word_array(tab), 0);
    CHECK(tab[0] == upper);
    CHECK(tab[1] == a || tab[1] == a2);
    CHECK(tab[2] == a || tab[2] == a2);
    CHECK(tab[3] == b);
    CHECK(tab[4] == c);
    CHECK(tab[5] == NULL);
    CHECK_INT(my_sort_word_array(one), 0);
    CHECK(one[0] == a);
    CHECK_INT(my_sort_word_array(empty), 0);
    TEST_END();
}
