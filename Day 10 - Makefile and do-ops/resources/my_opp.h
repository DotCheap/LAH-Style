/*
** EPITECH PROJECT, 2021
** my_opp.h
** File description:
** Table des operateurs de my_advanced_do-op (Day 10, task 05).
** A copier dans le dossier include/ du Day 10.
**
** `struct operator` doit etre definie dans un autre header de include/
** (inclus AVANT celui-ci) avec deux champs : la chaine de l'operateur
** puis un pointeur sur fonction `int (*)(int, int)`.
*/

#ifndef MY_OPP_H_
    #define MY_OPP_H_

struct operator OPERATORS_FUNCS[] = {
    {"+", &my_add},
    {"-", &my_sub},
    {"/", &my_div},
    {"*", &my_mul},
    {"%", &my_mod},
    {"", &my_usage}
};

#endif /* MY_OPP_H_ */
