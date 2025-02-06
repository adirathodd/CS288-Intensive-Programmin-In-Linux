#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int nthreads, scalar, length;
double long *array;

void *worker(void  *arg){
    int id = *(int *)arg, chunk = length / nthreads;
    int start = id * chunk, end = (id + 1) * chunk;

    if(nthreads - 1 == id) end = length;

    for(int i = start; i < end; i++){
        array[i] *= scalar;
    }

    return NULL;
}

int main(int argc, char *argv[]){
    if(argc != 4){
        printf("Usage - %s <no. of threads> <scalar> <no. of elements>\n", argv[0]);
        return -1;
    }

    nthreads = strtol(argv[1], NULL, 10);
    scalar = strtol(argv[2], NULL, 10);
    length = strtol(argv[3], NULL, 10);

    pthread_t *threads = malloc(sizeof(pthread_t) * nthreads);
    int thread_ids[nthreads];

    array = (double long *)malloc(sizeof(double long *) * length);

    for(int i = 0; i < length; i++){
        array[i] = (double long)i;
    }

    for(int i = 0; i < nthreads; i++){
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, worker, &thread_ids[i]);
    }

    for(int i = 0; i < nthreads; i++) pthread_join(threads[i], NULL);

    free(threads);
    free(array);
}