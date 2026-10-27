#include "test.h"

int my_advanced_sort_word_array(char **tab, int (*cmp)(char const *, char const *));

static int reverse_cmp(char const *s1, char const *s2)
{
    return strcmp(s2, s1);
}

static int len_cmp(char const *s1, char const *s2)
{
    return (int)strlen(s1) - (int)strlen(s2);
}

int main(void)
{
    char *w1 = "banane";
    char *w2 = "abricot";
    char *w3 = "kiwi";
    char *tab[] = {w1, w2, w3, NULL};

    CHECK_INT(my_advanced_sort_word_array(tab, &strcmp), 0);
    CHECK(tab[0] == w2 && tab[1] == w1 && tab[2] == w3);
    CHECK_INT(my_advanced_sort_word_array(tab, &reverse_cmp), 0);
    CHECK(tab[0] == w3 && tab[1] == w1 && tab[2] == w2);
    CHECK_INT(my_advanced_sort_word_array(tab, &len_cmp), 0);
    CHECK(tab[0] == w3 && tab[1] == w1 && tab[2] == w2);
    CHECK(tab[3] == NULL);
    TEST_END();
}
