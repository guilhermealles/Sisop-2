#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int matrix1_rows, matrix1_cols, **matrix1;
int matrix2_rows, matrix2_cols, **matrix2;
int matrix_out_rows, matrix_out_cols, **matrix_out;

int main (int argc, char **argv) {
    if (argc == 2) {
        //teste
        matrix = readMatrix(argv[1], &matrix_rows, &matrix_cols);
        printMatrix(matrix, matrix_rows, matrix_cols);
    }

    return 0;
}
