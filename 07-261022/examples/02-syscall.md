# syscalls (kernel-call)

```c
syscall(SYSCALL_ID, ...);  // SYS_open, "hello.txt"
// int 0x60 ; sysenter
// cpu sees interrupt
// cpu calls interrupt handler
// OS interrupt handler calls requested syscall
```

```c
int fd = open("hello.txt", O_RDONLY);
```

## interruptions

Interruptions:
* At any arbitrary moment of time OS interrupt handler
  - user-defined signal handlers

Can be triggered by:
* `int` instruction
* OS / hardware:
  - access unmapped memory
  - integer overflow
  - ...

### garbage collection

in primitive garbage collectors we would like to stop program execution to collect garbage (stop-the-world):
* each thread periodically checks stop-flag, if its true, then thread sleeps, until woken up
* `test page`
