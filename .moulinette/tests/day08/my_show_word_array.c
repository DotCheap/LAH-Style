#include "mouli.h"

int my_show_word_array(char * const *tab);

int main(void)
{
    CASE("my_show_word_array(exemple du sujet)") {
        char *tab[] = {"The", "Answer", "to", "the", "Great", "Question...",
            "Of", "Life,", "the", "Universe", "and", "Everything...",
            "Is...", "Forty-two,", 0};
        mouli_capture();
        my_show_word_array(tab);
        mouli_expect_out("The\nAnswer\nto\nthe\nGreat\nQuestion...\nOf\n"
            "Life,\nthe\nUniverse\nand\nEverything...\nIs...\nForty-two,\n");
    }
    CASE("my_show_word_array(tableau vide)") {
        char *tab[] = {0};
        mouli_capture();
        my_show_word_array(tab);
        mouli_expect_out("");
    }
    return 0;
}
