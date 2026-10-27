#include "mouli.h"
#include "list.h"

linked_list_t *my_params_to_list(int ac, char * const *av);

int main(void)
{
    CASE("my_params_to_list(4, {\"./a.out\", \"test\", \"arg2\", \"arg3\"})") {
        char *av[] = {"./a.out", "test", "arg2", "arg3", 0};
        EXPECT_LIST(my_params_to_list(4, av), "arg3", "arg2", "test", "./a.out");
    }
    CASE("my_params_to_list(1, {\"./a.out\"})") {
        char *av[] = {"./a.out", 0};
        EXPECT_LIST(my_params_to_list(1, av), "./a.out");
    }
    CHECK_INT(my_params_to_list(0, (char *[]){0}) == NULL, 1);
    return 0;
}
