#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int matrix1_rows, matrix1_cols, **matrix1;
int matrix2_rows, matrix2_cols, **matrix2;
int matrix_out_rows, matrix_out_cols, **matrix_out;

int main (int argc, char **argv) {
    matrix1 = readMatrix("in1.txt", &matrix1_rows, &matrix1_cols);
    //matrix2 = readMatrix("in2.txt", &matrix2_rows, &matrix2_cols);

    writeMatrix("out.txt", matrix1, matrix1_rows, matrix1_cols);
    return 0;
}
