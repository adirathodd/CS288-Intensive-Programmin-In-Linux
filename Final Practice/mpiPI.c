#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char *argv[]){
    int rank, numprocs, numworkers;
    double long sum = 0.0, partial_sum = 0.0, x;
    long double PI = 3.14159265358979323846264338327950288419716939937510;
    unsigned long terms, termsPerProc;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    if(rank == 0){
        printf("Enter the number of term: \n");
        scanf("%lu", &terms);

        termsPerProc = terms / numprocs;
    }

    MPI_Bcast(&termsPerProc, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);
    MPI_Bcast(&terms, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);

    for(int i = rank * termsPerProc + 1; i < (rank + 1) * termsPerProc + 1; i++){
        x = ((double long)i - 0.5)/terms;
        partial_sum += 4.0 / (1.0 + x*x);
    }

    MPI_Reduce(&partial_sum, &sum, 1, MPI_LONG_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0){
        printf("Approx PI - %.30Lf\n", sum/terms);
        printf("Actual PI - %.30Lf\n", PI);
    }

    MPI_Finalize();
    return 0;
}