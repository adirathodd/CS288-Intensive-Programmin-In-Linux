#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long *array, threadN, scalar, length;

void *scalar_mult(void *threadID) {
    long id = *(long *)threadID;
    long chunk = length / threadN;
    long start = id * chunk;
    long end = (id == threadN - 1) ? length : start + chunk; // Handle leftover elements

    for (long i = start; i < end; i++) {
        array[i] *= scalar;
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <thread_count> <scalar> <array_length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    threadN = atol(argv[1]);
    scalar = atol(argv[2]);
    length = atol(argv[3]);


    array = (long *)malloc(length * sizeof(long));

    for (long i = 0; i < length; i++) {
        array[i] = i;
    }

    pthread_t threads[threadN];
    long thread_ids[threadN];

    for (long i = 0; i < threadN; i++) {
        thread_ids[i] = i;
        int rc = pthread_create(&threads[i], NULL, scalar_mult, &thread_ids[i]);
    }

    for (long i = 0; i < threadN; i++) {
        pthread_join(threads[i], NULL);
    }

    free(array);
    return EXIT_SUCCESS;
}