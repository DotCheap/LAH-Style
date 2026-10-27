#include <stdlib.h>
#include "test.h"

char *concat_params(int argc, char **argv);

int main(void)
{
    char *av1[] = {"./concat_params", "toto", "titi", NULL};
    char *av2[] = {"./a.out", NULL};
    char *av3[] = {"./a.out", "", "fin", NULL};
    char *res = concat_params(3, av1);

    CHECK_STR(res, "./concat_params\ntoto\ntiti");
    free(res);
    res = concat_params(1, av2);
    CHECK_STR(res, "./a.out");
    free(res);
    res = concat_params(3, av3);
    CHECK_STR(res, "./a.out\n\nfin");
    free(res);
    TEST_END();
}
