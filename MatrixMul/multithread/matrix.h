#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>

typedef struct matrixInfo{
	int** matrix;
	int rows, cols;
} matrix;

matrix* readMatrix(const char *filename);
int matchIdentifier (FILE *f, const char *identifier);
void printMatrix(int **matrix, int rows, int cols);
void errorExit (const char *error_msg);
matrix* alocateNewMatrix(int rows, int cols);

#endif
