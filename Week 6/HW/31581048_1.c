#include <stdio.h>
#include <stdlib.h>

void radixSort(float arr[], int n);
void printArray(float arr[], int n);
void reverseArray(float arr[], int n);

int main() {
    int n;
    float arr[100];

    scanf("%d", &n);

    if (n > 100) {
        printf("Number of elements exceeds the maximum limit of 100.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        scanf("%f", &arr[i]);
    }

    radixSort(arr, n);
    printArray(arr, n);

    return 0;
}

void radixSort(float arr[], int n) {
    float positive[100], negative[100];
    int posCount = 0, negCount = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] >= 0) {
            positive[posCount++] = arr[i];
        } else {
            negative[negCount++] = -arr[i];
        }
    }

    for (int bit = 0; bit < 32; bit++) {
        float posBuckets[2][100];
        int posCountBuckets[2] = {0};

        for (int i = 0; i < posCount; i++) {
            unsigned int *p = (unsigned int *) &positive[i];
            int bucketIndex = (*p >> bit) & 1;
            posBuckets[bucketIndex][posCountBuckets[bucketIndex]++] = positive[i];
        }

        int posIndex = 0;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < posCountBuckets[i]; j++) {
                positive[posIndex++] = posBuckets[i][j];
            }
        }

        float negBuckets[2][100];
        int negCountBuckets[2] = {0};

        for (int i = 0; i < negCount; i++) {
            unsigned int *p = (unsigned int *) &negative[i];
            int bucketIndex = (*p >> bit) & 1;
            negBuckets[bucketIndex][negCountBuckets[bucketIndex]++] = negative[i];
        }

        int negIndex = 0;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < negCountBuckets[i]; j++) {
                negative[negIndex++] = negBuckets[i][j];
            }
        }
    }

    reverseArray(negative, negCount);
    for (int i = 0; i < negCount; i++) {
        negative[i] = -negative[i];
    }

    int index = 0;
    for (int i = 0; i < negCount; i++) {
        arr[index++] = negative[i];
    }
    for (int i = 0; i < posCount; i++) {
        arr[index++] = positive[i];
    }
}

void reverseArray(float arr[], int n) {
    for (int i = 0; i < n / 2; i++) {
        float temp = arr[i];
        arr[i] = arr[n - i - 1];
        arr[n - i - 1] = temp;
    }
}

void printArray(float arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%f\n", arr[i]);
    }
}