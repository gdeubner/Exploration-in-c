#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main(int argc, char** argv){

	char vowels[] = {'a', 'e', 'i', 'o', 'u'};

	for(int i = 1; i<argc; i++){
		
		char c = argv[i][0];
		if(c=='a'||c=='e'||c=='i'||c=='o'||c=='u'||c=='A'||c=='E'||c=='I'||c=='O'||c=='U'){
			printf(argv[i]);
			printf("yay");
		}
		else{
		//a=0, e=1, i=2, o=3, u=4
		char** vowelPositions = malloc(5*sizeof(char*));
		//gets position of all vowels in word
		for(int j = 0; j<5; j++){
			vowelPositions[j] = strchr(argv[i], vowels[j]);
		}
		//sets first to first a non-NULL position, if it exists
		char* first =vowelPositions[0];
		if(vowelPositions[0]==NULL){
			for(int l = 1; l<5; l++){
				if(vowelPositions[l]!=NULL){
					first = vowelPositions[l];
					break;
				}
			}
		}
		//if no vowels, prints word as is
		if(first==NULL){
			printf(argv[i]);
		}
		//sets first to position of first vowel
		else{
			for(int k = 0; k<5; k++){
				if(vowelPositions[k]!=NULL && strlen(vowelPositions[k])>strlen(first))
					first = vowelPositions[k];
			}
			printf(first);
			//prints consonants before vowel, 1 char at a time
			int numChars = strlen(argv[i])-strlen(first);
			for(int j = 0; j<numChars; j++)
				printf("%c", argv[i][j]);
			
		}
		printf("ay");
		free(vowelPositions);
		}
		if(i<argc-1)
				printf(" ");
	}
	printf("\n");

	return 0;
}
