#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

#define MAX 1000

int main(int argc, char *argv[]){
	int numprocs, myid, filesize, length, *array, *localarray, numPerProc;
	FILE *file;
	char filename[100];
	int counts[MAX] = {0};
	int local_counts[MAX] = {0};
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	
	if(myid == 0){

		scanf("%s", filename);
		
		file = fopen(filename, "rb");
		
		if(!file){
			printf("Error reading in the file.\n");
			MPI_Abort(MPI_COMM_WORLD, 1);
		}
		
		fseek(file, 0, SEEK_END);
		filesize = ftell(file);
		rewind(file);
		length = filesize >> 2;
		array = (int *)malloc(sizeof(int) * length);
		fread(array, sizeof(int), length, file);
		fclose(file);
	}
	
	MPI_Bcast(&length, 1, MPI_INT, 0, MPI_COMM_WORLD);
	numPerProc = length / numprocs;
	localarray = (int *)malloc(numPerProc * sizeof(int));
	
	MPI_Scatter(array, numPerProc, MPI_INT, localarray, numPerProc, MPI_INT, 0, MPI_COMM_WORLD);

	for (int i = 0; i < numPerProc; i++) {
        	local_counts[localarray[i]]++;
    	}
	
	MPI_Reduce(local_counts, counts, MAX, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	if (myid == 0) {
		int index = 0;
		for (int i = 0; i < MAX; i++) {
		    for (int j = 0; j < counts[i]; j++) {
		        array[index++] = i;
		    }
		}

		file = fopen(filename, "wb");
		if (!file) {
		    printf("Error opening the file for writing.\n");
		    MPI_Abort(MPI_COMM_WORLD, -1);
		}

		fwrite(array, sizeof(int), length, file);
		fclose(file);
		printf("File successfully sorted.\n");

		free(array);
    	}
    	
    	free(localarray);
    	MPI_Finalize();
		return 0;
}
