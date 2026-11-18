#include <assert.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

static volatile sig_atomic_t delivered;
static void handle(int signo) {
    (void)signo;
    ++delivered;
}

int main(void) {
    sigset_t set, oldmask, waitmask, pending;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    assert(sigprocmask(SIG_BLOCK, &set, &oldmask) == 0);

    struct sigaction sa = {0};
    sa.sa_handler = handle;
    sigemptyset(&sa.sa_mask);

    assert(sigaction(SIGUSR1, &sa, NULL) == 0);
    for (int i = 0; i < 1000; ++i) {
        assert(kill(getpid(), SIGUSR1) == 0);
    }
    assert(sigpending(&pending) == 0);

    printf("sent=1000 pending=%d\n", sigismember(&pending, SIGUSR1));

    waitmask = oldmask;
    sigdelset(&waitmask, SIGUSR1);
    while (!delivered) {
        assert(sigsuspend(&waitmask) == -1 && errno == EINTR);
    }
    printf("delivered=%d\n", delivered);

    assert(sigprocmask(SIG_SETMASK, &oldmask, NULL) == 0);
}
