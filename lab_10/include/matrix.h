#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    float **data;
    size_t rows;
    size_t columns;
} Matrix;

enum ret_codes {
    ERR_GET_DET = -7,
    ERR_PRINT_MATRIX,
    ERR_FREE_MATRIX,
    ERR_SET_ELEMENT,
    ERR_GET_ELEMENT,
    ERR_GET_COLS,
    ERR_GET_ROWS,
    OK
};

#define RAND_TOP 10000

Matrix *createMatrix(void);
Matrix *allocMemory(size_t rows, size_t cols);
int printMatrix(Matrix* matrix);
int freeMatrix(Matrix* matrix);
Matrix* sum(const Matrix* l, const Matrix* r);
Matrix* sumAsm(const Matrix* l, const Matrix* r);


#endif  // __MATRIX_H__