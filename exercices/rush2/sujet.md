# Rush 2 : quelle est cette langue ?

Sujet officiel : [B-CPE-100_Rush2.pdf](B-CPE-100_Rush2.pdf).

Compter les lettres d'un texte, calculer leurs fréquences et deviner la langue.

## Règles

- Rendu dans [`rendu/rush2/`](../../rendu/rush2/).
- Construit comme l'autograder : libmy depuis `lib/my/*.c`, puis `gcc -o rush2 *.c -I./include -lmy`.
- Fonction système autorisée : `write`.
- Les textes de test sont dans `.github/correction/rush2/textes/`.

## Tâches

| Tâche | À rendre | Ce qu'il faut faire | Correction |
|---|---|---|---|
| task01 | `*.c` | Étapes 1 et 2 : `lettre:nombre` pour chaque lettre demandée (sans tenir compte de la casse). | automatique |
| task02 | `*.c` | Étape 3 : fréquence avec deux décimales, `a:3 (6.25%)`. | automatique |
| task03 | `*.c` | Étape 4 : dernière ligne `=> English`, `French`, `German` ou `Spanish`. | automatique |

## Corriger en local

```sh
.github/correction/corriger.sh rush2
```
