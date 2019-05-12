[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2019a) > T6

# Comunicação coletiva em MPI

Nome: Adonai Gabriel Loreto Peres Gonçalves

Disciplina: ELC139 - Programação Paralela

## Parte 1

A solução utilizada para este trabalho envolve a substituição da seção onde havia "MPI_Send" e "MPI_Recv" por "MPI_Bcast" e "MPI_Scatter", onde o primeiro faz o envio da matriz B para todos os processos e o segundo faz o envio de cada linha, ou conjunto de linhas, da matriz A para cada processo conforme o número de processos, ou seja, o número total de elementos dividido pelo número de processos. E por fim, o "MPI_Gather" pega os elementos de cada processo e os reúne no processo root.
```
MPI_Bcast(void* data, int count, MPI_Datatype datatype, int root, MPI_Comm communicator);
```
```
MPI_Scatter(void* send_data, int send_count, MPI_Datatype send_datatype, void* recv_data, int recv_count, MPI_Datatype recv_datatype, int root, MPI_Comm communicator);
```
```
MPI_Gather(void* send_data, int send_count, MPI_Datatype send_datatype, void* recv_data, int recv_count, MPI_Datatype recv_datatype, int root, MPI_Comm communicator);
```
Abaixo o programa original e a solução implementada, respectivamente:
- [matrix_mult_sr.c](matrix_mult_sr.c)
- [matrix_mult_broadcast.c](matrix_mult_broadcast.c)

## Parte 2

Abaixo o link para o resumo crítico do artigo "[Send-receive considered harmful: Myths and realities of message passing](https://dl.acm.org/citation.cfm?id=963780)":
- []()

## Referências

- [Tutorial MPI](https://computing.llnl.gov/tutorials/mpi/)
- [MPI Send and Receive](http://mpitutorial.com/tutorials/mpi-send-and-receive/)
- [Open MPI Documentation](https://www.open-mpi.org/doc/)
- [Exemplos de comunicação](exemplos/)