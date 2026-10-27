#include <stdlib.h>
#include "test.h"

int count_island(char **world);

/* Affiche le monde modifié puis le nombre d'îles renvoyé. */
static void show(char **world, int count)
{
    char buf[32];
    int len = snprintf(buf, sizeof(buf), "=> %d\n", count);

    for (int i = 0; world[i] != NULL; i++) {
        write(1, world[i], strlen(world[i]));
        test_nl();
    }
    write(1, buf, len);
}

int main(void)
{
    {
        char *w[] = {strdup("....X....."), strdup("..XXX.X..."), strdup("......X..X"), strdup("XX.......X"), strdup("X...XXXX.."), NULL};

        show(w, count_island(w));
    }
    {
        char *w[] = {strdup("XXXX"), strdup("X..X"), strdup("X.XX"), strdup("XXX."), NULL};

        show(w, count_island(w));
    }
    {
        char *w[] = {strdup("...."), strdup("...."), strdup("...."), NULL};

        show(w, count_island(w));
    }
    {
        char *w[] = {strdup("X.X.X.X.X."), strdup(".X.X.X.X.X"), strdup(".........."), NULL};

        show(w, count_island(w));
    }
    {
        char *w[] = {strdup(".X......X."), strdup(".XXXX..XX."), strdup("....X..X.."), strdup("XX..XXXX.."), strdup("X........."), strdup("X..X..XX.X"), NULL};

        show(w, count_island(w));
    }
    TEST_END();
}
