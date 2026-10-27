#include "mouli.h"

void my_putchar(char c);
int my_isneg(int nb);
int my_put_nbr(int nb);
void my_swap(int *a, int *b);
int my_putstr(char const *str);
int my_strlen(char const *str);
int my_getnbr(char const *str);
void my_sort_int_array(int *tab, int size);
int my_compute_power_rec(int nb, int power);
int my_compute_square_root(int nb);
int my_is_prime(int nb);
int my_find_prime_sup(int nb);
char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, int n);
char *my_revstr(char *str);
char *my_strstr(char *str, char const *to_find);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strupcase(char *str);
char *my_strlowcase(char *str);
char *my_strcapitalize(char *str);
int my_str_isalpha(char const *str);
int my_str_isnum(char const *str);
int my_str_islower(char const *str);
int my_str_isupper(char const *str);
int my_str_isprintable(char const *str);
int my_showstr(char const *str);
int my_showmem(char const *str, int size);
char *my_strcat(char *dest, char const *src);
char *my_strncat(char *dest, char const *src, int nb);

int main(void)
{
    CHECK_OUT(my_putchar('k'), "k");
    CHECK_OUT(my_isneg(-3), "N");
    CHECK_OUT(my_put_nbr(-2147483647 - 1), "-2147483648");
    CASE("my_swap") {
        int a = 1;
        int b = 2;
        my_swap(&a, &b);
        EXPECT(a == 2 && b == 1);
    }
    CHECK_OUT(my_putstr("libmy"), "libmy");
    CHECK_INT(my_strlen("libmy"), 5);
    CHECK_INT(my_getnbr("-+-42"), 42);
    CASE("my_sort_int_array") {
        int tab[] = {3, 1, 2};
        my_sort_int_array(tab, 3);
        EXPECT(tab[0] == 1 && tab[1] == 2 && tab[2] == 3);
    }
    CHECK_INT(my_compute_power_rec(2, 8), 256);
    CHECK_INT(my_compute_square_root(81), 9);
    CHECK_INT(my_is_prime(13), 1);
    CHECK_INT(my_find_prime_sup(14), 17);
    CASE("my_strcpy / my_strncpy") {
        char buf[16];
        EXPECT_STR(my_strcpy(buf, "hello"), "hello");
        EXPECT_STR(my_strncpy(buf, "abc", 4), "abc");
    }
    CASE("my_revstr") {
        char *s = mouli_strdup("abc");
        EXPECT_STR(my_revstr(s), "cba");
    }
    CASE("my_strstr") {
        char *s = mouli_strdup("hello world");
        EXPECT_PTR(my_strstr(s, "wor"), s + 6);
    }
    CHECK_SIGN(my_strcmp("abc", "abd"), -1);
    CHECK_SIGN(my_strncmp("abc", "abd", 2), 0);
    CASE("my_strupcase / my_strlowcase / my_strcapitalize") {
        EXPECT_STR(my_strupcase(mouli_strdup("abC1")), "ABC1");
        EXPECT_STR(my_strlowcase(mouli_strdup("AbC1")), "abc1");
        EXPECT_STR(my_strcapitalize(mouli_strdup("hello wORLD")), "Hello World");
    }
    CHECK_INT(my_str_isalpha("abc1"), 0);
    CHECK_INT(my_str_isnum("123"), 1);
    CHECK_INT(my_str_islower("abc"), 1);
    CHECK_INT(my_str_isupper("ABc"), 0);
    CHECK_INT(my_str_isprintable("ab\n"), 0);
    CHECK_OUT(my_showstr("a\tb"), "a\\09b");
    CASE("my_showmem(\"abc\", 3)") {
        mouli_capture();
        my_showmem("abc", 3);
        mouli_expect_out_ws("00000000: 6162 63 abc\n");
    }
    CASE("my_strcat / my_strncat") {
        char buf[32] = "Hello";
        EXPECT_STR(my_strcat(buf, " World"), "Hello World");
        EXPECT_STR(my_strncat(buf, "!!!", 1), "Hello World!");
    }
    return 0;
}
