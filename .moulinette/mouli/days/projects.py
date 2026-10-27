"""Day 12, Day 13, rushs et projets (Star, CountIsland, partie 2)."""

import random
import re
from pathlib import Path

from ..checks import (Day, Task, compare, criterion_available, make_project)
from ..core import (CFLAGS, IMPLICIT_SYMBOLS, LIB_DIR, TESTS_DIR, Check,
                    defined_symbols, first_lines, libc_symbols, run, show,
                    undefined_symbols)
from ..shapes import count_island, rush1, rush3_answer, star

# Symboles ajoutes par l'editeur de liens dans tout executable.
STARTUP = {"__libc_start_main", "__cxa_finalize", "__gmon_start__",
           "_ITM_deregisterTMCloneTable", "_ITM_registerTMCloneTable",
           "__errno_location", *IMPLICIT_SYMBOLS}


def binary_forbidden(check, exe, allowed, label):
    """Fonctions de la libc utilisees par un binaire en dehors de celles
    autorisees par le sujet."""
    used = undefined_symbols(exe) & libc_symbols()
    bad = used - set(allowed) - STARTUP
    check.expect(not bad, "%s utilise des fonctions interdites : %s"
                 % (label, ", ".join(sorted(bad))))


def compile_objects(ctx, check, folder):
    """Compile chaque .c d'un dossier separement. Renvoie {nom: .o}."""
    objdir = ctx.build / ("obj_" + (folder.name or "root"))
    objdir.mkdir(exist_ok=True)
    objects = {}
    for source in sorted(folder.glob("*.c")):
        obj = objdir / (source.stem + ".o")
        proc = run(["gcc", *CFLAGS, "-c", source, "-o", obj, *ctx.include_flags()],
                   cwd=folder, timeout=60)
        if proc.rc != 0:
            check.fail("%s ne compile pas : %s" % (source.name, first_lines(proc.err, 3)))
            return None
        objects[source.name] = obj
    return objects


def forbid_definitions(check, objects, names, why):
    for name, obj in objects.items():
        found = defined_symbols(obj) & set(names)
        for symbol in sorted(found):
            check.fail("%s definit %s : %s" % (name, symbol, why))


# ------------------------------------------------------------------ Day 12
def write_inputs(folder):
    folder.mkdir(exist_ok=True)
    random.seed(42)
    files = {
        "small.txt": b"Hello World\nThis is a small file.\n",
        "empty.txt": b"",
        "nonl.txt": b"no newline at the end",
        "big.bin": bytes(random.randrange(256) for _ in range(100000)),
        "lines.txt": "".join("line %d: looneytunes %s\n" % (i, "http" * (i % 3))
                             for i in range(3000)).encode(),
    }
    for name, data in files.items():
        (folder / name).write_bytes(data)
    return files


def cat_task(ctx):
    check = Check()
    exe = make_project(ctx, check, "cat", "cat")
    if not exe:
        return check
    binary_forbidden(check, exe, {"open", "read", "write", "close"}, "cat")
    files = write_inputs(ctx.build / "inputs")
    cwd = ctx.build / "inputs"
    for args in (["small.txt"], ["small.txt", "nonl.txt", "small.txt"],
                 ["empty.txt"], ["big.bin"], ["lines.txt", "big.bin"]):
        expected = b"".join(files[a] for a in args)
        proc = run([exe, *args], cwd=cwd)
        ok = proc.out == expected and proc.rc == 0
        check.expect(ok, "./cat %s : sortie differente de celle de cat (%d octets "
                     "attendus, %d obtenus, code %d)"
                     % (" ".join(args), len(expected), len(proc.out), proc.rc))
    proc = run([exe], cwd=cwd, stdin=files["lines.txt"])
    check.expect(proc.out == files["lines.txt"],
                 "./cat sans argument doit lire l'entree standard")
    proc = run([exe, "small.txt", "doesnt_exist", "nonl.txt"], cwd=cwd)
    compare(check, "./cat small.txt doesnt_exist nonl.txt", proc, rc=84,
            err_contains="No such file or directory")
    check.expect(proc.out == files["small.txt"] + files["nonl.txt"],
                 "./cat doit continuer avec les fichiers suivants apres une erreur")
    return check


def grep_expected(pattern, names, files):
    out = []
    for name in names:
        for line in files[name].decode("latin-1").splitlines():
            if pattern in line:
                out.append((name + ":" if len(names) > 1 else "") + line + "\n")
    return "".join(out)


def grep_task(ctx):
    check = Check()
    exe = make_project(ctx, check, "grep", "grep")
    if not exe:
        return check
    binary_forbidden(check, exe, {"open", "read", "write", "close", "malloc", "free"},
                     "grep")
    files = write_inputs(ctx.build / "inputs")
    cwd = ctx.build / "inputs"
    for pattern, names in (("World", ["small.txt"]), ("line 299", ["lines.txt"]),
                           ("http", ["small.txt", "lines.txt"]),
                           ("absent", ["small.txt"]), ("end", ["nonl.txt"])):
        proc = run([exe, pattern, *names], cwd=cwd)
        compare(check, "./grep %s %s" % (pattern, " ".join(names)), proc,
                out=grep_expected(pattern, names, files))
    proc = run([exe, "line 1"], cwd=cwd, stdin=files["lines.txt"])
    expected = "".join(l + "\n" for l in files["lines.txt"].decode().splitlines()
                       if "line 1" in l)
    compare(check, "cat lines.txt | ./grep \"line 1\"", proc, out=expected)
    proc = run([exe, "http", "/doesnt_exist"], cwd=cwd)
    compare(check, "./grep http /doesnt_exist", proc, rc=84,
            err_contains="No such file or directory")
    return check


def tests_run(subdir):
    def func(ctx):
        check = Check()
        tests = list(ctx.p("tests").glob("*.c")) if ctx.p("tests").is_dir() else []
        if not check.expect(tests, "aucun fichier .c dans tests/ (a la racine)"):
            return check
        if not (ctx.p(subdir) / "Makefile").exists():
            check.fail("pas de Makefile dans %s/" % subdir)
            return check
        if not criterion_available():
            check.skip("Criterion n'est pas installe sur cette machine")
            return check
        proc = run(["make", "tests_run"], cwd=ctx.p(subdir), timeout=300)
        check.expect(proc.rc == 0, "`make tests_run` dans %s/ a echoue : %s"
                     % (subdir, first_lines(proc.out + proc.err)))
        return check
    return func


DAY12 = Day("Day 12 - File descriptors", "day12", tasks=[
    Task("01", "cat/", ["cat/*"], cat_task),
    Task("02", "tests + make tests_run (cat)", ["tests/*"],
         tests_run("cat")),
    Task("03", "grep/", ["grep/*"], grep_task),
    Task("04", "tests + make tests_run (grep)", ["tests/*"],
         tests_run("grep")),
])

# ------------------------------------------------------------------ Day 13
CSFML = ["-lcsfml-graphics", "-lcsfml-window", "-lcsfml-system"]


def csfml_available():
    return any(Path(p, "SFML/Graphics.h").exists()
               for p in ("/usr/include", "/usr/local/include"))


def csfml_build(ctx, check):
    sources = sorted(ctx.work.rglob("*.c"))
    sources = [s for s in sources if "tests" not in s.relative_to(ctx.work).parts
               and "bonus" not in s.relative_to(ctx.work).parts]
    if not sources:
        check.fail("aucun fichier .c")
        return None
    if not csfml_available():
        check.skip("la CSFML n'est pas installee sur cette machine")
        return None
    exe = ctx.build / "csfml"
    proc = run(["gcc", *CFLAGS, *sources, *ctx.include_flags(), "-o", exe, *CSFML],
               cwd=ctx.work, timeout=120)
    if not check.expect(proc.rc == 0, "la compilation avec la CSFML echoue : "
                        + first_lines(proc.err)):
        return None
    return exe


def csfml_task(symbol):
    def func(ctx):
        check = Check()
        exe = csfml_build(ctx, check)
        if exe and symbol:
            check.expect(symbol in defined_symbols(exe),
                         "la fonction %s est introuvable" % symbol)
        return check
    return func


DAY13 = Day("Day 13 - CSFML Discovery", "day13", tasks=[
    Task("01", "compilation (fenetre 800x600)", ["*.c", "**/*.c"], csfml_task(None)),
    Task("02", "framebuffer_create + put_pixel", ["*.c", "**/*.c"],
         csfml_task("put_pixel")),
    Task("03", "draw_square", ["*.c", "**/*.c"], csfml_task("draw_square")),
])

# ------------------------------------------------------------------ Rush 1


def rush1_task(number):
    folder_name = "rush-1-%d" % number

    def func(ctx):
        check = Check()
        folder = ctx.p(folder_name)
        objects = compile_objects(ctx, check, folder)
        if objects is None:
            return check
        if not check.expect(objects, "aucun .c dans %s/" % folder_name):
            return check
        forbid_definitions(check, objects, ["main"],
                           "ne rends pas de main, la moulinette ajoute le sien")
        forbid_definitions(check, objects, ["my_putchar"],
                           "ne rends pas my_putchar, la moulinette fournit le sien")
        for name, obj in objects.items():
            used = undefined_symbols(obj) & libc_symbols()
            bad = used - {"write"} - IMPLICIT_SYMBOLS
            check.expect(not bad, "%s utilise des fonctions interdites : %s"
                         % (name, ", ".join(sorted(bad))))
        if not check.ok:
            return check
        exe = ctx.build / ("rush1-%d" % number)
        proc = run(["gcc", *CFLAGS, *objects.values(), TESTS_DIR / "rush1/main.c",
                    LIB_DIR / "my_putchar.c", "-o", exe], timeout=60)
        if not check.expect(proc.rc == 0, "edition de liens impossible : "
                            + first_lines(proc.err)):
            return check
        sizes = [(5, 3), (5, 1), (1, 1), (1, 5), (4, 4), (2, 2), (2, 1),
                 (1, 2), (10, 6), (3, 2), (0, 5), (5, 0), (-1, 3), (0, 0)]
        for x, y in sizes:
            expected = rush1(number, x, y)
            proc = run([exe, str(x), str(y)], timeout=5)
            if expected is None:
                compare(check, "rush(%d, %d)" % (x, y), proc, out="",
                        err="Invalid size\n")
            else:
                compare(check, "rush(%d, %d)" % (x, y), proc, out=expected)
        return check

    return Task("%02d" % number, folder_name + "/", [folder_name + "/*.c"], func)


RUSH1 = Day("Rush 1 - The Squares", "rush1", resources=["others/*", "others/*/*"],
            tasks=[rush1_task(n) for n in range(1, 6)])

# ------------------------------------------------------------------ Rush 2
RUSH2_TEXTS = {
    "English": "The quick brown fox jumps over the lazy dog while the children "
               "were playing in the garden. It was a beautiful summer day and "
               "everybody wanted to stay outside as long as they could, "
               "talking about the weather, the holidays and their friends.",
    "French": "Le petit chat est assis sur le rebord de la fenetre et regarde "
              "les oiseaux qui chantent dans les arbres du jardin. Pendant ce "
              "temps, sa maitresse prepare une tarte aux pommes pour le "
              "dessert de ce soir avec toute la famille reunie.",
    "German": "Der kleine Hund schlaeft jeden Nachmittag unter dem grossen "
              "Tisch in der Kueche, waehrend die Kinder in der Schule sind. "
              "Wenn sie nach Hause kommen, spielen sie zusammen im Garten "
              "und gehen spaeter mit ihren Eltern spazieren.",
    "Spanish": "El perro de mi hermano duerme todas las tardes debajo de la "
               "mesa de la cocina mientras los nietos estan en el colegio. "
               "Cuando vuelven a casa, juegan juntos en el parque y despues "
               "comen una tortilla de patatas con sus abuelos.",
}
LETTER_LINE = re.compile(r"^(.):(\d+)(?: \((\d+\.\d\d)%\))?$")


def rush2_run(exe, text, letters):
    proc = run([exe, text, *letters], timeout=5)
    lines = proc.text.splitlines()
    return proc, lines


def percent_ok(got, count, total):
    value = count * 100 / total if total else 0
    candidates = {"%.2f" % value, "%.2f" % (int(value * 100) / 100)}
    return got in candidates


def rush2_build(ctx, check):
    if not ctx.build_libmy("build.sh"):
        check.fail(ctx.libmy_error)
        return None
    exe = ctx.build / "rush2"
    sources = sorted(ctx.work.glob("*.c"))
    proc = run(["gcc", *CFLAGS, "-o", exe, *sources, "-I", ctx.p("include"),
                *ctx.libmy_flags()], cwd=ctx.work, timeout=120)
    if not check.expect(proc.rc == 0, "gcc -o rush2 *.c -I./include -L./lib/my -lmy "
                        "echoue : " + first_lines(proc.err)):
        return None
    binary_forbidden(check, exe, {"write"}, "rush2")
    return exe


def rush2_step(step):
    def func(ctx):
        check = Check()
        exe = rush2_build(ctx, check)
        if exe is None:
            return check
        if step == 1:
            text = "Just because I don't care doesn't mean I don't understand!"
            for letter, count in (("a", 4), ("A", 4), ("j", 1), ("z", 0)):
                proc, lines = rush2_run(exe, text, [letter])
                match = LETTER_LINE.match(lines[0]) if lines else None
                check.expect(match and match.group(1) == letter
                             and int(match.group(2)) == count,
                             "./rush2 \"%s\" %s : premiere ligne attendue \"%s:%d\", "
                             "obtenu %s" % (text, letter, letter, count, show(proc.text)))
            proc = run([exe], timeout=5)
            compare(check, "./rush2 (sans argument)", proc, rc=84)
        elif step == 2:
            text = "I hope I didn't brain my damage."
            letters = ["A", "i", "I", "i", "z"]
            proc, lines = rush2_run(exe, text, letters)
            for idx, letter in enumerate(letters):
                count = text.lower().count(letter.lower())
                match = LETTER_LINE.match(lines[idx]) if idx < len(lines) else None
                check.expect(match and match.group(1) == letter
                             and int(match.group(2)) == count,
                             "ligne %d : attendu \"%s:%d\", sortie %s"
                             % (idx + 1, letter, count, show(proc.text)))
        elif step == 3:
            for text, letters in (
                    ("Good things do not end with 'ium'. They end with 'mania' "
                     "or 'teria'.", ["a", "q", "e", "i"]),
                    ("abc ABC aaa", ["a", "b", "z"])):
                total = sum(c.isascii() and c.isalpha() for c in text)
                proc, lines = rush2_run(exe, text, letters)
                for idx, letter in enumerate(letters):
                    count = text.lower().count(letter)
                    match = LETTER_LINE.match(lines[idx]) if idx < len(lines) else None
                    ok = (match and int(match.group(2)) == count and match.group(3)
                          and percent_ok(match.group(3), count, total))
                    check.expect(ok, "ligne %d : attendu \"%s:%d (%.2f%%)\", sortie %s"
                                 % (idx + 1, letter, count, count * 100 / total,
                                    show(proc.text)))
        else:
            letters = list("abcdefghijklmnopqrstuvwxyz")
            for language, text in RUSH2_TEXTS.items():
                proc, lines = rush2_run(exe, text, letters)
                last = lines[-1] if lines else ""
                check.expect(last == "=> " + language,
                             "texte en %s : derniere ligne attendue \"=> %s\", "
                             "obtenu %s" % (language, language, show(last)))
        return check
    return func


RUSH2 = Day("Rush 2 - What language is this?", "rush2", libmy="build.sh",
            allowed={"write"}, tasks=[
    Task("01", "step 1 - une lettre", ["*.c"], rush2_step(1)),
    Task("02", "step 2 - plusieurs lettres", ["*.c"], rush2_step(2)),
    Task("03", "step 3 - frequences", ["*.c"], rush2_step(3)),
    Task("04", "step 4 - langue", ["*.c"], rush2_step(4)),
])

# -------------------------------------------------------------------- Star


def star_task(ctx):
    check = Check()
    objects = compile_objects(ctx, check, ctx.work)
    if objects is None:
        return check
    forbid_definitions(check, objects, ["main"],
                       "ne rends pas de main, la moulinette ajoute le sien")
    forbid_definitions(check, objects, ["my_putchar"],
                       "ne rends pas my_putchar, la moulinette fournit le sien")
    for name, obj in objects.items():
        bad = (undefined_symbols(obj) & libc_symbols()) - {"write"} - IMPLICIT_SYMBOLS
        check.expect(not bad, "%s utilise des fonctions interdites : %s"
                     % (name, ", ".join(sorted(bad))))
    if not check.ok:
        return check
    exe = ctx.build / "star"
    proc = run(["cc", *CFLAGS, "-o", exe, *objects.values(), TESTS_DIR / "star/main.c",
                LIB_DIR / "my_putchar.c"], timeout=60)
    if not check.expect(proc.rc == 0, "cc -o star *.c my_putchar.c main.c echoue : "
                        + first_lines(proc.err)):
        return check
    for size in (0, 1, 2, 3, 4, 5, 7, 10, 20):
        proc = run([exe, str(size)], timeout=5)
        compare(check, "star(%d)" % size, proc, out=star(size))
    return check


STAR = Day("Project 1 - Star", "star", resources=["others/*"], tasks=[
    Task("01", "star", ["*.c"], star_task),
])

# ------------------------------------------------------------- CountIsland
WORLDS = [
    ["...XX....", "..XX..X..", ".......X.", "XX.....XX"],
    [".................XXXXXXXX..........................................",
     "....................XXXXXXXXX.......XXXXXXXX.......................",
     ".................XXXXXXXX..............XXX...XXXXX.................",
     ".....................XXXXXX.....X...XXXXXXXXXXX....................",
     "................................X..................................",
     "......XXXXXXXXXXXXX.............X..................................",
     "..................X.............XXXXXXXXX..........................",
     "..................X.........XXXXXXXXXXXX...........................",
     "..................X................................................",
     "XX.............................................................XXXX",
     "XX..................XXXXXXXXXXXXX.................................X",
     "...................................................................",
     ".................................................................X.",
     ".....................XXXXX.......................................XX"],
    ["....", "....", "...."],
    ["X"],
    ["X.X.X", ".X.X.", "X.X.X"],
    ["XXX.", "..X.", "XXX.", "X..."],
    ["X..X", "X..X", "XXXX"],
]


def countisland_task(ctx):
    check = Check()
    if not ctx.build_libmy("build.sh"):
        check.fail(ctx.libmy_error)
        return check
    objects = compile_objects(ctx, check, ctx.work)
    if objects is None:
        return check
    forbid_definitions(check, objects, ["main"],
                       "ne rends pas de main, la moulinette ajoute le sien")
    provided = set(IMPLICIT_SYMBOLS) | defined_symbols(ctx.libmy_path())
    for obj in objects.values():
        provided |= defined_symbols(obj)
    for name, obj in objects.items():
        bad = (undefined_symbols(obj) & libc_symbols()) - provided - {"write"}
        check.expect(not bad, "%s utilise des fonctions interdites : %s"
                     % (name, ", ".join(sorted(bad))))
    if not check.ok:
        return check
    exe = ctx.build / "count_island"
    proc = run(["gcc", *CFLAGS, "-o", exe, *objects.values(),
                TESTS_DIR / "countisland/main.c", *ctx.libmy_flags()],
               cwd=ctx.work, timeout=120)
    if not check.expect(proc.rc == 0, "gcc -o count_island *.c our_main.c ... echoue : "
                        + first_lines(proc.err)):
        return check
    for idx, world in enumerate(WORLDS):
        path = ctx.build / ("world_%d.txt" % idx)
        path.write_text("".join(row + "\n" for row in world))
        count, result = count_island(world)
        proc = run([exe, path], timeout=5)
        compare(check, "count_island(carte %d : %s)" % (idx + 1, show("\n".join(world), 60)),
                proc, out="%d\n" % count + "".join(r + "\n" for r in result))
    return check


COUNTISLAND = Day("Project 2 - Countisland", "countisland", libmy="build.sh",
                  allowed={"write"}, tasks=[
    Task("01", "count_island", ["*.c"], countisland_task),
])

# ---------------------------------------------------------------- InfinAdd


def infinadd_task(ctx):
    check = Check()
    exe = make_project(ctx, check, "", "infin_add")
    if not exe:
        return check
    binary_forbidden(check, exe, {"write", "malloc", "free"}, "infin_add")
    rng = random.Random(1337)
    cases = [("-876435", "987143265"), ("-807965", "-34532"),
             ("435439435845843984358439", "45359766785665822182412343254343435433339459569"),
             ("0", "0"), ("999999999999999999999", "1"), ("-1", "1"),
             ("123456789", "-123456789"), ("-1000000000000000000000", "1"),
             ("42", "-43"), ("5", "0")]
    for _ in range(8):
        a = rng.randint(-10 ** rng.randint(1, 60), 10 ** rng.randint(1, 60))
        b = rng.randint(-10 ** rng.randint(1, 60), 10 ** rng.randint(1, 60))
        cases.append((str(a), str(b)))
    for a, b in cases:
        proc = run([exe, a, b], timeout=5)
        compare(check, "./infin_add \"%s\" \"%s\"" % (a, b), proc,
                out="%d\n" % (int(a) + int(b)), rc=0)
    return check


INFINADD = Day("Part 2 - InfinAdd", "infinadd", tasks=[
    Task("01", "infin_add", ["Makefile", "*.c"], infinadd_task),
])

# ---------------------------------------------------------------- EvalExpr


def c_div(a, b):
    q = abs(a) // abs(b)
    return q if (a >= 0) == (b >= 0) else -q


def c_mod(a, b):
    return a - c_div(a, b) * b


def evaluate(expr):
    """Evalue une expression avec la semantique entiere du C."""
    tokens = re.findall(r"\d+|[-+*/%()]", expr)
    pos = 0

    def peek():
        return tokens[pos] if pos < len(tokens) else None

    def take():
        nonlocal pos
        pos += 1
        return tokens[pos - 1]

    def number():
        sign = 1
        while peek() in ("+", "-"):
            if take() == "-":
                sign = -sign
        if peek() == "(":
            take()
            value = summands()
            take()
            return sign * value
        return sign * int(take())

    def factors():
        value = number()
        while peek() in ("*", "/", "%"):
            op = take()
            rhs = number()
            value = value * rhs if op == "*" else c_div(value, rhs) if op == "/" \
                else c_mod(value, rhs)
        return value

    def summands():
        value = factors()
        while peek() in ("+", "-"):
            value = value + factors() if take() == "+" else value - factors()
        return value

    return summands()


EVAL_CASES = ["(3+2)*5", "42", "1+2*3", "(1+2)*3", "10-4-3", "100/7", "100%7",
              "-7/2", "-7%3", "2*(3+(4-1))*2", "((((1))))", "-(3+2)*2", "3*-2",
              "18/3/2", "1-(2-(3-(4-5)))", "-42", "+5", "0*999", "--3",
              "12*(13+15/5*(6/(12+14%(30%5+(10*25)-46)+16)-20)/43)*20"]


def evalexpr_task(ctx):
    check = Check()
    exe = make_project(ctx, check, "", "eval_expr")
    if not exe:
        return check
    binary_forbidden(check, exe, {"write", "malloc", "free"}, "eval_expr")
    for expr in EVAL_CASES:
        proc = run([exe, expr], timeout=5)
        compare(check, "./eval_expr \"%s\"" % expr, proc,
                out="%d\n" % evaluate(expr), rc=0)
    proc = run([exe], timeout=5)
    compare(check, "./eval_expr (sans argument)", proc, rc=84)
    return check


EVALEXPR = Day("Part 2 - EvalExpr", "evalexpr", tasks=[
    Task("01", "eval_expr", ["Makefile", "*.c"], evalexpr_task),
])

# ------------------------------------------------------------- Bistromatic


def to_base(value, base, minus):
    if value == 0:
        return base[0]
    digits = ""
    n = abs(value)
    while n:
        digits = base[n % len(base)] + digits
        n //= len(base)
    return (minus if value < 0 else "") + digits


def from_base_expr(expr, base, ops):
    """Traduit une expression ecrite dans une base/operateurs quelconques
    en expression decimale classique."""
    table = dict(zip(ops, "()+-*/%"))
    out, num = "", ""
    for char in expr:
        if char in base:
            num += char
            continue
        if num:
            out += str(sum(base.index(d) * len(base) ** i
                           for i, d in enumerate(reversed(num))))
            num = ""
        out += table[char]
    if num:
        out += str(sum(base.index(d) * len(base) ** i
                       for i, d in enumerate(reversed(num))))
    return out


BISTRO_CASES = [
    ("3+6", "0123456789", "()+-*/%", "9"),
    ("3v6", "0123456789", "{}vwxyz", "9"),
    ("----++-6(12)", "0123456789", "()+-*/%", "syntax error"),
    ("----++-6*12", "0123456789", "()+-*/%", "-72"),
    ("-(12-(4*32))", "0123456789", "()+-*/%", "116"),
    ("-(e@-(;*!@))", "0A@!;ie& ]", "()+-*/%", "ee"),
    ("-(12*(13+15/5*(6/(12+14%(30%5+(10*25)-46)+16)-20)/43)*20)*(-(12-98*42)"
     "*(16+63-50/3))", "0123456789", "()+-*/%", "-744629760"),
    ("(1+2", "0123456789", "()+-*/%", "syntax error"),
    ("1++", "0123456789", "()+-*/%", "syntax error"),
]


def bistro_generated():
    rng = random.Random(2021)
    cases = []
    for _ in range(12):
        a = rng.randint(0, 10 ** rng.randint(5, 50))
        b = rng.randint(1, 10 ** rng.randint(1, 30))
        c = rng.randint(1, 10 ** rng.randint(1, 20))
        op1, op2 = rng.choice("+-*"), rng.choice("+-*/%")
        expr = "%d%s(%d%s%d)" % (a, op1, b, op2, c)
        cases.append((expr, "0123456789", "()+-*/%", str(evaluate(expr))))
    for base in ("01", "0123456789ABCDEF", "abcdefgh"):
        a, b = rng.randint(1, 10 ** 15), rng.randint(1, 10 ** 15)
        expr = "%s*%s-%s" % (to_base(a, base, "-"), to_base(b, base, "-"),
                             to_base(a, base, "-"))
        result = evaluate(from_base_expr(expr, base, "()+-*/%"))
        cases.append((expr, base, "()+-*/%", to_base(result, base, "-")))
    return cases


def bistro_task(ctx):
    check = Check()
    exe = make_project(ctx, check, "", "calc")
    if not exe:
        return check
    binary_forbidden(check, exe, {"read", "write", "malloc", "free", "exit"}, "calc")
    for expr, base, ops, expected in BISTRO_CASES + bistro_generated():
        minus = ops[3]
        if expected not in ("syntax error", "error") and expected.startswith("-"):
            expected = minus + expected[1:]
        proc = run([exe, base, ops, str(len(expr))], stdin=expr, timeout=5)
        rc = 84 if expected in ("syntax error", "error") else 0
        compare(check, "echo '%s' | ./calc '%s' '%s' %d" % (expr[:60], base, ops, len(expr)),
                proc, out=expected, rc=rc, out_nl=True)
    return check


BISTROMATIC = Day("Part 2 - Bistromatic", "bistromatic", resources=["subject/*"], tasks=[
    Task("01", "calc", ["Makefile", "*.c", "*/*.c"], bistro_task),
])

# ----------------------------------------------------------- Final Stumper


def stumper_task(ctx):
    check = Check()
    exe = make_project(ctx, check, "", "rush3")
    if not exe:
        return check
    binary_forbidden(check, exe, {"read", "write", "malloc", "free"}, "rush3")
    inputs = []
    for number in range(1, 6):
        for x, y in ((4, 4), (3, 4), (1, 1), (5, 1), (1, 5), (2, 2), (12, 7)):
            inputs.append(("rush1-%d %d %d" % (number, x, y), rush1(number, x, y)))
    inputs += [("texte quelconque", "Hello World\n"),
               ("carre casse", "o--o\n|  |\no-o\n"),
               ("entree vide", "")]
    for label, text in inputs:
        proc = run([exe], stdin=text, timeout=5)
        compare(check, "%s | ./rush3" % label, proc, out=rush3_answer(text) + "\n")
    return check


FINAL_STUMPER = Day("Part 2 - Final Stumper", "stumper",
                    resources=["B-CPE-101_FinalStumper.txt", "*.tgz"], tasks=[
    Task("01", "rush3", ["Makefile", "*.c"], stumper_task),
])
