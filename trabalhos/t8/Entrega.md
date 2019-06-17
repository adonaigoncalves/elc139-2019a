[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2019a) > T8

# Geração de Imagem em Paralelo com CUDA

Nome: Adonai Gabriel Loreto Peres Gonçalves

Disciplina: ELC139 - Programação Paralela

## Ambiente de Desenvolvimento

- Dispositivo Testa T4 (0) da plataforma Google Colaboratory.

## Parte 1

O algoritmo desenvolvido e analisado foi [wavecuda1.cu](wavecuda1.cu), onde cada thread calcula um frame. Os tempos de execução foram obtidos através da média de 10 execuções para cada configuração, onde foram feitas execuções com tamanho de imagem de 1024 e 2048 e variação de 100 e 200 frames.
Abaixo a tabela com os resultados obtidos:
- [resultsP1.csv](resultsP1.csv)

## Parte 2

O algoritmo desenvolvido e analisado foi [wavecuda2.cu](wavecuda2.cu), onde cada thread calcula um pixel. Os tempos de execução foram obtidos através da média de 10 execuções para cada configuração, onde foram feitas execuções com tamanho de imagem de 1024 e 2048 e variação de 100 e 200 frames.
Abaixo a tabela com os resultados obtidos:
- [resultsP2.csv](resultsP2.csv)

## Referências

- [CUDA C Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/)
- [Experiência com grids, blocks e threads em CUDA](https://colab.research.google.com/drive/1uSTM6C0p4n4aAuvFksplqFxa4NG87rMp)
- [An Even Easier Introduction to CUDA](https://devblogs.nvidia.com/even-easier-introduction-cuda/)