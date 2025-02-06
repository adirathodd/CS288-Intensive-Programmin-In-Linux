#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX 1000

int counts[MAX] = {0}, nthreads, length, *array;
pthread_t *threads;
pthread_mutex_t mutex;

void *worker(void *arg){
    int id = *(int *)arg, chunk = nthreads/length, start = (id*chunk), end = (id+1)*chunk;
    if (id == nthreads - 1) end = length;
    int localCounts[MAX] = {0};
    for(int i = start; i < end; i++){
        localCounts[array[i]]++;
    }

    pthread_mutex_lock(&mutex);
    for(int i = 0; i < MAX; i++) counts[i] += localCounts[i];
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int argc, char *argv[]){
    if (argc != 2){
        printf("Usage - %s <no. of threads>\n", argv[0]);
        return -1;
    }
    char filename[256];
    printf("Enter filepath - ");
    scanf("%s", filename);

    nthreads = strtol(argv[1], NULL, 10);
    threads = malloc(sizeof(pthread_t) * nthreads);
    int thread_ids[nthreads];
    
    FILE *file;
    file = fopen(filename, "rb");
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    rewind(file);
    length = size >> 2;
    array = (int *)malloc(sizeof(int) * length);
    fread(array, sizeof(int), length, file);
    fclose(file);

    for(int i = 0; i < nthreads; i++){
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, worker, &thread_ids[i]);
    }

    for(int i = 0; i < nthreads; i++) pthread_join(threads[i], NULL);

    int index = 0;
    for(int i = 0; i < MAX; i++)
        for(int j = 0; j < counts[i]; j++)
            array[index++] = i;
    
    file = fopen(filename, "wb");
    fwrite(array, sizeof(int), length, file);
    fclose(file);

    free(array);
    free(threads);
    pthread_mutex_destroy(&mutex);

}