# More signals

```c
assert(sigprocmask(SIG_BLOCK, &sa.sa_mask, NULL) == 0);
while (!received) {
    sleep(1000);
}
```
