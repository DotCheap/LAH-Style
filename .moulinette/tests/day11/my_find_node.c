#include "mouli.h"
#include "list.h"

linked_list_t *my_find_node(linked_list_t const *begin, void const *data_ref,
    int (*cmp)());

int main(void)
{
    CASE("my_find_node(a -> b -> c -> b, \"b\", strcmp)") {
        linked_list_t *list = LIST("a", "b", "c", "b");
        EXPECT(my_find_node(list, "b", &cmp_str) == list->next);
    }
    CASE("my_find_node(a -> b, \"z\", strcmp)") {
        EXPECT(my_find_node(LIST("a", "b"), "z", &cmp_str) == NULL);
    }
    CASE("my_find_node(liste vide, \"a\", strcmp)") {
        EXPECT(my_find_node(NULL, "a", &cmp_str) == NULL);
    }
    return 0;
}
