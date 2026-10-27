# Piscine C (B-CPE-100 / B-CPE-101)

Ce dépôt contient **uniquement les sujets** de la piscine. À toi de faire les
exercices : chaque `git push` déclenche une **moulinette** (GitHub Actions)
qui corrige ton travail en respectant les consignes de rendu des sujets.

## Organisation

Chaque journée a son dossier, avec son sujet en PDF (et ses éventuelles
ressources) :

| Dossier | Contenu fourni |
|---|---|
| `Day 01 - Unix environments` | sujet |
| `Day 02 - Shell language` | sujet + ressources dans `Day02/` |
| `Day 03 - First C Programming` | sujet + `others/my_putchar.c` |
| `Day 04` à `Day 09` | sujet |
| `Day 10 - Makefile and do-ops` | sujet + `resources/my_opp.h` |
| `Day 11` à `Day 13` | sujet |
| `Rush 1 - The Squares` | sujet + binaires de test dans `others/` |
| `Rush 2 - What language is this?` | sujet |
| `Project 1 - Star` | sujet + exemples dans `others/` |
| `Project 2 - Countisland` | sujet |
| `Part 2 - InfinAdd`, `Part 2 - EvalExpr`, `Part 2 - Bistromatic` | sujets (+ `subject/` pour la Bistromatic) |
| `Part 2 - Final Stumper` | sujet + binaires de référence (`rush1_bins.tgz`, `rush3.tgz`) |

`Epitech C Coding Style.pdf` décrit la norme à respecter.

## Comment travailler

1. Va dans le dossier de la journée et lis le sujet **en entier**.
2. Rends chaque exercice **exactement** à l'emplacement indiqué par
   `Delivery:` dans le sujet, **relatif au dossier de la journée**.
   Quand le sujet parle de « la racine du dépôt du jour », c'est la racine
   du dossier de la journée.

   ```
   Day 03 - First C Programming/
   ├── B-CPE-100_Day03.pdf
   ├── my_print_alpha.c          <- Delivery: my_print_alpha.c
   ├── my_put_nbr.c
   └── tests/
       └── tests_my_put_nbr.c    <- Delivery: tests/tests_my_put_nbr.c
   ```
3. `git add`, `git commit`, `git push` régulièrement : chaque push est corrigé.

Les règles des sujets sont appliquées, en particulier :

- pas de `main` dans les fichiers de fonctions : la moulinette ajoute le sien ;
- Day 03 à Day 05, Rush 1, Star : seule `my_putchar` est autorisée, et il ne
  faut pas la rendre (la moulinette fournit la sienne) ;
- uniquement les fonctions de la libC autorisées par chaque sujet
  (`write`, `malloc`, `free`...) ;
- tous les `.c` d'un dossier doivent compiler ensemble (« `gcc *.c` ») ;
- `libmy` construite par `lib/my/build.sh` (Day 07 à 09, Rush 2,
  CountIsland) ou par `lib/my/Makefile` (à partir du Day 10) ;
- Makefiles avec les règles demandées et **sans relink** ;
- **aucun fichier inutile** dans le dépôt : binaires, `.o`, `.a`, `a.out`,
  fichiers temporaires, `.idea/`... (utilise un `.gitignore`).

Quelques précisions :

- Day 01, task06 : git ne versionne pas les dossiers vides, ajoute un
  fichier `.gitkeep` dans `1950s/` et dans `Isotopes/participants/`.
- Day 09 : la moulinette fournit `struct info_param` si tes fichiers ne la
  définissent pas.
- Day 10, task 05 : copie `resources/my_opp.h` dans `include/` et définis
  `struct operator` (champ chaîne, puis pointeur `int (*)(int, int)`) dans
  un autre header de `include/`.

## Voir sa note

Sur GitHub, onglet **Actions** → dernier run **Moulinette** → **Summary** :

- un tableau récapitule chaque journée (✅ tout est bon, ❌ à corriger,
  ⏳ non commencée) ;
- le détail de chaque exercice indique ce qui était attendu et ce qui a été
  obtenu ;
- un second rapport, **indicatif**, liste les fautes de coding style
  (outil officiel `coding-style-checker` d'Epitech).

Le run est rouge tant qu'un exercice **rendu** est faux. Les exercices pas
encore rendus ne comptent pas comme des erreurs.

## Lancer la moulinette en local

```bash
./install_criterion.sh            # une fois (tests unitaires du Day 06 et du Day 12)
./install_csfml.sh                # une fois (Day 13)
python3 .moulinette/grade.py "Day 03"   # une journée
python3 .moulinette/grade.py            # tout
```

La moulinette travaille sur une copie temporaire : elle ne modifie jamais
tes fichiers. Le dossier `.moulinette/` contient les tests ; ne le modifie
pas.
