#include "list_test.h"

int my_list_size(linked_list_t const *begin);

int main(void)
{
    CHECK_INT(my_list_size(NULL), 0);
    CHECK_INT(my_list_size(make_list("a", NULL)), 1);
    CHECK_INT(my_list_size(make_list("a", "b", "c", "d", NULL)), 4);
    TEST_END();
}
