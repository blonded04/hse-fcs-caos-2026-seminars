#include <stdio.h>
#include <unistd.h>

int main(void) {
    printf("Hello ");
    // fflush(stdout);
    fork();
    return 0;
}
