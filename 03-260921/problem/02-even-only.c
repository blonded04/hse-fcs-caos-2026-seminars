#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

TODO even_only(TODO, TODO) {
    TODO
}

int main(void) {
    int array[] = {1, 2, 3, 4, 5};

    int *even_array = even_only(array, sizeof(array) / sizeof(int));
    assert(even_array != array);
    for (int i = 0; i < 5; i++) {
        assert(array[i] == i + 1);
    }
    assert(even_array != array);
    for (int i = 0; i < 2; i++) {
        assert(even_array[i] == 2 * (i + 1));
    }

    assert(even_only(NULL, 0) == NULL);

    free(even_array);

    printf("All OK\n");
    return 0;
}
