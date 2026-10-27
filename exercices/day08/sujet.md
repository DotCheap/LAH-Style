# Day 08 : compilation et allocation

Sujet officiel : [B-CPE-100_Day08.pdf](B-CPE-100_Day08.pdf).

Allocation dynamique avec `malloc` et `free`.

## Règles

- Rendu dans [`rendu/day08/`](../../rendu/day08/).
- Liés avec votre libmy (`lib/my/*.c`, `include/`).
- Compilation : `gcc -Wall -Wextra -Werror` (un warning suffit à refuser la tâche).
- Pas de `main` dans les fichiers rendus, sauf pour les programmes.
- Les tests tournent avec AddressSanitizer et UndefinedBehaviorSanitizer.
- Fonctions autorisées : `write`, `malloc`, `free`.

## Tâches

| Tâche | À rendre | Ce qu'il faut faire | Correction |
|---|---|---|---|
| task01 | `my_strdup.c` | Dupliquer une chaîne dans une zone allouée. | automatique |
| task02 | `concat_params.c` | Concaténer les arguments en une chaîne, séparés par `\n`. | automatique |
| task03 | `my_show_word_array.c` | Afficher un tableau de mots, un par ligne. | automatique |
| task04 | `my_str_to_word_array.c` | Découper une chaîne en mots (séparateurs : tout ce qui n'est pas alphanumérique), tableau terminé par `NULL`. | automatique |
| task05 | `convert_base.c` | Convertir un nombre d'une base vers une autre, dans une chaîne allouée. | automatique |

## Corriger en local

```sh
.github/correction/corriger.sh day08
```
