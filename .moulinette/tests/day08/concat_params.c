#include "mouli.h"

char *concat_params(int argc, char **argv);

int main(void)
{
    CASE("concat_params(3, {\"./concat_params\", \"toto\", \"titi\"})") {
        char *av[] = {"./concat_params", "toto", "titi", 0};
        EXPECT_STR(concat_params(3, av), "./concat_params\ntoto\ntiti");
    }
    CASE("concat_params(1, {\"./a.out\"})") {
        char *av[] = {"./a.out", 0};
        EXPECT_STR(concat_params(1, av), "./a.out");
    }
    CASE("concat_params(4, {\"a\", \"\", \"This is\", \"c\"})") {
        char *av[] = {"a", "", "This is", "c", 0};
        EXPECT_STR(concat_params(4, av), "a\n\nThis is\nc");
    }
    return 0;
}
