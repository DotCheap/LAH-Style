# Day 03 : premiers pas en C

Sujet officiel : [B-CPE-100_Day03.pdf](B-CPE-100_Day03.pdf).

Premières fonctions d'affichage avec `my_putchar`.

## Règles

- Rendu dans [`rendu/day03/`](../../rendu/day03/).
- Compilation : `gcc -Wall -Wextra -Werror` (un warning suffit à refuser la tâche).
- Pas de `main` dans les fichiers rendus, sauf pour les programmes.
- Les tests tournent avec AddressSanitizer et UndefinedBehaviorSanitizer.
- Seule `my_putchar` est autorisée : elle est fournie par la correction, ne la rendez pas.
- Les fonctions renvoient `0`.

## Tâches

| Tâche | À rendre | Ce qu'il faut faire | Correction |
|---|---|---|---|
| task00 | — | Lire la norme : [`coding-style.pdf`](../coding-style.pdf). | manuelle |
| task01 | `my_print_alpha.c` | Afficher l'alphabet de `a` à `z`. | automatique |
| task02 | `my_print_revalpha.c` | Afficher l'alphabet de `z` à `a`. | automatique |
| task03 | `my_print_digits.c` | Afficher les chiffres de `0` à `9`. | automatique |
| task04 | `my_isneg.c` | Afficher `N` si le nombre est négatif, `P` sinon. | automatique |
| task05 | `my_print_comb.c` | Afficher toutes les combinaisons de 3 chiffres différents croissants : `012, 013, …, 789`. | automatique |
| task06 | `my_print_comb2.c` | Afficher toutes les paires de nombres à 2 chiffres : `00 01, 00 02, …, 98 99`. | automatique |
| task07 | `my_put_nbr.c` | Afficher un `int`, y compris `-2147483648`. | automatique |
| task08 | — | Écrire `tests/tests_my_put_nbr.c`, un `main` qui teste `my_put_nbr`. | manuelle |
| task09 | `my_print_combn.c` | Généraliser `my_print_comb` à `n` chiffres. | automatique |

## Corriger en local

```sh
.github/correction/corriger.sh day03
```
