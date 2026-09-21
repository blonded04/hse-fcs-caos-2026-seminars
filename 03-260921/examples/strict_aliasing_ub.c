#include <stdio.h>

__attribute__((noinline))
int overwrite(int *integer, float *real) {
    *integer = 1;
    *real = 0.0f;
    return *integer;
}

int main(void) {
    union { int integer; float real; } storage;
    int result = overwrite(&storage.integer, &storage.real);
    printf("result=%d\n", result);
    return 0;
}
