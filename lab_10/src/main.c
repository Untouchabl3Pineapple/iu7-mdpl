#include "../include/measurements.h"

int main(void) {
    Matrix *matrix_1 = createMatrix();
    Matrix *matrix_2 = createMatrix();

    cTime(matrix_1, matrix_2);
    asmTime(matrix_1, matrix_2);

    freeMatrix(matrix_1);
    freeMatrix(matrix_2);

    return EXIT_SUCCESS;
}