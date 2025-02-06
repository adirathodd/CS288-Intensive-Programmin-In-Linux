#include <stdio.h>
#include <stdlib.h>

struct node {
	int value;
	struct node *next;
};

void bubblesort(struct node** head){
	struct node** curr;
	struct node* temp;
	struct node* lastSwap = NULL;
	int changed = 1;

	while(changed){
		changed = 0;
		curr = head;
		while((*curr)->next != lastSwap){
			if((*curr)->value > (*curr)->next->value){
				temp = (*curr)->next;
				(*curr)->next = temp->next;
				temp->next = *curr;
				*curr = temp;
				
				changed = 1;
			}
			curr = &((*curr)->next);
		}
		lastSwap = *curr;
	}
}

int main(){
	struct node* head = NULL;
	struct node* tail = NULL;
	int data;

	while(1){
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
	
	bubblesort(&head);
	
	struct node *curr = head;
	
	while(curr != NULL){
		printf("%d\n", curr->value);
		curr = curr->next;
	}
}