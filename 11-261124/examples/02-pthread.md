# pthread

## `pthread_create`
```c
// void *(*start_routine)(void *)
void* start_routine(void* arg) {
    // ...
}

int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
```

## `pthread_join`

fork-join:
```
|
|
fork
|   \
|   |
|   |
|   /
join
|
|
````

join: 
```c
int pthread_join(pthread_t thread, void **value_ptr);
```

1. Waits for thread function to end.
2. Cleanup.

## `pthread_detach`

```c
// pthread_detach(pthread_self());
int pthread_detach(pthread_t thread);
```

## `pthread_self`

```c
pthread_t pthread_self(void);
```

## thread-local

### `pthread_key_create`

### `pthread_key_delete`

### `pthread_getspecific`

### `pthread_setspecific`

## `pthread_cancel`

```c
int pthread_cancel(pthread_t thread);
```
