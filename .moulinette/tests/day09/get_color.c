#include "mouli.h"

int get_color(unsigned char red, unsigned char green, unsigned char blue);

int main(void)
{
    CHECK_INT(get_color(0, 0, 0), 0);
    CHECK_INT(get_color(255, 0, 0), 0xFF0000);
    CHECK_INT(get_color(0, 255, 0), 0x00FF00);
    CHECK_INT(get_color(0, 0, 255), 0x0000FF);
    CHECK_INT(get_color(0x12, 0x34, 0x56), 0x123456);
    CHECK_INT(get_color(255, 255, 255), 0xFFFFFF);
    return 0;
}
