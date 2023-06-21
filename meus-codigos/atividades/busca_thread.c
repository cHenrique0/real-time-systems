/*
Crie um programa multithread que realize uma busca de um número em um
vetor aleatório de 100 números inteiros. Devem ser criadas quatro threads e o
vetor deve ser populado com números aleatórios inteiros gerados pelo sistema.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 0

#define THREADS 4
#define VECTOR_LEN 100
int vector[VECTOR_LEN] = {0};
int num = 0;

typedef struct
{
    int start;
    int end;
    int lenth;
    int id_thread;

} thread_arg, *p_thread;

void *find_num(void *arg){

    int i, pos = 0, verify = FALSE;
    p_thread args = (p_thread)arg;

    printf("\nThread %d: buscando entre os indices %d e %d \n", args->id_thread, args->start, (args->end-1));
    for(i = args->start; i < args->end; i++){
        if(vector[i] == num){
            verify = TRUE;
            pos = i;
        }
        else{
            verify = FALSE;
        }
    }
    if(verify == TRUE){
        printf("> A thread %d encontrou numero [%d] na posicao %d do vetor.\n", args->id_thread, num, pos);
    }
    else{
        printf("> A thread %d nao encontrou o numero [%d].\n", args->id_thread, num);
    }
}

int main()
{

    pthread_t threads[THREADS];
    thread_arg args[THREADS];
    int data_lenth = VECTOR_LEN / THREADS;
    int i;

    printf("Digite o numero inteiro(entre 0 e 999) a ser procurado: ");
    scanf("%d", &num);
    
    // Motando o vetor
    srand(time(NULL));
    for (i = 0; i < 100; i++){
        vector[i] = rand() % 1000;
    }
    
    // Imprimindo o vetor
    printf("VETOR:\n");
    for(i = 0; i < 100; i++){
        printf("%d ", vector[i]);
    }
    printf("\n");

    // Criando as Threads
    for(i = 0; i < THREADS; i ++){
        args[i].start = i * data_lenth;
        args[i].lenth = data_lenth;
        args[i].end = args[i].start + args[i].lenth;
        args[i].id_thread = i + 1;
        pthread_create(&threads[i], NULL, find_num, &args[i]);
    }

    // Finalizando as Threads
    for(i = 0; i < THREADS; i++){
        pthread_join(threads[i], NULL);
    }
    
    return 0;
}
