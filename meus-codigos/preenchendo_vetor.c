#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 11

int vetor[SIZE];

// Preenche um vetor com 2 numeros
/* 
    a primeira thread preenche do inicio até a metade
    a segunda thread preence da metade até o fim
*/
void *funcao(void *arg){
    int *valor = (int *)arg;
    int i;
    
    if (*valor == 1){
        printf("Executando Thread %i ...\n", *valor);
        for(i = 0; i < SIZE / 2; i++){
            vetor[i] = 10;
        }
    }
    else{
        printf("Executando Thread %i ...\n", *valor);
        for(i = SIZE / 2; i < SIZE; i++){
            vetor[i] = 20;
        }
    }
}

int main(){
    pthread_t threads[2];
    int i, arg[2] = {1, 2};

    for(i = 0; i < 2; i++){
        pthread_create(&threads[i], NULL, funcao, (void *)&arg[i]);
    }

    for(i = 0; i < 2; i++){
        pthread_join(threads[i], NULL);
    }
    
    printf("\n");
    for(i = 0; i < SIZE; i++){
        printf("%i ", vetor[i]);
    }
    printf("\n");

    return 0;
}