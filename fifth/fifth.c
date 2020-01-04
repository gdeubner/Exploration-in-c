#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>


void cleanMatrix(int**, int);
void printMatrix(int**, int, int);
bool isMagic(int**, int);
bool isComplete(int**, int);


bool isComplete(int** matrix, int n){
	bool* array = malloc(n*n*sizeof(bool));
	for(int i = 0; i<n; i++){
		for(int j = 0; j<n; j++){
			array[matrix[i][j]-1] = true;
		}
	}
	for(int i = 0; i<n*n; i++)
		if(array[i]==false){
			free(array);
			return false;
		}
	free(array);
	return true;
}




bool isMagic(int** matrix, int n){
	int num=0;
	for(int i = 0; i<n; i++)
		num += matrix[0][i];
	int verticalTotals = 0;
	int horizontalTotals = 0;
	//checks vertical totals and horizontal totals
	for(int i = i; i<n; i++){
		for(int j = 0; j<n; j++){
			verticalTotals+=matrix[i][j];
			horizontalTotals+=matrix[j][i];
		}
		if(verticalTotals!=num||horizontalTotals!=num)
			return false;
	}
	//checks diagonals
	int diagonal1 = 0;
	int diagonal2 = 0;
	for(int i = 0; i<n; i++){
		diagonal1+=matrix[i][i];
		diagonal2+=matrix[i][n-1-i];
	}
	if(diagonal1!=num||diagonal2!=num)
		return false;
	
		
	return isComplete(matrix, n);
}


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




int main(int argc, char**argv){
	if(argc!=2)
		exit(0);
	FILE* fp = fopen(argv[1], "r");
	int n;
	if(fscanf(fp, "%d\n", &n)==EOF)
		exit(0);
	int** matrix = malloc(n*sizeof(int*));
	for(int i = 0; i<n; i++)
		matrix[i] = malloc(n*sizeof(int));
	int num;
	for(int i = 0; i<n; i++){
		for(int j = 0; j<n; j++){
			fscanf(fp, "%d", &num);
			matrix[i][j] = num;
			if(j<n-1)
				fscanf(fp, "\t");
		}
		fscanf(fp, "\n");
	}
	
	if(isMagic(matrix, n))
		printf("magic\n");
	else
		printf("not-magic\n");
	
	cleanMatrix(matrix, n);
	fclose(fp);

	return 0;
}
