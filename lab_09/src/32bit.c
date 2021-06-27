#include "32bit.h"

static void
default32BitSumLoop(const float a, const float b, const size_t count) {
    float _;

    for (size_t i = 0; i < count; ++i) {
        _ = a + b;
    }
}

static void
asm32BitSumLoop(const float a, const float b, const size_t count) {
    float _;

    for (size_t i = 0; i < count; ++i) {
        asm("flds %1\n"
            "flds %2\n"
            "faddp %%ST(0), %%ST(1)\n"
            "fstps %0\n"
            : "=m"(_)
            : "m"(a), "m"(b));
    }
}

static void
default32BitMulLoop(const float a, const float b, const size_t count) {
    float _;

    for (size_t i = 0; i < count; ++i) {
        _ = a * b;
    }
}

static void
asm32BitMulLoop(const float a, const float b, const size_t count) {
    float _;

    for (size_t i = 0; i < count; ++i) {
        asm("flds %1\n"
            "flds %2\n"
            "fmulp %%ST(0), %%ST(1)\n"
            "fstps %0\n"
            : "=m"(_)
            : "m"(a), "m"(b));
    }
}

void
print32BitResults(void) {
    printf("float type size: %zu bites\n", sizeof(float) * CHAR_BIT);

    float a = 2e43, b = 11e53;

    clock_t begin = clock();
    default32BitSumLoop(a, b, ITS);
    clock_t end = clock();

    printf(SUM_FMT, (double)(end - begin) / CLOCKS_PER_SEC / ITS);

    begin = clock();
    default32BitMulLoop(a, b, ITS);
    end = clock();

    printf(MUL_FMT, (double)(end - begin) / CLOCKS_PER_SEC / ITS);

    begin = clock();
    asm32BitSumLoop(a, b, ITS);
    end = clock();

    printf(ASM_SUM_FMT, (double)(end - begin) / CLOCKS_PER_SEC / ITS);

    begin = clock();
    asm32BitMulLoop(a, b, ITS);
    end = clock();

    printf(ASM_MUL_FMT, (double)(end - begin) / CLOCKS_PER_SEC / ITS);

    printf("\n");
}
