# Day 11 : listes chaînées

Sujet officiel : [B-CPE-100_Day11.pdf](B-CPE-100_Day11.pdf).

Manipuler des listes chaînées `linked_list_t`.

## Règles

- Rendu dans [`rendu/day11/`](../../rendu/day11/).
- Liés avec votre libmy (`lib/my/*.c`, `include/`). La structure est dans `include/mylist.h`.
- Compilation : `gcc -Wall -Wextra -Werror` (un warning suffit à refuser la tâche).
- Pas de `main` dans les fichiers rendus, sauf pour les programmes.
- Les tests tournent avec AddressSanitizer et UndefinedBehaviorSanitizer.
- Fonctions autorisées : `write`, `malloc`, `free`.

## Tâches

| Tâche | À rendre | Ce qu'il faut faire | Correction |
|---|---|---|---|
| task01 | `my_params_to_list.c` | Créer une liste depuis les arguments (le dernier argument en tête). | automatique |
| task02 | `my_list_size.c` | Nombre d'éléments. | automatique |
| task03 | `my_rev_list.c` | Inverser la liste. | automatique |
| task04 | `my_apply_on_nodes.c` | Appliquer une fonction à chaque élément. | automatique |
| task05 | `my_apply_on_matching_nodes.c` | Appliquer une fonction aux éléments égaux à une donnée de référence. | automatique |
| task06 | `my_find_node.c` | Trouver le premier élément égal à une donnée de référence. | automatique |
| task07 | `my_delete_nodes.c` | Supprimer tous les éléments égaux à une donnée de référence. | automatique |
| task08 | `my_concat_list.c` | Accrocher une liste au bout d'une autre (sans créer d'élément). | automatique |
| task09 | `my_sort_list.c` | Trier la liste. | automatique |
| task10 | `my_add_in_sorted_list.c` | Insérer un élément dans une liste triée. | automatique |
| task11 | `my_merge.c` | Fusionner deux listes triées. | automatique |

## Corriger en local

```sh
.github/correction/corriger.sh day11
```
