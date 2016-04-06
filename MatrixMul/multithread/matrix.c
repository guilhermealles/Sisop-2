#include <stdlib.h>
#include "matrix.h"

matrix* readMatrix (const char *filename) {
    FILE *f;
    int local_rows=0, local_cols=0, i;

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

    matrix *m = (matrix*) malloc(sizeof(matrix));
    m->matrix = (int**) malloc(sizeof(int*) * local_rows);
    for (i=0; i<local_rows; i++) {
        m->matrix[i] = (int*) malloc(sizeof(int) * local_cols);
    }

    int j, value;
    for (i=0; i<local_cols; i++) {
        for (j=0; j<local_rows; j++) {
            if (fscanf(f, "%d ", &value) == 1) {
                m->matrix[i][j] = value;
            }
            else {
                errorExit("Error reading value from matrix file.\n");
            }
        }
    }

    m->rows = local_rows;
    m->cols = local_cols;
    return m;
}

matrix *alocateNewMatrix(int rows, int cols){
    matrix *newMatrix;
    int i, j;

	newMatrix = (matrix*) malloc(sizeof(matrix));

    newMatrix->matrix = (int**) malloc(sizeof(int*) * rows);
	newMatrix->rows = rows;
	newMatrix->cols = cols;

    for(i=0; i<rows; i++){
		newMatrix->matrix[i] = (int*) malloc(sizeof(int) * cols);
    }

    for(i=0; i<rows; i++){
		for(j=0; j<cols; j++){
			newMatrix->matrix[i][j] = -999;    // valor padrao p/ indicar erro
		}
    }

    return newMatrix;	
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
