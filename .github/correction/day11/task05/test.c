#include "list_test.h"

int my_apply_on_matching_nodes(linked_list_t *begin, int (*f)(),
    void const *data_ref, int (*cmp)());

static void *seen[16];
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
    linked_list_t *list = make_list("a", "b", "a", "c", "a", NULL);

    my_apply_on_matching_nodes(list, &record, "a", &strcmp);
    CHECK_INT(nb_seen, 3);
    CHECK(seen[0] == list->data);
    CHECK(seen[1] == list->next->next->data);
    nb_seen = 0;
    my_apply_on_matching_nodes(list, &record, "z", &strcmp);
    CHECK_INT(nb_seen, 0);
    my_apply_on_matching_nodes(NULL, &record, "a", &strcmp);
    CHECK_INT(nb_seen, 0);
    TEST_END();
}
