#include <stddef.h>
#include <stdint.h>

float sum(const float *a, size_t n) {
    float s = 0.0f;
    for (size_t i = 0; i < n; i++) {
        s += a[i];
    }
    return s;
}
