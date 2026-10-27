#include "mouli.h"
#include "list.h"

void my_concat_list(linked_list_t **begin1, linked_list_t *begin2);

int main(void)
{
    CASE("my_concat_list(a -> b, c -> d)") {
        linked_list_t *l1 = LIST("a", "b");
        linked_list_t *l2 = LIST("c", "d");
        my_concat_list(&l1, l2);
        EXPECT_LIST(l1, "a", "b", "c", "d");
        EXPECT(l1->next->next == l2);
    }
    CASE("my_concat_list(liste vide, c)") {
        linked_list_t *l1 = NULL;
        linked_list_t *l2 = LIST("c");
        my_concat_list(&l1, l2);
        EXPECT(l1 == l2);
    }
    return 0;
}
