#include "test.h"
#include "info_param.h"

int my_show_param_array(struct info_param const *par);

int main(void)
{
    char *w1[] = {"a", "out", NULL};
    char *w2[] = {"hello", "world", NULL};
    char s1[] = "./a.out";
    char s2[] = "hello world";
    struct info_param par[] = {
        {7, s1, s1, w1},
        {11, s2, s2, w2},
        {0, NULL, NULL, NULL},
    };

    my_show_param_array(par);
    TEST_END();
}
