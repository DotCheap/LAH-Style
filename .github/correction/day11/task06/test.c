#include "list_test.h"

linked_list_t *my_find_node(linked_list_t const *begin, void const *data_ref,
    int (*cmp)());

int main(void)
{
    linked_list_t *list = make_list("a", "b", "c", "b", NULL);

    CHECK(my_find_node(list, "a", &strcmp) == list);
    CHECK(my_find_node(list, "b", &strcmp) == list->next);
    CHECK(my_find_node(list, "c", &strcmp) == list->next->next);
    CHECK(my_find_node(list, "z", &strcmp) == NULL);
    CHECK(my_find_node(NULL, "a", &strcmp) == NULL);
    TEST_END();
}
