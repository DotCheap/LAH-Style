# LAH-Style

Piscine Epitech (B-CPE-100 et B-CPE-101), avec correction automatique par
GitHub Actions.

Piscine partie 1 : Grade A

| Dossier | Contenu |
|---|---|
| [`exercices/`](exercices/) | Les sujets PDF et, pour chaque jour ou projet, un `sujet.md` qui liste les tâches |
| [`rendu/`](rendu/) | Le travail rendu, au format de rendu Epitech |

## Comment ça marche

1. Lisez le sujet dans `exercices/<dossier>/` (PDF officiel et `sujet.md`).
2. Mettez votre travail dans `rendu/<dossier>/`.
3. Poussez sur GitHub : le workflow **Correction** compile et teste les
   tâches des dossiers modifiés, et affiche le résultat dans l'onglet **Actions**.

Pour corriger en local : `.github/correction/corriger.sh day03`.

Les solutions de la piscine déjà faite (Grade A) sont sur la branche
[`solutions`](../../tree/solutions/rendu).

Détails : [liste des exercices](exercices/README.md) · [comment rendre](rendu/README.md).

## Outils

- `install_criterion.sh` : installe Criterion (tests unitaires des Day06, Day12…).
- `install_csfml.sh` : installe la CSFML (Day13).

## Organisation interne

```text
.github/
├── correction/
│   ├── corriger.sh          # script de correction (local et CI)
│   ├── selection.sh         # dossiers modifiés par un push
│   ├── lib/                 # test.h, test_lib.sh, fichiers fournis aux tests
│   └── <dossier>/<tâche>/   # config, test.c ou test.sh, expected.txt
└── workflows/
    └── correction.yml       # lance la correction à chaque push sur rendu/
```
