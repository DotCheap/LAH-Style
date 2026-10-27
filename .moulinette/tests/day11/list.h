#include <stdlib.h>
#include <string.h>

typedef struct linked_list {
    void *data;
    struct linked_list *next;
} linked_list_t;

static linked_list_t *make_list(char const **words)
{
    linked_list_t *head = NULL;
    linked_list_t **tail = &head;

    for (int i = 0; words[i]; i++) {
        *tail = malloc(sizeof(linked_list_t));
        (*tail)->data = (void *)words[i];
        (*tail)->next = NULL;
        tail = &(*tail)->next;
    }
    return head;
}

static int cmp_str(char const *a, char const *b)
{
    return strcmp(a, b);
}

static void check_list(linked_list_t const *list, char const **exp)
{
    int i = 0;

    for (; exp[i]; i++, list = list->next) {
        if (list == NULL) {
            mouli_fail("la liste s'arrete apres %d element(s), attendu \"%s\"", i, exp[i]);
            return;
        }
        if (strcmp(list->data, exp[i])) {
            mouli_fail("element %d : attendu \"%s\", obtenu \"%s\"", i, exp[i],
                (char *)list->data);
            return;
        }
    }
    if (list != NULL)
        mouli_fail("la liste contient trop d'elements (element %d : \"%s\")", i,
            (char *)list->data);
}

#define LIST(...) make_list((char const *[]){__VA_ARGS__, 0})
#define EXPECT_LIST(list, ...) check_list(list, (char const *[]){__VA_ARGS__, 0})
