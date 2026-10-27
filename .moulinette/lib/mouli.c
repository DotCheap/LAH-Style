/*
** Moulinette de la piscine - mini framework de tests unitaires.
*/

#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>
#include "mouli.h"

#define MSG_SIZE 4096

static char const *g_desc = "";
static int g_pipe[2] = {-1, -1};
static char g_msg[MSG_SIZE];
static int g_failed = 0;
static FILE *g_out = NULL;
static FILE *g_err = NULL;
static int g_saved_out = -1;
static int g_saved_err = -1;

static void escape(char *dst, size_t size, char const *src)
{
    size_t j = 0;

    if (src == NULL) {
        snprintf(dst, size, "(null)");
        return;
    }
    for (size_t i = 0; src[i] && j + 8 < size; i++) {
        unsigned char c = (unsigned char)src[i];
        if (c == '\n')
            j += snprintf(dst + j, size - j, "\\n");
        else if (c == '\t')
            j += snprintf(dst + j, size - j, "\\t");
        else if (c < 32 || c >= 127)
            j += snprintf(dst + j, size - j, "\\x%02x", c);
        else
            dst[j++] = c;
    }
    if (j + 8 >= size)
        j += snprintf(dst + j, size - j, "[...]");
    dst[j] = '\0';
}

static void write_result(char const *status, char const *msg)
{
    char line[MSG_SIZE + 512];
    char const *file = getenv("MOULI_RESULTS");
    FILE *f;
    int len = snprintf(line, sizeof(line), "%s\t%s\t%s\n", status, g_desc,
        msg ? msg : "");

    for (int i = 0; i < len - 1; i++)
        if (line[i] == '\n')
            line[i] = ' ';
    f = file ? fopen(file, "a") : stderr;
    if (f == NULL)
        return;
    fputs(line, f);
    if (f != stderr)
        fclose(f);
}

int mouli_fork(char const *desc)
{
    pid_t pid;
    int status = 0;
    char buf[MSG_SIZE + 2];
    ssize_t total = 0;
    ssize_t len;
    char const *timeout = getenv("MOULI_TIMEOUT");

    g_desc = desc;
    fflush(stdout);
    fflush(stderr);
    if (pipe(g_pipe) < 0)
        return 0;
    pid = fork();
    if (pid == 0) {
        struct rlimit lim = {16 << 20, 16 << 20};
        close(g_pipe[0]);
        setrlimit(RLIMIT_FSIZE, &lim);
        alarm(timeout ? atoi(timeout) : 2);
        g_failed = 0;
        g_msg[0] = '\0';
        return 1;
    }
    close(g_pipe[1]);
    while (total < MSG_SIZE
        && (len = read(g_pipe[0], buf + total, MSG_SIZE - total)) > 0)
        total += len;
    buf[total] = '\0';
    close(g_pipe[0]);
    waitpid(pid, &status, 0);
    if (total > 0 && buf[0] == 'P')
        write_result("PASS", NULL);
    else if (total > 0)
        write_result("FAIL", buf + 1);
    else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGALRM)
        write_result("FAIL", "TIMEOUT : le test a pris trop de temps "
            "(boucle infinie ?)");
    else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGXFSZ)
        write_result("FAIL", "sortie beaucoup trop longue "
            "(boucle infinie ?)");
    else if (WIFSIGNALED(status)) {
        snprintf(buf, sizeof(buf), "CRASH : %s",
            strsignal(WTERMSIG(status)));
        write_result("FAIL", buf);
    } else {
        snprintf(buf, sizeof(buf), "le programme s'est arrete (exit %d) "
            "avant la fin du test", WEXITSTATUS(status));
        write_result("FAIL", buf);
    }
    return 0;
}

int mouli_done(void)
{
    char buf[MSG_SIZE + 2];
    int len;

    fflush(stdout);
    fflush(stderr);
    len = snprintf(buf, sizeof(buf), "%c%s", g_failed ? 'F' : 'P', g_msg);
    if (write(g_pipe[1], buf, len) < 0)
        _exit(1);
    _exit(0);
    return 0;
}

void mouli_fail(char const *fmt, ...)
{
    size_t len = strlen(g_msg);
    va_list ap;

    g_failed = 1;
    if (len + 4 >= MSG_SIZE)
        return;
    if (len > 0)
        len += snprintf(g_msg + len, MSG_SIZE - len, " | ");
    va_start(ap, fmt);
    vsnprintf(g_msg + len, MSG_SIZE - len, fmt, ap);
    va_end(ap);
}

void mouli_capture(void)
{
    fflush(stdout);
    fflush(stderr);
    g_out = tmpfile();
    g_err = tmpfile();
    if (g_out == NULL || g_err == NULL)
        return;
    g_saved_out = dup(1);
    g_saved_err = dup(2);
    dup2(fileno(g_out), 1);
    dup2(fileno(g_err), 2);
}

static char const *read_capture(FILE *f)
{
    long size;
    char *buf;

    fflush(stdout);
    fflush(stderr);
    if (f == NULL)
        return "";
    size = lseek(fileno(f), 0, SEEK_END);
    if (size < 0)
        size = 0;
    buf = malloc(size + 1);
    if (buf == NULL)
        return "";
    lseek(fileno(f), 0, SEEK_SET);
    size = read(fileno(f), buf, size);
    buf[size < 0 ? 0 : size] = '\0';
    return buf;
}

char const *mouli_stdout(void)
{
    return read_capture(g_out);
}

char const *mouli_stderr(void)
{
    return read_capture(g_err);
}

void mouli_expect_int(char const *what, long long got, long long expected)
{
    if (got != expected)
        mouli_fail("%s : attendu %lld, obtenu %lld", what, expected, got);
}

void mouli_expect_sign(char const *what, long long got, long long expected)
{
    int gs = (got > 0) - (got < 0);
    int es = (expected > 0) - (expected < 0);

    if (gs != es)
        mouli_fail("%s : attendu une valeur %s, obtenu %lld", what,
            es == 0 ? "nulle" : es > 0 ? "positive" : "negative", got);
}

void mouli_expect_ptr(char const *what, void const *got, void const *expected)
{
    if (got != expected)
        mouli_fail("%s : ne retourne pas le pointeur attendu", what);
}

void mouli_expect_offset(char const *what, char const *got, char const *base,
    char const *expected)
{
    char eg[64];
    char ee[64];

    if (got == expected)
        return;
    if (expected)
        snprintf(ee, sizeof(ee), "str + %ld", (long)(expected - base));
    else
        snprintf(ee, sizeof(ee), "NULL");
    if (got)
        snprintf(eg, sizeof(eg), "str + %ld", (long)(got - base));
    else
        snprintf(eg, sizeof(eg), "NULL");
    mouli_fail("%s : attendu %s, obtenu %s", what, ee, eg);
}

void mouli_expect_str(char const *what, char const *got, char const *expected)
{
    char eg[600];
    char ee[600];

    if (got == expected)
        return;
    if (got == NULL || expected == NULL || strcmp(got, expected) != 0) {
        escape(eg, sizeof(eg), got);
        escape(ee, sizeof(ee), expected);
        mouli_fail("%s : attendu \"%s\", obtenu \"%s\"", what, ee, eg);
    }
}

void mouli_expect_true(char const *what, int cond)
{
    if (!cond)
        mouli_fail("condition fausse : %s", what);
}

void mouli_expect_out(char const *expected)
{
    mouli_expect_str("sortie standard", mouli_stdout(), expected);
}

void mouli_expect_out_nl(char const *expected)
{
    char const *got = mouli_stdout();
    size_t len = strlen(got);
    size_t elen = strlen(expected);

    if (len == elen + 1 && got[elen] == '\n' && !strncmp(got, expected, elen))
        return;
    mouli_expect_str("sortie standard", got, expected);
}

static char *squeeze(char const *str)
{
    char *res = malloc(strlen(str) + 1);
    size_t j = 0;

    for (size_t i = 0; str[i]; i++) {
        if (str[i] == ' ' || str[i] == '\t') {
            while (str[i + 1] == ' ' || str[i + 1] == '\t')
                i++;
            if (str[i + 1] == '\n' || str[i + 1] == '\0')
                continue;
            res[j++] = ' ';
        } else
            res[j++] = str[i];
    }
    res[j] = '\0';
    return res;
}

void mouli_expect_out_ws(char const *expected)
{
    char *got = squeeze(mouli_stdout());
    char *exp = squeeze(expected);

    mouli_expect_str("sortie standard (espaces normalises)", got, exp);
}

void mouli_expect_err(char const *expected)
{
    mouli_expect_str("sortie d'erreur", mouli_stderr(), expected);
}

char *mouli_strdup(char const *str)
{
    char *res = malloc(strlen(str) + 1);

    return res ? strcpy(res, str) : NULL;
}
