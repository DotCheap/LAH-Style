# Day 02 : langage shell

Sujet officiel : [B-CPE-100_Day02.pdf](B-CPE-100_Day02.pdf).

Scripts bash : filtres, `find`, `sed`, `cut`, `sort`, variables d'environnement.

## Règles

- Rendu dans [`rendu/day02/`](../../rendu/day02/).
- Chaque script commence par un shebang (`#!/bin/bash`) et est exécutable.
- Les ressources du sujet sont dans [`fournis/`](fournis/). Attention : le `passwd` fourni a perdu ses retours à la ligne (remplacés par des espaces) ; les tests utilisent leurs propres données au format passwd normal.
- `fournis/task05` est l'énoncé chiffré de la tâche 5 (clé `LONEYTUSARFPDHIKZBCGJMQVWX`).

## Tâches

| Tâche | À rendre | Ce qu'il faut faire | Correction |
|---|---|---|---|
| task01 | `how_many_are_we.sh` | `how_many_are_we.sh` : nombre d'étudiants d'une ville (lu sur l'entrée standard), ou le total sans argument. | automatique |
| task02 | `find_sh.sh` | `find_sh.sh` : noms des fichiers `.sh` du dossier courant et des sous-dossiers. | automatique |
| task03 | `count_files.sh` | `count_files.sh` : nombre de fichiers réguliers du dossier courant et des sous-dossiers. | automatique |
| task04 | `gotta_catch_them_all.sh` | `gotta_catch_them_all.sh` : nombre de personnes dont le nom de famille commence par l'argument. | automatique |
| task05 | `looneytised.sh` | `looneytised.sh` (énoncé chiffré) : remplace `theo1`, `steven1`, `arnaud1`, `pierre-jean` par des Looney Tunes et n'affiche que ces lignes. | automatique |
| task06 | `skip.sh` | `skip.sh` : affiche une ligne sur deux de l'entrée, en commençant par la première. | automatique |
| task07 | `r_tacpy.sh` | `r_tacpy.sh` : logins d'une ligne sur deux (à partir de la 2e), inversés, triés à l'envers, entre `MY_LINE1` et `MY_LINE2`, séparés par `, ` et finis par `.`. | automatique |

## Corriger en local

```sh
.github/correction/corriger.sh day02
```
