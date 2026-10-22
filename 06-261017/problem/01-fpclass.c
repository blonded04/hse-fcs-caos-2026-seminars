#include "01-fpclass.h"

/*
Функция на вход принимает число `value` типа `float` и возвращает значение,
соответствующее классу этого числа.
Если число не является `NaN`, то в переменную `psign` возвращается бит знака числа.
Для чисел `NaN` бит знака всегда должен быть 0.
typedef enum FPClass {
    FFP_ZERO,
    FFP_DENORMALIZED,
    FFP_NORMALIZED,
    FFP_INF,
    FFP_NAN
} FPClass;
*/

enum { EXPONENT = 0x7f800000, MANTISSA = 0x007fffff, NAN_EXPONENT = 255 };

FPClass fpclassf(float value, int *psign) {
    const unsigned* unsigned_value_ptr = (unsigned*) &value;  // beware of strict aliasing rule
    unsigned sign = *unsigned_value_ptr >> 31;
    unsigned exponent = (*unsigned_value_ptr & EXPONENT) >> 23;
    unsigned mantissa = *unsigned_value_ptr & MANTISSA;

    *psign = 0;
    if (exponent == NAN_EXPONENT && mantissa != 0) {
        return FFP_NAN;
    }
    *psign = sign;
    if (exponent == NAN_EXPONENT) {
        return FFP_INF;
    }
    if (exponent == 0) {
        if (mantissa == 0) {
            return FFP_ZERO;
        } else {
            return FFP_DENORMALIZED;
        }
    }
    return FFP_NORMALIZED;
}
