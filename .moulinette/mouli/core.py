"""Briques de base de la moulinette : execution, compilation, resultats."""

import os
import shutil
import signal
import subprocess
from pathlib import Path

MOULI_DIR = Path(__file__).resolve().parent.parent
LIB_DIR = MOULI_DIR / "lib"
TESTS_DIR = MOULI_DIR / "tests"
FIXTURES = MOULI_DIR / "fixtures"

CFLAGS = [
    "-std=gnu17", "-g", "-w",
    "-Wno-error=implicit-function-declaration",
    "-Wno-error=implicit-int",
    "-Wno-error=int-conversion",
    "-Wno-error=incompatible-pointer-types",
]

# Symboles qu'un compilateur peut inserer de lui-meme.
IMPLICIT_SYMBOLS = {
    "__stack_chk_fail", "_GLOBAL_OFFSET_TABLE_", "memset", "memcpy",
}

# Fichiers consideres comme inutiles dans un rendu.
USELESS_PATTERNS = [
    "*.o", "*.a", "*.so", "*.gch", "a.out", "vgcore.*", "*~", "#*#",
    "*.swp", "*.tmp", "*.gcda", "*.gcno", "*.gcov", ".DS_Store",
]
USELESS_DIRS = {".idea", ".vscode", "__pycache__", "cmake-build-debug"}

PASS = "PASS"
FAIL = "FAIL"
TODO = "TODO"
SKIP = "SKIP"


class Proc:
    def __init__(self, rc, out, err, timeout=False):
        self.rc = rc
        self.out = out
        self.err = err
        self.timeout = timeout

    @property
    def text(self):
        return self.out.decode("utf-8", "replace")

    @property
    def errtext(self):
        return self.err.decode("utf-8", "replace")


def run(cmd, cwd=None, stdin=None, timeout=10, env=None):
    """Lance une commande sans jamais bloquer la moulinette."""
    full_env = dict(os.environ)
    full_env["LC_ALL"] = "C"
    if env:
        full_env.update(env)
    if isinstance(stdin, str):
        stdin = stdin.encode()
    try:
        proc = subprocess.Popen(
            [str(c) for c in cmd], cwd=cwd, env=full_env,
            stdin=subprocess.PIPE if stdin is not None else subprocess.DEVNULL,
            stdout=subprocess.PIPE, stderr=subprocess.PIPE,
            start_new_session=True)
    except OSError as exc:
        return Proc(-1, b"", str(exc).encode())
    try:
        out, err = proc.communicate(stdin, timeout=timeout)
        return Proc(proc.returncode, out, err)
    except subprocess.TimeoutExpired:
        try:
            os.killpg(proc.pid, signal.SIGKILL)
        except OSError:
            pass
        out, err = proc.communicate()
        return Proc(-9, out, err, timeout=True)


def describe_rc(proc):
    if proc.timeout:
        return "TIMEOUT (le programme ne s'est pas termine a temps)"
    if proc.rc < 0:
        try:
            return "CRASH : " + signal.Signals(-proc.rc).name
        except ValueError:
            return "CRASH (signal %d)" % -proc.rc
    return "code de sortie %d" % proc.rc


def show(data, limit=300):
    """Affiche une chaine en rendant visibles les retours a la ligne."""
    if isinstance(data, bytes):
        data = data.decode("utf-8", "replace")
    text = data.replace("\\", "\\\\").replace("\n", "\\n").replace("\t", "\\t")
    if len(text) > limit:
        text = text[:limit] + "[...]"
    return '"%s"' % text


def first_lines(text, count=6):
    if isinstance(text, bytes):
        text = text.decode("utf-8", "replace")
    lines = [line for line in text.strip().splitlines() if line.strip()]
    keys = ("error", "undefined reference", "multiple definition", "No rule")
    useful = [line for line in lines if any(k in line for k in keys)
              and "collect2" not in line and "ld returned" not in line]
    picked = (useful or lines)[:count]
    return " / ".join(line.strip()[:200] for line in picked)


def is_elf(path):
    try:
        with open(path, "rb") as handle:
            return handle.read(4) == b"\x7fELF"
    except OSError:
        return False


def is_executable(path):
    return os.access(path, os.X_OK) and Path(path).is_file()


class TaskResult:
    def __init__(self, ident, name, status, details=None, score=None):
        self.ident = ident
        self.name = name
        self.status = status
        self.details = details or []
        self.score = score


class Check:
    """Accumule les verifications d'un exercice."""

    def __init__(self):
        self.details = []
        self.ok = True
        self.passed = 0
        self.total = 0
        self.skipped = None

    def fail(self, message):
        self.ok = False
        self.total += 1
        self.details.append(message)

    def expect(self, condition, message):
        if condition:
            self.total += 1
            self.passed += 1
        else:
            self.fail(message)
        return condition

    def merge(self, other):
        self.ok = self.ok and other.ok
        self.details.extend(other.details)
        self.passed += other.passed
        self.total += other.total
        if other.skipped:
            self.skipped = other.skipped

    def skip(self, reason):
        self.skipped = reason


class DayContext:
    """Copie de travail d'une journee : on ne salit jamais le depot."""

    def __init__(self, day, repo, tmp):
        self.day = day
        self.repo = Path(repo)
        self.src = self.repo / day.folder
        self.tmp = Path(tmp)
        self.work = self.tmp / "work"
        self.build = self.tmp / "build"
        self.build.mkdir(parents=True, exist_ok=True)
        shutil.copytree(self.src, self.work, symlinks=True)
        self._lib = None
        self._libmy = None
        self.libmy_error = None

    def p(self, rel):
        return self.work / rel

    def exists(self, rel):
        return os.path.lexists(self.p(rel))

    def glob(self, pattern):
        return sorted(self.work.glob(pattern))

    def tests(self, name):
        return TESTS_DIR / self.day.slug / name

    # ----------------------------------------------------------- libmy
    def build_libmy(self, method):
        """Construit libmy.a comme indique dans les sujets."""
        if self._libmy is not None:
            return self._libmy
        libdir = self.p("lib/my")
        self._libmy = False
        if method == "build.sh":
            script = libdir / "build.sh"
            if not script.exists():
                self.libmy_error = "lib/my/build.sh introuvable"
                return False
            if not is_executable(script):
                self.libmy_error = "lib/my/build.sh n'est pas executable"
                return False
            for old in libdir.glob("*.a"):
                old.unlink()
            proc = run(["bash", "-c", "./build.sh"], cwd=libdir, timeout=120)
            if proc.rc != 0:
                self.libmy_error = ("lib/my/build.sh a echoue (%s) : %s"
                                    % (describe_rc(proc), first_lines(proc.err)))
                return False
        else:
            if not (libdir / "Makefile").exists():
                self.libmy_error = "lib/my/Makefile introuvable"
                return False
            proc = run(["make", "-C", libdir], timeout=180)
            if proc.rc != 0:
                self.libmy_error = ("make dans lib/my a echoue : %s"
                                    % first_lines(proc.out + proc.err))
                return False
        if not self.libmy_path():
            self.libmy_error = "libmy.a n'a pas ete construite dans lib/my/ ou lib/"
            return False
        self._libmy = True
        return True

    def libmy_path(self):
        for rel in ("lib/my/libmy.a", "lib/libmy.a"):
            if self.p(rel).exists():
                return self.p(rel)
        return None

    def libmy_flags(self):
        return ["-L", self.p("lib/my"), "-L", self.p("lib"), "-lmy"]

    # ------------------------------------------------- sources du jour
    def include_flags(self):
        flags = []
        for rel in ("include", "."):
            if self.p(rel).is_dir():
                flags += ["-I", self.p(rel)]
        return flags

    def student_lib(self):
        """Compile tous les .c a la racine du jour (comme `gcc -c *.c`)."""
        if self._lib is not None:
            return self._lib
        objdir = self.build / "obj"
        objdir.mkdir(exist_ok=True)
        objects = {}
        errors = []
        for source in sorted(self.work.glob("*.c")):
            obj = objdir / (source.stem + ".o")
            cmd = ["gcc", *CFLAGS, "-c", source, "-o", obj, *self.include_flags()]
            proc = run(cmd, cwd=self.work, timeout=60)
            if proc.rc != 0 and self.day.provided_header:
                # Le sujet fournit lui-meme certaines structures.
                proc2 = run(cmd + ["-include", self.day.provided_header],
                            cwd=self.work, timeout=60)
                proc = proc2 if proc2.rc == 0 else proc
            if proc.rc != 0:
                errors.append("%s ne compile pas : %s"
                              % (source.name, first_lines(proc.err, 3)))
            else:
                objects[source.name] = obj
        archive = None
        if objects and not errors:
            archive = self.build / "libstudent.a"
            run(["ar", "rcs", archive, *objects.values()])
        self._lib = (archive, objects, errors)
        return self._lib


def defined_symbols(path):
    proc = run(["nm", "--defined-only", "-g", path])
    symbols = set()
    for line in proc.text.splitlines():
        parts = line.split()
        if len(parts) >= 3 and parts[1] in "TDBRVWCGS":
            symbols.add(parts[2])
    return symbols


def undefined_symbols(path):
    proc = run(["nm", "-u", path])
    return {line.split()[-1].split("@")[0] for line in proc.text.splitlines()
            if line.strip() and not line.endswith(":")}


_LIBC = None


def libc_symbols():
    """Fonctions exportees par la libc (pour distinguer une fonction
    interdite d'une fonction simplement manquante)."""
    global _LIBC
    if _LIBC is None:
        proc = run(["gcc", "-print-file-name=libc.so.6"])
        path = proc.text.strip() or "libc.so.6"
        proc = run(["nm", "-D", "--defined-only", path])
        _LIBC = {line.split()[-1].split("@")[0] for line in proc.text.splitlines()
                 if line.strip()}
        if not _LIBC:
            for candidate in ("/lib/x86_64-linux-gnu/libc.so.6", "/usr/lib/libc.so.6",
                              "/lib64/libc.so.6"):
                proc = run(["nm", "-D", "--defined-only", candidate])
                _LIBC |= {line.split()[-1].split("@")[0]
                          for line in proc.text.splitlines() if line.strip()}
    return _LIBC


def git_tracked(repo, folder):
    """Fichiers suivis par git (None si on n'est pas dans un depot git)."""
    proc = run(["git", "-C", repo, "ls-files", "-z", "--", folder])
    if proc.rc != 0:
        return None
    prefix = folder.rstrip("/") + "/"
    return [p[len(prefix):] for p in proc.text.split("\0") if p.startswith(prefix)]

