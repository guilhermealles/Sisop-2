#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"


matrix *matrix1, *matrix2, *multMatrix;
int num_threads;

int main (int argc, char **argv) {
   if (argc == 3) {

        // read and allocate matrix
        matrix1 = readMatrix(argv[1]);
		matrix2 = readMatrix(argv[2]);

		// validate if is possible to multiply
		if(matrix1->cols == matrix2->rows){
	    	multMatrix = alocateNewMatrix(matrix1->cols, matrix2->rows);
		}else{
			errorExit("First matrix cols must be the same length to second matrix rows \n");
		}
		   
		

		// verificacao 
		printMatrix(matrix1->matrix, matrix1->rows, matrix1->cols);
		printMatrix(matrix2->matrix, matrix2->rows, matrix2->cols);
	    printMatrix(multMatrix->matrix, matrix1->cols, matrix2->rows);
    }

    return 0;
}
