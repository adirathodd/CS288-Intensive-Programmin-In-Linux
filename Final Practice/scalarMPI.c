#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 100


int main(int argc, char *argv[]){
    int rank, numprocs, localsize, *array, *localarray;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        array = (int *)malloc(N * sizeof(int));
        for(int i = 0; i < N; i++) array[i] = i;
    }

    localsize = N / numprocs;
    localarray = (int *)malloc(sizeof(int) * localsize);

    MPI_Scatter(array, localsize, MPI_INT, localarray, localsize, MPI_INT, 0, MPI_COMM_WORLD);

    for(int i = 0; i < localsize; i++) localarray[i] *= 2;

    MPI_Gather(localarray, localsize, MPI_INT, array, localsize, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0){
        for(int i = 0; i < N; i++) printf("%d ", array[i]);
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}