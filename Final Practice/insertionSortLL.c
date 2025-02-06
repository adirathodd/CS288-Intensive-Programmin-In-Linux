#include <stdio.h>
#include <stdlib.h>

struct node {
    int val;
    struct node *next;
};

struct node *add_to_sorted_list(struct node *head, struct node *node){
    struct node *prev, *curr, *dummy = (struct node *)malloc(sizeof(struct node));
    dummy->next = head;
    prev = dummy;
    curr = prev->next;

    while(curr){
        if (node->val > curr->val){
            break;
        }

        prev = curr;
        curr = curr->next;
    }

    node->next = curr;
    prev->next = node;
    
    struct node *new_head = dummy->next;
    free(dummy);
    return new_head;
}

int main(int argc, char *argv[]){
    struct node *head = NULL;

    for(int i = 1; i < argc; i++){
        struct node *node = (struct node *)malloc(sizeof(struct node));
        node->val = strtol(argv[i], NULL, 10);
        node->next = NULL;
        head = add_to_sorted_list(head, node);
    }

    struct node *curr = head;

    while(curr){
        printf("%d ", curr->val);
        curr = curr->next;
    }
    
    printf("\n");
    return 0;
}