#include <string.h>
#include "mouli.h"

char **my_str_to_word_array(char const *str);

static void check_words(char const *str, char const **exp)
{
    char **got = my_str_to_word_array(str);
    int i = 0;

    if (got == NULL) {
        mouli_fail("a renvoye NULL");
        return;
    }
    for (; exp[i]; i++) {
        if (got[i] == NULL) {
            mouli_fail("mot %d : attendu \"%s\", obtenu NULL (tableau trop court)", i, exp[i]);
            return;
        }
        if (strcmp(got[i], exp[i])) {
            mouli_fail("mot %d : attendu \"%s\", obtenu \"%s\"", i, exp[i], got[i]);
            return;
        }
    }
    if (got[i] != NULL)
        mouli_fail("le tableau doit se terminer par NULL apres %d mots (obtenu \"%s\")", i, got[i]);
}

#define WORDS(str, ...) CASE("my_str_to_word_array(\"" str "\")") { \
    char const *exp[] = {__VA_ARGS__}; \
    check_words(str, exp); \
}

int main(void)
{
    WORDS("Hello World", "Hello", "World", 0);
    WORDS("  Hello,   World! 42 is the answer...  ", "Hello", "World", "42",
        "is", "the", "answer", 0);
    WORDS("forty-two;fifty+one", "forty", "two", "fifty", "one", 0);
    WORDS("abc", "abc", 0);
    WORDS("", 0);
    WORDS(" ,;!", 0);
    return 0;
}
