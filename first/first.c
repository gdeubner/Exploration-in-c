#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>

bool isPrime(int);
void truncPrime(int);
void isTruncatablePrime(FILE*);

int main(int argc, char**argv){
	if(argc!=2)
		return 0;
	FILE* fp = fopen(argv[1],"r");
	isTruncatablePrime(fp);
	fclose(fp);
	return 0;
}

void isTruncatablePrime(FILE* fp){
	int total;
	fscanf(fp,"%d\n", &total);
	for(int i=0; i<total;i++){
		int temp;
		fscanf(fp,"%d\n",&temp);
		truncPrime(temp);
	}
}

bool isPrime(int num){
	if(num==0||num==1)
		return false;
	if (num==2)
		return true;
	for(int i = 2; i<=(num)/2+1; i++){
		if (num%i==0){
			return false;
		}
	}
	return true;
}

void truncPrime(int num){
	
	int x = num;
	while(x>0){
		
		if(!isPrime(x)){
			printf("no\n");
			return;
		}
		x/=10;;
	}
	printf("yes\n");
}
