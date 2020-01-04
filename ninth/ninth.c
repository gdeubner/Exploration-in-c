#include<stdlib.h>
#include<stdio.h>

struct node{
	int key;
	struct node* left;
	struct node* right;
	//struct node* parent;
};

struct node* insert(struct node*, int);
int search(struct node*, int);
struct node* delete(struct node*, int);
void cleanTree(struct node*);
struct node* delete(struct node*, int);
struct node* replace(struct node*, struct node* prev);

//recursive method to find th node that the deleted node will be replaced with, and the node that will replace the that node, and so on
struct node* replace(struct node* ptr, struct node* prev){
		struct node* ptr2 = ptr->right;
		struct node* prev2 = NULL;
		while(ptr2->left!=NULL){
			prev2 = ptr2;
			ptr2=ptr2->left;
		}
		//base case
		if(ptr2->right==NULL){
			if(prev2!=NULL)
				prev2->left = NULL;
			if(ptr->right==ptr2)
				ptr2->right = NULL;
			else
				ptr2->right = ptr->right;
			ptr2->left = ptr->left;
			return ptr2;
		}
		else if(prev2==NULL){
			ptr2->left = ptr->left;
			return ptr2;
		}
		else{
			if(prev2->left == ptr2){
		 		prev2->left = replace(ptr2, prev2);
		 		ptr2->left = ptr->left;
				ptr2->right = ptr->right;
		 		return ptr2;
		 	}
		 	else
		 		prev2->right = replace(ptr2, prev2);
		 		ptr2->left = ptr->left;
				ptr2->right = ptr->right;
		 		return ptr2;
		}
}
struct node* delete(struct node* head, int key){
	struct node* prev = NULL;
	struct node* ptr = head;
	//searches for node
	while(ptr!=NULL){
		if(key<ptr->key){
			prev = ptr;
			ptr=ptr->left;
		}
		else if(key>ptr->key){
			prev = ptr;
			ptr=ptr->right;
		}
		else if(key==ptr->key){
			break;
		}
	}
	//node not found
	if(ptr==NULL){
		printf("fail\n");
		return head;
	}
	//found node at the bottom of the tree
	if((ptr->left==NULL&&ptr->right==NULL)){
		if(prev==NULL)
			head=NULL;
		else{
			if(prev->left==ptr)
				prev->left = NULL;
			else
				prev->right=NULL;
		}
		printf("success\n");
		free(ptr);
		return head;
	}
	//head points to ptr, deleting the root of the tree
	if(prev==NULL){
		head = replace(ptr, prev);
	}
	//else
	else{
		if(prev->right == ptr){
			prev->right = replace(ptr, prev);
		}
		else{
			prev->left = replace(ptr, prev);
		}
	}
	free(ptr);
	printf("success\n");
	return head;
}

void cleanTree(struct node* head){
	if(head==NULL)
		return;
	cleanTree(head->left);
	cleanTree(head->right);
	free(head);
}
struct node* insert(struct node* head, int key){
	int level = 1;
	if (head==NULL){
		struct node* node = malloc(sizeof(struct node));
		node->key = key;
		node->left = NULL;
		node->right = NULL;
		head = node;
		printf("inserted 1\n");
		return head;
	}
	else{
		struct node* prev = NULL;
		struct node* ptr = head;
		while(ptr!=NULL){
			if(ptr->key == key){
				printf("duplicate\n");
				return head;
			}
			else if(key < ptr->key){
				level++;
				prev = ptr;
				ptr=ptr->left;
			}
			else{
				level++;
				prev = ptr;
				ptr = ptr->right;
			}
		}
		struct node* node = malloc(sizeof(struct node));
		node->key = key;
		node->left = NULL;
		node->right = NULL;
		if(key > prev->key){
			prev->right = node;
			printf("inserted %d\n", level);
			return head;
		}
		else{
			prev->left = node;
			printf("inserted %d\n", level);
			return head;
		}
	}
}
int search(struct node* head, int key){
	struct node* ptr = head;
	int level = 1;
	while(ptr!=NULL){
		if(ptr->key==key){
			return level;
		}
		else if(key<ptr->key){
			ptr=ptr->left;
			level++;
		}
		else{
			ptr=ptr->right;
			level++;
		}
	}
	return 0;
}
int main(int argc,char** argv){
	if(argc!=2)
		exit(0);
	FILE* fp = fopen(argv[1], "r");
	if(fp==NULL){
		printf("error\n");
		exit(0);
	}
	char action;
	int val;
	struct node* head = NULL;
	
	while(fscanf(fp, "%c\t%d\n", &action, &val)!=EOF){
		
		
		if(action=='i'){
			head = insert(head, val);
		}
		else if(action=='s'){
			
			int ret = search(head, val);
			if(ret == 0)
				printf("absent\n");
			else
				printf("present %d\n", ret);
		}
		else if(action == 'd'){
			head = delete(head, val);
		}
	}
	cleanTree(head);
	fclose(fp);
	return 0;
}
