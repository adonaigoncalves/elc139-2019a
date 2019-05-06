#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char *argv[]){
    if ((argc != 1)){
        printf("Use: mpiexec -np <ntasks> %s\n", argv[0]);
        exit(EXIT_FAILURE);
        MPI_Finalize();
    }
    int rank, ntasks, source, dest, msg, tag = 0;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);

    if (rank == 0){
        msg = 0;
        dest = 1;
        printf("(Task %d) Sending message '%d' to task %d!\n", rank, msg, dest);
        MPI_Send(&msg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
    }
    else if (rank == (ntasks - 1)){
        source = rank - 1;
        MPI_Recv(&msg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
        printf("(Task %d) Message reveived: '%d'\n", rank, msg);
    }
    else{
        source = rank - 1;
        MPI_Recv(&msg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
        dest = rank + 1;
        printf("(Task %d) Message received: '%d' - Sending message '%d' to task %d!\n", rank, msg, msg + 1, dest);
        msg++;
        MPI_Send(&msg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}