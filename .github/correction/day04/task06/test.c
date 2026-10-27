#include <limits.h>
#include "test.h"

void my_sort_int_array(int *array, int size);

static void check_sorted(int *got, int const *want, int size, int line)
{
    for (int i = 0; i < size; i++) {
        if (got[i] != want[i]) {
            fprintf(stderr, "  ligne %d : case %d vaut %d, attendu %d\n",
                line, i, got[i], want[i]);
            test_failures++;
            return;
        }
    }
}

int main(void)
{
    int a[] = {5, 3, 8, 1, 9, 2};
    int const a_ok[] = {1, 2, 3, 5, 8, 9};
    int b[] = {4, -1, 4, 0, -1, 4};
    int const b_ok[] = {-1, -1, 0, 4, 4, 4};
    int c[] = {INT_MAX, 0, INT_MIN, -5, 5};
    int const c_ok[] = {INT_MIN, -5, 0, 5, INT_MAX};
    int d[] = {1, 2, 3, 4};
    int const d_ok[] = {1, 2, 3, 4};
    int e[] = {9, 7, 5, 3, 1, 0};
    int const e_ok[] = {0, 1, 3, 5, 7, 9};
    int f[] = {42};
    int const f_ok[] = {42};
    int g[] = {3, 2, 1};
    int const g_ok[] = {3, 2, 1};

    my_sort_int_array(a, 6);
    check_sorted(a, a_ok, 6, __LINE__);
    my_sort_int_array(b, 6);
    check_sorted(b, b_ok, 6, __LINE__);
    my_sort_int_array(c, 5);
    check_sorted(c, c_ok, 5, __LINE__);
    my_sort_int_array(d, 4);
    check_sorted(d, d_ok, 4, __LINE__);
    my_sort_int_array(e, 6);
    check_sorted(e, e_ok, 6, __LINE__);
    my_sort_int_array(f, 1);
    check_sorted(f, f_ok, 1, __LINE__);
    my_sort_int_array(g, 0);
    check_sorted(g, g_ok, 3, __LINE__);
    TEST_END();
}
