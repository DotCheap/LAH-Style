#include "mouli.h"

int swap_endian_color(int color);

int main(void)
{
    CHECK_INT(swap_endian_color(0x11223344), 0x44332211);
    CHECK_INT(swap_endian_color(0x44332211), 0x11223344);
    CHECK_INT(swap_endian_color(0), 0);
    CHECK_INT(swap_endian_color(0x000000FF), (int)0xFF000000);
    CHECK_INT(swap_endian_color((int)0xFF00FF00), 0x00FF00FF);
    return 0;
}
