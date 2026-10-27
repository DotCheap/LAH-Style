/*
** my_putchar fournie par la correction aux exercices qui l'autorisent.
*/

#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}
