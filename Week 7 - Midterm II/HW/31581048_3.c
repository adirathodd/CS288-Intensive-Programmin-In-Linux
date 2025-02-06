#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void bubbleSort(char *array[], const int size) {
    int pass, j;
    for (pass = 0; pass < size - 1; pass++)
        for (j = 0; j < size - 1; j++){
            char *copy1 = strdup(array[j]);
            char *copy2 = strdup(array[j + 1]);

            char *elem1 = strtok(copy1, "=");
            char *elem2 = strtok(copy2, "=");

            int cmp = strcmp(elem1, elem2);
            if (cmp > 0){
                char *hold = array[j];
                array[j] = array[j + 1];
                array[j + 1] = hold;
            }
            free(copy1);
            free(copy2);
        }
}

int main(int argc, char *argv[], char *envp[]){
    int index = 0;

    while(envp[index]){
        index++;
    }

    bubbleSort(envp, index);

    index = 0;

    while(envp[index]){
        printf("%s\n", envp[index++]);
    }
}