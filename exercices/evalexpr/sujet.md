# EvalExpr

Sujet officiel : [B-CPE-101_EvalExpr.pdf](B-CPE-101_EvalExpr.pdf) · [B-CPE-101_EvalExprBootstrap.pdf](B-CPE-101_EvalExprBootstrap.pdf).

Évaluer une expression arithmétique avec parenthèses et priorités.

## Règles

- Rendu dans [`rendu/evalexpr/`](../../rendu/evalexpr/).
- Binaire `eval_expr` construit par le Makefile à la racine, avec le `main` imposé par le sujet.
- Fonctions autorisées : `write`, `malloc`, `free`.

## Tâches

| Tâche | À rendre | Ce qu'il faut faire | Correction |
|---|---|---|---|
| task01 | `Makefile` | `./eval_expr "(3+2)*5"` affiche `25` ; résultats comparés au calcul du compilateur C. | automatique |

## Corriger en local

```sh
.github/correction/corriger.sh evalexpr
```
