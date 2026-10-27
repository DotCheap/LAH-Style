# Rendu

Déposez votre travail dans le dossier du jour ou du projet, **avec la même
organisation que le rendu Epitech** : les fichiers à la racine du dossier, la
libmy dans `lib/my/`, les headers dans `include/`, les programmes dans leur
sous-dossier. Le `sujet.md` de chaque dossier d'[`exercices/`](../exercices/)
indique le chemin exact de chaque fichier.

```text
rendu/
├── day03/
│   ├── my_print_alpha.c
│   └── my_put_nbr.c
├── day07/
│   ├── lib/my/build.sh
│   ├── lib/my/my_putchar.c
│   ├── include/my.h
│   ├── my_strcat.c
│   └── task04/my_print_params.c
└── ...
```

Les solutions d'une piscine déjà faite sont gardées à part, sur la branche
[`solutions`](../../../tree/solutions/rendu) du dépôt.

## Faire corriger son travail

1. Commitez et poussez :

   ```sh
   git add rendu/day03
   git commit -m "day03"
   git push
   ```

2. Sur GitHub, ouvrez l'onglet **Actions**, puis le dernier workflow
   **Correction**. Le résumé donne, pour chaque dossier, le nombre de tâches
   validées, en échec et non rendues, puis le détail de chaque échec.

Seuls les dossiers modifiés par le push sont corrigés : pousser
`rendu/day03/` ne corrige que le Day03. Pour tout corriger, lancez le workflow
à la main (onglet **Actions**, **Correction**, **Run workflow**), en
indiquant éventuellement un dossier ou une tâche.

Une tâche absente n'est pas une erreur : elle apparaît comme « non rendue ».
Le workflow est rouge dès qu'une tâche rendue échoue.

## Corriger en local, avant de pousser

Il faut `gcc` sous Linux (ou WSL), et Criterion pour les tâches de tests
unitaires (`./install_criterion.sh`, ou `sudo apt install libcriterion-dev`).

```sh
.github/correction/corriger.sh              # tout
.github/correction/corriger.sh day06        # un dossier
.github/correction/corriger.sh day06/task18 # une tâche
```

## Ce que vérifie la correction

1. Les fichiers demandés sont présents.
2. Ils compilent avec `gcc -Wall -Wextra -Werror`. En cas de simples
   warnings, la tâche échoue, mais les tests sont quand même lancés, pour
   savoir si le reste fonctionne.
3. Pas de `main` dans les fichiers de fonctions, et seulement des fonctions
   autorisées (vérifié avec `nm`).
4. Les fonctions `_rec` sont récursives, les `_it` ne le sont pas.
5. Les tests passent, sans erreur mémoire ni comportement indéfini
   (AddressSanitizer et UndefinedBehaviorSanitizer), dans le temps imparti.
6. Pour les programmes : le Makefile fonctionne et ne relinke pas, et la
   sortie et le code de retour sont ceux attendus.

Comme chez Epitech (`gcc *.c`), une fonction peut utiliser les autres
fichiers `.c` du même dossier, ou la libmy à partir du Day07.
