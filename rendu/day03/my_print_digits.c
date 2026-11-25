#include <stdio.h>
#include <unistd.h>
int my_print_digits(void){
  int nombre = 48;
  while (nombre < 58){
  putchar (nombre);
  nombre = nombre + 1;
  }
    return 0;

