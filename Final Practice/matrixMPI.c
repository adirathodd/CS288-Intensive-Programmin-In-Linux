#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 100

int main (int argc, char *argv[]) {
    int	numtasks, taskid,rows, i, j, k;
    double a[N][N], b[N][N], c[N][N], aprime[N][N], cprime[N][N];
    MPI_Status status;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

    if (taskid == 0)   {
        printf("run with %d tasks.\n",numtasks);
        for (i=0; i<N; i++)
            for (j=0; j<N; j++) { a[i][j]= i+j; b[i][j]= i*j; }
    }

    rows = N / numtasks;
    MPI_Bcast(b, N*N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(a, rows * N, MPI_DOUBLE, aprime, rows*N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for(i = 0; i < rows; i++)
        for(k = 0; k < N; k++)
            for(j = 0; j < N; j++)
                cprime[i][k] = cprime[i][k] + aprime[i][j] * b[j][k];
    
    MPI_Gather(cprime, rows*N, MPI_DOUBLE, c, rows*N, MPI_DOUBE, 0, MPI_COMM_WORLD);

    if(rank == 0){
        printf("Matrix Multiplication completed!\n");
    }

    MPI_Finalize();
    return 0;
}