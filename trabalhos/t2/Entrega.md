[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2019a) > T2

# Programação Paralela Multithread

Nome: Adonai Gabriel Lorto Peres Gonçalves

[Pthreads](#Pthreads)
[OpenMP](#openmp)

# Pthreads

1. Explique como se encontram implementadas as 4 etapas de projeto: particionamento, comunicação, aglomeração, mapeamento (use trechos de código para ilustrar a explicação).

#### Particionamento

Este programa implementa um paralelismo de dados, onde os dados são particionados e cada uma das threads realiza os mesmos cálculos sobre o seu segmento dos dados. Abaixo o trecho de código que deixa esse particionamento mais explícito:
```
long offset = (long) arg;
double *a = dotdata.a;
double *b = dotdata.b;
int wsize = dotdata.wsize;
int start = offset*wsize;
int end = start + wsize;
```
Onde ‘offset’ representa qual segmento que a thread vai trabalhar sobre, ‘wsize’ representa o número de posições do vetor de dados que o segmento contém, ‘start’ representa a primeira posição segmento e ‘end’ representa a última posição do segmento. E então, o cálculo é feito em:
```
for (k = 0; k < dotdata.repeat; k++) {
    mysum = 0.0;
    for (i = start; i < end ; i++)  {
        mysum += (a[i] * b[i]);
    }
}
```

#### Comunicação

A comunicação é feita na etapa onde ocorre dependência entre os cálculos do produto escalar, ou seja, durante as somas dos produtos parciais calculadas em cada thread. Abaixo o trecho de código trata esse problema:
```
pthread_mutex_lock (&mutexsum);
dotdata.c += mysum;
pthread_mutex_unlock (&mutexsum);
```

#### Aglomeração

A aglomeração é feita por um agrupamento das várias somas e multiplicações realizadas por cada thread, gerando as somas parciais mencionadas anteriormente. Abaixo o trecho de código que realiza esse agrupamento:
```
double mysum;
for (k = 0; k < dotdata.repeat; k++) {
    mysum = 0.0;
    for (i = start; i < end ; i++)  {
        mysum += (a[i] * b[i]);
    }
}
pthread_mutex_lock (&mutexsum);
dotdata.c += mysum;
pthread_mutex_unlock (&mutexsum);
```

#### Mapeamento

No mapeamento é realizada uma distribuição estática de tarefas aos processadores, cada um calcula o mesmo número de operações sobre a mesma quantidade de dados.
```
for (i = 0; i < nthreads; i++) {
   pthread_create(&threads[i], &attr, dotprod_worker, (void *) i);
}
```

2. Considerando o tempo (em microssegundos) mostrado na saída do programa, qual foi a aceleração (speedup) com o uso de threads?

Média de 5 execuções, considerando os menores tempos:

Speedup = 2723435 usec / 1608536 usec = 1.69

A aceleração foi de ~ 1.69.

3. A aceleração se sustenta para outros tamanhos de vetores, números de threads e repetições? Para responder a essa questão, você terá que realizar diversas execuções, variando o tamanho do problema (tamanho dos vetores e número de repetições) e o número de threads (1, 2, 4, 8..., dependendo do número de núcleos). Cada caso deve ser executado várias vezes, para depois calcular-se um tempo de processamento médio para cada caso. Atenção aos fatores que podem interferir na confiabilidade da medição: uso compartilhado do computador, tempos muito pequenos, etc.

| Tamanho  | Repetições | 1 Thread | 2 Threads | 4 Threads |
| -------- | ---------- | -------- | --------- | --------- |
| 1000000  | 1000       | 2723435  | 1782653   | 1608536   |
| 1000000  | 2000       | 5408812  | 3868067   | 3567237   |
| 1000000  | 3000       | 8181887  | 6342766   | 6135867   |
| 5000000  | 1000       | 13662816 | 11978328  | 10904851  |
| 5000000  | 2000       | 27410897 | 25057043  | 21463494  |
| 5000000  | 3000       | 41154303 | 37560038  | 33136946  |
| 10000000 | 1000       | 27356148 | 23436885  | 20620489  |
| 10000000 | 2000       | 54600561 | 46666305  | 42163011  |
| 10000000 | 3000       | 83784850 | 75609937  | 71391537  |

4. Elabore um gráfico/tabela de aceleração a partir dos dados obtidos no exercício anterior.

| Tamanho  | Repetições | 2 Threads(Speedup) | 4 Threads(Speedup) |
| -------- | ---------- | ------------------ | ------------------ |
| 1000000  | 1000       | 1.52               | 1.69               |
| 1000000  | 2000       | 1.39               | 1.51               |
| 1000000  | 3000       | 1.28               | 1.33               |
| 3000000  | 1000       | 1.14               | 1.25               |
| 3000000  | 2000       | 1.09               | 1.27               |
| 3000000  | 3000       | 1.09               | 1.24               |
| 10000000 | 1000       | 1.16               | 1.32               |
| 10000000 | 2000       | 1.17               | 1.29               |
| 10000000 | 3000       | 1.10               | 1.17               |

Com base nas tabelas acima, houve um pequeno ganho com o acréscimo de threads em relação ao sequencial, porém é notável que o ganho não foi consistente com o aumento de threads, possívelmente por alguma falha de configuração ou por eu estar utilizando cygwin no Windows.

5. Explique as diferenças entre [pthreads_dotprod.c](pthreads_dotprod/pthreads_dotprod.c) e [pthreads_dotprod2.c](pthreads_dotprod/pthreads_dotprod2.c). Com as linhas removidas, o programa está correto?

O `pthreads_dotprod2.c` não realiza exclusão mútua na função `dotprod_worker` durante o acesso a variável que receberá a soma total (`dotdata.c`). Isso pode acarretar em inconsistência no resultado, pois as duas threads podem querer incrementar a mesma variável ao mesmo tempo, porém algumas vezes o programa pode gerar saídas consistentes.