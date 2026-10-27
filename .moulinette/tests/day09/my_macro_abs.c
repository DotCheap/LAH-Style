#include "mouli.h"
#include "my_macro_abs.h"

int main(void)
{
    CHECK_INT(ABS(-5), 5);
    CHECK_INT(ABS(5), 5);
    CHECK_INT(ABS(0), 0);
    CHECK_INT(ABS(1 - 4), 3);
    CHECK_INT(ABS(-2) * 2, 4);
    CHECK_INT(10 - ABS(-3), 7);
    CASE("ABS(x) avec x = -2") {
        int x = -2;
        EXPECT(ABS(x) == 2);
    }
    return 0;
}
