#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int int_comp(TODO) {
    return TODO;
}

int main() {
    int data[] = {3, 2, 1, 5, 4};
    qsort(data, TODO, TODO, int_comp);
    assert(data[0] == 1);
    assert(data[1] == 2);
    assert(data[2] == 3);
    assert(data[3] == 4);
    assert(data[4] == 5);
    printf("OK\n");
}
