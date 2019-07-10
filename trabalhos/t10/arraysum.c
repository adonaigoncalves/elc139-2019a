#include <stdio.h>
#include <stdlib.h>

//Preenche vetor
void fill(int *a, int size, int value) {
    int i;
    for (i = 0; i < size; i++) {
        a[i] = value;
    }
}

int main(int argc, char **argv) {
    int wsize, repeat, i, j;

    if ((argc != 3)) {
        printf("Uso: %s <worksize> <repetitions>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    wsize = atoi(argv[1]);  // worksize = tamanho do vetor de cada thread
    repeat = atoi(argv[2]); // numero de repeticoes dos calculos (para aumentar carga)

    // Cria vetores
    int *a = (int *)malloc(wsize * sizeof(int));
    fill(a, wsize, 42);
    int *b = (int *)malloc(wsize * sizeof(int));
    fill(b, wsize, 50);
    int *c = (int *)malloc(wsize * sizeof(int));
        
    if (a == NULL || b == NULL || c == NULL) {
        printf("Erro de alocacao de memoria\n");
        exit(EXIT_FAILURE);
    }
    
    //Calcula o produto escalar (repeat vezes)
    #pragma acc data copy(a[:wsize], b[:wsize])
    #pragma acc parallel loop
    for (j = 0; j < repeat; j++) {
        for (i = 0; i < wsize; i++) {
            c[i] = a[i] + b[i];
        }
    }
    
    for (i = 0; i < 100; i++) {
        printf("%d - ", c[i]);
    }
    
    free(a);
    free(b);
    free(c);

    return EXIT_SUCCESS;
}