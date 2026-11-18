# signal

`signal` - tell another process to asynchronously interrrupt and call signal handler.

Few signals:
* `SIGTERM`, `SIGKILL`: kill process, unfreezable.
* `SIGUSR1`, `SIGUSR2`.

## IPC via `signal`

### Signal sender

```c
kill(pid, SIGUSR1)
```

1. sender-process calls `kill`
2. sender-process enters kernel-space
3. kernel checks sender rights to destination
4. if receiver-process:
  * has this signal frozen, SIGUSR1 becomes pending
  * else, nothing
5. when signal is unfrozen, signal is sent

### Signal receiver

1. when receiver-process exits kernel-space: syscall execution ends or kernel interrupt
2. kernel chooses random non-sleeping thread
3. kernel saves registers of this thread
4. chosen thread executes signal-handler
5. trampoline executes
