#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_t *threads;
pthread_mutex_t mutex;
unsigned long sum = 0;

void *worker(void *arg){
    unsigned long localSum = 0;
    unsigned long iters = *(unsigned long *)arg;

    for(double long i = 0; i < iters; i++) localSum++;

    pthread_mutex_lock(&mutex);
    sum += localSum;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int argc, char *argv[]){
    if (argc != 3){
        printf("Usage - %s <no. of threads> <no. of iterations>\n", argv[0]);
        return -1;
    }

    int nthreads = strtol(argv[1], NULL, 10);
    unsigned long iterations = strtol(argv[2], NULL, 10);
    unsigned long iterPerThread = iterations/nthreads;
    threads = malloc(nthreads * sizeof(pthread_t));
    
    for(int i = 0; i < nthreads; i++) pthread_create(&threads[i], NULL, worker, &iterPerThread);
    for(int i = 0; i < nthreads; i++) pthread_join(threads[i], NULL);

    printf("Sum - %lu\n", sum);
}