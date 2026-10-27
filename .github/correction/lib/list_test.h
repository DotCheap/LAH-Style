/*
** Outils des tests du Day11 : la structure du sujet, la construction d'une
** liste de chaînes et sa vérification.
*/

#ifndef LIST_TEST_H_
    #define LIST_TEST_H_

    #include <stdarg.h>
    #include <stdlib.h>
    #include "test.h"

typedef struct linked_list {
    void *data;
    struct linked_list *next;
} linked_list_t;

/* Construit une liste dans l'ordre des arguments, terminés par NULL. */
static inline linked_list_t *make_list(char const *first, ...)
{
    linked_list_t *head = NULL;
    linked_list_t **last = &head;
    char const *str = first;
    va_list ap;

    va_start(ap, first);
    while (str != NULL) {
        *last = malloc(sizeof(linked_list_t));
        (*last)->data = (void *)str;
        (*last)->next = NULL;
        last = &(*last)->next;
        str = va_arg(ap, char const *);
    }
    va_end(ap);
    return head;
}

/* Vérifie que la liste contient exactement les chaînes de want (fin : NULL). */
static inline void check_list(linked_list_t const *list, char const * const *want,
    int line)
{
    int i = 0;

    for (; want[i] != NULL; i++, list = list->next) {
        if (list == NULL) {
            fprintf(stderr, "  ligne %d : la liste s'arrête après %d élément(s), "
                "attendu \"%s\" ensuite\n", line, i, want[i]);
            test_failures++;
            return;
        }
        if (list->data == NULL || strcmp(list->data, want[i]) != 0) {
            fprintf(stderr, "  ligne %d : élément %d vaut \"%s\", attendu \"%s\"\n",
                line, i, list->data ? (char *)list->data : "(NULL)", want[i]);
            test_failures++;
            return;
        }
    }
    if (list != NULL) {
        fprintf(stderr, "  ligne %d : élément en trop \"%s\" après %d élément(s)\n",
            line, (char *)list->data, i);
        test_failures++;
    }
}

    #define CHECK_LIST(list, ...) \
    do { \
        char const *want_[] = {__VA_ARGS__, NULL}; \
        check_list(list, want_, __LINE__); \
    } while (0)

    #define CHECK_EMPTY(list) CHECK((list) == NULL)

#endif /* LIST_TEST_H_ */
