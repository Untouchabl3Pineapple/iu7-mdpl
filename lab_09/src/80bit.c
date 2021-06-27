#include "80bit.h"

static void
default80BitSumLoop(const long double a, const long double b, const size_t count) {
    long double _;

    for (size_t i = 0; i < count; ++i) {
        _ = a + b;
    }
}

static void
asm80BitSumLoop(const long double a, const long double b, const size_t count) {
    long double _;

    for (size_t i = 0; i < count; ++i) {
        asm("fldt %1\n"
            "fldt %2\n"
            "faddp %%ST(0), %%ST(1)\n"
            "fstpt %0\n"
            : "=m"(_)
            : "m"(a), "m"(b));
    }
}

static void
default80BitMulLoop(const long double a, const long double b, const size_t count) {
    long double _;

    for (size_t i = 0; i < count; ++i) {
        _ = a * b;
    }
}

static void
asm80BitMulLoop(const long double a, const long double b, const size_t count) {
    long double c;

    for (size_t i = 0; i < count; ++i) {
        asm("fldt %1\n"
            "fldt %2\n"
            "fmulp %%ST(0), %%ST(1)\n"
            "fstpt %0\n"
            : "=m"(c)
            : "m"(a), "m"(b));
    }
}

void
print80BitResults(void) {
    printf("long double type size: %zu bites\n", sizeof(long double) * CHAR_BIT);

    long double a = 2e43, b = 11e53;    

    clock_t begin = clock();
    default80BitSumLoop(a, b, ITS);
    clock_t end = clock();

    printf(SUM_FMT, (double)(end - begin) / CLOCKS_PER_SEC / ITS);

    begin = clock();
    default80BitMulLoop(a, b, ITS);
    end = clock();

    printf(MUL_FMT, (double)(end - begin) / CLOCKS_PER_SEC / ITS);

    begin = clock();
    asm80BitSumLoop(a, b, ITS);
    end = clock();

    printf(ASM_SUM_FMT, (double)(end - begin) / CLOCKS_PER_SEC / ITS);

    begin = clock();
    asm80BitMulLoop(a, b, ITS);
    end = clock();

    printf(ASM_MUL_FMT, (double)(end - begin) / CLOCKS_PER_SEC / ITS);

    printf("\n");
}
