#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>


int** readMatrix(const char *filename, int *rows, int *cols);
int matchIdentifier (FILE *f, const char *identifier);
void printMatrix(int **matrix, int rows, int cols);
void errorExit (const char *error_msg);
int** alocateNewMatrix(int rows, int cols);

#endif
