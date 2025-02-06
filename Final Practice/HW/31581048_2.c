#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

pthread_t *threads;
long double PI = 3.14159265358979323846264338327950288419716939937510;
long double pi, sum;

pthread_mutex_t mutex;
int nthreads, terms;

void *worker(void *arg){
	int id = *(int *)arg;
	long double partial_sum = 0.0, x;
	for(double i=terms/nthreads*id+1; i<= terms/nthreads*(id+1); i++) {
		x = (i - 0.5)/(long double)terms;
		partial_sum+= 4.0 / (1.0 + x*x);
	}
	
	pthread_mutex_lock(&mutex);
	sum+=partial_sum;
	pthread_mutex_unlock(&mutex);
	
	return NULL;
}

int main(int argc, char *argv[]){
	if (argc != 3) {
		printf("Usage - %s <no. of threads> <no. of terms>\n", argv[0]);
		return -1;
	}
	
	nthreads = strtol(argv[1], NULL, 10);
	terms = strtol(argv[2], NULL, 10);
	
	threads = malloc(sizeof(pthread_t) * nthreads);
	int thread_ids[nthreads];
	pthread_mutex_init(&mutex, NULL);
	
	for(int i = 0; i < nthreads; i++){
		thread_ids[i] = i;
		pthread_create(&threads[i], NULL, worker, &thread_ids[i]);
	}
	
	for(int i = 0; i < nthreads; i++){
		pthread_join(threads[i], NULL);
	}
	
	pi = sum / terms;
	long double error = pi - PI;
	printf("PI - %.30Lf\n", pi);
	printf("Real PI - %.30Lf\n", PI);
	printf("Error - %.30Lf\n", fabsl(error));

	free(threads);
	pthread_mutex_destroy(&mutex);
}