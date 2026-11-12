#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

enum { PAGE_SIZE = 4096 };

static void dump_file(const char *path) {
    int fd = open(path, O_RDONLY);
    char buf[PAGE_SIZE + 1] = {0};
    ssize_t n = read(fd, buf, PAGE_SIZE);
    close(fd);
    if (n < 0) {
        perror("read");
        return;
    }
    buf[n] = 0;
    printf("  file content: \"%s\"\n", buf);
}

int main(void) {
    const char *path = "/tmp/mmap_demo.txt";

    int fd = open(path, O_CREAT | O_TRUNC | O_RDWR, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }
    if (ftruncate(fd, PAGE_SIZE) < 0) {
        perror("ftruncate");
        return 1;
    }
    char init[PAGE_SIZE];
    memset(init, 'A', PAGE_SIZE);
    if (pwrite(fd, init, PAGE_SIZE, 0) != PAGE_SIZE) {
        perror("pwrite");
        return 1;
    }

    // MAP_SHARED
    char *sh = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (sh == MAP_FAILED) {
        perror("mmap shared");
        return 1;
    }
    printf("[MAP_SHARED]\n");
    printf("  before write, file: ");
    dump_file(path);
    memcpy(sh, "HELLO_SHARED", 12);
    msync(sh, PAGE_SIZE, MS_SYNC);
    printf("  after  write, file: ");
    dump_file(path);

    // MAP_PRIVATE
    char *pr = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (pr == MAP_FAILED) {
        perror("mmap private");
        return 1;
    }
    printf("[MAP_PRIVATE]\n");
    printf("  before write, file: ");
    dump_file(path);
    memcpy(pr, "HELLO_PRIVATE", 13);
    msync(pr, PAGE_SIZE, MS_SYNC);
    printf("  after  write, file: ");
    dump_file(path);
    printf("  private view in memory: \"%.13s\"\n", pr);

    munmap(sh, PAGE_SIZE);
    munmap(pr, PAGE_SIZE);
    close(fd);
    unlink(path);
    return 0;
}