#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int matrix_rows;
int matrix_cols;
int **matrix;

int main (int argc, char **argv) {
    if (argc == 2) {
        //teste
        matrix = readMatrix(argv[1], &matrix_rows, &matrix_cols);
        printMatrix(matrix, matrix_rows, matrix_cols);
    }

    return 0;
}
