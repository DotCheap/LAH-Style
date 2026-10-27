#include "mouli.h"
#include "list.h"

void my_sort_list(linked_list_t **begin, int (*cmp)());

int main(void)
{
    CASE("my_sort_list(d -> b -> a -> c -> b, strcmp)") {
        linked_list_t *list = LIST("d", "b", "a", "c", "b");
        my_sort_list(&list, &cmp_str);
        EXPECT_LIST(list, "a", "b", "b", "c", "d");
    }
    CASE("my_sort_list(a, strcmp)") {
        linked_list_t *list = LIST("a");
        my_sort_list(&list, &cmp_str);
        EXPECT_LIST(list, "a");
    }
    CASE("my_sort_list(liste vide, strcmp)") {
        linked_list_t *list = NULL;
        my_sort_list(&list, &cmp_str);
        EXPECT(list == NULL);
    }
    return 0;
}
