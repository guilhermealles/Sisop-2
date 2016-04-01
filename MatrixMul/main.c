#include <stdio.h>
#include <stdlib.h>

int readMatrix (const char *filename);
int matchIdentifier(FILE *f, const char *identifier);
void printMatrix();
void errorExit(const char *error_msg);

int matrix_rows;
int matrix_cols;
int **matrix;

int main (int argc, char **argv) {
    if (argc == 2) {
        readMatrix(argv[1]);
        printMatrix();
    }
    return 0;
}

int readMatrix (const char *filename) {
    FILE *f;

    f = fopen(filename, "r");
    if (!f) {
        errorExit("Fatal error: failed to open file.\n");
    }

    if (matchIdentifier(f, "LINHAS =")) {
        fscanf(f, "%u\n", &matrix_rows);
    }
    else {
        errorExit("Error: expected \"LINHAS =\".\n");
    }

    if (matchIdentifier(f, "COLUNAS =")) {
        fscanf(f, "%u\n", &matrix_cols);
    }
    else {
        errorExit("Error: expected \"COLUNAS =\"");
    }

    // Allocate matrix in memory
    matrix = (int**) malloc(sizeof(int*) * matrix_rows);
    int i;
    for (i=0; i<matrix_rows; i++) {
        matrix[i] = (int*) malloc(sizeof(int) * matrix_cols);
    }

    int j;
    for (i=0; i<matrix_cols; i++) {
        for (j=0; j<matrix_rows; j++) {
            int value;
            if (fscanf(f, "%d ", &value) == 1) {
                matrix[i][j] = value;
            }
            else {
                errorExit("Error reading value from matrix file.\n");
            }
        }
    }

    return 0;
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

void printMatrix() {
    int i, j;
    for (i=0; i<matrix_rows; i++) {
        for (j=0; j<matrix_cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void errorExit (const char *error_msg) {
    fprintf(stderr, error_msg);
    exit (EXIT_FAILURE);
}
