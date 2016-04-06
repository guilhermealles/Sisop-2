#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>


int** readMatrix(const char *filename, int *rows, int *cols);
int writeMatrix(const char *filename, int **matrix, int rows, int columns);
int matchIdentifier (FILE *f, const char *identifier);
void printMatrix(int **matrix, int rows, int cols);
void errorExit (const char *error_msg);

#endif
