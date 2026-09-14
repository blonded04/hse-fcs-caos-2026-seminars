#include <stdio.h>

struct point {  // TODO
    int x, y;
};  // TODO

void print_point(point *p) {
    printf("(%d,%d)\n", p->x, p->y);
}

int main() {
    point p = {.x = 10, .y = 20};
    print_point(&p);
}
