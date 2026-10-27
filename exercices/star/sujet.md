# Star

Sujet officiel : [B-CPE-100_Star.pdf](B-CPE-100_Star.pdf).

Afficher une étoile de taille donnée.

## Règles

- Rendu dans [`rendu/star/`](../../rendu/star/).
- Compilation : `gcc -Wall -Wextra -Werror` (un warning suffit à refuser la tâche).
- Pas de `main` dans les fichiers rendus, sauf pour les programmes.
- Les tests tournent avec AddressSanitizer et UndefinedBehaviorSanitizer.
- Fonctions autorisées : `my_putchar` (fournie) et `write`.
- Exemples officiels : [`fournis/B-CPE-100_Star_examples.txt`](fournis/B-CPE-100_Star_examples.txt).

## Tâches

| Tâche | À rendre | Ce qu'il faut faire | Correction |
|---|---|---|---|
| task01 | `star.c` | `star(size)` : étoile de taille `size` (rien pour 0). | automatique |

## Corriger en local

```sh
.github/correction/corriger.sh star
```
