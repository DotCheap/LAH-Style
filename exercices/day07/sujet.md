# Day 07 : libmy et arguments

Sujet officiel : [B-CPE-100_Day07.pdf](B-CPE-100_Day07.pdf).

Construire sa bibliothèque `libmy.a` et écrire ses premiers programmes.

## Règles

- Rendu dans [`rendu/day07/`](../../rendu/day07/).
- Les fonctions sont liées avec votre libmy, construite depuis `lib/my/*.c` ; les headers vont dans `include/`.
- Compilation : `gcc -Wall -Wextra -Werror` (un warning suffit à refuser la tâche).
- Pas de `main` dans les fichiers rendus, sauf pour les programmes.
- Les tests tournent avec AddressSanitizer et UndefinedBehaviorSanitizer.
- Fonction système autorisée : `write`.

## Tâches

| Tâche | À rendre | Ce qu'il faut faire | Correction |
|---|---|---|---|
| task01 | `lib/my/build.sh` | `lib/my/build.sh` construit `lib/my/libmy.a` avec les 30 fonctions listées dans le sujet. | automatique |
| task02 | `my_strcat.c` | Concaténer deux chaînes. | automatique |
| task03 | `my_strncat.c` | Concaténer au plus `nb` caractères. | automatique |
| task04 | `task04/*.c` | Programme `task04/` : affiche ses arguments, un par ligne. | automatique |
| task05 | `task05/*.c` | Programme `task05/` : affiche ses arguments dans l'ordre inverse. | automatique |
| task06 | `task06/*.c` | Programme `task06/` : affiche ses arguments triés (ordre ASCII). | automatique |

## Corriger en local

```sh
.github/correction/corriger.sh day07
```
