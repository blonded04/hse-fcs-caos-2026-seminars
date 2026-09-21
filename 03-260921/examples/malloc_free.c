#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum { BATCH_SIZE = 1024, DEFAULT_BATCHES = 500000 };

typedef struct {
    uint64_t a, b;
} Pair;

static Pair *objects[BATCH_SIZE];
static volatile uint64_t sink;

static uint64_t now_ns(void) {
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
        perror("clock_gettime");
        exit(1);
    }
    return (uint64_t)ts.tv_sec * UINT64_C(1000000000) + ts.tv_nsec;
}

__attribute__((noinline))
static uint64_t run(int batches) {
    uint64_t checksum = 0;
    for (int batch = 0; batch < batches; ++batch) {
        // Сначала создаём всю пачку: объекты существуют одновременно.
        for (int i = 0; i < BATCH_SIZE; ++i) {
            uint64_t n = (uint64_t)batch * BATCH_SIZE + i;
            Pair *p = malloc(sizeof(*p));
            if (p == NULL) {
                fputs("malloc failed\n", stderr);
                exit(1);
            }
            p->a = n;
            p->b = n ^ UINT64_C(0x12345678);
            objects[i] = p;
        }
        // Прочитаем оба поля каждого объекта до освобождения.
        for (int i = 0; i < BATCH_SIZE; ++i)
            checksum += objects[i]->a + objects[i]->b;
        for (int i = 0; i < BATCH_SIZE; ++i) {
            free(objects[i]);
            objects[i] = NULL;
        }
    }
    sink = checksum;
    return checksum;
}

int main(int argc, char **argv) {
    long batches = DEFAULT_BATCHES;
    if (argc == 2) {
        char *end;
        errno = 0;
        batches = strtol(argv[1], &end, 10);
        if (errno || end == argv[1] || *end || batches < 1 || batches > 1000000) {
            fputs("batches must be in 1..1000000\n", stderr);
            return 2;
        }
    } else if (argc > 2) {
        fputs("usage: malloc_free [batches]\n", stderr);
        return 2;
    }

    // Прогрев входит во внешнее /usr/bin/time, но не во внутренний таймер.
    run(10000);
    uint64_t start = now_ns();
    uint64_t checksum = run((int)batches);
    double elapsed_ms = (double)(now_ns() - start) / 1e6;
    printf("C: objects=%" PRIu64 " elapsed_ms=%.3f checksum=%" PRIu64 "\n",
           (uint64_t)batches * BATCH_SIZE, elapsed_ms, checksum);
    return 0;
}
