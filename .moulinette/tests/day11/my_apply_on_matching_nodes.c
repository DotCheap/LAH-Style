#include "mouli.h"
#include "list.h"

int my_apply_on_matching_nodes(linked_list_t *begin, int (*f)(),
    void const *data_ref, int (*cmp)());

static int g_calls = 0;

static int count(void *data)
{
    (void)data;
    g_calls++;
    return 0;
}

int main(void)
{
    CASE("my_apply_on_matching_nodes(a -> b -> a -> c, f, \"a\", strcmp)") {
        my_apply_on_matching_nodes(LIST("a", "b", "a", "c"), &count, "a", &cmp_str);
        EXPECT_INT(g_calls, 2);
    }
    CASE("my_apply_on_matching_nodes(a -> b, f, \"z\", strcmp)") {
        g_calls = 0;
        my_apply_on_matching_nodes(LIST("a", "b"), &count, "z", &cmp_str);
        EXPECT_INT(g_calls, 0);
    }
    return 0;
}
