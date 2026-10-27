#include "mouli.h"
#include "list.h"

int my_delete_nodes(linked_list_t **begin, void const *data_ref, int (*cmp)());

int main(void)
{
    CASE("my_delete_nodes(a -> b -> a -> c -> a, \"a\", strcmp)") {
        linked_list_t *list = LIST("a", "b", "a", "c", "a");
        my_delete_nodes(&list, "a", &cmp_str);
        EXPECT_LIST(list, "b", "c");
    }
    CASE("my_delete_nodes(a -> a, \"a\", strcmp)") {
        linked_list_t *list = LIST("a", "a");
        my_delete_nodes(&list, "a", &cmp_str);
        EXPECT(list == NULL);
    }
    CASE("my_delete_nodes(a -> b, \"z\", strcmp)") {
        linked_list_t *list = LIST("a", "b");
        my_delete_nodes(&list, "z", &cmp_str);
        EXPECT_LIST(list, "a", "b");
    }
    return 0;
}
