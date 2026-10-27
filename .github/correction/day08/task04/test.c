#include <stdlib.h>
#include "test.h"

char **my_str_to_word_array(char const *str);

static void check_words(char const *str, char const * const *want, int line)
{
    char **got = my_str_to_word_array(str);
    int i = 0;

    if (got == NULL) {
        fprintf(stderr, "  ligne %d : NULL renvoyé pour \"%s\"\n", line, str);
        test_failures++;
        return;
    }
    for (; want[i] != NULL; i++) {
        if (got[i] == NULL || strcmp(got[i], want[i]) != 0) {
            fprintf(stderr, "  ligne %d : \"%s\" : mot %d vaut \"%s\", attendu \"%s\"\n",
                line, str, i, got[i] ? got[i] : "(NULL)", want[i]);
            test_failures++;
            return;
        }
    }
    if (got[i] != NULL) {
        fprintf(stderr, "  ligne %d : \"%s\" : mot en trop \"%s\" (le tableau doit finir par NULL)\n",
            line, str, got[i]);
        test_failures++;
    }
}

int main(void)
{
    char const *w1[] = {"Hello", "World", "42", "is", "the", "answer", NULL};
    char const *w2[] = {"abc", NULL};
    char const *w3[] = {"a", "b", "c", NULL};
    char const *w4[] = {"debut", "fin", NULL};
    char const *none[] = {NULL};

    check_words("Hello, World! 42 is the answer", w1, __LINE__);
    check_words("abc", w2, __LINE__);
    check_words("a-b_c", w3, __LINE__);
    check_words("   debut   \t\n fin   ", w4, __LINE__);
    check_words("", none, __LINE__);
    check_words(" ,;! ", none, __LINE__);
    TEST_END();
}
