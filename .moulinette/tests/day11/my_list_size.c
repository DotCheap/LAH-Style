#include "mouli.h"
#include "list.h"

int my_list_size(linked_list_t const *begin);

int main(void)
{
    CHECK_INT(my_list_size(LIST("a", "b", "c")), 3);
    CHECK_INT(my_list_size(LIST("a")), 1);
    CHECK_INT(my_list_size(NULL), 0);
    return 0;
}
