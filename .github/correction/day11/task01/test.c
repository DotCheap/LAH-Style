#include "list_test.h"

linked_list_t *my_params_to_list(int ac, char * const *av);

int main(void)
{
    char *av[] = {"./a.out", "test", "arg2", "arg3", NULL};
    char *one[] = {"./a.out", NULL};

    CHECK_LIST(my_params_to_list(4, av), "arg3", "arg2", "test", "./a.out");
    CHECK_LIST(my_params_to_list(1, one), "./a.out");
    CHECK_EMPTY(my_params_to_list(0, av));
    TEST_END();
}
