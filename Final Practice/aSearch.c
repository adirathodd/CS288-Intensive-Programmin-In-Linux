#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 3

struct node {
    int f, g, h;
    struct node *prev, *next;
    int state[3][3];
    int zero_col, zero_row;
};

struct node *openHead = NULL, *closeHead = NULL, *initial, *goal;
struct node *succ[4];

void initialize(int argc, char *argv[]){
    initial = (struct node *)malloc(sizeof(struct node));
    initial->f = 0; initial->g = 0; initial->h = 0;
    initial->next = NULL; initial->prev = NULL;

    goal = (struct node *)malloc(sizeof(struct node));
    goal->f = 0; goal->g = 0; goal->h = 0;
    goal->next = NULL; goal->prev = NULL;
    goal->zero_col = 2; goal->zero_row = 2;

    for(int i = 0; i < 9; i++){
        int x = i / 3, y = i % 3;
        initial->state[x][y] = strtol(argv[i+1], NULL, 10);
        if(initial->state[x][y] == 0){
            initial->zero_row = x;
            initial->zero_col = y;
        }
    }

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
        goal->state[i][j] = (i * 3 + j + 1) % 9;
    }
}

    openHead = initial;
}

int move_up(struct node* node){
    if(node == NULL) return 0;
    if(node->zero_row == 0) return 0;
    int zero_x = node->zero_row, zero_y = node->zero_col;

    int temp = node->state[zero_x - 1][zero_y];
    node->state[zero_x][zero_y] = temp;
    node->state[zero_x - 1][zero_y] = 0;
    node->zero_row--;

    return 1;
}

int move_down(struct node* node){
    if(node == NULL) return 0;
    if(node->zero_row == 2) return 0;
    int zero_x = node->zero_row, zero_y = node->zero_col;

    int temp = node->state[zero_x + 1][zero_y];
    node->state[zero_x][zero_y] = temp;
    node->state[zero_x + 1][zero_y] = 0;
    node->zero_row++;

    return 1;
}

int move_left(struct node* node){
    if(node == NULL) return 0;
    if(node->zero_col == 0) return 0;
    int zero_x = node->zero_row, zero_y = node->zero_col;

    int temp = node->state[zero_x][zero_y - 1];
    node->state[zero_x][zero_y] = temp;
    node->state[zero_x][zero_y - 1] = 0;
    node->zero_col--;

    return 1;
}

int move_right(struct node* node){
    if(node == NULL) return 0;
    if(node->zero_col == 2) return 0;
    int zero_x = node->zero_row, zero_y = node->zero_col;

    int temp = node->state[zero_x][zero_y + 1];
    node->state[zero_x][zero_y] = temp;
    node->state[zero_x][zero_y + 1] = 0;
    node->zero_col++;

    return 1;
}

void expand(struct node *cnode){
    int index = 0;

    // Move up
    struct node *node1 = (struct node *)malloc(sizeof(struct node));
    memcpy(node1, cnode, sizeof(struct node));
    node1->prev = cnode;
    node1->next = NULL;
    if(move_up(node1)){
        succ[index++] = node1;
    } else {
        free(node1);
    }

    // Move down
    struct node *node2 = (struct node *)malloc(sizeof(struct node));
    memcpy(node2, cnode, sizeof(struct node));
    node2->prev = cnode;
    node2->next = NULL;
    if(move_down(node2)){
        succ[index++] = node2;
    } else {
        free(node2);
    }

    // Move left
    struct node *node3 = (struct node *)malloc(sizeof(struct node));
    memcpy(node3, cnode, sizeof(struct node));
    node3->prev = cnode;
    node3->next = NULL;
    if(move_left(node3)){
        succ[index++] = node3;
    } else {
        free(node3);
    }

    // Move right
    struct node *node4 = (struct node *)malloc(sizeof(struct node));
    memcpy(node4, cnode, sizeof(struct node));
    node4->prev = cnode;
    node4->next = NULL;
    if(move_right(node4)){
        succ[index++] = node4;
    } else {
        free(node4);
    }

    for(int i = index; i < 4; i++){
        succ[i] = NULL;
    }
}

int checkstate(int state1[3][3], int state2[3][3]){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if (state1[i][j] != state2[i][j]){
                return 1;
            }
        }
    }

    return 0;
}

int filter(struct node* head, struct node** node_ptr) {
    if(node_ptr == NULL || *node_ptr == NULL) return 0;
    if(head == NULL) return 0;

    struct node* node = *node_ptr;
    struct node *curr = head;
    while(curr != NULL){
        if(checkstate(curr->state, node->state) == 0){
            free(node);
            *node_ptr = NULL;
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}

int heuristic(int state[3][3]){
    int dist = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            int val = state[i][j];
            if(val != 0){
                int x = (val - 1) / N;
                int y = (val - 1) % N;
                dist += abs(x - i) + abs(y - j);
            }
        }
    }
    return dist;
}

void update_fgh(struct node *curr){
    if(curr == NULL) return;
    
    curr->g++;
    curr->h = heuristic(curr->state);
    curr->f = curr->g + curr->h;
}

void add_to_open(struct node *add){
    if (openHead == NULL) {
        openHead = add;
        return;
    }

    struct node *curr = openHead;
    struct node *prev = NULL;

    while (curr != NULL && curr->f < add->f) {
        prev = curr;
        curr = curr->next;
    }

    add->next = curr;
    add->prev = prev;

    if (prev == NULL) {
        openHead = add;
    } else {
        prev->next = add;
    }

    if (curr != NULL) {
        curr->prev = add;
    }
}

int main(int argc, char *argv[]){
    initialize(argc, argv);
    int found = 0;

    while (openHead != NULL){
        struct node *cnode = openHead;
        openHead = openHead->next;

        if(checkstate(cnode->state, goal->state) == 0){
            found = 1;
            printf("Solution was found with cost - %d\n", cnode->f);
            return 0;
        }

        expand(cnode);

        for(int i = 0; i < 4; i++){
            if (succ[i] == NULL) continue;
            if (filter(openHead, &succ[i])) continue;
            if (filter(closeHead, &succ[i])) continue;

            if (succ[i] == NULL) continue;

            update_fgh(succ[i]);
            add_to_open(succ[i]);
        }

        cnode->next = closeHead;
        closeHead = cnode;
    }

    if (!found){
        printf("No solution was found\n");
        return 1;
    }
}