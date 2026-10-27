#include "mouli.h"
#include "list.h"

void my_merge(linked_list_t **begin1, linked_list_t *begin2, int (*cmp)());

int main(void)
{
    CASE("my_merge(a -> c -> e, b -> d -> f, strcmp)") {
        linked_list_t *l1 = LIST("a", "c", "e");
        my_merge(&l1, LIST("b", "d", "f"), &cmp_str);
        EXPECT_LIST(l1, "a", "b", "c", "d", "e", "f");
    }
    CASE("my_merge(c -> d, a -> b -> e, strcmp)") {
        linked_list_t *l1 = LIST("c", "d");
        my_merge(&l1, LIST("a", "b", "e"), &cmp_str);
        EXPECT_LIST(l1, "a", "b", "c", "d", "e");
    }
    CASE("my_merge(liste vide, a -> b, strcmp)") {
        linked_list_t *l1 = NULL;
        my_merge(&l1, LIST("a", "b"), &cmp_str);
        EXPECT_LIST(l1, "a", "b");
    }
    CASE("my_merge(a -> b, NULL, strcmp)") {
        linked_list_t *l1 = LIST("a", "b");
        my_merge(&l1, NULL, &cmp_str);
        EXPECT_LIST(l1, "a", "b");
    }
    return 0;
}
