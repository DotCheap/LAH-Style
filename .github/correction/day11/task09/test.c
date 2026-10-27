#include "list_test.h"

void my_sort_list(linked_list_t **begin, int (*cmp)());

int main(void)
{
    linked_list_t *list = make_list("d", "b", "e", "a", "c", "b", NULL);
    linked_list_t *one = make_list("x", NULL);
    linked_list_t *empty = NULL;

    my_sort_list(&list, &strcmp);
    CHECK_LIST(list, "a", "b", "b", "c", "d", "e");
    my_sort_list(&one, &strcmp);
    CHECK_LIST(one, "x");
    my_sort_list(&empty, &strcmp);
    CHECK_EMPTY(empty);
    TEST_END();
}
