#include <stddef.h>
#include <stdint.h>

// vector operations:
// * sse 128bit=16byte
// * avx 256bit=32byte
// * avx2 512bit=64byte

// memset,memcpy
// algorithmica: Sergey Slotin Algorithms for modern hardware

// O(n^3)
int sum(const int *a, size_t n) {
    int s = 0.0f;
    for (size_t i = 0; i < n; i++) {
        s += a[i];
    }
    return s;
}
