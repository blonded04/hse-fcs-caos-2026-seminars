# mmap

`mmap` (memory map) - maps file contents / anonymous memory into current process' address space 

```c
int fd = open("/tmp/privet.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);
if (fd < 0) {
    // ...
}
ftruncate("/tmp/privet.txt", 1024 * 1024);
void *map = mmap(NULL, 1024 * 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
if (map == MAP_FAILED) {
    // ... 
}
// ...
munmap(map, 1024 * 1024);
// read / write? mmap
```

## page kinds

page kinds:
* file-backed (MAP_SHARED)
* anonymous page: malloc -> sbrk / mmap, 4KB + hugepages (2MiB, 1GB) (MAP_ANONYMOUS)
* special kinds: vdso, java jit

## mprotect

```c
mprotect(map, 1024 * 1024, PROT_NONE);
```

## msync

```c
msync(map, 1024 * 1024, 0);
```

## shmem

```
p1   -> |        |
        | Memory |
p2   -> |        |
```

```c
int fd = shm_open(...);
void *map = mmap(NULL, 1024 * 1024, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, fd, 0);
```
