#include <stdio.h>
int my_print_revalpha(void){
    int lettre = 122;
    putchar(lettre);
    lettre = lettre - 1; 
    putchar (lettre);
    while (lettre > 96){
        putchar(lettre);
        lettre = lettre - 1;
    }
    return 0;
}
int main(void){
    my_print_revalpha();
    return 0;
}