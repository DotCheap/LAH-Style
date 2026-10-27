#include "mouli.h"

void my_sort_int_array(int *array, int size);

static void check_sorted(int *tab, int const *exp, int size)
{
    for (int i = 0; i < size; i++)
        if (tab[i] != exp[i]) {
            mouli_fail("case %d : attendu %d, obtenu %d", i, exp[i], tab[i]);
            return;
        }
}

int main(void)
{
    CASE("my_sort_int_array({5, 3, -2, 8, 0, 3}, 6)") {
        int tab[] = {5, 3, -2, 8, 0, 3};
        int exp[] = {-2, 0, 3, 3, 5, 8};
        my_sort_int_array(tab, 6);
        check_sorted(tab, exp, 6);
    }
    CASE("my_sort_int_array sur un tableau deja trie") {
        int tab[] = {1, 2, 3, 4};
        int exp[] = {1, 2, 3, 4};
        my_sort_int_array(tab, 4);
        check_sorted(tab, exp, 4);
    }
    CASE("my_sort_int_array sur un tableau trie a l'envers") {
        int tab[] = {9, 7, 5, 3, 1, -1, -2147483647 - 1};
        int exp[] = {-2147483647 - 1, -1, 1, 3, 5, 7, 9};
        my_sort_int_array(tab, 7);
        check_sorted(tab, exp, 7);
    }
    CASE("my_sort_int_array ne doit trier que les size premieres cases") {
        int tab[] = {3, 2, 1, 0};
        int exp[] = {2, 3, 1, 0};
        my_sort_int_array(tab, 2);
        check_sorted(tab, exp, 4);
    }
    CASE("my_sort_int_array avec size = 1 et size = 0") {
        int tab[] = {4, 2};
        my_sort_int_array(tab, 1);
        my_sort_int_array(tab, 0);
        EXPECT_INT(tab[0], 4);
        EXPECT_INT(tab[1], 2);
    }
    CASE("my_sort_int_array sur 2000 elements") {
        int tab[2000];
        int ok = 1;
        for (int i = 0; i < 2000; i++)
            tab[i] = (i * 7919) % 2000 - 1000;
        my_sort_int_array(tab, 2000);
        for (int i = 1; i < 2000; i++)
            ok = ok && tab[i - 1] <= tab[i];
        EXPECT(ok);
    }
    return 0;
}
