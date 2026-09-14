#include <stdio.h>

struct point {
    int x, y;
};

void print_point(point *p) {  // TODO
    printf("(%d,%d)\n", p->x, p->y);
}

int main() {
    point p = {.x = 10, .y = 20};  // TODO
    print_point(&p);
}
