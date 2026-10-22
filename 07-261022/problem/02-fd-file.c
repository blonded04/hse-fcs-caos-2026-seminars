/*
Программе передаётся один аргумент командной строки — путь к входному файлу.
Напишите программу, которая выводит всё содержимое этого файла на стандартный
вывод без изменений.

Откройте файл для чтения с помощью open. Читайте данные через полученный
файловый дескриптор с помощью read, а выводите с помощью write.

После обработки закройте открытый файл с помощью close.
Файл может быть пустым или содержать произвольные байты, включая \0.
Он не обязан целиком помещаться в память. Для копирования используйте буфер
размером 4096 байт; дополнительная память не должна зависеть от размера файла.

Корректно обрабатывайте короткое чтение, частичную запись и EINTR.

Чтение заканчивается, когда read возвращает 0.

При неправильном количестве аргументов или ошибке системного вызова
выведите сообщение в стандартный поток ошибок и завершите программу
с кодом 1. При успешном выполнении код завершения — 0.

На стандартный вывод попадают только байты входного файла, без дополнительных
сообщений и переводов строки.

Не используйте stdio для чтения и копирования содержимого файла.
Для сообщений об ошибках можно использовать perror.

./02-fd-file input.txt
*/

#include <sys/types.h>
#include <sys/uio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

enum { BUFFER_SIZE = 4096 };
char buffer[BUFFER_SIZE + 1];

enum { GOOD_SUBSTRING_LENGTH = 13 };
const char* GOOD_SUBSTRING = "Hello, files!";

// onvre...Hello, files!rejgonvre...Hello,
//  files!

int main(int argc, char **argv) {
    if (argc != 2) {
        perror("expected 1 argument");
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("failed to open file");
        return 1;
    }

    int read_bytes = 0;
    int current_offset = 0;
    do {
        read_bytes = read(fd, buffer + current_offset, BUFFER_SIZE - current_offset);
        if (read_bytes == -1) {
            if (errno == EINTR) {
                continue;
            }
            perror("Error occurred when reading");
            close(fd);
            return 1;
        }
        if (read_bytes == 0) {
            break;
        }

        current_offset += read_bytes;
        buffer[current_offset] = '\0';
        if (current_offset >= GOOD_SUBSTRING_LENGTH
            && strcmp(GOOD_SUBSTRING, buffer + current_offset - GOOD_SUBSTRING_LENGTH) == 0) {
            perror("All good");
            return 2;
        }
        if (current_offset >= BUFFER_SIZE - 1) {
            memcpy(buffer, buffer + BUFFER_SIZE - GOOD_SUBSTRING_LENGTH, GOOD_SUBSTRING_LENGTH);
            current_offset = GOOD_SUBSTRING_LENGTH;
        }
    } while (read_bytes != 0);

    int err = close(fd);
    if (err != 0) {
        perror("failed to close file");
        return 1;
    }

    return 0;
}
