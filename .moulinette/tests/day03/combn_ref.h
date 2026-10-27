/* Generation de la sortie attendue pour my_print_comb / comb2 / combn. */
#include <stdio.h>
#include <string.h>

static char g_expected[200000];

static void ref_combn(int n, int pos, int start, char *cur)
{
    if (pos == n) {
        if (g_expected[0])
            strcat(g_expected, ", ");
        strncat(g_expected, cur, n);
        return;
    }
    for (int d = start; d <= 9; d++) {
        cur[pos] = '0' + d;
        ref_combn(n, pos + 1, d + 1, cur);
    }
}

static char const *expected_combn(int n)
{
    char cur[10];

    g_expected[0] = '\0';
    ref_combn(n, 0, 0, cur);
    return g_expected;
}

static char const *expected_comb2(void)
{
    size_t len = 0;

    for (int a = 0; a <= 98; a++)
        for (int b = a + 1; b <= 99; b++)
            len += sprintf(g_expected + len, "%s%02d %02d",
                len ? ", " : "", a, b);
    return g_expected;
}
