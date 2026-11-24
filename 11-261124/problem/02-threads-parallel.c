/*
разберитесь почему при изменении K числа потоков программа не ускоряется
*/

#include <pthread.h>
#include <stdio.h>
#include <time.h>

#define MAX_PRIMES 1000000

static int isPrime(int n) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

static int primes[MAX_PRIMES];
static int primes_count = 0;

typedef struct {
    int begin;
    int end;
} range_t;

static void *findPrimes(void *p) {
    range_t *r = (range_t *)p;
    for (int i = r->begin; i < r->end; i++) {
        if (isPrime(i)) {
            primes[primes_count++] = i;
        }
    }
    return NULL;
}

int main(void) {
    const int N = 10000000;
    const int K = 4;

    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);

    for (int i = 0; i < K; i++) {
        range_t r = { N * i / K, N * (i + 1) / K };
        pthread_t t;
        pthread_create(&t, NULL, findPrimes, &r);
        pthread_join(t, NULL);
    }

    printf("%d\n", primes_count);

    clock_gettime(CLOCK_MONOTONIC, &t1);
    long long ms = (t1.tv_sec - t0.tv_sec) * 1000LL
                 + (t1.tv_nsec - t0.tv_nsec) / 1000000LL;
    printf("Elapsed %lldms\n", ms);

    return 0;
}
