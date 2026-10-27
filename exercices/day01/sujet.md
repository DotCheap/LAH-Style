# Day 01 : environnement Unix

Sujet officiel : [B-CPE-100_Day01.pdf](B-CPE-100_Day01.pdf).

Découverte du terminal, des droits, des liens, de `find`, de git et de `tar`.

## Règles

- Rendu dans [`rendu/day01/`](../../rendu/day01/).
- Rendu à la racine de `rendu/day01/`, dans les dossiers indiqués.
- Git ne garde que le bit d'exécution des fichiers et ne garde pas les dossiers vides : mettez un fichier caché (`.gitkeep`) dans un dossier vide.

## Tâches

| Tâche | À rendre | Ce qu'il faut faire | Correction |
|---|---|---|---|
| task01 | `task01` | Dossier `task01` : `test01` vide, `test02` (texte imposé, exécutable par tous), `test03` lien symbolique vers `test02`. | automatique |
| task02 | `task02/z` | Fichier `z` qui contient `Z` suivi d'un retour à la ligne. | automatique |
| task03 | `task03/midLS` | Commande `midLS` : liste triée du dossier courant, séparée par des virgules, dossiers suffixés par `/`, sans fichiers cachés. | automatique |
| task04 | `mr_clean` | Commande `mr_clean` : une seule commande `find` qui supprime les fichiers finissant par `~` ou commençant et finissant par `#`. | automatique |
| task05 | `push_that.sh` | Script `push_that.sh` : ajoute tout, commite avec le message passé en argument et pousse. | automatique |
| task06 | `task06` | Arborescence des conférences Solvay (dossiers, fichiers et liens symboliques) du sujet. | automatique |
| task07 | `task07/task06.tgz` | Archive `task07/task06.tgz` (tar + gzip) du contenu de `task06`. | automatique |

## Corriger en local

```sh
.github/correction/corriger.sh day01
```
