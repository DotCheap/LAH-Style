#include "list_test.h"

int my_delete_nodes(linked_list_t **begin, void const *data_ref, int (*cmp)());

int main(void)
{
    linked_list_t *list = make_list("a", "a", "b", "a", "c", "a", NULL);
    linked_list_t *all = make_list("x", "x", NULL);
    linked_list_t *empty = NULL;

    my_delete_nodes(&list, "a", &strcmp);
    CHECK_LIST(list, "b", "c");
    my_delete_nodes(&list, "z", &strcmp);
    CHECK_LIST(list, "b", "c");
    my_delete_nodes(&all, "x", &strcmp);
    CHECK_EMPTY(all);
    my_delete_nodes(&empty, "x", &strcmp);
    CHECK_EMPTY(empty);
    TEST_END();
}
