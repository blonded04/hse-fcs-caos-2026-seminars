#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*
A
├── B
│   └── D
└── C
*/
int main(void) {
    pid_t b = fork();
    if (b == 0) {
        pid_t d = fork();
        if (d == 0) {
            printf("D");
            fflush(stdout);
            return 0;
        }

        waitpid(d, NULL, 0);
        printf("B");
        fflush(stdout);
        return 0;
    }

    pid_t c = fork();
    if (c == 0) {
        printf("C");
        fflush(stdout);
        return 0;
    }

    waitpid(b, NULL, 0);
    waitpid(c, NULL, 0);
    printf("A");
    fflush(stdout);

    return 0;
}
