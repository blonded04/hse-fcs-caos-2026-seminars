#include <stddef.h>

float dot_product(const float *a, const float *b, size_t n) {
    float s = 0.0f;
    for (size_t i = 0; i < n; i++) {
        s += a[i] * b[i];
    }
    return s;
}
