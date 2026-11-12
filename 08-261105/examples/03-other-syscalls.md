## Other syscalls:

* `exit(char)` - exits process with given exit code
* `execve("ls", {"ls", "hse-fcs-caos-2026-seminars", NULL}, NULL)` - turns this process into execution of command specified to `exec`.
* `dup2` - duplicates file descriptor.
* `pipe` - unidirectional channel between processes.
* `waitpid(pid_t)` - wait at parent for child exit.

## Why would we `dup2`?

`dup2(NETWORK_SOCKET, STDOUT_FILENO)` -> `printf(...)` по сети.

```c
int fd[2];
if (pipe(fd) != 0) {
    return 1;
}
pid_t child_pid = fork();
if (child_pid == 0) {
    // child logic:
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    execve("ls", {"ls", NULL}, NULL);
} else {
    // parent logic:
    close(fd[1]);
    // read from fd[0]...
}
```
