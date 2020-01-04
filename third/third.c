#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct node{
	int val;
	struct node* next;
};

bool insert(int num, struct node** table);
bool search(int num, struct node* *table);
void cleanTable(struct node* table[]);


bool insert(int num, struct node** table){
	struct node* newNode = malloc(sizeof(struct node));
	newNode->val = num;
	newNode->next = NULL;
	int hashNum = num%sizeof(table);
	if(table[hashNum]==NULL){
		table[hashNum] = newNode;
		return true;
	}
	else{
		struct node* temp = table[hashNum];
		while(temp!=NULL){
			if(temp->val == num)
				return false;
			else
				temp = temp->next;
		}
		newNode->next = table[hashNum];
		table[hashNum]=newNode;
		return true;
	}
}

bool search(int num, struct node** table){
	
	int hashNum = num%sizeof(table);
	if(table[hashNum]==NULL)
		return false;
	struct node* temp = table[hashNum];
	while(temp!=NULL){
		if(temp->val == num)
			return true;
		else
			temp=temp->next;
	}
	return false;	
}

void cleanTable(struct node** table){
	for(int i = 0; i < sizeof(table); i++){
		if(table[i]!=NULL){
			struct node* prev = NULL;
			struct node* ptr = table[i];
			while(ptr!=NULL){
				prev = ptr;
				ptr = ptr->next;
				free(prev);
			}
		}
	}
}

int main(int argc, char**argv){
	if(argc!=2)
		return 0;
	struct node** table = malloc(1000*sizeof(struct node));
	FILE* fp = fopen(argv[1], "r");
	char action;
	int num;
	while(fscanf(fp,"%c\n%d", &action, &num)!=EOF){
		if(action=='i'){
			if(insert(num,table))
				printf("inserted\n");
			else
				printf("duplicate\n");
		}
		if(action == 's'){
			if(search(num, table))
				printf("present\n");
			else
				printf("absent\n");
		}
	}
	cleanTable(table);
	fclose(fp);
	return 0;
}
