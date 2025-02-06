#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

pthread_t *threads;
sem_t sem;
long sum = 0, length, nthreads;

void *worker(void *arg){
    int id = *(int *)arg;
    long localsum = 0, end = length/nthreads;

    for(int i = 0; i < end; i++){
        localsum++;
    }

    sem_wait(&sem);
    sum += localsum;
    sem_post(&sem);

    return NULL;
}

int main(int argc, char *argv[]){
    if(argc != 3){
        printf(
            "Usage - %s <no. of threads> <no. of iterations>\n", argv[0]);
    }

    nthreads = strtol(argv[1], NULL, 10);
    length = strtol(argv[2], NULL, 10);
    threads = malloc(nthreads * sizeof(pthread_t));
    int thread_ids[nthreads];

    for(int i = 0; i < nthreads; i++){
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, worker, &thread_ids[i]);
    }

    for(int i = 0; i < nthreads; i++){
        pthread_join(threads[i], NULL);
    }

    printf("Sum - %ld\n", sum);
    sem_close(&sem);
    free(threads);
    return 0;
}