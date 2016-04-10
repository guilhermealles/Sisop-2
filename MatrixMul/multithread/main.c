#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "matrix.h"


matrix *matrix1, *matrix2, *multMatrix;
int num_threads;

void* multiply(void* tid){
	int i, j,k, result;
	int line = (int) tid;

	for(k = line; k < matrix1->rows; k += num_threads){ 
		for(i=0; i < matrix2->cols; i++){
			result = 0;
			for(j=0; j < matrix1->rows; j++){
				result = result + (matrix1->matrix[k][i] * matrix2->matrix[j][i]); 
			}
			multMatrix->matrix[k][i] = result;	
		}
	}
	return 0;
}

int main (int argc, char **argv) {
   if (argc == 4) {
		pthread_t * thread;
		int i=0;

        // read and allocate matrix
        matrix1 = readMatrix(argv[1]);
		matrix2 = readMatrix(argv[2]);

		num_threads = strtol(argv[3], NULL, 10);

		if(num_threads == 0){
			errorExit("Threads number must be higher than 0.\n");
		}

		// validate if is possible to multiply
		if(matrix1->cols == matrix2->rows){
	    	multMatrix = alocateNewMatrix(matrix1->cols, matrix2->rows);
		}else{
			errorExit("First matrix cols must be the same length to second matrix rows \n");
		}
		   
		if(num_threads > matrix1->rows){
			num_threads = matrix1->rows;
		}

		thread = (pthread_t*) malloc(sizeof(pthread_t) * num_threads);
		/* descriptors */
		pthread_attr_t attr; 
		pthread_attr_init(&attr);
		pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

		for(i=0; i < num_threads; i++){
			if(pthread_create(&thread[i], NULL, (void *(*) (void *)) multiply, (void *)i) != 0){
				printf("Error creating threads \n");
			}	
		}

		for(i=0; i < num_threads; i++){
      		pthread_join(thread[i], NULL); 
		}

		// verificacao 
		printMatrix(matrix1->matrix, matrix1->rows, matrix1->cols);
		printMatrix(matrix2->matrix, matrix2->rows, matrix2->cols);
	    printMatrix(multMatrix->matrix, matrix1->cols, matrix2->rows);

		
    }

    return 0;
}
