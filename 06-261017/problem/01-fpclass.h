#ifndef FPCLASS_H_
#define FPCLASS_H_

typedef enum FPClass {
    FFP_ZERO,
    FFP_DENORMALIZED,
    FFP_NORMALIZED,
    FFP_INF,
    FFP_NAN
} FPClass;

FPClass fpclassf(float value, int *psign);

#endif  // FPCLASS_H_
