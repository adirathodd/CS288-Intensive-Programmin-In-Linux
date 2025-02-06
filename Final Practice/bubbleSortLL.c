#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct node {
    int val;
    struct node *next;
};

void bubblesort(struct node **head){
    if(head == NULL || *head == NULL) return;

    struct node **curr, *lastswap = NULL;
    int changed = 1;

    while(changed){
        changed = 0;
        curr = head;
        while((*curr)->next != lastswap){
            if((*curr)->val > (*curr)->next->val){
                changed = 1;
                struct node *temp = (*curr)->next;
                (*curr)->next = temp->next;
                temp->next = *curr;
                *curr = temp;
            }

            curr = &((*curr)->next);
        }

        lastswap = *curr;
    }
}

int main(int argc, char *argv[]){
    struct node *head = NULL, *tail = NULL;

    for(int i = 1; i < argc; i++){
        struct node *curr = (struct node *)malloc(sizeof(struct node));
        curr->val = strtol(argv[i], NULL, 10);
        curr->next = NULL;
        if(i == 1){ head = curr; tail = curr; }
        else { tail->next = curr; tail = tail->next; }
    }

    bubblesort(&head);

    struct node *curr = head;
    while (curr != NULL) { printf("%d ", curr->val); curr = curr->next; }
    printf("\n");
    return 0;
}