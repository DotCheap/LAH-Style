# Day 06 : retour des pointeurs

Sujet officiel : [B-CPE-100_Day06.pdf](B-CPE-100_Day06.pdf).

Recoder les fonctions de `string.h`, et premiers tests unitaires avec Criterion.

## Règles

- Rendu dans [`rendu/day06/`](../../rendu/day06/).
- Compilation : `gcc -Wall -Wextra -Werror` (un warning suffit à refuser la tâche).
- Pas de `main` dans les fichiers rendus, sauf pour les programmes.
- Les tests tournent avec AddressSanitizer et UndefinedBehaviorSanitizer.
- Seule `my_putchar` est autorisée ; aucune fonction de `string.h`.
- Tests unitaires : Criterion doit être installé (`install_criterion.sh` à la racine). La correction compile `tests/test_<fonction>.c` avec `<fonction>.c`, lance les tests et mesure la couverture (lignes exécutées, branches prises au moins une fois).

## Tâches

| Tâche | À rendre | Ce qu'il faut faire | Correction |
|---|---|---|---|
| task01 | `my_strcpy.c` | Copier une chaîne. | automatique |
| task02 | `my_strncpy.c` | Copier au plus `n` caractères (complète avec des `\0`). | automatique |
| task03 | `my_revstr.c` | Inverser une chaîne. | automatique |
| task04 | `tests/test_my_strncpy.c` `tests/test_my_revstr.c` | Tests Criterion de `my_strncpy` et `my_revstr` : couverture ≥ 60 % des lignes, ≥ 40 % des branches. | automatique |
| task05 | `my_strstr.c` | Recoder `strstr`. | automatique |
| task06 | `my_strcmp.c` | Recoder `strcmp`. | automatique |
| task07 | `my_strncmp.c` | Recoder `strncmp`. | automatique |
| task08 | `my_strupcase.c` | Passer une chaîne en majuscules. | automatique |
| task09 | `my_strlowcase.c` | Passer une chaîne en minuscules. | automatique |
| task10 | `my_strcapitalize.c` | Majuscule au début de chaque mot, minuscules ailleurs. | automatique |
| task11 | `tests/test_my_strstr.c` `tests/test_my_strncmp.c` `tests/test_my_strcapitalize.c` | Tests Criterion de `my_strstr`, `my_strncmp`, `my_strcapitalize` : ≥ 80 % des lignes, ≥ 60 % des branches. | automatique |
| task12 | `my_str_isalpha.c` | `1` si la chaîne ne contient que des lettres. | automatique |
| task13 | `my_str_isnum.c` | `1` si la chaîne ne contient que des chiffres. | automatique |
| task14 | `my_str_islower.c` | `1` si la chaîne ne contient que des minuscules. | automatique |
| task15 | `my_str_isupper.c` | `1` si la chaîne ne contient que des majuscules. | automatique |
| task16 | `my_str_isprintable.c` | `1` si la chaîne ne contient que des caractères imprimables. | automatique |
| task17 | `tests/test_my_str_isalpha.c` `tests/test_my_str_islower.c` `tests/test_my_str_isprintable.c` | Tests Criterion de `my_str_isalpha`, `my_str_islower`, `my_str_isprintable` : 100 % des lignes, ≥ 80 % des branches. | automatique |
| task18 | `my_putnbr_base.c` | Afficher un nombre dans une base donnée par ses symboles. | automatique |
| task19 | `my_getnbr_base.c` | Convertir une chaîne écrite dans une base en `int`. | automatique |
| task20 | `my_showstr.c` | Afficher une chaîne, les non imprimables en `\xx` hexadécimal. | automatique |
| task21 | `my_showmem.c` | Afficher un dump mémoire (adresse, hexadécimal, caractères), 16 octets par ligne. | automatique |

## Corriger en local

```sh
.github/correction/corriger.sh day06
```
