#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int first_matrix_rows, second_matrix_rows;
int first_matrix_cols, second_matrix_cols;
int **first_matrix, **second_matrix, **multMatrix;

int main (int argc, char **argv) {
   if (argc == 3) {

        //teste
        first_matrix = readMatrix(argv[1], &first_matrix_rows, &first_matrix_cols);
		second_matrix = readMatrix(argv[2], &second_matrix_rows, &second_matrix_cols);

		if(first_matrix_cols == second_matrix_rows){
	    	multMatrix = alocateNewMatrix(first_matrix_cols, second_matrix_rows);
		}else{
			errorExit("First matrix cols must be the same length to second matrix rows \n");
		}
		    
		printMatrix(first_matrix, first_matrix_rows, first_matrix_cols);
		printMatrix(second_matrix, second_matrix_rows, second_matrix_cols);
	    printMatrix(multMatrix, first_matrix_cols, second_matrix_rows);
    }

    return 0;
}
