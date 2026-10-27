/*
** my_putchar fourni par la moulinette (Day 03 a Day 05, Rush 1, Star).
*/

#include <unistd.h>

int my_putchar(char c)
{
    return write(1, &c, 1);
}
