#include "mouli.h"
#include "list.h"

int my_apply_on_nodes(linked_list_t *begin, int (*f)(void *));

static char g_seen[64];

static int record(void *data)
{
    strcat(g_seen, data);
    return 0;
}

int main(void)
{
    CASE("my_apply_on_nodes(a -> b -> c, f)") {
        g_seen[0] = '\0';
        my_apply_on_nodes(LIST("a", "b", "c"), &record);
        EXPECT_STR(g_seen, "abc");
    }
    CASE("my_apply_on_nodes(liste vide, f)") {
        g_seen[0] = '\0';
        my_apply_on_nodes(NULL, &record);
        EXPECT_STR(g_seen, "");
    }
    return 0;
}
