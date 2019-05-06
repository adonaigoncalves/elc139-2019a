[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2019a) > T5

# Primeiros passos com MPI

Nome: Adonai Gabriel Loreto Peres Gonçalves

Disciplina: ELC139 - Programação Paralela

## Parte 1

A solução implementada foi baseada na solução do trabalho 2 em pthreads, onde deve-se informar manualmente o pedaço que cada processo fica responsável por calcular:
- [mpi_dotprod.c](mpi_dotprod.c)

Os resultados da avaliação de desempenho, considerando uma média de 5 execuções para cada tipo, foram:
- [results.csv](results.csv)

Especificações do meu computador:
- [specs.txt](specs.txt)

## Parte 2

Na implementação dessa solução foi definido que a mensagem inicial seria 0 e então ela seria incrementada antes de cada processo recebê-la:
- [mpi_pipeline.c](mpi_pipeline.c)

## Parte 3

O problema do programa [mpi_errado1.c](mpi_errado1.c) é o valor passado para a variável tag no MPI_Send e no MPI_Recv, pois o valor da tag é diferente em ambos processos e é necessário que ela seja igual. Abaixo o programa corrigido:
- [mpi_corrigido1.c](mpi_corrigido1.c)

Já o problema do programa [mpi_errado2.c](mpi_errado2.c) é que está faltando a chamada da função MPI_Finalize() antes de sair do programa, impedindo assim o funcionamento do mesmo. Abaixo o programa corrigido:
- [mpi_corrigido2.c](mpi_corrigido2.c)

## Observações

Não tenho certeza se calculei o tempo de execução de maneira correta na Parte 1, pois só considerei a parte do cálculo do produto escalar.

## Referências

- Tutorial MPI: https://computing.llnl.gov/tutorials/mpi/
- MPI Send and Receive: http://mpitutorial.com/tutorials/mpi-send-and-receive/
- Open MPI Documentation: https://www.open-mpi.org/doc/