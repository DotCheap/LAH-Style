# Day 10 : Makefile et do-op

Sujet officiel : [B-CPE-100_Day10.pdf](B-CPE-100_Day10.pdf).

Makefiles, pointeurs sur fonctions.

## Règles

- Rendu dans [`rendu/day10/`](../../rendu/day10/).
- Liés avec votre libmy (`lib/my/*.c`, `include/`).
- Compilation : `gcc -Wall -Wextra -Werror` (un warning suffit à refuser la tâche).
- Pas de `main` dans les fichiers rendus, sauf pour les programmes.
- Les tests tournent avec AddressSanitizer et UndefinedBehaviorSanitizer.
- Fonctions autorisées : `write`, `malloc`, `free`.
- Les Makefiles ne doivent pas relinker si rien n'a changé.

## Tâches

| Tâche | À rendre | Ce qu'il faut faire | Correction |
|---|---|---|---|
| task01 | `lib/my/Makefile` | `lib/my/Makefile` : construit la libmy, copie `libmy.a` dans `lib/` et `my.h` dans `include/`, règle `clean`. | automatique |
| task02 | `do_op/Makefile` | Programme `do-op` (dossier `do_op/` avec Makefile) : `./do-op 1 + 1` ; erreurs sur `stderr` et code 84. | automatique |
| task03 | `my_sort_word_array.c` | Trier un tableau de mots (ordre ASCII) en échangeant les pointeurs. | automatique |
| task04 | `my_advanced_sort_word_array.c` | Même chose avec une fonction de comparaison passée en paramètre. | automatique |
| task05 | — | `my_advanced_do-op` : nécessite le fichier `my_opp.h` de l'intranet, absent du dépôt. | manuelle |

## Corriger en local

```sh
.github/correction/corriger.sh day10
```
