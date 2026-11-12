#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>

static int x = 100;

int main(void) {
    pid_t pid = fork();

    if (pid == 0) {
        printf("child  before: x=%d\n", x);
        x = 200;
        printf("child  after:  x=%d\n", x);
        _exit(0);
    }

    waitpid(pid, NULL, 0);
    printf("parent after:  x=%d\n", x);

    char *p = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    p[0] = 'A';
    printf("wrote '%c' at %p (rw)\n", p[0], (void*)p);

    mprotect(p, 4096, PROT_READ);
    printf("mprotect -> PROT_READ; writing...\n");
    fflush(stdout);

    p[0] = 'B';  // SIGSEGV

    printf("unreachable\n");
    return 0;
}