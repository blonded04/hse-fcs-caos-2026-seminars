#include <assert.h>
#include <stdio.h>

void create_matrix(TODO) {
    // TODO: allocate a 2D array NxN and store it in the argument.
}

void destroy_matrix(TODO) {
    // TODO: destroy a 2D array NxN creatd by `create_matrix`.
}

int main() {
    int **m;
    create_matrix(3, &m);
    assert(m[0][0] == 1);
    assert(m[0][1] == 2);
    assert(m[0][2] == 3);
    assert(m[1][0] == 4);
    assert(m[1][1] == 5);
    assert(m[1][2] == 6);
    assert(m[2][0] == 7);
    assert(m[2][1] == 8);
    assert(m[2][2] == 9);
    destroy_matrix(3, m);
    printf("OK\n");
}