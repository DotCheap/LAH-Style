"""Day 03 a Day 06 : premieres fonctions en C."""

from ..checks import Day, Task, c_function, unit_tests
from ..core import CFLAGS, LIB_DIR, Check, defined_symbols, first_lines, run


def func(ident, name, deliveries=None, test=None, **kwargs):
    deliveries = deliveries or [name + ".c"]
    return Task(ident, name, deliveries,
                c_function(test or name + ".c", deliveries, **kwargs))


def tests_my_put_nbr(ctx):
    """Day03 task08 : un main de test pour my_put_nbr."""
    check = Check()
    test = ctx.p("tests/tests_my_put_nbr.c")
    if not check.expect(test.is_file(), "tests/tests_my_put_nbr.c introuvable"):
        return check
    if not check.expect(ctx.exists("my_put_nbr.c"),
                        "my_put_nbr.c est necessaire pour compiler les tests"):
        return check
    exe = ctx.build / "tests_my_put_nbr"
    proc = run(["gcc", *CFLAGS, test, ctx.p("my_put_nbr.c"),
                LIB_DIR / "my_putchar.c", "-o", exe], cwd=ctx.work)
    if not check.expect(proc.rc == 0, "tests/tests_my_put_nbr.c ne compile pas "
                        "avec my_put_nbr.c : " + first_lines(proc.err)):
        return check
    check.expect("main" in defined_symbols(exe), "le fichier doit contenir un main")
    calls = test.read_text("utf-8", "replace").count("my_put_nbr(")
    check.expect(calls >= 4, "seulement %d appel(s) a my_put_nbr : couvre aussi "
                 "0, les negatifs, INT_MAX et INT_MIN" % calls)
    proc = run([exe], cwd=ctx.work, timeout=5)
    check.expect(proc.rc >= 0 and not proc.timeout,
                 "l'execution des tests plante (signal %d)" % -proc.rc)
    return check


DAY03 = Day("Day 03 - First C Programming", "day03", putchar=True,
            resources=["others/*"], tasks=[
    func("01", "my_print_alpha"),
    func("02", "my_print_revalpha"),
    func("03", "my_print_digits"),
    func("04", "my_isneg"),
    func("05", "my_print_comb"),
    func("06", "my_print_comb2"),
    func("07", "my_put_nbr"),
    Task("08", "tests/tests_my_put_nbr.c", ["tests/tests_my_put_nbr.c"],
         tests_my_put_nbr),
    func("09", "my_print_combn"),
])

DAY04 = Day("Day 04 - Pointers", "day04", putchar=True, tasks=[
    func("01", "my_swap"),
    func("02", "my_putstr"),
    func("03", "my_strlen"),
    func("04", "my_evil_str"),
    func("05", "my_getnbr"),
    func("06", "my_sort_int_array"),
])

DAY05 = Day("Day 05 - Recursivity", "day05", putchar=True, tasks=[
    func("01", "my_compute_factorial_it"),
    func("02", "my_compute_factorial_rec"),
    func("03", "my_compute_power_it"),
    func("04", "my_compute_power_rec"),
    func("05", "my_compute_square_root"),
    func("06", "my_is_prime"),
    func("07", "my_find_prime_sup"),
    func("08", "count_valid_queens_placements"),
])


def criterion(ident, name, functions, line_min, branch_min):
    tests = ["tests/test_%s.c" % f for f in functions]
    return Task(ident, name, tests, unit_tests(tests, functions, line_min, branch_min))


DAY06 = Day("Day 06 - Pointers are back", "day06", putchar=True, tasks=[
    func("01", "my_strcpy"),
    func("02", "my_strncpy"),
    func("03", "my_revstr"),
    criterion("04", "unit tests - part I", ["my_strncpy", "my_revstr"], 60, 40),
    func("05", "my_strstr"),
    func("06", "my_strcmp"),
    func("07", "my_strncmp"),
    func("08", "my_strupcase"),
    func("09", "my_strlowcase"),
    func("10", "my_strcapitalize"),
    criterion("11", "unit tests - part II",
              ["my_strstr", "my_strncmp", "my_strcapitalize"], 80, 60),
    func("12", "my_str_isalpha"),
    func("13", "my_str_isnum"),
    func("14", "my_str_islower"),
    func("15", "my_str_isupper"),
    func("16", "my_str_isprintable"),
    criterion("17", "unit tests - part III",
              ["my_str_isalpha", "my_str_islower", "my_str_isprintable"], 100, 80),
    func("18", "my_putnbr_base"),
    func("19", "my_getnbr_base"),
    func("20", "my_showstr"),
    func("21", "my_showmem"),
])
