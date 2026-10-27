#include "list_test.h"

void my_add_in_sorted_list(linked_list_t **begin, void *data, int (*cmp)());

int main(void)
{
    linked_list_t *list = make_list("b", "d", NULL);
    linked_list_t *empty = NULL;

    my_add_in_sorted_list(&list, "c", &strcmp);
    CHECK_LIST(list, "b", "c", "d");
    my_add_in_sorted_list(&list, "a", &strcmp);
    CHECK_LIST(list, "a", "b", "c", "d");
    my_add_in_sorted_list(&list, "e", &strcmp);
    CHECK_LIST(list, "a", "b", "c", "d", "e");
    my_add_in_sorted_list(&empty, "x", &strcmp);
    CHECK_LIST(empty, "x");
    TEST_END();
}
