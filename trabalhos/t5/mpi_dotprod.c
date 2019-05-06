#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "mpi.h"

/*
 * Tempo (wallclock) em microssegundos
 */
long wtime(){
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec * 1000000 + t.tv_usec;
}

/*
 * Preenche vetores
 */
void fill(double *a, double *b, int size){
    for (int i = 0; i < size; i++){
        a[i] = 0.01;
        b[i] = 1.0;
    }
}

/*
 * Calcula o produto escalar
 */
double dot_product(double *a, double *b, int n, int repeat){
    double mysum;
    for (int k = 0; k < repeat; k++){
        mysum = 0.0;
        for (int i = 0; i < n; i++){
            mysum += a[i] * b[i];
        }
    }
    return mysum;
}

int main(int argc, char **argv){
    if ((argc != 3)){
        printf("Use: mpiexec -np <ntasks> %s <worksize> <repetitions>\n", argv[0]);
        exit(EXIT_FAILURE);
        MPI_Finalize();
    }
    int wsize, ntasks, repeat, rank, source;
    long start_time, end_time;
    double dotP, aux_dotP;

    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);

    wsize = atoi(argv[1]);
    repeat = atoi(argv[2]);

    double *a = (double *)malloc(sizeof(double) * wsize);
    double *b = (double *)malloc(sizeof(double) * wsize);

    fill(a, b, wsize);

    start_time = wtime();
    dotP = dot_product(a, b, wsize, repeat);
    end_time = wtime();

    if (rank != 0){
        MPI_Send(&dotP, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
    else{
        for (source = 1; source < ntasks; source++){
            MPI_Recv(&aux_dotP, 1, MPI_DOUBLE, source, 0, MPI_COMM_WORLD, &status);
            dotP += aux_dotP;
        }
        printf("Time: %ld\nResult: %f\n", (long)(end_time - start_time), dotP);
    }

    free((void *)a);
    free((void *)b);

    MPI_Finalize();
    return EXIT_SUCCESS;
}