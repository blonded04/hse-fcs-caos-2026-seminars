#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_line() {
    int data_cap = 10;
    char *data = malloc(data_cap);
    int data_len = 0;

    for (;;) {
        int c = getc(stdin);  // int, not char! EOF is not a char
        if (c == EOF || c == '\n') {
            break;
        }
        if (data_len + 1 >= data_cap) {
            // TODO: reallocate memory in 'data', return NULL if there is not enough memory.
            // Be careful not to leak.  Use 'realloc', it copies data for you.
        }
        data[data_len++] = c;
    }

    data[data_len] = 0;
    return data;
}

int main() {
    char *a = read_line();
    char *b = read_line();
    char *c = read_line();
    char *d = read_line();
    printf("%zd %zd %zd %zd\n", strlen(a), strlen(b), strlen(c), strlen(d));
    printf("|%s|%s|%s|%s|\n", a, b, c, d);
    free(d);
    free(c);
    free(b);
    free(a);
}
