[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2019a) > T4

# Geração de Fractais de Mandelbrot em OpenMP

Nome: Adonai Gabriel Loreto Peres Gonçalves

Disciplina: ELC139 - Programação Paralela

## Desenvolvimento

Foram desenvolvidas duas soluções de paralelismo, onde na primeira o *for* das linhas foi paralelizado, e na segunda o *for* das colunas foi paralelizado:
- [fractalpar1.cpp](fractalpar1.cpp)
- [fractalpar2.cpp](fractalpar2.cpp)

## Resultado

Abaixo a tabela com o resultado dos testes realizados em ambas as soluções:
- [Results.md](Results.md)

## Slides

Abaixo os slides construídos para uma eventual apresentação:
- [T4 - ELC139.pdf](T4 - ELC139.pdf)

## Observações

Infelizmente não consegui utilizar o cluster para executar os códigos paralelizados, acabei deixando para muito tarde e, portanto, não enviei email para a senhora. Pelo que entendi, a pasta do meu usuário não pôde ser criada. Abaixo estão os erros que obtive:

- [Erro1](Erro1.png)
- [Erro2](Erro2.png)

## Referências

- Tutorial OpenMP: https://computing.llnl.gov/tutorials/openMP/
- OpenMP: For & Scheduling: http://jakascorner.com/blog/2016/06/omp-for-scheduling.html