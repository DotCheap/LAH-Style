#!/usr/bin/env python3
"""Moulinette de la piscine.

Corrige chaque journee de la piscine en respectant les consignes de rendu
des sujets. Utilisation :

    python3 .moulinette/grade.py                 # toutes les journees
    python3 .moulinette/grade.py "Day 03"        # une journee (filtre)
    python3 .moulinette/grade.py --summary r.md  # rapport Markdown
"""

import argparse
import fnmatch
import os
import sys
import tempfile
import traceback
from pathlib import Path

sys.dont_write_bytecode = True
sys.path.insert(0, str(Path(__file__).resolve().parent))

from mouli.core import (FAIL, PASS, SKIP, TODO, DayContext, TaskResult,  # noqa: E402
                        git_tracked, is_elf, USELESS_DIRS, USELESS_PATTERNS)
from mouli.days import DAYS  # noqa: E402

ICONS = {PASS: "✅", FAIL: "❌", TODO: "⏳", SKIP: "⚪"}
LABELS = {PASS: "OK", FAIL: "KO", TODO: "non rendu", SKIP: "ignore"}


def student_files(repo, day):
    """Fichiers rendus par l'eleve (tout sauf le sujet et ses ressources)."""
    folder = repo / day.folder
    tracked = git_tracked(repo, day.folder)
    if tracked is None:
        tracked = [os.path.relpath(os.path.join(d, f), folder)
                   for d, _, files in os.walk(folder) for f in files]
    return [f for f in tracked
            if not any(fnmatch.fnmatch(f, pat) for pat in day.resources)]


def clean_repo_check(repo, day, files):
    """Les sujets exigent un rendu sans fichiers inutiles."""
    bad = []
    for rel in files:
        parts = rel.split("/")
        if any(part in USELESS_DIRS for part in parts[:-1]):
            bad.append(rel)
        elif any(fnmatch.fnmatch(parts[-1], pat) for pat in USELESS_PATTERNS):
            bad.append(rel)
        else:
            full = repo / day.folder / rel
            if not full.is_symlink() and is_elf(full):
                bad.append(rel + " (binaire)")
    if bad:
        shown = ", ".join(bad[:8]) + (" ..." if len(bad) > 8 else "")
        return TaskResult("--", "Depot propre", FAIL,
                          ["fichiers inutiles dans le depot (binaires, .o, "
                           ".a, temporaires...) : " + shown,
                           "supprime-les avec `git rm` et ajoute un .gitignore"])
    return TaskResult("--", "Depot propre", PASS)


def grade_day(repo, day):
    folder = repo / day.folder
    if not folder.is_dir():
        return [TaskResult("--", "Dossier du jour", FAIL,
                           ["dossier `%s` introuvable" % day.folder])], False
    files = student_files(repo, day)
    if not files:
        return [TaskResult(t.ident, t.name, TODO) for t in day.tasks], False
    results = []
    with tempfile.TemporaryDirectory(prefix="mouli_") as tmp:
        ctx = DayContext(day, repo, tmp)
        for task in day.tasks:
            if not task.attempted(ctx):
                results.append(TaskResult(task.ident, task.name, TODO))
                continue
            try:
                check = task.func(ctx)
            except Exception:  # la moulinette ne doit jamais s'arreter
                results.append(TaskResult(task.ident, task.name, FAIL,
                                          ["erreur interne de la moulinette :",
                                           traceback.format_exc(limit=3)]))
                continue
            if check.skipped:
                status = SKIP
                details = [check.skipped]
            else:
                status = PASS if check.ok else FAIL
                details = check.details
            score = (check.passed, check.total) if check.total else None
            results.append(TaskResult(task.ident, task.name, status,
                                      details, score))
    results.append(clean_repo_check(repo, day, files))
    return results, True


def day_score(results):
    graded = [r for r in results if r.status in (PASS, FAIL, TODO)]
    done = [r for r in graded if r.status == PASS]
    return len(done), len(graded)


def text_report(day, results, started):
    done, total = day_score(results)
    lines = ["", "=" * 72,
             "%s  [%d/%d]%s" % (day.folder, done, total,
                                "" if started else "  (non commence)"),
             "=" * 72]
    if not started:
        return "\n".join(lines)
    for res in results:
        score = " (%d/%d)" % res.score if res.score else ""
        lines.append("%s %-4s %-34s %s%s" % (ICONS[res.status], res.ident,
                                              res.name, LABELS[res.status], score))
        for detail in res.details[:15]:
            lines.append("        - " + detail)
        if len(res.details) > 15:
            lines.append("        - ... (%d autres)" % (len(res.details) - 15))
    return "\n".join(lines)


def md_escape(text):
    for char in "\\`*_[]|":
        text = text.replace(char, "\\" + char)
    return text.replace("\n", " ").replace("<", "&lt;")


def markdown_report(report):
    out = ["# 🏊 Correction de la piscine", "",
           "| Journee | Exercices valides | |", "|---|---|---|"]
    for day, results, started in report:
        done, total = day_score(results)
        if not started:
            state = "⏳ non commencee"
        elif any(r.status == FAIL for r in results):
            state = "❌ a corriger"
        else:
            state = "✅ tout est bon"
        out.append("| %s | %d / %d | %s |" % (day.folder, done, total, state))
    for day, results, started in report:
        if not started:
            continue
        done, total = day_score(results)
        out += ["", "<details%s><summary><b>%s</b> — %d / %d</summary>"
                % (" open" if any(r.status == FAIL for r in results) else "",
                   md_escape(day.folder), done, total), "",
                "| # | Exercice | Resultat | Details |", "|---|---|---|---|"]
        for res in results:
            score = " %d/%d" % res.score if res.score else ""
            details = "<br>".join(md_escape(d)[:400] for d in res.details[:10])
            if len(res.details) > 10:
                details += "<br>... (%d autres)" % (len(res.details) - 10)
            out.append("| %s | `%s` | %s %s%s | %s |"
                       % (res.ident, res.name, ICONS[res.status],
                          LABELS[res.status], score, details))
        out += ["", "</details>"]
    return "\n".join(out) + "\n"


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument("days", nargs="*",
                        help="filtre sur le nom des journees (ex: 'Day 03')")
    parser.add_argument("--repo", default=Path(__file__).resolve().parent.parent,
                        type=Path, help="racine du depot a corriger")
    parser.add_argument("--summary", help="ecrit un rapport Markdown")
    args = parser.parse_args()

    repo = args.repo.resolve()
    days = [d for d in DAYS
            if not args.days or any(f.lower() in d.folder.lower() for f in args.days)]
    if not days:
        parser.error("aucune journee ne correspond a %s" % args.days)
    report = []
    failed = False
    for day in days:
        results, started = grade_day(repo, day)
        report.append((day, results, started))
        failed = failed or any(r.status == FAIL for r in results)
        print(text_report(day, results, started), flush=True)
    if args.summary:
        with open(args.summary, "a", encoding="utf-8") as handle:
            handle.write(markdown_report(report))
    print("\n" + ("Des exercices rendus sont a corriger." if failed
                  else "Tous les exercices rendus sont valides."))
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
