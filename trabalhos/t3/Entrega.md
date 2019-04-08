[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2019a) > T3

# Scheduling com OpenMP

Nome: Adonai Gabriel Lorto Peres Gonçalves

Disciplina: ELC139 - Programação Paralela

##  Casos de teste
Neste trabalho foram implementados 9 casos de teste utilizando OpenMP, cuja implementação pode ser encontrada em: [OpenMPDemoABC.cpp](OpenMPDemoABC.cpp). Para o tratamento da exclusão mútua, foi utilizada a cláusula critical do OpenMP, conforme o trechos de código abaixo:

``` 
void addChar(char c){
    #pragma omp critical
    {
        array[index] = c;
        spendSomeTime();
        index++;
    }
}
```
A seguir a descrição e as saídas para cada um dos casos de teste realizados.

### 1) Com scheduling STATIC e chunk
Nesse tipo de escalonamento, cada thread executa o número de vezes que foi especificado no chunk até o número de caractéres escolhido. Isso pode causar uma saída incorreta, caso o número de caractéres não seja divisível pelo chunk.

Saída do código:
```
Case 1: Static schedule with chunk                                                                                   ACCCCCCCCCCCCCCCCCCCCBBBBBBBBBBBBBBBBBBBBAAAAAAAAAAAAAAAAAAA                                                         A=20 B=20 C=20 
```

### 2) Com scheduling STATIC e sem chunk
Se não for fornecido um valor de chunk, cada thread executa o número de iterações (nThreads*nTimes) do laço dividido pelo número de threads, fazendo com que todas as threads possuam a mesma quantidade de iterações.

Saída do código:
```
Case 2: Static schedule without chunk                                                                                CAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBCCCCCCCCCCCCCCCCCCC                                                         A=20 B=20 C=20
```

### 3) Com scheduling DYNAMIC e chunk
Neste caso, cada thread executa o número de vezes que foi especificado no chunk, porém a distribuição das iterações do laço entre as threads não segue um padrão e será dado a primeira thread que solicitar uma nova iteração.

Saída do código:
```
Case 3: Dynamic schedule with chunk                                                                                  CAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBCCCC                                                         A=50 B=5 C=5
```

### 4) om scheduling DYNAMIC e sem chunk
Similar ao caso anterior (com chunk), porém com chunk valendo 1.

Saída do código:
```
Case 4: Dynamic schedule without chunk                                                                               BAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABC                                                         A=57 B=2 C=1 
```

### 5) Com scheduling GUIDED e chunk
Este caso é semelhante ao anterior (dynamic), porém com um tratamento diferente em relação ao chunk. Onde o chunk é proporcional ao número de iterações não atribídas divido pelo número de threads. Assim, o chunk vai diminuindo conforme a execução vai sendo realizada, chegando até o tamanho do chunk especificado ou menos. 

Saída do código:
```
Case 5: Guided schedule with chunk                                                                                   CAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBCCCCCCCCCCCCCCCCCCC                                                         A=31 B=9 C=20 
```

### 6) Com tratamento de exclusão mútua e com scheduling GUIDED
Similar ao caso anterior (com chunk), porém o tamanho de chunk final é 1.

Saída do código:
```
Case 6: Guided schedule without chunk                                                                                BAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCBBBBBBBBBBBBBBBBBBB                                                         A=31 B=20 C=9 
```

### 7) Com scheduling RUNTIME
Como o próprio nome já diz, esse caso deixa que o tipo de scheduling seja escolhido em tempo de execução. Esse possibilita que o scheduling seja trocado no meio da execução pelo próprio algoritmo.

Saída do código:
```
Case 7: Runtime schedule                                                                                             CAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACB                                                         A=57 B=1 C=2
```

### 8) Com scheduling AUTO
Neste caso, a tarefa de escolher a melhor forma de escalonar o problema é designada ao compilador.

Saída do código:
```
Case 8: Auto schedule                                                                                                BCCCCCCCCCCCCCCCCCCCCBBBBBBBBBBBBBBBBBBBAAAAAAAAAAAAAAAAAAAA                                                         A=20 B=20 C=20 
```

### 9) Sem tratamento de exclusão mútua e com scheduling AUTO
Para este caso, usei outra função sem exclusão mútua para apresentar saídas incorretas:

``` 
 void addCharNoCritical(char c){
    array[index] = c;
    spendSomeTime();
    index++;
}
```

Este caso mostra com clareza que, sem a exclusão mútua, o vetor não é totalmente preenchido e a saída é incorreta, pois a soma das quantidades de caractéres A, B e C não é igual a 60:

``` 
Case 9: Auto schedule without critical section                                                                       ABCABACBACBACBACBACABCABCABCABCABCABCABCABCABCABCABCACBACB--                                                         A=20 B=19 C=19
``` 

### Observações

Para todos os testes foi usado o seguinte número de threads, caractéres e chunk:
```
./OpenMPDemoABC 3 20 5
```
Fiquei em dúvida sobre o motivo pelo qual todas as saídas, com exceção do caso 9, começaram com um caractér e depois uma sequência de outro caractér. Imagino que seja porque estou usando um subsistema do Linux no Windows.

## Referências

- Tutorial OpenMP: https://computing.llnl.gov/tutorials/openMP/
- OpenMP: For & Scheduling: http://jakascorner.com/blog/2016/06/omp-for-scheduling.html