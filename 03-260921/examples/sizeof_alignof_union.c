#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdalign.h>
#include <stdio.h>

typedef struct {
    char tag;
    uint32_t value;
    char tail;
} Record;

typedef union {
    uint32_t u32;
    uint64_t u64;
    unsigned char bytes[sizeof(uint64_t)];
} Bits;

static void dump_bytes(const void *object, size_t size) {
    const unsigned char *bytes = object;
    for (size_t i = 0; i < size; ++i)
        printf("%02x%s", (unsigned)bytes[i], i + 1 == size ? "\n" : " ");
}

int main(void) {
    printf("type       sizeof  alignof\n");
    printf("char       %6zu  %7zu\n", sizeof(char), alignof(char));
    printf("uint32_t   %6zu  %7zu\n", sizeof(uint32_t), alignof(uint32_t));
    printf("uint64_t   %6zu  %7zu\n", sizeof(uint64_t), alignof(uint64_t));
    printf("Record     %6zu  %7zu\n", sizeof(Record), alignof(Record));
    printf("Bits       %6zu  %7zu\n", sizeof(Bits), alignof(Bits));

    printf("Record offsets: tag=%zu value=%zu tail=%zu\n",
           offsetof(Record, tag), offsetof(Record, value), offsetof(Record, tail));
    printf("Bits offsets: u32=%zu u64=%zu bytes=%zu\n",
           offsetof(Bits, u32), offsetof(Bits, u64), offsetof(Bits, bytes));

    Bits bits = {.u64 = UINT64_C(0x1122334455667788)};
    printf("bits.u64 = 0x%016" PRIx64 "\n", bits.u64);
    printf("union bytes, from lowest to highest address:\n");
    dump_bytes(&bits, sizeof(bits));
    return 0;
}
