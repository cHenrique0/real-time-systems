#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


sem_t mutex;

void *thread_function(void *arg){
    int *id = (int *)arg;

    // wait
    sem_wait(&mutex);
    printf("Thread %d: Entrando...\n", *id);
    
    // REGIÃO CRITICA
    sleep(5);

    // signal
    printf("Thread %d: Saindo...\n", *id);
    sem_post(&mutex);

}

int main(int argc, char const *argv[])
{
    sem_init(&mutex, 0, 1);     // Iniciando o semaforo
    pthread_t threads[2];
    int i, args[2] = {1, 2};
    
    for(i=0; i<2; i++){
        pthread_create(&threads[i], NULL, thread_function, (void *)&args[i]);
    }

    for(i=0; i<2; i++){
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&mutex);        // Finalizando o semaforo
    return 0;
}
