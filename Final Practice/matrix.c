#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t *threads;
int length, nthreads;
long long **a, **b, **c;

void *worker(void *arg){
    long id = *(long *)arg;
    long start, end, chunk = length/nthreads;
    start = id * chunk, end = (id+1) * chunk;

    if (id + 1 == nthreads) end = length;

    for (int i= start; i < end ;i++)
        for(int j = 0; j < length; j++)
            for(int k = 0; k < length; k++)
                c[i][j] += a[i][k] * b[k][j];
    
    return NULL;
}

int main(int argc, char *argv[]){
    if (argc != 3){
        printf("Usage - %s <no. of threads> <matrix length>\n", argv[0]);
        return -1;
    }

    nthreads = strtol(argv[1], NULL, 10);
    length = strtol(argv[2], NULL, 10);

    a = (long long **)malloc(sizeof(long long *) * length);
    b = (long long **)malloc(sizeof(long long *) * length);
    c = (long long **)malloc(sizeof(long long *) * length);

    for(int i = 0; i < length; i++){
        a[i] = (long long *)malloc(sizeof(long long) * length);
        b[i] = (long long *)malloc(sizeof(long long) * length);
        c[i] = (long long *)malloc(sizeof(long long) * length);
    }

    for(int i = 0; i < length; i++){
        for(int j = 0; j < length; j++) {  a[i][j]= (long long)(i+j);  b[i][j]= (long long)(i*j); }
    }

    threads = malloc(sizeof(pthread_t) * nthreads);
    long thread_ids[nthreads];

    for(int i = 0; i < nthreads; i++){
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, worker, &thread_ids[i]);
    }

    for(int i = 0; i < nthreads; i++) pthread_join(threads[i], NULL);

    for(int i = 0; i < length; i++){
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }

    free(a);
    free(b);
    free(c);
    free(threads);
    return 0;
}