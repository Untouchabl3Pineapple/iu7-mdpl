#include "../include/measurements.h"

void cTime(const Matrix* l, const Matrix* r) {
    Matrix *matrix_res = NULL;

    clock_t start = clock();

    for (size_t i = 0; i < REPEATS; ++i) {
        matrix_res = sum(l, r);

        freeMatrix(matrix_res);
    }

    clock_t end = clock();

    printf("cTime: %.3g s\n", ((double)(end - start)) / CLOCKS_PER_SEC / REPEATS);
}

void asmTime(const Matrix* l, const Matrix* r) {
    Matrix *matrix_res = NULL;

    clock_t start = clock();

    for (size_t i = 0; i < REPEATS; ++i) {
        matrix_res = sumAsm(l, r);

        freeMatrix(matrix_res);
    }

    clock_t end = clock();

    printf("asmTime: %.3g s\n", ((double)(end - start)) / CLOCKS_PER_SEC / REPEATS);
}
