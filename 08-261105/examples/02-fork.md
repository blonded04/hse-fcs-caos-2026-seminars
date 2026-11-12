# Fork

`fork` -- syscall, that creates duplicate of current process.

```
pid_t child_pid = fork();
if (child_pid != -1) {
    // ...
}
if (child_pid != 0) {
    // parent
} else {
    // child
}
```

## Is it safe to `fork`?

No:
* In-memory OS structures are duplicates
* Multithreaded environment

We need safepoint.

## Side note: consistent snapshot

```
* begin snapshot (AB)
* read A (AB)
* somebody writes D at B position (AD)
* somebody writes C at A position (CD)
* read D (CD), we've read AD
```

Naive: global lock, read snapshot, global unlock.

Fork (redis, tarantool, ...):
* Safepoint.
* `fork`.
* Child process has copy of parent's address space.
* Copy-on-write (4096B) for parent.
