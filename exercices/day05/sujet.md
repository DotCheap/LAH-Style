# Day 05 : récursivité

Sujet officiel : [B-CPE-100_Day05.pdf](B-CPE-100_Day05.pdf).

Fonctions mathématiques itératives et récursives.

## Règles

- Rendu dans [`rendu/day05/`](../../rendu/day05/).
- Compilation : `gcc -Wall -Wextra -Werror` (un warning suffit à refuser la tâche).
- Pas de `main` dans les fichiers rendus, sauf pour les programmes.
- Les tests tournent avec AddressSanitizer et UndefinedBehaviorSanitizer.
- Seule `my_putchar` est autorisée.
- Réponse en moins de 2 secondes ; les dépassements d'`int` renvoient `0`.
- Les fonctions `_it` ne doivent pas s'appeler elles-mêmes, les `_rec` si.

## Tâches

| Tâche | À rendre | Ce qu'il faut faire | Correction |
|---|---|---|---|
| task01 | `my_compute_factorial_it.c` | Factorielle itérative (`0` si négatif ou trop grand). | automatique |
| task02 | `my_compute_factorial_rec.c` | Factorielle récursive. | automatique |
| task03 | `my_compute_power_it.c` | Puissance itérative (`0` si `p < 0` ou dépassement). | automatique |
| task04 | `my_compute_power_rec.c` | Puissance récursive. | automatique |
| task05 | `my_compute_square_root.c` | Racine carrée entière, `0` si elle n'est pas entière. | automatique |
| task06 | `my_is_prime.c` | `1` si le nombre est premier, `0` sinon. | automatique |
| task07 | `my_find_prime_sup.c` | Plus petit nombre premier supérieur ou égal. | automatique |
| task08 | `count_valid_queens_placements.c` | Nombre de façons de placer `n` dames sur un échiquier `n × n` (récursif). | automatique |

## Corriger en local

```sh
.github/correction/corriger.sh day05
```
