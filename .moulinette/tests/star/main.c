#include <stdlib.h>

void star(unsigned int size);

int main(int ac, char **av)
{
    if (ac == 2)
        star(atoi(av[1]));
    return 0;
}
