#include "sin_cmp.h"

void
sinPiCmp(void) {
    double res = 0.0;

    puts("__math.h sin(pi)__");
    printf("pi=3.14: %g\n", sin(3.14));
    printf("pi=3.141596: %g\n", sin(3.141596));

    asm("fldpi\n"
        "fsin\n"
        "fstpl %0\n"
        :
        : "m"(res));

    puts("__fpu sin(pi)__");
    printf("%g\n\n", res);
}

void
sinPiDel2Cmp(void) {
    puts("__math.h sin(pi / 2)__");
    printf("pi=3.14: %g\n", sin(3.14 / 2));
    printf("pi=3.141596: %g\n", sin(3.141596 / 2));

    double res = 0.0;
    double del = 2.0;

    asm("fldl %1\n"
        "fldpi\n"
        "fdivp %%ST(0), %%ST(1)\n"
        "fsin\n"
        "fstpl %0\n"
        : "=m"(res)
        : "m"(del));

    puts("__fpu sin(pi / 2)__");
    printf("%g\n\n", res);
}