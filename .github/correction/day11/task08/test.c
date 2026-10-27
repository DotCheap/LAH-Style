#include "list_test.h"

void my_concat_list(linked_list_t **begin1, linked_list_t *begin2);

int main(void)
{
    linked_list_t *l1 = make_list("a", "b", NULL);
    linked_list_t *l2 = make_list("c", "d", NULL);
    linked_list_t *empty = NULL;
    linked_list_t *l3 = make_list("e", NULL);

    my_concat_list(&l1, l2);
    CHECK_LIST(l1, "a", "b", "c", "d");
    CHECK(l1->next->next == l2);
    my_concat_list(&empty, l3);
    CHECK(empty == l3);
    my_concat_list(&l3, NULL);
    CHECK_LIST(l3, "e");
    TEST_END();
}
