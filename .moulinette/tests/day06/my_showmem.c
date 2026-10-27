#include "mouli.h"

int my_showmem(char const *str, int size);

static char const DATA[] = "hey guys show mem is cool you can do some pretty "
    "neat stuff\0\017\033\177\005.\0\001\002\003\004\005\006\007\010\t\016"
    "\017\033\177";

static char const EXPECTED[] =
"00000000: 6865 7920 6775 7973 2073 686f 7720 6d65 hey guys show me\n"
"00000010: 6d20 6973 2063 6f6f 6c20 796f 7520 6361 m is cool you ca\n"
"00000020: 6e20 646f 2073 6f6d 6520 7072 6574 7479 n do some pretty\n"
"00000030: 206e 6561 7420 7374 7566 6600 0f1b 7f05  neat stuff.....\n"
"00000040: 2e00 0102 0304 0506 0708 090e 0f1b 7f ...............\n";

int main(void)
{
    CASE("my_showmem(str, 79) (exemple du sujet, espaces normalises)") {
        mouli_capture();
        EXPECT_INT(my_showmem(DATA, 79), 0);
        mouli_expect_out_ws(EXPECTED);
    }
    CASE("my_showmem(\"abc\", 3) (espaces normalises)") {
        mouli_capture();
        my_showmem("abc", 3);
        mouli_expect_out_ws("00000000: 6162 63 abc\n");
    }
    return 0;
}
