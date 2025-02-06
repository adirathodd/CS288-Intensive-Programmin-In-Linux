#include <stdio.h>
#include <stdlib.h>

struct node {
    int val;
    struct node *next;
};

struct node *add_to_sorted_list(struct node *head, struct node *n){
    struct node **n_next, *curr;
    n_next = &head;
    curr = *n_next;

    while(curr != NULL){
        if (n->val < curr->val) break;
        n_next = &(curr->next);
        curr = *n_next;
    }

    *n_next = n;
    n->next = curr;
    return head;
}

int main(int argc, char *argv[]){
    struct node *head = NULL;

    for(int i = 1; i < argc; i++){
        struct node *n = (struct node *)malloc(sizeof(struct node));
        n->val = strtol(argv[i], NULL, 10);
        n->next = NULL;
        head = add_to_sorted_list(head, n);
    }

    struct node *curr = head;
    while(curr != NULL){
        printf("%d ", curr->val);
        curr = curr->next;
    }
    printf("\n");
    return 0;
}