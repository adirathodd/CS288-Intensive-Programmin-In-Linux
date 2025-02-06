#include <stdio.h>
#include <stdlib.h>

struct node {
	int value;
	struct node *next;
};

int main(){
	struct node* head = NULL;
	struct node* tail = NULL;
	int data, count = 1;

	while(1){
	 	printf("Input data for node %d - ", count++);
		if(scanf("%d", &data) == EOF) break;
		struct node *currNode = (struct node *)malloc(sizeof(struct node));
		currNode->value = data;
		currNode->next = NULL;
		
		if(head == NULL){
			head = currNode;
		} else {
			tail->next = currNode;
		}
		tail = currNode;
	}
	
	printf("\n\n");
	
	struct node *curr = head;
	count = 1;
	printf("Data entered in the list is: \n");
	while(curr != NULL){
		printf("Node %d - %d\n", count++, curr->value);
		curr = curr->next;
	}
	printf("\n");
	
	struct node* dummy = NULL;
	curr = head;
	
	while(curr != NULL){
		struct node* temp = curr->next;
		curr->next = dummy;
		dummy = curr;
		curr = temp;
	}
	
	count = 1;
	
	printf("The list in reverse is: \n");
	
	while(dummy != NULL){
		printf("Node %d - %d\n", count++, dummy->value);
		dummy = dummy->next;
	}
	printf("\n");
}