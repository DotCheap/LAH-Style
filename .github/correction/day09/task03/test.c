#include <stdlib.h>
#include "test.h"
#include "info_param.h"

struct info_param *my_params_to_array(int ac, char **av);

int main(void)
{
    char *av[] = {"./a.out", "hello world", "42-fifty", NULL};
    char const *words[][3] = {{"a", "out", NULL}, {"hello", "world", NULL},
        {"42", "fifty", NULL}};
    struct info_param *res = my_params_to_array(3, av);

    if (res == NULL) {
        fprintf(stderr, "  my_params_to_array a renvoyé NULL\n");
        return 1;
    }
    for (int i = 0; i < 3; i++) {
        CHECK_INT(res[i].length, (int)strlen(av[i]));
        CHECK(res[i].str == av[i]);
        CHECK(res[i].copy != av[i]);
        CHECK_STR(res[i].copy, av[i]);
        CHECK(res[i].word_array != NULL);
        if (res[i].word_array == NULL)
            continue;
        for (int j = 0; words[i][j] != NULL; j++)
            CHECK_STR(res[i].word_array[j], words[i][j]);
    }
    CHECK(res[3].str == NULL);
    TEST_END();
}
