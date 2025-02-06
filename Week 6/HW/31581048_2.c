#include <stdio.h>
#include <stdlib.h>

void radixSort(int arr[], int n);
void printArray(int arr[], int n);
void reverseArray(int arr[], int n);

int main() {
    int n;
    int arr[100];

    scanf("%d", &n);

    if (n > 100) {
        printf("Number of elements exceeds the maximum limit of 100.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    radixSort(arr, n);
    printArray(arr, n);

    return 0;
}

void radixSort(int arr[], int n) {
    int positive[100], negative[100];
    int posCount = 0, negCount = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] >= 0) {
            positive[posCount++] = arr[i];
        } else {
            negative[negCount++] = -arr[i];
        }
    }

    for (int bit = 0; bit < 8; bit++) {
        int posBuckets[16][100];
        int posCountBuckets[16] = {0};
        unsigned int mask = 0xF << (4 * bit);

        for (int i = 0; i < posCount; i++) {
            int bucketIndex = (positive[i] & mask) >> (4 * bit);
            posBuckets[bucketIndex][posCountBuckets[bucketIndex]++] = positive[i];
        }

        int posIndex = 0;
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < posCountBuckets[i]; j++) {
                positive[posIndex++] = posBuckets[i][j];
            }
        }

        int negBuckets[16][100];
        int negCountBuckets[16] = {0};

        for (int i = 0; i < negCount; i++) {
            int bucketIndex = (negative[i] & mask) >> (4 * bit);
            negBuckets[bucketIndex][negCountBuckets[bucketIndex]++] = negative[i];
        }

        int negIndex = 0;
        for (int i = 0; i < 16; i++) {
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

void reverseArray(int arr[], int n) {
    for (int i = 0; i < n / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[n - i - 1];
        arr[n - i - 1] = temp;
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d\n", arr[i]);
    }
}