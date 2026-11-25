#include <stdio.h>
#include <unistd.h>
int my_isneg (int n) {
 if (n>0){
    putchar ('P');
 }
 if (n<0){
    putchar('N');
 }
    return 0;
}
