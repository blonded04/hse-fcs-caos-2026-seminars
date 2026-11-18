#include <assert.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/signalfd.h>

int main(void) {
    // fork
    // child reads from signalfd
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGUSR2);
    sigaddset(&set, SIGCONT);
    sigaddset(&set, SIGCHLD);
    sigprocmask(SIG_BLOCK, &set, NULL);

    pid_t pid = fork();
    if (pid == 0) {
        int fd = signalfd(-1, &set, SFD_CLOEXEC);

        if (fd < 0) {
            return 1;
        }

        struct signalfd_siginfo siginfo;
        int calls = 0;
        ssize_t bytes;
        char sigusr2_received = 0;
        do {
            ssize_t bytes = read(fd, &siginfo, sizeof(siginfo));
            if (bytes != sizeof(siginfo)) {
                _exit(1);
            }
            printf("Received: %d by %d\n", siginfo.ssi_signo, siginfo.ssi_pid);
            fflush(0);
            calls++;
            if (siginfo.ssi_signo == SIGUSR2) {
                sigusr2_received = 1;
            }
        } while (sigusr2_received == 0 || (bytes < 0 && errno == EINTR));

        printf("Received %d signals\n", calls);

        _exit(0);
    }

    printf("%d sends %d\n", getpid(), SIGCONT);
    kill(pid, SIGCONT);
    fflush(0);
    printf("%d sends %d\n", getpid(), SIGCHLD);
    kill(pid, SIGCHLD);
    fflush(0);
    printf("%d sends %d\n", getpid(), SIGCHLD);
    kill(pid, SIGCHLD);
    fflush(0);
    printf("%d sends %d\n", getpid(), SIGUSR1);
    kill(pid, SIGUSR1);
    fflush(0);
    printf("%d sends %d\n", getpid(), SIGCONT);
    kill(pid, SIGCONT);
    fflush(0);
    printf("%d sends %d\n", getpid(), SIGUSR1);
    kill(pid, SIGUSR1);
    fflush(0);
    printf("%d sends %d\n", getpid(), SIGUSR1);
    kill(pid, SIGUSR1);
    fflush(0);
    printf("%d sends %d\n", getpid(), SIGUSR1);
    kill(pid, SIGUSR1);
    fflush(0);
    printf("%d sends %d\n", getpid(), SIGCHLD);
    kill(pid, SIGCHLD);
    fflush(0);
    printf("%d sends %d\n", getpid(), SIGUSR2);
    kill(pid, SIGUSR2);
    fflush(0);

    waitpid(pid, NULL, 0);
    return 0;
}
