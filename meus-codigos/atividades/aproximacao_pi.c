#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>
#include <time.h>
#include <unistd.h>


#define NUM_THREADS 4
#define TERMS 100

typedef struct
{
    int id_thread;
    int start;
    int end;
    int lenth;

} thread_args;

sem_t semaphore;
pthread_t threads[2];
double pi = 0, total_sum = 0;

void *pi_approach(void *arg){

    thread_args *args = (thread_args *)arg;
    int i;
    double local_sum = 0;
    
    printf("Thread %d: somando entre os termos %d e %d\n", args->id_thread, args->start, args->end-1);
    for(i = args->start; i < args->end; i++){
        local_sum += (pow(-1, i) / ((2*i) + 1));
    }

    sem_wait(&semaphore);
    total_sum += local_sum;
    sem_post(&semaphore);

    pi = 4*total_sum;
}

int main(int argc, char const *argv[])
{
    sem_init(&semaphore, 0, 1);

    clock_t start_time, end_time, var_time;
    double elapsed_time;

    thread_args args[NUM_THREADS];
    int data_lenth = TERMS / NUM_THREADS;
    int i;
    
    start_time = clock();

    for(i=0; i<NUM_THREADS; i++){
        args[i].id_thread = i + 1;
        args[i].start = i * data_lenth;
        args[i].end = args[i].start + data_lenth;
        args[i].lenth = data_lenth;

        pthread_create(&threads[i], NULL, pi_approach, &args[i]);
    }

    for(i=0; i<NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    end_time = clock();

    var_time = end_time - start_time;
    elapsed_time = (double)var_time / CLOCKS_PER_SEC;

    sem_destroy(&semaphore);
    
    printf("\n> pi = %.15f\n", pi);
    printf("\n> Tempo decorrido para o calculo: %f s\n", elapsed_time);


    return 0;
}
