"""Day 07 a Day 11 : libmy, allocation, structures, Makefile, listes."""

import re
import shutil

from ..checks import (Day, Task, c_function, compare, fixture, gcc_program,
                      make_project, run_mouli)
from ..core import (CFLAGS, IMPLICIT_SYMBOLS, TESTS_DIR, Check, defined_symbols, first_lines,
                    run, undefined_symbols)

LIBMY_FUNCTIONS = [
    "my_putchar", "my_isneg", "my_put_nbr", "my_swap", "my_putstr",
    "my_strlen", "my_getnbr", "my_sort_int_array", "my_compute_power_rec",
    "my_compute_square_root", "my_is_prime", "my_find_prime_sup",
    "my_strcpy", "my_strncpy", "my_revstr", "my_strstr", "my_strcmp",
    "my_strncmp", "my_strupcase", "my_strlowcase", "my_strcapitalize",
    "my_str_isalpha", "my_str_isnum", "my_str_islower", "my_str_isupper",
    "my_str_isprintable", "my_showstr", "my_showmem", "my_strcat",
    "my_strncat",
]


def func(ident, name, deliveries=None, test=None, **kwargs):
    deliveries = deliveries or [name + ".c"]
    return Task(ident, name, deliveries,
                c_function(test or name + ".c", deliveries, **kwargs))


# ------------------------------------------------------------------ Day 07
def libmy_task(ctx):
    check = Check()
    if not ctx.build_libmy("build.sh"):
        check.fail(ctx.libmy_error)
        return check
    symbols = defined_symbols(ctx.libmy_path())
    missing = [f for f in LIBMY_FUNCTIONS if f not in symbols]
    check.expect(not missing, "fonctions absentes de libmy.a : " + ", ".join(missing))
    if missing:
        return check
    bad = undefined_symbols(ctx.libmy_path()) - symbols - IMPLICIT_SYMBOLS - {"write"}
    check.expect(not bad, "libmy.a utilise des fonctions interdites ou absentes : "
                 + ", ".join(sorted(bad)))
    run_mouli(ctx, "libmy.c", check, link=ctx.libmy_flags())
    return check


def params_program(ident, subdir, transform):
    def func_(ctx):
        check = Check()
        if not ctx.build_libmy(ctx.day.libmy):
            check.fail(ctx.libmy_error)
            return check
        exe = gcc_program(ctx, check, subdir, subdir)
        if exe is None:
            return check
        for args in (["test", "This is a test", "retest"], [],
                     ["zz", "b", "B", "a", "aa", "", "42"]):
            argv = [str(exe)] + args
            expected = "".join(a + "\n" for a in transform(argv))
            proc = run(argv, cwd=ctx.build)
            compare(check, "./%s %s" % (subdir, " ".join(repr(a) for a in args)),
                    proc, out=expected, rc=0)
        return check
    return Task(ident, subdir + "/*.c", [subdir + "/*.c"], func_)


DAY07 = Day("Day 07 - Libmy, arguments", "day07", libmy="build.sh",
            allowed={"write"}, tasks=[
    Task("01", "libmy.a (lib/my/build.sh)", ["lib/my/build.sh"], libmy_task),
    func("02", "my_strcat"),
    func("03", "my_strncat"),
    params_program("04", "task04", lambda av: av),
    params_program("05", "task05", lambda av: av[::-1]),
    params_program("06", "task06", lambda av: sorted(av, key=lambda s: s.encode())),
])

# ------------------------------------------------------------------ Day 08
ALLOC = {"write", "malloc", "free"}

DAY08 = Day("Day 08 - Compilation, Allocation", "day08", libmy="build.sh",
            allowed=ALLOC, tasks=[
    func("01", "my_strdup"),
    func("02", "concat_params"),
    func("03", "my_show_word_array"),
    func("04", "my_str_to_word_array"),
    func("05", "convert_base"),
])

# ------------------------------------------------------------------ Day 09


def macro_abs(ctx):
    check = Check()
    run_mouli(ctx, "my_macro_abs.c", check, includes=["-I", ctx.p("include")])
    return check


def my_h(ctx):
    check = Check()
    header = ctx.p("include/my.h")
    if not ctx.build_libmy("build.sh"):
        check.fail(ctx.libmy_error)
        return check
    text = header.read_text("utf-8", "replace")
    proc = run(["gcc", *CFLAGS, "-fsyntax-only", "-x", "c", header])
    check.expect(proc.rc == 0, "include/my.h ne compile pas : " + first_lines(proc.err))
    proc = run(["gcc", *CFLAGS, "-fsyntax-only", "-x", "c", "-"],
               stdin='#include "my.h"\n#include "my.h"\nint main(void) { return 0; }\n',
               cwd=ctx.p("include"))
    check.expect(proc.rc == 0, "include/my.h ne supporte pas une double inclusion "
                 "(protege-le avec #ifndef MY_H_ ...) : " + first_lines(proc.err))
    exposed = sorted(defined_symbols(ctx.libmy_path()))
    missing = [f for f in exposed if not re.search(r"\b%s\s*\(" % re.escape(f), text)]
    check.expect(not missing, "prototypes absents de my.h pour des fonctions "
                 "exposees par libmy.a : " + ", ".join(missing))
    return check


DAY09 = Day("Day 09 - Structures", "day09", libmy="build.sh",
            allowed=ALLOC, provided_header=TESTS_DIR / "day09/info_param.h", tasks=[
    Task("01", "include/my_macro_abs.h", ["include/my_macro_abs.h"], macro_abs),
    Task("02", "include/my.h", ["include/my.h"], my_h),
    func("03", "my_params_to_array"),
    func("04", "my_show_param_array"),
    func("05", "get_color"),
    func("06", "swap_endian_color"),
])

# ------------------------------------------------------------------ Day 10


def lib_makefile(ctx):
    check = Check()
    libdir = ctx.p("lib/my")
    if not check.expect((libdir / "Makefile").exists(), "lib/my/Makefile introuvable"):
        return check
    for stale in [libdir / "build.sh", ctx.p("lib/libmy.a"), libdir / "libmy.a",
                  ctx.p("include/my.h")]:
        if stale.exists():
            stale.unlink()
    proc = run(["make", "-C", libdir], timeout=180)
    if not check.expect(proc.rc == 0, "make dans lib/my a echoue (build.sh est "
                        "supprime avant) : " + first_lines(proc.out + proc.err)):
        return check
    check.expect(ctx.p("lib/libmy.a").exists(), "le Makefile doit copier libmy.a dans lib/")
    check.expect(ctx.p("include/my.h").exists(), "le Makefile doit copier my.h dans include/")
    if ctx.p("lib/libmy.a").exists():
        missing = [f for f in LIBMY_FUNCTIONS
                   if f not in defined_symbols(ctx.p("lib/libmy.a"))]
        check.expect(not missing, "fonctions absentes de lib/libmy.a : "
                     + ", ".join(missing))
    proc = run(["make", "-n", "clean"], cwd=libdir)
    if check.expect(proc.rc == 0, "la regle `clean` est absente de lib/my/Makefile"):
        run(["make", "clean"], cwd=libdir)
        left = [o.name for o in libdir.glob("*.o")]
        check.expect(not left, "`make clean` doit supprimer les .o de lib/my "
                     "(reste : %s)" % ", ".join(left[:5]))
    return check


DO_OP_CASES = [
    (["1", "+", "1"], "2", 0),
    (["42friends", "-", "---20toto12"], "62", 0),
    (["1", "p", "1"], "0", 84),
    (["1", "+toto", "1"], "2", 0),
    (["1", "+", "toto3"], "1", 0),
    (["toto3", "+", "4"], "4", 0),
    (["foo", "plus", "bar"], "0", 84),
    (["6", "*", "7"], "42", 0),
    (["-7", "/", "2"], "-3", 0),
    (["-7", "%", "3"], "-1", 0),
]


def do_op_cases(check, exe, name, cases):
    for args, out, rc in cases:
        proc = run([exe, *args])
        compare(check, "./%s %s" % (name, " ".join(args)), proc, out=out,
                rc=rc, out_nl=True)
    for args, msg in ((["25", "/", "0"], "Stop: division by zero"),
                      (["25", "%", "0"], "Stop: modulo by zero")):
        proc = run([exe, *args])
        compare(check, "./%s %s" % (name, " ".join(args)), proc, rc=84,
                err_contains=msg)
    for args in ([], ["1", "+"], ["1", "+", "1", "1"]):
        proc = run([exe, *args])
        compare(check, "./%s %s (mauvais nombre d'arguments)" % (name, " ".join(args)),
                proc, out="", rc=84)


def do_op(ctx):
    check = Check()
    if ctx.p("lib/my/Makefile").exists():
        run(["make", "-C", ctx.p("lib/my")], timeout=180)
    exe = make_project(ctx, check, "do_op", "do-op")
    if exe:
        do_op_cases(check, exe, "do-op", DO_OP_CASES)
    return check


def advanced_do_op(ctx):
    check = Check()
    shutil.copy(fixture("my_opp.h"), ctx.p("include/my_opp.h"))
    if ctx.p("lib/my/Makefile").exists():
        run(["make", "-C", ctx.p("lib/my")], timeout=180)
    exe = make_project(ctx, check, "my_advanced_do_op", "my_advanced_do-op")
    if not exe:
        return check
    cases = [c for c in DO_OP_CASES if c[2] == 0 and c[0][1] in "+-*/%"]
    do_op_cases(check, exe, "my_advanced_do-op", cases)
    proc = run([exe, "1", "p", "1"])
    compare(check, "./my_advanced_do-op 1 p 1", proc, rc=84,
            err_contains="error: only [ + - / * % ] are supported")
    return check


DAY10 = Day("Day 10 - Makefile and do-ops", "day10", libmy="make",
            allowed=ALLOC, resources=["resources/*"], tasks=[
    Task("01", "lib/my/Makefile", ["lib/my/Makefile"], lib_makefile),
    Task("02", "do_op/", ["do_op/*"], do_op),
    func("03", "my_sort_word_array"),
    func("04", "my_advanced_sort_word_array"),
    Task("05", "my_advanced_do_op/", ["my_advanced_do_op/*"], advanced_do_op),
])

# ------------------------------------------------------------------ Day 11


def mylist_h(ctx):
    check = Check()
    header = ctx.p("include/mylist.h")
    text = header.read_text("utf-8", "replace")
    proc = run(["gcc", *CFLAGS, "-fsyntax-only", "-x", "c", "-"],
               stdin='#include "mylist.h"\nint main(void) { linked_list_t l; '
                     'l.data = 0; l.next = &l; return 0; }\n',
               cwd=ctx.p("include"))
    check.expect(proc.rc == 0, "include/mylist.h doit definir le type linked_list_t "
                 "(data, next) : " + first_lines(proc.err))
    check.expect("struct linked_list" in text,
                 "include/mylist.h doit definir la structure `struct linked_list`")
    return check


DAY11 = Day("Day 11 - Linked lists", "day11", libmy="make", allowed=ALLOC, tasks=[
    Task("00", "include/mylist.h", ["include/mylist.h"], mylist_h),
    func("01", "my_params_to_list"),
    func("02", "my_list_size"),
    func("03", "my_rev_list"),
    func("04", "my_apply_on_nodes"),
    func("05", "my_apply_on_matching_nodes"),
    func("06", "my_find_node"),
    func("07", "my_delete_nodes"),
    func("08", "my_concat_list"),
    func("09", "my_sort_list"),
    func("10", "my_add_in_sorted_list"),
    func("11", "my_merge"),
])
