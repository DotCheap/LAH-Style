#include "list_test.h"

void my_rev_list(linked_list_t **begin);

int main(void)
{
    linked_list_t *list = make_list("a", "b", "c", "d", NULL);
    linked_list_t *one = make_list("seul", NULL);
    linked_list_t *empty = NULL;

    my_rev_list(&list);
    CHECK_LIST(list, "d", "c", "b", "a");
    my_rev_list(&one);
    CHECK_LIST(one, "seul");
    my_rev_list(&empty);
    CHECK_EMPTY(empty);
    TEST_END();
}
