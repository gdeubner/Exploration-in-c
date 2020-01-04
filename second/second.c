#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct node{
	int val;
	struct node* next;
};


struct node* head = NULL;
int total = 0;

void insert(int num);
void printLL();
void delete(int num);
void cleanUp();


void insert(int num){
	struct node* newNode = malloc(sizeof(struct node));
	newNode->val = num;
	newNode->next = NULL;
	//adds newNode is the first and only entry
	if(head==NULL){
		newNode->next = head;
		head=newNode;
		total++;
		return;
	}
	struct node* prev = NULL;
	struct node* ptr = head;
	while(ptr!=NULL){
		//duplicate, do nothing
		if(num==ptr->val){  
			free(newNode);
			return;
		}
		//found correct spot, insert
		if(num<ptr->val){
			newNode->next=ptr;
			if(prev==NULL){
				head = newNode;
			}
			else{
				prev->next = newNode;
			}
			total++;
			return;
		}
		//move to next node
		else{
			prev=ptr;
			ptr=ptr->next;
		}
	}
	prev->next = newNode;
	total++;
	return;
}

void delete(int num){
	struct node* prev = NULL;
	struct node* ptr = head;
	while(ptr!=NULL){
		if(ptr->val==num){
			//removes first node
			if(prev==NULL){
				head=ptr->next;
				free(ptr);
				total--;
				return;
			}
			//removes any other node
			else{
				prev->next = ptr->next;
				free(ptr);
				total--;
				return;
			}
		}
		else{
			prev = ptr;
			ptr=ptr->next;
		}
	}
}

void printLL(){
	printf("%d\n", total);
	struct node* ptr = head;
	while(ptr!=NULL){
		printf("%d", ptr->val);
		if(ptr->next!=NULL)
			printf("\t");
		ptr=ptr->next;
	}
	printf("\n");
}

void cleanUp(){
	struct node* prev = NULL;
	struct node* ptr = head;
	while(ptr!=NULL){
		free(prev);
		prev=ptr;
		ptr=ptr->next;
	}
}



int main(int argc, char**argv){
	if(argc!=2)
		return 0;
	FILE* fp = fopen(argv[1], "r");
	if(fp==NULL){
		printf("error\n");
		return 0;
	}
	char action;
	int num;
	bool go = true;
	while(go){
		if(fscanf(fp,"%c\t%d\n",&action, &num) == EOF)
			break;
		if(action=='i')
			insert(num);
		if(action=='d')
			delete(num);
	}
	printLL();
	cleanUp();
	fclose(fp);
	return 0;
}
