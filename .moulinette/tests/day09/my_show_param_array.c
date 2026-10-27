#include "mouli.h"
#include "info_param.h"

int my_show_param_array(struct info_param const *par);

int main(void)
{
    CASE("my_show_param_array({\"./a.out\", \"hello world\"})") {
        char *w0[] = {"a", "out", 0};
        char *w1[] = {"hello", "world", 0};
        struct info_param par[] = {
            {7, "./a.out", "./a.out", w0},
            {11, "hello world", "hello world", w1},
            {0, 0, 0, 0},
        };
        mouli_capture();
        my_show_param_array(par);
        mouli_expect_out("./a.out\n7\na\nout\nhello world\n11\nhello\nworld\n");
    }
    return 0;
}
