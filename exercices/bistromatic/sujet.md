# Bistro-matic

Sujet officiel : [B-CPE-101_Bistro-matic.pdf](B-CPE-101_Bistro-matic.pdf).

Calculatrice en nombres infinis, dans n'importe quelle base, avec des opérateurs personnalisables.

## Règles

- Rendu dans [`rendu/bistromatic/`](../../rendu/bistromatic/).
- Binaire `calc` construit par le Makefile à la racine.
- Fonctions autorisées : `read`, `write`, `malloc`, `free`, `exit`.
- Le `main.c` et le `bistromatic.h` du sujet sont dans [`fournis/`](fournis/).

## Tâches

| Tâche | À rendre | Ce qu'il faut faire | Correction |
|---|---|---|---|
| task01 | `Makefile` | `echo "3+6" | ./calc 0123456789 "()+-*/%" 3` affiche `9` ; erreurs de syntaxe : `syntax error` et code 84. | automatique |

## Corriger en local

```sh
.github/correction/corriger.sh bistromatic
```
