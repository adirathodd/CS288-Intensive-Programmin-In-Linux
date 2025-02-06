#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
    int n;
   
    // Open matrix1.bin and matrix2.bin for reading
    FILE *f1, *f2, *res;
    f1 = fopen("matrix1.bin", "rb");
    f2 = fopen("matrix2.bin", "rb");
    if(f1 == NULL){
        printf("FILE 1 DIDNT OPEN");
        exit(1);
    }
    if(f2 == NULL){
        printf("FILE 2 DIDNT OPEN");
        exit(1);
    }

    // Read the dimension of the matrices
    fread(&n, sizeof(int), 1, f1);
    fread(&n, sizeof(int), 1, f2);

    long long ***matrix_1 = (long long ***)malloc(n * sizeof(long long **));
    long long ***matrix_2 = (long long ***)malloc(n * sizeof(long long **));
    long long ***result_matrix = (long long ***)malloc(n * sizeof(long long **));

    for (int i = 0; i < n; i++) {
        matrix_1[i] = (long long **)malloc(n * sizeof(long long *));
        matrix_2[i] = (long long **)malloc(n * sizeof(long long *));
        result_matrix[i] = (long long **)malloc(n * sizeof(long long *));
        for (int j = 0; j < n; j++) {
            matrix_1[i][j] = (long long *)malloc(n * sizeof(long long));
            matrix_2[i][j] = (long long *)malloc(n * sizeof(long long));
            result_matrix[i][j] = (long long *)malloc(n * sizeof(long long));
        }
    }

    // Read the elements of the matrices
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                fread(&matrix_1[i][j][k], sizeof(int), 1, f1);
                fread(&matrix_2[i][j][k], sizeof(int), 1, f2);
            }
        }
    }

    // Close the input files
    fclose(f1);
    fclose(f2);

    // Perform element-wise multiplication
    int count = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                result_matrix[i][j][k] = (matrix_1[i][j][k] * matrix_2[i][j][k]);
                printf("result element %d: %lld\n", count, result_matrix[i][j][k]);
                count++;
            }
        }
    }

    // Open result.bin for writing
    res = fopen("result.bin", "wb");
    if(res == NULL){
        printf("FILE 3 DIDNT OPEN");
        exit(1);
    }

    // Write the dimension of the result_matrix
    fwrite(&n, sizeof(int), 1, res);

    // Write the elements of the result_matrix
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                fwrite(&result_matrix[i][j][k], sizeof(long long), 1, res);
            }
            free(matrix_1[i][j]);
            free(matrix_2[i][j]);
            free(result_matrix[i][j]);
        }
        free(matrix_1[i]);
        free(matrix_2[i]);
        free(result_matrix[i]);
    }

    free(matrix_1);
    free(matrix_2);
    free(result_matrix);

    // Close the output file
    fclose(res);
    return 0;
}