#include <string.h>
#include "mouli.h"

int my_sort_word_array(char **tab);

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
    CASE("my_sort_word_array({\"world\", \"Hello\", \"abc\", \"Abc\", \"hello\", \"42\"})") {
        char *tab[] = {"world", "Hello", "abc", "Abc", "hello", "42", 0};
        char const *exp[] = {"42", "Abc", "Hello", "abc", "hello", "world", 0};
        char *ptr = tab[0];
        EXPECT_INT(my_sort_word_array(tab), 0);
        check_tab(tab, exp);
        EXPECT(tab[5] == ptr);
    }
    CASE("my_sort_word_array({\"ab\", \"a\", \"abc\", \"a\"})") {
        char *tab[] = {"ab", "a", "abc", "a", 0};
        char const *exp[] = {"a", "a", "ab", "abc", 0};
        my_sort_word_array(tab);
        check_tab(tab, exp);
    }
    CASE("my_sort_word_array(tableau vide)") {
        char *tab[] = {0};
        EXPECT_INT(my_sort_word_array(tab), 0);
    }
    return 0;
}
