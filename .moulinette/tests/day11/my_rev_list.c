#include "mouli.h"
#include "list.h"

void my_rev_list(linked_list_t **begin);

int main(void)
{
    CASE("my_rev_list(a -> b -> c)") {
        linked_list_t *list = LIST("a", "b", "c");
        my_rev_list(&list);
        EXPECT_LIST(list, "c", "b", "a");
    }
    CASE("my_rev_list(a)") {
        linked_list_t *list = LIST("a");
        my_rev_list(&list);
        EXPECT_LIST(list, "a");
    }
    CASE("my_rev_list(liste vide)") {
        linked_list_t *list = NULL;
        my_rev_list(&list);
        EXPECT(list == NULL);
    }
    return 0;
}
