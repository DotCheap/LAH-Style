#include "test.h"

void star(unsigned int size);

int main(void)
{
    unsigned int sizes[] = {0, 1, 2, 3, 4, 5, 8};
    char buf[32];
    int len;

    for (size_t i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++) {
        len = snprintf(buf, sizeof(buf), "== star(%u) ==\n", sizes[i]);
        write(1, buf, len);
        star(sizes[i]);
    }
    TEST_END();
}
