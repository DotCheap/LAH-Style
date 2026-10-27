# Exercices

Un dossier par jour ou par projet de la piscine, avec :

- le **sujet officiel en PDF** ;
- un **`sujet.md`** qui liste les tâches : fichier à rendre, ce qu'il faut faire, et si la tâche est corrigée automatiquement ;
- parfois un dossier **`fournis/`** avec les fichiers donnés par le sujet.

La norme de code Epitech est dans [`coding-style.pdf`](coding-style.pdf).

| Dossier | Sujet | Tâches corrigées automatiquement |
|---|---|---|
| [`day01`](day01/sujet.md) | Day 01 : environnement Unix | 7 / 7 |
| [`day02`](day02/sujet.md) | Day 02 : langage shell | 7 / 7 |
| [`day03`](day03/sujet.md) | Day 03 : premiers pas en C | 8 / 10 |
| [`day04`](day04/sujet.md) | Day 04 : pointeurs | 6 / 6 |
| [`day05`](day05/sujet.md) | Day 05 : récursivité | 8 / 8 |
| [`day06`](day06/sujet.md) | Day 06 : retour des pointeurs | 21 / 21 |
| [`day07`](day07/sujet.md) | Day 07 : libmy et arguments | 6 / 6 |
| [`day08`](day08/sujet.md) | Day 08 : compilation et allocation | 5 / 5 |
| [`day09`](day09/sujet.md) | Day 09 : structures | 6 / 6 |
| [`day10`](day10/sujet.md) | Day 10 : Makefile et do-op | 4 / 5 |
| [`day11`](day11/sujet.md) | Day 11 : listes chaînées | 11 / 11 |
| [`day12`](day12/sujet.md) | Day 12 : descripteurs de fichiers | 4 / 4 |
| [`day13`](day13/sujet.md) | Day 13 : découverte de CSFML | correction manuelle |
| [`rush1`](rush1/sujet.md) | Rush 1 : les carrés | 5 / 5 |
| [`rush2`](rush2/sujet.md) | Rush 2 : quelle est cette langue ? | 3 / 3 |
| [`star`](star/sujet.md) | Star | 1 / 1 |
| [`countisland`](countisland/sujet.md) | Count Island | 1 / 2 |
| [`infinadd`](infinadd/sujet.md) | InfinAdd | 1 / 1 |
| [`evalexpr`](evalexpr/sujet.md) | EvalExpr | 1 / 1 |
| [`bistromatic`](bistromatic/sujet.md) | Bistro-matic | 1 / 1 |
| [`final_stumper`](final_stumper/sujet.md) | Final Stumper | 1 / 1 |

## Ajouter ou modifier un test

Les tests sont dans `.github/correction/<dossier>/<tâche>/` :

- `config` : fichiers à rendre (`FILES`), fonctions autorisées (`ALLOWED`), mode de test, etc. (la liste complète des variables est en tête de `.github/correction/corriger.sh`) ;
- `test.c` (+ `expected.txt`) pour tester des fonctions, ou `test.sh` pour tester des programmes et des scripts (fonctions utiles dans `.github/correction/lib/test_lib.sh`).
