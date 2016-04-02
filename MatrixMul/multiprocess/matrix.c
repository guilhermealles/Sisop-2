#include <stdlib.h>
#include "matrix.h"

int** readMatrix (const char *filename, int *rows, int *cols) {
    FILE *f;
    int local_rows=0, local_cols=0;

    f = fopen(filename, "r");
    if (!f) {
        errorExit("Fatal error: failed to open file.\n");
    }

    if (matchIdentifier(f, "LINHAS =")) {
        fscanf(f, "%u\n", &local_rows);
    }
    else {
        errorExit("Error: expected \"LINHAS =\".\n");
    }

    if (matchIdentifier(f, "COLUNAS =")) {
        fscanf(f, "%u\n", &local_cols);
    }
    else {
        errorExit("Error: expected \"COLUNAS =\"");
    }

    // Allocate matrix in memory
    int **matrix;
    matrix = (int**) malloc(sizeof(int*) * local_rows);
    int i;
    for (i=0; i<local_rows; i++) {
        matrix[i] = (int*) malloc(sizeof(int) * local_cols);
    }

    int j;
    for (i=0; i<local_cols; i++) {
        for (j=0; j<local_rows; j++) {
            int value;
            if (fscanf(f, "%d ", &value) == 1) {
                matrix[i][j] = value;
            }
            else {
                errorExit("Error reading value from matrix file.\n");
            }
        }
    }

    *rows = local_rows;
    *cols = local_cols;
    return matrix;
}

int matchIdentifier (FILE *f, const char *identifier) {
    int i=0, done=0;
    char c;

    while (! done) {
        if (identifier[i] == '\0') {
            done = 1;
        }
        else {
            c = fgetc(f);
            if (identifier[i] != c) {
                return 0;
            }
            i++;
        }
    }
    return 1;
}

void printMatrix(int**matrix, int rows, int cols) {
    printf("Rows: %d,\tCols: %d.\n", rows, cols);
    int i, j;
    for (i=0; i<rows; i++) {
        for (j=0; j<cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void errorExit (const char *error_msg) {
    fprintf(stderr, error_msg);
    exit (EXIT_FAILURE);
}
