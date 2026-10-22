#include <stdint.h>

// whole + frac / 10^8; frac < 10^9
typedef struct {
    int32_t whole;
    uint32_t frac;
} decimal_t;

// value / 10^exp + value % 10^exp
typedef struct {
    int32_t value;
    int8_t exp;
} number_t;
// точность до K знаков после запятой (2^24,2^24+1)

// optimize for:
// 1. memory
// 2. perfomance

/*
typedef struct {
    int32_t raw;
} fixed_t;
*/
