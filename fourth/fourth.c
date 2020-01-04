#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


void printMatrix(int** mat, int rows, int cols);
void multiply(int**, int**, int, int, int, int);
void cleanMatrix(int**, int);

void cleanMatrix(int** mat, int rows){
	for(int i = 0; i<rows; i++){
		free(mat[i]);
	}
	free(mat);
}

void printMatrix(int** mat, int rows, int cols){
	for(int i = 0; i<rows; i++){
		for(int j = 0; j<cols; j++){
			printf("%d",mat[i][j]);
			if(j<cols-1)
			printf("\t");
		}
		printf("\n");
	}
}

void multiply(int** matA, int** matB, int rowsA, int colsA, int rowsB, int colsB){
	if(colsA!=rowsB){
		printf("bad-matrices");
		return;
	}
	int rowsC = rowsA;
	int colsC = colsB;
	int** matC = malloc(rowsC*sizeof(int*));
	for(int i = 0; i<rowsC; i++)
		matC[i] = malloc(colsC*sizeof(int));
	for(int i = 0; i<rowsC; i++){
		for(int j = 0; j<colsC; j++){
			int total=0;
			
			for(int k =0; k<colsA; k++){
			 	total+= matA[i][k]*matB[k][j];
			 }
			 matC[i][j]=total;
		}
	}
	printMatrix(matC, rowsC, colsC);
	cleanMatrix(matC, rowsC);
}



int main(int argc, char** argv){
	if(argc!=2){
		exit(0);
	}
	FILE* fp = fopen(argv[1],"r");
	int rowsA, colsA, rowsB, colsB;
	if(fscanf(fp, "%d\t%d\n", &rowsA, &colsA)==EOF){
		printf("\n");
		exit(0);
	}
	//allocates space for and scans in matrixA
	int** matrixA = malloc(rowsA*sizeof(int*));
	for(int i = 0; i<rowsA; i++)
		matrixA[i]=malloc(colsA*sizeof(int ));
	for(int i = 0; i<rowsA; i++){
		for(int j = 0; j<colsA; j++){
			int num;
			fscanf(fp, "%d", &num);
			matrixA[i][j]=num;
		}
		fscanf(fp, "\n");
	}
	//allocates space for and scans in matrixB
	fscanf(fp, "%d\t%d\n", &rowsB, &colsB);
	int** matrixB = malloc(rowsB*sizeof(int*));
	for(int i = 0; i<rowsB; i++)
		matrixB[i]=malloc(colsB*sizeof(int ));
	for(int i = 0; i<rowsB; i++){
		for(int j = 0; j<colsB; j++){
			int num;
			fscanf(fp, "%d", &num);
			matrixB[i][j]=num;
		}
		fscanf(fp, "\n");
	}
	multiply(matrixA, matrixB, rowsA, colsA, rowsB, colsB);
	//frees matrixA and matrixB
	cleanMatrix(matrixA, rowsA);
	cleanMatrix(matrixB, rowsB);
	fclose(fp);

	return 0;
}
