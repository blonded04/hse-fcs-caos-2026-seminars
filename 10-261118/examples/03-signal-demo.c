#include <assert.h>
#include <inttypes.h>
#include <signal.h>
#include <unistd.h>

static volatile sig_atomic_t square_mode;

// activate via `kill -USR2 PID`
static void handle(int signo) {
    square_mode = (signo == SIGUSR2);
}

int main(void) {
    struct sigaction sa = {0};
    sa.sa_handler = handle;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGUSR1);
    sigaddset(&sa.sa_mask, SIGUSR2);
    assert(sigaction(SIGUSR1, &sa, NULL) == 0);
    assert(sigaction(SIGUSR2, &sa, NULL) == 0);
    assert(sigprocmask(SIG_UNBLOCK, &sa.sa_mask, NULL) == 0);

    assert(printf("%ld\n", getpid()) >= 0);
    assert(fflush(STDOUT_FILENO) == 0);

    int32_t x;
    while (scanf("%" SCNd32, &x) == 1) {
        int64_t y = x;
        sig_atomic_t mode = square_mode;
        assert(printf("%ld\n", mode ? y * y : -y) >= 0);
        assert(fflush(STDOUT_FILENO) == 0);
    }
    return 0;
}
