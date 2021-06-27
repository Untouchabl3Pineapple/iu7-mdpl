#include "64bit.h"

static void
default64BitSumLoop(const double a, const double b, const size_t count) {
    double _;

    for (size_t i = 0; i < count; ++i) {
        _ = a + b;
    }
}

static void
asm64BitSumLoop(const double a, const double b, const size_t count) {
    double _;

    for (size_t i = 0; i < count; ++i) {
        asm("fldl %1\n"
            "fldl %2\n"
            "faddp %%ST(0), %%ST(1)\n"
            "fstpl %0\n"
            : "=m"(_)
            : "m"(a), "m"(b));
    }
}

static void
default64BitMulLoop(const double a, const double b, const size_t count) {
    double _;

    for (size_t i = 0; i < count; ++i) {
        _ = a * b;
    }
}

static void
asm64BitMulLoop(const double a, const double b, const size_t count) {
    double _;

    for (size_t i = 0; i < count; ++i) {
        asm("fldl %1\n"
            "fldl %2\n"
            "fmulp %%ST(0), %%ST(1)\n"
            "fstpl %0\n"
            : "=m"(_)
            : "m"(a), "m"(b)
            :);
    }
}

void
print64BitResults(void) {
    printf("double type size: %zu bites\n", sizeof(double) * CHAR_BIT);

    double a = 2e43, b = 11e53;

    clock_t begin = clock();
    default64BitSumLoop(a, b, ITS);
    clock_t end = clock();

    printf(SUM_FMT, (double)(end - begin) / CLOCKS_PER_SEC / ITS);

    begin = clock();
    default64BitMulLoop(a, b, ITS);
    end = clock();

    printf(MUL_FMT, (double)(end - begin) / CLOCKS_PER_SEC / ITS);

    begin = clock();
    asm64BitSumLoop(a, b, ITS);
    end = clock();

    printf(ASM_SUM_FMT, (double)(end - begin) / CLOCKS_PER_SEC  / ITS);

    begin = clock();
    asm64BitMulLoop(a, b, ITS);
    end = clock();

    printf(ASM_MUL_FMT, (double)(end - begin) / CLOCKS_PER_SEC / ITS);

    printf("\n");
}
