// Adaptado de www.mpitutorial.com
// Exemplo de implementação do MPI_Bcast usando MPI_Send e MPI_Recv

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <sys/time.h>

long wtime(){
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec * 1000000 + t.tv_usec;
}

int main(int argc, char** argv) {

    int myrank;    // "rank" do processo
    int p;         // numero de processos
    int root;      // rank do processo root
    long start_time, end_time;      // variáveis para cálculo de tempo de execução
    
    // MPI_Init deve ser invocado antes de qualquer outra chamada MPI
    MPI_Init(&argc, &argv);
    // Descobre o "rank" do processo
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    // Descobre o numero de processos
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    int data = 100;     // dado a ser enviado
    root = 0;     // define o rank do root

    if (myrank == root) {
        start_time = wtime();
        printf("Processo %d (root) realizando broadcast do dado %d\n", root, data);
    }

    MPI_Bcast(&data, 1, MPI_INT, root, MPI_COMM_WORLD);

    printf("Processo %d recebendo dado %d do processo root\n", myrank, data);

    MPI_Barrier(MPI_COMM_WORLD);
    if (myrank == root) {
        end_time = wtime();
        printf("Tempo de execução: %ld\n", (long)(end_time - start_time));
    }

    MPI_Finalize();
    return 0;
}