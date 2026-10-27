"""Day 01 (environnement Unix) et Day 02 (shell)."""

import os
import re
import shutil
import stat
import tempfile
from pathlib import Path

from ..checks import (Day, Task, compare, fixture, require_exec,
                      require_shebang, script_cmd)
from ..core import Check, describe_rc, run, show

# ------------------------------------------------------------------ Day 01


def task01(ctx):
    check = Check()
    test01, test02, test03 = (ctx.p("task01/" + n) for n in ("test01", "test02", "test03"))
    if check.expect(test01.is_file() and not test01.is_symlink(),
                    "task01/test01 doit etre un fichier"):
        check.expect(test01.stat().st_size == 0, "task01/test01 doit etre vide")
        check.expect(not test01.stat().st_mode & 0o111,
                     "task01/test01 doit avoir les permissions par defaut (pas d'execution)")
    if check.expect(test02.is_file() and not test02.is_symlink(),
                    "task01/test02 doit etre un fichier"):
        content = test02.read_text("utf-8", "replace").rstrip("\n").replace("’", "'")
        check.expect(content == "If you don't struggle, you don't improve.",
                     "task01/test02 : contenu inattendu %s" % show(content))
        mode = stat.S_IMODE(test02.stat().st_mode)
        check.expect(mode & 0o555 == 0o555,
                     "task01/test02 : tout le monde doit pouvoir lire et executer "
                     "(permissions actuelles %o)" % mode)
        check.expect(mode & 0o022 == 0,
                     "task01/test02 : seul le proprietaire doit pouvoir ecrire "
                     "(permissions actuelles %o)" % mode)
    if check.expect(test03.is_symlink(), "task01/test03 doit etre un lien symbolique"):
        target = os.readlink(test03)
        check.expect(os.path.basename(target) == "test02" and test03.resolve() == test02.resolve(),
                     "task01/test03 doit pointer vers test02 (pointe vers %s)" % target)
    return check


def task02(ctx):
    check = Check()
    z = ctx.p("task02/z")
    if check.expect(z.is_file(), "task02/z est introuvable"):
        content = z.read_bytes()
        check.expect(content == b"Z\n", "cat -e z doit afficher Z$ (contenu : %s)"
                     % show(content))
    return check


def task03(ctx):
    check = Check()
    script = ctx.p("task03/midLS")
    if not require_exec(check, script, "task03/midLS"):
        return check
    mode = stat.S_IMODE(script.stat().st_mode)
    check.expect(mode & 0o111 == 0o111,
                 "task03/midLS : le droit d'execution doit etre donne a tout le monde")
    with tempfile.TemporaryDirectory() as tmp:
        for name in ("banana", "cherry", "zebra"):
            Path(tmp, name).write_text("x")
        for name in ("apple", "dir"):
            Path(tmp, name).mkdir()
        Path(tmp, ".hidden").write_text("x")
        Path(tmp, ".hiddendir").mkdir()
        proc = run(script_cmd(script), cwd=tmp)
        got = re.sub(r"\s+", "", proc.text)
        check.expect(got == "apple/,banana,cherry,dir/,zebra",
                     "sortie attendue \"apple/, banana, cherry, dir/, zebra\" "
                     "(espaces ignores), obtenue %s" % show(proc.text))
    return check


def task04(ctx):
    check = Check()
    script = ctx.p("mr_clean")
    if not require_exec(check, script, "mr_clean"):
        return check
    body = [line for line in script.read_text("utf-8", "replace").splitlines()
            if line.strip() and not line.startswith("#")]
    check.expect(len(body) == 1 and not re.search(r";|&&|\|\|", body[0] if body else ""),
                 "mr_clean doit contenir une seule commande (pas de ;, && ou ||)")
    with tempfile.TemporaryDirectory() as tmp:
        root = Path(tmp)
        (root / "sub/deep").mkdir(parents=True)
        delete = ["a~", "#b#", "sub/c~", "sub/#d#", "sub/deep/e.c~", "#x y#"]
        keep = ["keep.c", "#nope", "nope#", "a~b", "sub/f", "sub/deep/#g"]
        for name in delete + keep:
            (root / name).write_text("x")
        run(script_cmd(script), cwd=tmp)
        left = [n for n in delete if (root / n).exists()]
        lost = [n for n in keep if not (root / n).exists()]
        check.expect(not left, "fichiers non supprimes : " + ", ".join(left))
        check.expect(not lost, "fichiers supprimes a tort : " + ", ".join(lost))
    return check


def task05(ctx):
    check = Check()
    script = ctx.p("push_that.sh")
    if not require_exec(check, script, "push_that.sh"):
        return check
    first = (script.read_text("utf-8", "replace").splitlines() or [""])[0]
    check.expect(first.startswith("#!") and "bash" in first,
                 "push_that.sh doit commencer par un shebang bash (#!/bin/bash)")
    with tempfile.TemporaryDirectory() as tmp:
        remote, clone = Path(tmp, "remote.git"), Path(tmp, "clone")
        env = {"GIT_AUTHOR_NAME": "mouli", "GIT_AUTHOR_EMAIL": "mouli@example.com",
               "GIT_COMMITTER_NAME": "mouli", "GIT_COMMITTER_EMAIL": "mouli@example.com",
               "HOME": tmp}
        run(["git", "init", "-q", "--bare", "-b", "main", remote], env=env)
        run(["git", "clone", "-q", remote, clone], env=env)
        run(["git", "checkout", "-q", "-b", "main"], cwd=clone, env=env)
        Path(clone, "first").write_text("1")
        run(["git", "add", "first"], cwd=clone, env=env)
        run(["git", "commit", "-qm", "init"], cwd=clone, env=env)
        run(["git", "push", "-q", "-u", "origin", "main"], cwd=clone, env=env)
        shutil.copy2(script, clone / "push_that.sh")
        Path(clone, "new_file.c").write_text("int x;\n")
        Path(clone, "sub").mkdir()
        Path(clone, "sub/other").write_text("y")
        proc = run(script_cmd(clone / "push_that.sh", "mon message de commit"),
                   cwd=clone, env=env, timeout=30)
        log = run(["git", "--git-dir", remote, "log", "--all", "--format=%s"], env=env)
        files = run(["git", "--git-dir", remote, "ls-tree", "-r", "--name-only", "main"],
                    env=env).text.split()
        check.expect("mon message de commit" in log.text.splitlines(),
                     "aucun commit avec le message passe en parametre n'a ete pousse "
                     "(%s, sortie : %s)" % (describe_rc(proc), show(proc.errtext, 200)))
        check.expect("new_file.c" in files and "sub/other" in files,
                     "les fichiers du dossier courant n'ont pas tous ete pousses")
    return check


def read_tree(root):
    entries = set()
    for dirpath, dirnames, filenames in os.walk(root):
        for name in dirnames + filenames:
            full = os.path.join(dirpath, name)
            rel = os.path.relpath(full, root)
            if name in (".gitkeep", ".keep", ".gitignore"):
                continue
            if os.path.islink(full):
                entries.add("l %s -> %s" % (rel, os.readlink(full).rstrip("/")))
            elif os.path.isdir(full):
                entries.add("d " + rel)
            else:
                entries.add("f " + rel)
    return entries


def compare_tree(check, root, label):
    expected = set(fixture("day01_task06.txt").read_text().splitlines())
    got = read_tree(root)
    missing = sorted(expected - got)
    extra = sorted(got - expected)
    check.expect(not missing, "%s : elements manquants ou incorrects : %s"
                 % (label, "; ".join(missing[:6]) + (" ..." if len(missing) > 6 else "")))
    check.expect(not extra, "%s : elements en trop ou incorrects : %s"
                 % (label, "; ".join(extra[:6]) + (" ..." if len(extra) > 6 else "")))


def task06(ctx):
    check = Check()
    if not check.expect(ctx.p("task06").is_dir(), "dossier task06 introuvable"):
        return check
    compare_tree(check, ctx.p("task06"), "task06")
    return check


def task07(ctx):
    check = Check()
    archive = ctx.p("task07/task06.tgz")
    if not check.expect(archive.is_file(), "task07/task06.tgz introuvable"):
        return check
    with open(archive, "rb") as handle:
        check.expect(handle.read(2) == b"\x1f\x8b", "task06.tgz doit etre compresse avec gzip")
    with tempfile.TemporaryDirectory() as tmp:
        proc = run(["tar", "xf", archive, "-C", tmp])
        if not check.expect(proc.rc == 0, "impossible d'extraire task06.tgz : "
                            + proc.errtext.strip()):
            return check
        root = Path(tmp, "task06") if Path(tmp, "task06").is_dir() else Path(tmp)
        compare_tree(check, root, "contenu de task06.tgz")
    return check


DAY01 = Day("Day 01 - Unix environments", "day01", shell=True, tasks=[
    Task("01", "task01 (fichiers et lien)", ["task01"], task01),
    Task("02", "task02/z", ["task02/z"], task02),
    Task("03", "task03/midLS", ["task03/midLS"], task03),
    Task("04", "mr_clean", ["mr_clean"], task04),
    Task("05", "push_that.sh", ["push_that.sh"], task05),
    Task("06", "task06 (arborescence)", ["task06"], task06),
    Task("07", "task07/task06.tgz", ["task07/task06.tgz"], task07),
])

# ------------------------------------------------------------------ Day 02


def passwd_lines():
    return fixture("passwd").read_text("utf-8", "surrogateescape").splitlines()


def prepare_resources(tmp):
    """Les ressources sont fournies dans le dossier courant et dans Day02/."""
    Path(tmp, "Day02").mkdir(exist_ok=True)
    for name in ("passwd", "students.csv"):
        shutil.copy(fixture(name), Path(tmp, name))
        shutil.copy(fixture(name), Path(tmp, "Day02", name))


def shell_task(name, cases_fn):
    def func(ctx):
        check = Check()
        script = ctx.p(name)
        if not require_exec(check, script) or not require_shebang(check, script):
            return check
        with tempfile.TemporaryDirectory() as tmp:
            cases_fn(check, script, tmp)
        return check
    return func


def how_many_cases(check, script, tmp):
    prepare_resources(tmp)
    data = fixture("students.csv").read_text()
    rows = [line.split(";") for line in data.splitlines() if line]
    for city in ("ncy", "par", "stg", "MAR"):
        count = sum(1 for row in rows if row[-1].lower() == city.lower())
        proc = run(script_cmd(script, city), cwd=tmp, stdin=data)
        compare(check, "cat students.csv | ./how_many_are_we.sh " + city, proc,
                out="%d" % count, out_nl=True)
    proc = run(script_cmd(script), cwd=tmp, stdin=data)
    compare(check, "cat students.csv | ./how_many_are_we.sh (sans argument)",
            proc, out="%d" % len(rows), out_nl=True)


def find_sh_cases(check, script, tmp):
    root = Path(tmp)
    expected = ["a.sh", "b/c.sh", "b/d/e.sh", "b/d/.hidden.sh", "x/y z.sh"]
    for name in expected + ["no.shx", "nosh", "b/d/sh", "b/f.bash"]:
        (root / name).parent.mkdir(parents=True, exist_ok=True)
        (root / name).write_text("x")
    proc = run(script_cmd(script), cwd=tmp)
    got = [re.sub(r"^\./", "", line) for line in proc.text.splitlines() if line]
    names = [os.path.basename(p) for p in expected]
    ok = sorted(got) in (sorted(expected), sorted(names),
                         sorted(n[:-3] for n in names))
    check.expect(ok, "./find_sh.sh doit afficher les fichiers .sh %s, obtenu %s"
                 % (expected, show(proc.text)))


def count_files_cases(check, script, tmp):
    root = Path(tmp)
    for i, name in enumerate(["a", "b", ".c", "d/e", "d/f/g", "d/f/h", "i/j"]):
        (root / name).parent.mkdir(parents=True, exist_ok=True)
        (root / name).write_text(str(i))
    (root / "empty_dir").mkdir()
    os.symlink("a", root / "link")
    proc = run(script_cmd(script), cwd=tmp)
    compare(check, "./count_files.sh (7 fichiers reguliers)", proc, out="7",
            out_nl=True)


def gotta_cases(check, script, tmp):
    prepare_resources(tmp)
    lines = passwd_lines()
    data = "\n".join(lines) + "\n"
    gecos = [line.split(":")[4] for line in lines]
    for name in ("martin", "dupon", "moreau", "zz"):
        count = sum(1 for g in gecos if " " in g and g.split(" ", 1)[1].startswith(name))
        proc = run(script_cmd(script, name), cwd=tmp, stdin=data)
        compare(check, "cat passwd | ./gotta_catch_them_all.sh " + name, proc,
                out="%d" % count, out_nl=True)


TOONS = [("theo1", "Wile E. Coyote"), ("steven1", "Daffy Duck"),
         ("arnaud1", "Porky Pig"), ("pierre-jean", "Marvin the Martian")]


def looney_cases(check, script, tmp):
    prepare_resources(tmp)
    lines = passwd_lines()
    expected = []
    for line in lines:
        for old, new in TOONS:
            line = line.replace(old, new)
        if any(new in line for _, new in TOONS):
            expected.append(line)
    proc = run(script_cmd(script), cwd=tmp, stdin="\n".join(lines) + "\n")
    compare(check, "cat passwd | ./looneytised.sh", proc,
            out="\n".join(expected) + "\n")


def skip_cases(check, script, tmp):
    for lines in (["skip.sh", "toto", "tata", "tutu", "titi", "tete"],
                  ["un"], ["1", "2"], ["a", "", "b", "", "c"]):
        proc = run(script_cmd(script), cwd=tmp, stdin="\n".join(lines) + "\n")
        compare(check, "printf %s | ./skip.sh" % show("\n".join(lines) + "\n", 60),
                proc, out="".join(l + "\n" for l in lines[::2]))


def r_tacpy_cases(check, script, tmp):
    prepare_resources(tmp)
    lines = passwd_lines()
    logins = sorted((line.split(":")[0][::-1] for line in lines[1::2]),
                    key=lambda s: s.encode("utf-8", "surrogateescape"), reverse=True)
    for first, last in ((24, 42), (1, 3), (100, 100)):
        expected = ", ".join(logins[first - 1:last]) + ".\n"
        proc = run(script_cmd(script), cwd=tmp, stdin="\n".join(lines) + "\n",
                   env={"MY_LINE1": str(first), "MY_LINE2": str(last)})
        compare(check, "MY_LINE1=%d MY_LINE2=%d ./r_tacpy.sh" % (first, last),
                proc, out=expected)


DAY02 = Day("Day 02 - Shell language", "day02", shell=True,
            resources=["Day02/*"], tasks=[
    Task("01", "how_many_are_we.sh", ["how_many_are_we.sh"],
         shell_task("how_many_are_we.sh", how_many_cases)),
    Task("02", "find_sh.sh", ["find_sh.sh"], shell_task("find_sh.sh", find_sh_cases)),
    Task("03", "count_files.sh", ["count_files.sh"],
         shell_task("count_files.sh", count_files_cases)),
    Task("04", "gotta_catch_them_all.sh", ["gotta_catch_them_all.sh"],
         shell_task("gotta_catch_them_all.sh", gotta_cases)),
    Task("05", "looneytised.sh (encrypted)", ["looneytised.sh"],
         shell_task("looneytised.sh", looney_cases)),
    Task("06", "skip.sh", ["skip.sh"], shell_task("skip.sh", skip_cases)),
    Task("07", "r_tacpy.sh", ["r_tacpy.sh"], shell_task("r_tacpy.sh", r_tacpy_cases)),
])
