#include <fcntl.h>
#include "test.h"

void rush(int x, int y);

static void title(int x, int y)
{
    char buf[32];
    int len = snprintf(buf, sizeof(buf), "== rush(%d, %d) ==\n", x, y);

    write(1, buf, len);
}

/* Vérifie que rush(x, y) affiche « Invalid size\n » sur la sortie d'erreur. */
static void check_invalid(int x, int y)
{
    char err[64] = {0};
    int saved = dup(2);
    int fd = open("stderr.tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);

    dup2(fd, 2);
    rush(x, y);
    dup2(saved, 2);
    lseek(fd, 0, SEEK_SET);
    read(fd, err, sizeof(err) - 1);
    close(fd);
    close(saved);
    if (strcmp(err, "Invalid size\n") != 0) {
        fprintf(stderr, "  rush(%d, %d) doit afficher \"Invalid size\\n\" sur la sortie "
            "d'erreur, obtenu \"%s\"\n", x, y, err);
        test_failures++;
    }
}

int main(void)
{
    int sizes[][2] = {{5, 3}, {5, 1}, {1, 1}, {1, 5}, {4, 4}, {2, 2}, {2, 1}, {1, 2}, {10, 6}, {3, 7}};

    for (size_t i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++) {
        title(sizes[i][0], sizes[i][1]);
        rush(sizes[i][0], sizes[i][1]);
    }
    check_invalid(0, 5);
    check_invalid(5, 0);
    check_invalid(-3, 2);
    TEST_END();
}
