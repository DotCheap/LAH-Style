/*
** Lit une carte (fichier passe en argument), appelle count_island puis
** affiche la valeur de retour et la carte modifiee.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_island(char **world);

int main(int ac, char **av)
{
    char *lines[256];
    char buf[4096];
    int n = 0;
    FILE *f = ac == 2 ? fopen(av[1], "r") : NULL;
    int ret;

    if (f == NULL)
        return 1;
    while (n < 255 && fgets(buf, sizeof(buf), f)) {
        buf[strcspn(buf, "\n")] = '\0';
        lines[n++] = strdup(buf);
    }
    lines[n] = NULL;
    fclose(f);
    ret = count_island(lines);
    printf("%d\n", ret);
    for (int i = 0; i < n; i++)
        printf("%s\n", lines[i]);
    return 0;
}
