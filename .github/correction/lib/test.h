/*
** Mini-framework de test utilisé par la correction automatique.
** Les messages d'erreur partent sur stderr : stdout est réservé à la
** sortie des fonctions testées (comparée au fichier expected.txt).
*/

#ifndef TEST_H_
    #define TEST_H_

    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>

static int test_failures = 0;

    #define CHECK(expr) \
    do { \
        if (!(expr)) { \
            fprintf(stderr, "  ligne %d : %s est faux\n", __LINE__, #expr); \
            test_failures++; \
        } \
    } while (0)

    #define CHECK_INT(expr, want) \
    do { \
        long long got_ = (long long)(expr); \
        long long want_ = (long long)(want); \
        if (got_ != want_) { \
            fprintf(stderr, "  ligne %d : %s vaut %lld, attendu %lld\n", \
                __LINE__, #expr, got_, want_); \
            test_failures++; \
        } \
    } while (0)

    #define CHECK_STR(got, want) \
    do { \
        const char *got_ = (got); \
        const char *want_ = (want); \
        if (got_ == NULL || strcmp(got_, want_) != 0) { \
            fprintf(stderr, "  ligne %d : %s vaut \"%s\", attendu \"%s\"\n", \
                __LINE__, #got, got_ ? got_ : "(null)", want_); \
            test_failures++; \
        } \
    } while (0)

    #define TEST_END() return (test_failures != 0)

/* Écrit un retour à la ligne sur stdout, sans passer par le buffer de stdio. */
static inline void test_nl(void)
{
    write(1, "\n", 1);
}

#endif /* TEST_H_ */
