#include <string.h>
#include "mouli.h"
#include "info_param.h"

struct info_param *my_params_to_array(int ac, char **av);

int main(void)
{
    CASE("my_params_to_array(3, {\"./a.out\", \"hello world\", \"\"})") {
        char *av[] = {"./a.out", "hello world", "", 0};
        struct info_param *p = my_params_to_array(3, av);
        if (p == NULL) {
            mouli_fail("a renvoye NULL");
        } else {
            EXPECT_INT(p[0].length, 7);
            EXPECT(p[0].str == av[0]);
            EXPECT_STR(p[0].copy, "./a.out");
            EXPECT(p[0].copy != av[0]);
            EXPECT_INT(p[1].length, 11);
            EXPECT(p[1].str == av[1]);
            EXPECT_STR(p[1].copy, "hello world");
            EXPECT(p[1].word_array != NULL);
            if (p[1].word_array) {
                EXPECT_STR(p[1].word_array[0], "hello");
                EXPECT_STR(p[1].word_array[1], "world");
                EXPECT(p[1].word_array[2] == NULL);
            }
            EXPECT_INT(p[2].length, 0);
            EXPECT(p[3].str == 0);
        }
    }
    return 0;
}
