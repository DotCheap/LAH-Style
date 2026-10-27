#include "list_test.h"

void my_merge(linked_list_t **begin1, linked_list_t *begin2, int (*cmp)());

int main(void)
{
    linked_list_t *l1 = make_list("a", "c", "e", NULL);
    linked_list_t *l2 = make_list("b", "c", "d", "f", NULL);
    linked_list_t *empty = NULL;
    linked_list_t *l3 = make_list("x", NULL);

    my_merge(&l1, l2, &strcmp);
    CHECK_LIST(l1, "a", "b", "c", "c", "d", "e", "f");
    my_merge(&empty, make_list("y", "z", NULL), &strcmp);
    CHECK_LIST(empty, "y", "z");
    my_merge(&l3, NULL, &strcmp);
    CHECK_LIST(l3, "x");
    TEST_END();
}
