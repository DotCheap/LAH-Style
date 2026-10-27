#include <string.h>
#include "mouli.h"

int my_advanced_sort_word_array(char **tab, int (*cmp)(char const *, char const *));

static int cmp_asc(char const *a, char const *b)
{
    return strcmp(a, b);
}

static int cmp_desc(char const *a, char const *b)
{
    return strcmp(b, a);
}

static int cmp_len(char const *a, char const *b)
{
    return (int)strlen(a) - (int)strlen(b);
}

static void check_tab(char **tab, char const **exp)
{
    for (int i = 0; exp[i] || tab[i]; i++)
        if (!tab[i] || !exp[i] || strcmp(tab[i], exp[i])) {
            mouli_fail("case %d : attendu \"%s\", obtenu \"%s\"", i,
                exp[i] ? exp[i] : "(null)", tab[i] ? tab[i] : "(null)");
            return;
        }
}

int main(void)
{
    CASE("my_advanced_sort_word_array(tab, strcmp)") {
        char *tab[] = {"world", "Hello", "abc", "42", 0};
        char const *exp[] = {"42", "Hello", "abc", "world", 0};
        EXPECT_INT(my_advanced_sort_word_array(tab, &cmp_asc), 0);
        check_tab(tab, exp);
    }
    CASE("my_advanced_sort_word_array(tab, ordre inverse)") {
        char *tab[] = {"world", "Hello", "abc", "42", 0};
        char const *exp[] = {"world", "abc", "Hello", "42", 0};
        my_advanced_sort_word_array(tab, &cmp_desc);
        check_tab(tab, exp);
    }
    CASE("my_advanced_sort_word_array(tab, par longueur)") {
        char *tab[] = {"xxxx", "x", "xxx", "xx", 0};
        char const *exp[] = {"x", "xx", "xxx", "xxxx", 0};
        my_advanced_sort_word_array(tab, &cmp_len);
        check_tab(tab, exp);
    }
    return 0;
}
