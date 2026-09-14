#include <stddef.h>

void foo(const char *, int*, size_t);

int main(void) {
    int arr[5] = {
        [2] = 239,
        [4] = 17,
    };
    foo("hello world", arr, sizeof(arr) / sizeof(arr[0]));
}
