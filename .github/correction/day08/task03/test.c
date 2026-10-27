#include "test.h"

int my_show_word_array(char * const *tab);

int main(void)
{
    char *words[] = {"The", "Answer", "to", "the", "Great", "Question...",
        "Of", "Life,", "the", "Universe", "and", "Everything...", "Is...",
        "Forty-two,", NULL};
    char *empty[] = {NULL};

    my_show_word_array(words);
    my_show_word_array(empty);
    TEST_END();
}
