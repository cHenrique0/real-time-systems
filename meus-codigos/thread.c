#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *PrintHello(void *arg){
    int *id = (int *)arg;
    
    printf("Thread %i: Ola, mundo!\n", *id);

}

int main(int argc, char const *argv[])
{
    pthread_t threads[10];   // Instancia um vetor de threads, no caso, 2 threads
    int i, id[10];              // Identificador das  threads

    for(i = 0; i < 10; i++){
        id[i] = i + 1;
        printf("Main: Criando a thread %d\n", id[i]);
        pthread_create(&threads[i], NULL, PrintHello, (void *)&id[i]);
    }

    for(i = 0; i < 10; i++){
        pthread_join(threads[i], NULL);
    }
    
    return 0;
}




/*
#define NUM_THREAD 5    // Determina o numero de threads

// Função que executa as threads
void *funcao(void *arg){

    int pvalor = (int *)arg;
    printf("Thread %i executando...\n", pvalor);
}

int main()
{
    pthread_t threads[NUM_THREAD];  //Instanciando as threads
    int i, arg[NUM_THREAD];

    // Criando as threads
    for(i = 0; i < NUM_THREAD; i++){
        arg[i] = i + 1;
        pthread_create(&threads[i], NULL, funcao, (void *)&arg[i]); // Cria as threads
    }

    // Finalizando as threads
    for(i = 0; i < NUM_THREAD; i++){
        pthread_join(threads[i], NULL); // Finaliza as threads
    }

    printf("\n");

    return 0;
}
*/