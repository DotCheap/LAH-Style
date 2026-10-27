# Count Island

Sujet officiel : [B-CPE-100_CountIsland.pdf](B-CPE-100_CountIsland.pdf).

Numéroter les îles d'une carte, en récursif.

## Règles

- Rendu dans [`rendu/countisland/`](../../rendu/countisland/).
- Lié avec votre libmy (`lib/my/*.c`, `include/`).
- Compilation : `gcc -Wall -Wextra -Werror` (un warning suffit à refuser la tâche).
- Pas de `main` dans les fichiers rendus, sauf pour les programmes.
- Les tests tournent avec AddressSanitizer et UndefinedBehaviorSanitizer.
- Fonction système autorisée : `write`.

## Tâches

| Tâche | À rendre | Ce qu'il faut faire | Correction |
|---|---|---|---|
| task01 | `count_island.c` | `count_island(world)` : remplace les `X` de chaque île par son numéro (ordre d'apparition) et renvoie le nombre d'îles. | automatique |
| tests | — | Tests unitaires de toutes les fonctions. | manuelle |

## Corriger en local

```sh
.github/correction/corriger.sh countisland
```
