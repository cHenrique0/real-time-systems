#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 4
#define VECTOR_SIZE 1000

typedef struct
{
    int start;
    int end;
    int lenth;
    int id_thread;
} thread_arg, *p_thread;

sem_t semaphore;
pthread_t threads[NUM_THREADS];
thread_arg args[NUM_THREADS];
int total_sum = 0;

void *sum(void *arg){
    p_thread argument = (p_thread)arg;
    int i, local_sum = 0;

    printf("THREAD %d: Somando numeros entre %d e %d\n", argument->id_thread, argument->start, (argument->end-1));
    for(i=argument->start; i<argument->end; i++){
        local_sum += i;
    }

    sem_wait(&semaphore);
    total_sum += local_sum;
    sem_post(&semaphore);
}

int main(int argc, char const *argv[])
{
    sem_init(&semaphore, 0, 1);
    int i, data_lenth, resto;
    data_lenth = VECTOR_SIZE/NUM_THREADS;
    resto = VECTOR_SIZE % NUM_THREADS;

    for(i=0; i<NUM_THREADS; i++){
        args[i].start = i * data_lenth;
        args[i].lenth = data_lenth;
        args[i].end = args[i].start + data_lenth;
        args[i].id_thread = i + 1;

        if(i == (NUM_THREADS - 1)){
            args[i].lenth += resto;
        }
        
        pthread_create(&threads[i], NULL, sum, &args[i]);
    }

    for(i=0; i<NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    printf("Soma dos numeros do vetor: %d\n", total_sum);

    sem_destroy(&semaphore);

    return 0;
}
