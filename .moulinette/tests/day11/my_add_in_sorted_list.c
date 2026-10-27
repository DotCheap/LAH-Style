#include "mouli.h"
#include "list.h"

void my_add_in_sorted_list(linked_list_t **begin, void *data, int (*cmp)());

int main(void)
{
    CASE("my_add_in_sorted_list(a -> c -> e, \"d\", strcmp)") {
        linked_list_t *list = LIST("a", "c", "e");
        my_add_in_sorted_list(&list, "d", &cmp_str);
        EXPECT_LIST(list, "a", "c", "d", "e");
    }
    CASE("my_add_in_sorted_list(b -> c, \"a\", strcmp) (en tete)") {
        linked_list_t *list = LIST("b", "c");
        my_add_in_sorted_list(&list, "a", &cmp_str);
        EXPECT_LIST(list, "a", "b", "c");
    }
    CASE("my_add_in_sorted_list(a -> b, \"z\", strcmp) (en fin)") {
        linked_list_t *list = LIST("a", "b");
        my_add_in_sorted_list(&list, "z", &cmp_str);
        EXPECT_LIST(list, "a", "b", "z");
    }
    CASE("my_add_in_sorted_list(liste vide, \"a\", strcmp)") {
        linked_list_t *list = NULL;
        my_add_in_sorted_list(&list, "a", &cmp_str);
        EXPECT_LIST(list, "a");
    }
    return 0;
}
