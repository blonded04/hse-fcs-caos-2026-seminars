#include <stdio.h>
#include <stdlib.h>

void foo(const char *msg, int *arr, size_t len) {
    int numbers[] = {[1] = 20, [0] = 10};
    printf("%s (10=%d, 20=%d):", msg, numbers[0], numbers[1]);
    for (size_t i = 0; i < len; i++) {
        printf(" %d", arr[i]);
    }
    printf("\n");

    void *ptr = malloc(10);
    (void)ptr;  // Mark as unused and leak.
}
