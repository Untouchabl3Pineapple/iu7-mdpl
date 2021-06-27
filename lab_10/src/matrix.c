#include "../include/matrix.h"

Matrix *createMatrix(void) {
    Matrix *matrix = NULL;
    size_t rows, columns;

    puts("Input rows and columns (with space): ");
    if (fscanf(stdin, "%zu%zu", &rows, &columns) != 2) {
        return NULL;
    }
    if (rows < 1 || columns < 1) {
        return NULL;
    }

    if ((matrix = allocMemory(rows, columns)) == NULL) {
        return NULL;
    }

    srand(time(NULL));
    for (size_t i = 0; i < matrix->rows; ++i) {
        for (size_t j = 0; j < matrix->columns; ++j) {
            matrix->data[i][j] = (float)(rand() % RAND_TOP);
        }
    }

    return matrix;
}

static void initMatrix(Matrix *const matrix, size_t rows, size_t cols) {
    matrix->data = NULL;
    matrix->rows = rows;
    matrix->columns = cols;
}

Matrix *allocMemory(size_t rows, size_t cols) {
    if (rows < 1 || cols < 1) {
        return NULL;
    }

    Matrix *matrix = (Matrix *) malloc(sizeof(Matrix));
    if (matrix == NULL) {
        return NULL;
    }

    initMatrix(matrix, rows, cols);

    matrix->data = (float **) calloc(matrix->rows, sizeof(float *));
    if (matrix->data == NULL) {
        free(matrix);
        return NULL;
    }

    for (size_t i = 0; i < matrix->rows; ++i) {
        matrix->data[i] = (float *) calloc(matrix->columns, sizeof(float));
        if (matrix->data[i] == NULL) {
            freeMatrix(matrix);
            return NULL;
        }
    }

    return matrix;
}

int printMatrix(Matrix* matrix) {
    if (matrix == NULL) {
        return ERR_PRINT_MATRIX;
    }

    for (size_t i = 0; i < matrix->rows; ++i) {
        for (size_t j = 0; j < matrix->columns; ++j) {
            printf("%12.3f", matrix->data[i][j]);
        }
        puts("");
    }

    return OK;
}

int freeMatrix(Matrix* matrix) {
    if (matrix == NULL || matrix->data == NULL) {
        return ERR_FREE_MATRIX;
    }

    for (size_t i = 0; i < matrix->rows; ++i) {
        free(matrix->data[i]);
    }

    free(matrix->data);

    free(matrix);

    return OK;
}

Matrix* sum(const Matrix* l, const Matrix* r) {
    if (l == NULL || r == NULL) {
        return NULL;
    }

    if (l->rows < 1 || l->columns < 1 || r->rows < 1 || r->columns < 1) {
        return NULL;
    }

    if (l->rows != r->rows || l->columns != r->columns) {
        return NULL;
    }

    Matrix *dst_matrix = allocMemory(l->rows, l->columns);
    if (dst_matrix == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < l->rows; ++i) {
        for (size_t j = 0; j < l->columns; ++j) {
            dst_matrix->data[i][j] = l->data[i][j] + r->data[i][j];
        }
    }

    return dst_matrix;
}

Matrix* sumAsm(const Matrix* l, const Matrix* r) {
    if (l == NULL || r == NULL) {
        return NULL;
    }

    if (l->rows < 1 || l->columns < 1 || r->rows < 1 || r->columns < 1) {
        return NULL;
    }

    if (l->rows != r->rows || l->columns != r->columns) {
        return NULL;
    }

    Matrix *dst_matrix = allocMemory(l->rows, l->columns);
    if (dst_matrix == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < l->rows; ++i) {
        for (size_t j = 0; j < l->columns; ++j) {
            __asm__(
                "movss %1, %%xmm0\n\t"
                "movss %2, %%xmm1\n\t"
                "addss %%xmm0, %%xmm1\n\t"
                "movss %%xmm1, %0\n\t"
                : "=m"(dst_matrix->data[i][j])
                : "m"(l->data[i][j]), "m"(r->data[i][j])
            );
        }
    }

    return dst_matrix;
}



