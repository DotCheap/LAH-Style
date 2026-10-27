"""Types d'exercices generiques : fonctions C, programmes, Makefiles..."""

import os
import re
import shutil
from pathlib import Path

from .core import (CFLAGS, FIXTURES, IMPLICIT_SYMBOLS, LIB_DIR, Check, run,
                   defined_symbols, describe_rc, first_lines, is_executable,
                   libc_symbols, show, undefined_symbols)


class Task:
    def __init__(self, ident, name, files, func):
        self.ident = ident
        self.name = name
        self.files = files
        self.func = func

    def attempted(self, ctx):
        return any(ctx.glob(pattern) or ctx.exists(pattern)
                   for pattern in self.files)


class Day:
    def __init__(self, folder, slug, tasks, resources=(), libmy=None,
                 allowed=(), putchar=False, shell=False, provided_header=None):
        self.folder = folder
        self.slug = slug
        self.tasks = tasks
        self.resources = ["*.pdf", *resources]
        self.libmy = libmy
        self.allowed = set(allowed)
        self.putchar = putchar
        self.shell = shell
        self.provided_header = provided_header


# ---------------------------------------------------------------- mouli
def run_mouli(ctx, test, check, link=(), sources=(), defines=(),
              includes=(), timeout=2):
    """Compile un fichier de test .moulinette/tests/<jour>/<test>.c et
    l'execute. Chaque CASE du test devient une verification."""
    exe = ctx.build / ("test_" + Path(test).stem)
    results = ctx.build / ("results_" + Path(test).stem)
    if results.exists():
        results.unlink()
    cmd = ["gcc", *CFLAGS, "-I", LIB_DIR, *includes, *defines,
           ctx.tests(test), LIB_DIR / "mouli.c", *sources, *link, "-o", exe]
    proc = run(cmd, cwd=ctx.build, timeout=120)
    if proc.rc != 0:
        hint = ""
        if b"multiple definition" in proc.err:
            hint = (" -> une meme fonction est definie dans plusieurs fichiers "
                    "(rends tes fonctions utilitaires `static`)")
        check.fail("compilation du test impossible : " + first_lines(proc.err) + hint)
        return
    proc = run([exe], cwd=ctx.build, timeout=120,
               env={"MOULI_RESULTS": str(results), "MOULI_TIMEOUT": str(timeout)})
    if proc.timeout:
        check.fail("le test a depasse le temps maximum")
    if not results.exists():
        check.fail("le test n'a produit aucun resultat (%s)" % describe_rc(proc))
        return
    for line in results.read_text("utf-8", "replace").splitlines():
        parts = line.split("\t", 2)
        if len(parts) < 2:
            continue
        status, desc = parts[0], parts[1]
        msg = parts[2] if len(parts) > 2 else ""
        if msg.startswith(desc + " : "):
            msg = msg[len(desc) + 3:]
        check.expect(status == "PASS", "%s -> %s" % (desc, msg))


def day_link(ctx, check):
    """Bibliotheques a ajouter lors de l'edition de liens d'un test."""
    link = []
    if ctx.day.putchar:
        link.append(LIB_DIR / "my_putchar.c")
    if ctx.day.libmy:
        if not ctx.build_libmy(ctx.day.libmy):
            check.fail(ctx.libmy_error)
            return None
        link += ctx.libmy_flags()
    return link


def check_allowed(ctx, check, files, allowed=None):
    """Verifie que les fichiers rendus n'utilisent que des fonctions
    autorisees par le sujet."""
    archive, objects, _ = ctx.student_lib()
    allowed = set(ctx.day.allowed if allowed is None else allowed)
    provided = set(IMPLICIT_SYMBOLS)
    for obj in objects.values():
        provided |= defined_symbols(obj)
    if ctx.day.putchar:
        provided.add("my_putchar")
    lib = ctx.libmy_path()
    if ctx.day.libmy and lib:
        provided |= defined_symbols(lib)
    for name in files:
        if name not in objects:
            continue
        unknown = undefined_symbols(objects[name]) - provided - allowed
        forbidden = unknown & libc_symbols()
        missing = unknown - forbidden
        if forbidden:
            check.fail("%s utilise des fonctions interdites : %s"
                       % (name, ", ".join(sorted(forbidden))))
        if missing:
            check.fail("%s appelle des fonctions qui ne sont definies nulle part "
                       "(ni dans tes .c, ni dans ta libmy) : %s"
                       % (name, ", ".join(sorted(missing))))


def c_function(test, files, **kwargs):
    """Exercice classique : une ou plusieurs fonctions dans des .c a la
    racine du jour, compilees avec le main de la moulinette."""

    def func(ctx):
        check = Check()
        missing = [f for f in files if not ctx.exists(f)]
        if missing:
            check.fail("fichier(s) manquant(s) : " + ", ".join(missing))
            return check
        archive, objects, errors = ctx.student_lib()
        if errors:
            for err in errors:
                check.fail(err)
            check.fail("le sujet impose que tous les .c compilent ensemble "
                       "(gcc *.c) : corrige d'abord la compilation")
            return check
        for name in files:
            if "main" in defined_symbols(objects[name]):
                check.fail("%s contient une fonction main : la moulinette "
                           "ajoute la sienne, ne la rends pas" % name)
        link = day_link(ctx, check)
        if link is None:
            return check
        check_allowed(ctx, check, files)
        if not check.ok:
            return check
        run_mouli(ctx, test, check, sources=[archive], link=link, **kwargs)
        return check

    return func


# ------------------------------------------------------------ programmes
def compare(check, label, proc, out=None, rc=None, err=None, out_nl=False,
            err_contains=None, out_ws=False):
    """Compare l'execution d'un programme avec le resultat attendu."""
    problems = []
    if proc.timeout or proc.rc < 0:
        problems.append(describe_rc(proc))
    else:
        if out is not None:
            got = proc.text
            exp = out
            if out_nl and got == exp + "\n":
                got = exp
            if out_ws:
                got = " ".join(got.split())
                exp = " ".join(exp.split())
            if got != exp:
                problems.append("sortie attendue %s, obtenue %s"
                                % (show(exp), show(got)))
        if rc is not None and proc.rc != rc:
            problems.append("code de sortie attendu %d, obtenu %d" % (rc, proc.rc))
        if err is not None and proc.errtext != err:
            problems.append("sortie d'erreur attendue %s, obtenue %s"
                            % (show(err), show(proc.errtext)))
        if err_contains is not None and err_contains not in proc.errtext:
            problems.append("la sortie d'erreur devrait contenir %s (obtenu %s)"
                            % (show(err_contains), show(proc.errtext)))
    return check.expect(not problems, "%s : %s" % (label, " ; ".join(problems)))


def gcc_program(ctx, check, subdir, name, link_libmy=True):
    """Compile un programme comme decrit dans les sujets du Day07 :
    cd taskXX ; gcc *.c -c -I../include ; gcc *.o -L../lib/my -lmy"""
    folder = ctx.p(subdir)
    sources = sorted(folder.glob("*.c"))
    if not sources:
        check.fail("aucun fichier .c dans %s/" % subdir)
        return None
    exe = ctx.build / name
    cmd = ["gcc", *CFLAGS, *sources, "-I", ctx.p("include"), "-o", exe]
    if link_libmy:
        cmd += ctx.libmy_flags()
    proc = run(cmd, cwd=folder, timeout=120)
    if proc.rc != 0:
        check.fail("compilation de %s/*.c impossible : %s"
                   % (subdir, first_lines(proc.err)))
        return None
    return exe


def make_project(ctx, check, subdir, binary, rules=("all", "clean", "fclean", "re")):
    """Verifie un Makefile (regles, pas de relink) et construit le binaire."""
    folder = ctx.p(subdir) if subdir else ctx.work
    where = (subdir + "/") if subdir else "la racine"
    if not (folder / "Makefile").exists():
        check.fail("pas de Makefile dans " + where)
        return None
    for rule in rules:
        proc = run(["make", "-n", rule], cwd=folder, timeout=30)
        check.expect(proc.rc == 0, "la regle `%s` est absente du Makefile" % rule)
    proc = run(["make"], cwd=folder, timeout=300)
    exe = folder / binary
    if proc.rc != 0:
        check.fail("`make` a echoue : " + first_lines(proc.out + proc.err))
        return None
    if not is_executable(exe):
        check.fail("`make` n'a pas produit le binaire `%s`" % binary)
        return None
    before = os.stat(exe).st_mtime_ns
    run(["make"], cwd=folder, timeout=300)
    after = os.stat(exe).st_mtime_ns if exe.exists() else 0
    check.expect(before == after,
                 "relink : un second `make` reconstruit le binaire alors que "
                 "rien n'a change")
    keep = ctx.build / ("bin_" + binary)
    shutil.copy2(exe, keep)
    proc = run(["make", "fclean"], cwd=folder, timeout=60)
    check.expect(proc.rc == 0 and not exe.exists(),
                 "`make fclean` doit supprimer le binaire `%s`" % binary)
    objs = list(folder.rglob("*.o"))
    check.expect(not objs, "`make fclean` doit supprimer les .o (reste : %s)"
                 % ", ".join(o.name for o in objs[:5]))
    proc = run(["make", "re"], cwd=folder, timeout=300)
    check.expect(proc.rc == 0 and is_executable(exe),
                 "`make re` doit reconstruire le binaire `%s`" % binary)
    return keep


def script_cmd(path, *args):
    """Lance un script comme depuis un terminal bash (./script args)."""
    return ["bash", "-c", '"$0" "$@"', str(path), *args]


def require_exec(check, path, label=None):
    label = label or path.name
    if not path.exists():
        check.fail("%s est introuvable" % label)
        return False
    if not is_executable(path):
        check.fail("%s n'a pas le droit d'execution (chmod +x)" % label)
        return False
    return True


def require_shebang(check, path):
    try:
        first = path.read_text("utf-8", "replace").splitlines()[0]
    except (OSError, IndexError):
        first = ""
    if not first.startswith("#!"):
        check.fail("%s : il manque le shebang (#!/bin/bash) en premiere ligne"
                   % path.name)
        return False
    return True


# -------------------------------------------------------- tests unitaires
def criterion_available():
    return any(Path(p, "criterion/criterion.h").exists()
               for p in ("/usr/include", "/usr/local/include"))


def gcov_coverage(ctx, source_name, objdir):
    """Renvoie (lignes %, branches %) pour un fichier source."""
    proc = run(["gcov", "-b", "-c", "-o", objdir, ctx.p(source_name)],
               cwd=ctx.build, timeout=60)
    lines = branches = None
    current = None
    for line in proc.text.splitlines():
        match = re.match(r"File '(.*)'", line)
        if match:
            current = os.path.basename(match.group(1))
            continue
        if current != source_name:
            continue
        match = re.match(r"Lines executed:([\d.]+)% of (\d+)", line)
        if match:
            lines = float(match.group(1))
        match = re.match(r"Taken at least once:([\d.]+)% of (\d+)", line)
        if match:
            branches = float(match.group(1))
        if line.startswith("No branches"):
            branches = 100.0
    return lines, branches


def unit_tests(tests, functions, line_min, branch_min):
    """Tests unitaires Criterion avec un minimum de couverture."""

    def func(ctx):
        check = Check()
        missing = [t for t in tests if not ctx.exists(t)]
        if missing:
            check.fail("fichier(s) manquant(s) : " + ", ".join(missing))
            return check
        if not criterion_available():
            check.skip("Criterion n'est pas installe sur cette machine")
            return check
        objdir = ctx.build / "cov"
        if objdir.exists():
            shutil.rmtree(objdir)
        objdir.mkdir()
        objects = []
        for source in sorted(ctx.work.glob("*.c")):
            obj = objdir / (source.stem + ".o")
            proc = run(["gcc", *CFLAGS, "--coverage", "-c", source, "-o", obj,
                        *ctx.include_flags()], cwd=ctx.work, timeout=60)
            if proc.rc != 0:
                check.fail("%s ne compile pas : %s" % (source.name,
                                                      first_lines(proc.err, 3)))
                return check
            objects.append(obj)
        archive = objdir / "libcov.a"
        run(["ar", "rcs", archive, *objects])
        for test in tests:
            for gcda in objdir.glob("*.gcda"):
                gcda.unlink()
            exe = ctx.build / ("unit_" + Path(test).stem)
            link = [LIB_DIR / "my_putchar.c"] if ctx.day.putchar else []
            proc = run(["gcc", *CFLAGS, "--coverage", ctx.p(test), archive,
                        *link, "-o", exe, *ctx.include_flags(), "-lcriterion"],
                       cwd=ctx.work, timeout=120)
            if proc.rc != 0:
                check.fail("%s ne compile pas : %s" % (test, first_lines(proc.err)))
                continue
            proc = run([exe, "-j1"], cwd=ctx.work, timeout=120)
            check.expect(proc.rc == 0,
                         "%s : des tests echouent (%s)"
                         % (test, first_lines(proc.err, 4)))
            func_name = Path(test).stem.replace("test_", "", 1)
            source = func_name + ".c"
            if func_name not in functions or not ctx.exists(source):
                continue
            lines, branches = gcov_coverage(ctx, source, objdir)
            if lines is None:
                check.fail("%s : aucune couverture mesuree pour %s"
                           % (test, source))
                continue
            check.expect(lines >= line_min,
                         "%s : couverture des lignes de %s = %.0f%% (minimum %d%%)"
                         % (test, source, lines, line_min))
            check.expect((branches or 0) >= branch_min,
                         "%s : couverture des branches de %s = %.0f%% (minimum %d%%)"
                         % (test, source, branches or 0, branch_min))
        return check

    return func


def fixture(name):
    return FIXTURES / name
