# Day 04 : pointeurs

Sujet officiel : [B-CPE-100_Day04.pdf](B-CPE-100_Day04.pdf).

Pointeurs, chaînes de caractères et tableaux.

## Règles

- Rendu dans [`rendu/day04/`](../../rendu/day04/).
- Compilation : `gcc -Wall -Wextra -Werror` (un warning suffit à refuser la tâche).
- Pas de `main` dans les fichiers rendus, sauf pour les programmes.
- Les tests tournent avec AddressSanitizer et UndefinedBehaviorSanitizer.
- Seule `my_putchar` est autorisée (fournie par la correction).

## Tâches

| Tâche | À rendre | Ce qu'il faut faire | Correction |
|---|---|---|---|
| task01 | `my_swap.c` | Échanger deux entiers via leurs adresses. | automatique |
| task02 | `my_putstr.c` | Afficher une chaîne caractère par caractère. | automatique |
| task03 | `my_strlen.c` | Longueur d'une chaîne. | automatique |
| task04 | `my_evil_str.c` | Inverser une chaîne sur place et la renvoyer. | automatique |
| task05 | `my_getnbr.c` | Convertir une chaîne en `int` : suite de `+`/`-`, puis chiffres ; `0` si le nombre dépasse un `int`. | automatique |
| task06 | `my_sort_int_array.c` | Trier un tableau d'entiers par ordre croissant. | automatique |

## Corriger en local

```sh
.github/correction/corriger.sh day04
```
