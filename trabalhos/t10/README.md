[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2019a) > T10

# Resolvendo um problema anterior com OpenAcc

Nomes: Adonai Gabriel Loreto Peres Gonçalves e Gabriel Doyle Balk

Disciplina: ELC139 - Programação Paralela

## Ambiente de Desenvolvimento

- Dispositivo Testa T4 (0) da plataforma Google Colaboratory.

## Introdução

Utilizamos o compilador da PGI (PGI Accelerator) para compilar nossos exemplos com diretivas em OpenAcc. Essas diretivas são similares às diretivas em OpenMP que vimos anteriormente. Com essas diretivas podemos facilmente executar códigos em GPU, porém com o custo de um menor desempenho em relação à CUDA.
Como usamos o Google Colaboratory para a execução dos testes, as intruções de instalação abaixo são voltadas à essa plataforma.

- Baixar o compilador:
```
!wget http://www-usr.inf.ufsm.br/~agoncalves/pgilinux-2019-194-x86-64.tar.gz
```
- Descompactar:
```
!tar -xzvf pgilinux-2019-194-x86-64.tar.gz
```
- Instalar:
```
!./install
```
- Compilar:
```
!pgi/linux86-64/19.4/bin/pgc++ programa.c -o programa -ta=nvidia -Minfo=accel
```
-Executar(com tempo de execução):
```
!time ./programa <args>
```

## Preparação

O algoritmo de aquecimento desenvolvido e analisado foi [arraysum.c](arraysum.c), onde se calcula a soma de dois vetores repetidas vezes. Os tempos de execução foram obtidos através da média de 10 execuções para cada configuração, onde foram feitas execuções com tamanho de array de 1000000 e 10000000 e de 1000 e 2000 repetições.
Abaixo a tabela com os resultados obtidos:
- [resultsAS.csv](resultsAS.csv)

## Desenvolvimento

O algoritmo já desenvolvido e analisado foi [fractal.cpp](fractal.cpp), que foi o tema do [t4](../t4), onde gera uma sequência de imagens representando um "zoom" em um [fractal de Mandelbrot](https://en.wikipedia.org/wiki/Mandelbrot_set). A nossa versão desse algoritmo em OpenAcc é [fractalAcc.cpp](fractalAcc.cpp). Os tempos de execução foram obtidos através da média de 10 execuções para cada configuração, onde foram feitas execuções com tamanho de imagem de 512 e 1024 e variação de 32 e 64 frames.
Abaixo a tabela com os resultados obtidos:
- [resultsFR.csv](resultsFR.csv)

## Referências

- [PGI Accelerator](https://www.pgroup.com/resources/accel.htm?utm_source=openacc&utm_medium=website&utm_campaign=ce&ncid=pa-par-pgctdn-40231)
- [OpenACC Directives](http://ccfit.nsu.ru/arom/data/CUDA_2015/11_1%20openacc.pdf)
- [OpenACC Programming and Best Practices Guide](https://www.openacc.org/sites/default/files/inline-files/OpenACC_Programming_Guide_0.pdf)