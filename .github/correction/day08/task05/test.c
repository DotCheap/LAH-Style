#include <stdlib.h>
#include "test.h"

char *convert_base(char const *nbr, char const *base_from, char const *base_to);

#define DEC "0123456789"
#define HEX "0123456789ABCDEF"
#define BIN "01"

static void check_convert(char const *nbr, char const *from, char const *to,
    char const *want, int line)
{
    char *got = convert_base(nbr, from, to);

    if (got == NULL || strcmp(got, want) != 0) {
        fprintf(stderr, "  ligne %d : convert_base(\"%s\") vaut \"%s\", attendu \"%s\"\n",
            line, nbr, got ? got : "(NULL)", want);
        test_failures++;
    }
    free(got);
}

int main(void)
{
    check_convert("255", DEC, HEX, "FF", __LINE__);
    check_convert("-255", DEC, HEX, "-FF", __LINE__);
    check_convert("101", BIN, DEC, "5", __LINE__);
    check_convert("FF", HEX, BIN, "11111111", __LINE__);
    check_convert("0", DEC, BIN, "0", __LINE__);
    check_convert("42", DEC, "poneyvif", "vn", __LINE__);
    check_convert("2147483647", DEC, HEX, "7FFFFFFF", __LINE__);
    check_convert("-2147483648", DEC, HEX, "-80000000", __LINE__);
    TEST_END();
}
