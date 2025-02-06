#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
    int n;
   
    // Open matrix1.bin and matrix2.bin for reading
    FILE *f1;
    f1 = fopen("result.bin", "rb");
    if(f1 == NULL){
        printf("FILE 1 DIDNT OPEN");
        exit(1);
    }

    // Read the dimension of the matrices
    fread(&n, sizeof(int), 1, f1);

    long long ***matrix = (long long ***)malloc(n * sizeof(long long **));

    for (int i = 0; i < n; i++) {
        matrix[i] = (long long **)malloc(n * sizeof(long long *));
        for (int j = 0; j < n; j++) {
            matrix[i][j] = (long long *)malloc(n * sizeof(long long));
        }
    }
    int count = 0;
    // Read the elements of the matrices
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                fread(&matrix[i][j][k], sizeof(long long), 1, f1);
                printf("element %d: %lld\n", count, matrix[i][j][k]);
            }
        }
    }

    // Close the input files
    fclose(f1);
}