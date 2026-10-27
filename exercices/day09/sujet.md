# Day 09 : structures

Sujet officiel : [B-CPE-100_Day09.pdf](B-CPE-100_Day09.pdf).

Macros, headers, structures, opérations bit à bit et unions.

## Règles

- Rendu dans [`rendu/day09/`](../../rendu/day09/).
- Liés avec votre libmy (`lib/my/*.c`, `include/`).
- Compilation : `gcc -Wall -Wextra -Werror` (un warning suffit à refuser la tâche).
- Pas de `main` dans les fichiers rendus, sauf pour les programmes.
- Les tests tournent avec AddressSanitizer et UndefinedBehaviorSanitizer.
- Fonctions autorisées : `write`, `malloc`, `free`.
- La structure `struct info_param` est fournie par la correction : ne la rendez pas, incluez `info_param.h` (copie dans [`fournis/info_param.h`](fournis/info_param.h)).

## Tâches

| Tâche | À rendre | Ce qu'il faut faire | Correction |
|---|---|---|---|
| task01 | `include/my_macro_abs.h` | Macro `ABS(value)` dans `include/my_macro_abs.h` (attention aux parenthèses). | automatique |
| task02 | `include/my.h` | `include/my.h` : prototypes de toutes les fonctions de la libmy, protégé contre la double inclusion. | automatique |
| task03 | `my_params_to_array.c` | Ranger les arguments dans un tableau de `struct info_param` (fin : `str` à `0`). | automatique |
| task04 | `my_show_param_array.c` | Afficher ce tableau : argument, longueur, puis les mots, un par ligne. | automatique |
| task05 | `get_color.c` | Couleur `0xRRGGBB` à partir de ses composantes, avec des décalages de bits. | automatique |
| task06 | `swap_endian_color.c` | Inverser l'ordre des octets d'une couleur, avec une union. | automatique |

## Corriger en local

```sh
.github/correction/corriger.sh day09
```
