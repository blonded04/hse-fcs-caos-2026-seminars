# threads

## parallelism vs concurrency

* parallelism is when something are executed at the same time:
  - mimd (core-level parallelism)
  - simd (data-level parallelism)
  - instruction-level parallelism
  - speculative (branch prediction)
* concurrency is when something is executed asynchronously but not necessarily

## thread vs process

* threads live inside a process
* address space
* threads are generally cheaper to create
* fault-tolerance
* security
* os resources
* processes form a tree

## shared memory operations

```c
int x = 0;

// T1:
for (int i = 0; i < 40; i++) {
    x = i;
}

// T2:
for (int i = 0; i < 1000; i++) {
    int y = x;
}
```

       T1:
       r  w
T2: r  v  x
    w  x  x

## rabbit picture conclusions:
1. Creating a lot of threads is bad (reusing threads is good, nice to have: threads ~= O(CPUs)).
2. Userspace schedulers are good: golang, java.util.concurrent, java vthreads, kotlin, swift. 
