#include "list_test.h"

int my_apply_on_nodes(linked_list_t *begin, int (*f)(void *));

static char const *seen[16];
static int nb_seen = 0;

static int record(void *data)
{
    if (nb_seen < 16)
        seen[nb_seen] = data;
    nb_seen++;
    return 0;
}

int main(void)
{
    my_apply_on_nodes(make_list("a", "b", "c", NULL), &record);
    CHECK_INT(nb_seen, 3);
    CHECK_STR(seen[0], "a");
    CHECK_STR(seen[1], "b");
    CHECK_STR(seen[2], "c");
    nb_seen = 0;
    my_apply_on_nodes(NULL, &record);
    CHECK_INT(nb_seen, 0);
    TEST_END();
}
