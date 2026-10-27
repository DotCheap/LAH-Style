# Rush 1 : les carrés

Sujet officiel : [B-CPE-100_Rush1.pdf](B-CPE-100_Rush1.pdf).

Afficher des rectangles de 5 styles différents avec `rush(x, y)`.

## Règles

- Rendu dans [`rendu/rush1/`](../../rendu/rush1/).
- Compilation : `gcc -Wall -Wextra -Werror` (un warning suffit à refuser la tâche).
- Pas de `main` dans les fichiers rendus, sauf pour les programmes.
- Les tests tournent avec AddressSanitizer et UndefinedBehaviorSanitizer.
- Fonctions autorisées : `my_putchar` (fournie, ne la rendez pas) et `write`.
- Taille invalide : `Invalid size\n` sur la sortie d'erreur.
- Les binaires de référence de l'intranet sont dans [`fournis/`](fournis/).

## Tâches

| Tâche | À rendre | Ce qu'il faut faire | Correction |
|---|---|---|---|
| assignment1 | `rush-1-1/*.c` | `rush-1-1/` : style 1. | automatique |
| assignment2 | `rush-1-2/*.c` | `rush-1-2/` : style 2. | automatique |
| assignment3 | `rush-1-3/*.c` | `rush-1-3/` : style 3. | automatique |
| assignment4 | `rush-1-4/*.c` | `rush-1-4/` : style 4. | automatique |
| assignment5 | `rush-1-5/*.c` | `rush-1-5/` : style 5. | automatique |

## Corriger en local

```sh
.github/correction/corriger.sh rush1
```
