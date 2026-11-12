/*
Напишите функцию:

```
int mysys(const char *str);
```

Функция должна работать аналогично функции system, то есть
создавать процесс, запускать на выполнение строку str
и дожидаться результата.
Строка str может содержать несколько аргументов, разделенных пробелами.
Функция mysys должна возвращать -1 в случае, если новый процесс не может
быть создан. Если выполнение str завершилось с кодом завершения 0-127, функция
должна возвращать это значение. Если выполнение str завершилось из-за
сигнала K, то функция должна возвращать значение 128 + K.
Если интерпретатор /bin/sh не может быть запущен, функция должна завершаться
со значением 127.
Для интерпретации строки str должен использоваться стандартный шелл /bin/sh.
(sh -c STR).
Сама функция mysys не должна ничего выводить ни на стандартный поток ошибок,
ни на стандартный поток вывода.
Функция mysys должна корректно работать независимо от использования основным процессом других функций создания процессов и функций ввода-вывода.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int mysys(const char *str) {
    pid_t pid = fork();
    if (pid == -1) {
        return -1;
    }
    if (pid == 0) {
        // child
        execlp("/bin/sh", "sh", "-c", str, NULL);
        exit(127);
    } else {
        // parent
        int status;
        pid_t result = waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            status = WEXITSTATUS(status);
            if (status < 0 || 128 < status) {
                abort();
            }
            return status;
        }
        if (WIFSIGNALED(status)) {
            status = WTERMSIG(status);
            return 128 + status;
        }
        abort();
    }
}

int main() {
    int error = mysys("ls -alh");
    printf("Error code: %d\n", error);
    error = mysys("ls -alh fjgerogreogmioregker");
    printf("Error code: %d\n", error);
    error = mysys("echo \"vsem privet\"");
    printf("Error code: %d\n", error);
}
