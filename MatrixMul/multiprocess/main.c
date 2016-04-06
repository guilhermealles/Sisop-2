#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "matrix.h"

int matrix1_rows, matrix1_cols, **matrix1;
int matrix2_rows, matrix2_cols, **matrix2;
int matrix_out_rows, matrix_out_cols, **matrix_out;

int process_count = 0;
int process_rank = 0;
pid_t pid = -1;

void multiplyMatrices();

int main (int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <processcount>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    process_count = strtol(argv[1], NULL, 10);
    if (process_count == 0) {
        fprintf(stderr, "Error: process count cannot be zero.\n");
        exit(EXIT_FAILURE);
    }

    matrix1 = readMatrix("in1.txt", &matrix1_rows, &matrix1_cols);
    matrix2 = readMatrix("in2.txt", &matrix2_rows, &matrix2_cols);

    if (matrix1_cols != matrix2_rows) {
        fprintf(stderr, "Error: these two matrices cannot be multiplied!\n");
        exit(EXIT_FAILURE);
    }

    // Allocate output matrix in memory;
    matrix_out_rows = matrix1_rows;
    matrix_out_cols = matrix2_cols;
    matrix_out = (int**) malloc(sizeof(int*) * matrix_out_rows);
    int i;
    for(i=0; i<matrix_out_rows; i++) {
        matrix_out[i] = (int*) malloc(sizeof(int) * matrix_out_cols);
    }

    // Create child processes
    for (i=0; i<process_count-1; i++) {
        // Parent process sets the rank for the child and forks
        if (pid != 0) {
            process_rank++;
            pid = fork();
            if (pid == -1) {
                fprintf(stderr, "Error while creating child processes.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    if (pid != 0) {
        // Parent is always rank 0
        process_rank = 0;
    }

    /*  A partir daqui dá pra iniciar a multiplicação.
        Os processos são identificados na variável process_rank
        e são numerados de 0 a n-1, sendo 0 o processo pai */
    //multiplyMatrices();
    //writeMatrix("out.txt", matrix_out, matrix_out_rows, matrix_out_cols);
    return 0;
}

void multiplyMatrices() {
    int i, j, k, sum=0;

    for(i=0; i<matrix1_rows; i++) {
        for(j=0; j<matrix2_cols; j++) {
            for(k=0; k<matrix2_rows; k++) {
                sum += matrix1[i][k] * matrix2[k][j];
            }

            matrix_out[i][j] = sum;
            sum = 0;
        }
    }
}
