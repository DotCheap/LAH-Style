# Day 12 : descripteurs de fichiers

Sujet officiel : [B-CPE-100_Day12.pdf](B-CPE-100_Day12.pdf).

Recoder `cat` et `grep` avec `open`, `read`, `write`, `close`.

## Règles

- Rendu dans [`rendu/day12/`](../../rendu/day12/).
- Chaque programme a son Makefile (`all`, `clean`, `fclean`, `re`, sans relink).
- Les sorties sont comparées octet par octet à celles de `cat` et `grep -F`.
- Erreurs sur la sortie d'erreur, code de retour 84.

## Tâches

| Tâche | À rendre | Ce qu'il faut faire | Correction |
|---|---|---|---|
| task01 | `cat/Makefile` | `cat/` : binaire `cat`, fonctions autorisées `open read write close` (pas de `malloc`). | automatique |
| task02 | `cat/Makefile` `tests` | Règle `tests_run` dans `cat/Makefile` qui lance les tests unitaires de `tests/`. | automatique |
| task03 | `grep/Makefile` | `grep/` : binaire `grep` (recherche simple, sans regex), `malloc` et `free` autorisés. | automatique |
| task04 | `grep/Makefile` `tests` | Règle `tests_run` dans `grep/Makefile`. | automatique |

## Corriger en local

```sh
.github/correction/corriger.sh day12
```
