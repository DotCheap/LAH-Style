#define CONV(fn, in, out) CASE(#fn "(\"" in "\")") { \
    char *s = mouli_strdup(in); \
    EXPECT_PTR(fn(s), s); \
    EXPECT_STR(s, out); \
}
