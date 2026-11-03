#include <stdio.h>
int my_print_revalpha(void){
    int lettre = 122;
    while (lettre > 96){
        putchar (lettre);
        lettre = lettre - 1; 
    }
    return 0;
}