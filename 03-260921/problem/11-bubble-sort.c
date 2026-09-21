#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void swap(char *a, char *b, size_t size) {
    // TODO: byte-wise swap 2 objects of size `size` at `a` and `b`.
}

void bubble_sort(void *data, size_t num, size_t size, int (*compar)(const void*, const void*)) {
    // TODO: bubble sort array `data` of `num` elements `size` bytes each using `compar`.
}

// TODO: copy your `int_comp` from `*-qsort-int.cpp`
// TODO: copy your `str_comp` from `*-qsort-str.cpp`

int main() {
    {
        int data[] = {3, 2, 1, 5, 4};
        bubble_sort(data, sizeof(data) / sizeof(data[0]), sizeof(data[0]), int_comp);
        assert(data[0] == 1);
        assert(data[1] == 2);
        assert(data[2] == 3);
        assert(data[3] == 4);
        assert(data[4] == 5);
    }
    {
        const char *data[] = {
            "hello",
            "world",
            "meow",
            "abcd",
        };
        bubble_sort(data, sizeof(data) / sizeof(data[0]), sizeof(data[0]), str_comp);
        assert(strcmp(data[0], "abcd") == 0);
        assert(strcmp(data[1], "hello") == 0);
        assert(strcmp(data[2], "meow") == 0);
        assert(strcmp(data[3], "world") == 0);
    }
    printf("OK\n");
}
