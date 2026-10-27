#!/usr/bin/env python3
"""Transforme le rapport du coding-style-checker d'Epitech en Markdown,
regroupe par journee. Ce rapport est indicatif : il ne bloque pas."""

import sys
from collections import defaultdict

ICON = {"FATAL": "💀", "MAJOR": "🔴", "MINOR": "🟠", "INFO": "🔵"}


def main():
    path = sys.argv[1] if len(sys.argv) > 1 else "coding-style-reports.log"
    print("# 🎨 Coding style (indicatif)\n")
    try:
        with open(path, encoding="utf-8", errors="replace") as handle:
            lines = [line.strip() for line in handle if line.strip()]
    except OSError:
        print("Le rapport du coding-style-checker est introuvable "
              "(l'image Docker n'a peut-etre pas pu etre telechargee).")
        return 0
    days = defaultdict(list)
    for line in lines:
        # Format : ./Dossier/fichier.c:12: MAJOR:C-O1
        try:
            location, severity, rule = line.rsplit(":", 2)
            filename, number = location.rsplit(":", 1)
        except ValueError:
            continue
        filename = filename[2:] if filename.startswith("./") else filename
        if filename.startswith(".moulinette/") or filename.startswith(".github/"):
            continue
        folder = filename.split("/", 1)[0] if "/" in filename else "(racine)"
        days[folder].append((severity.strip(), rule.strip(), filename, number))
    if not days:
        print("✅ Aucune faute de coding style detectee.")
        return 0
    print("| Journee | 💀 Fatal | 🔴 Major | 🟠 Minor | 🔵 Info |")
    print("|---|---|---|---|---|")
    for folder in sorted(days):
        count = defaultdict(int)
        for severity, *_ in days[folder]:
            count[severity] += 1
        print("| %s | %d | %d | %d | %d |" % (folder, count["FATAL"], count["MAJOR"],
                                            count["MINOR"], count["INFO"]))
    for folder in sorted(days):
        print("\n<details><summary><b>%s</b> (%d)</summary>\n" % (folder, len(days[folder])))
        for severity, rule, filename, number in sorted(days[folder], key=lambda e: (e[2], int(e[3]) if e[3].isdigit() else 0)):
            name = filename.split("/", 1)[1] if "/" in filename else filename
            print("- %s `%s` ligne %s : **%s**" % (ICON.get(severity, ""), name, number, rule))
        print("\n</details>")
    print("\nLes regles sont decrites dans `Epitech C Coding Style.pdf`.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
