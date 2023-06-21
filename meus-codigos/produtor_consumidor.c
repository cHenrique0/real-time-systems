#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TRUE 1
pthread_t threads[2];

void *prod_consum(void *arg){

    int *id_thread = (int *)arg;
    
    int N = 7;      // Tamanho do buffer
    int buffer[N];
    int i = 0;      // aponta para o primeiro elemento no buffer
    int f = 0;      // aponta para a próxima posição livre no buffer
    int c = 0;      // quantidade de elementos presentes no buffer

}

int main(int argc, char const *argv[])
{
    int id[2] = {1, 2};
    int i;

    for(i=0; i<2; i++){
        pthread_create(&threads[i], NULL, prod_consum, &id[i]);
    }

    for(i=0; i<2; i++){
        pthread_join(threads[i], NULL);
    }

    return 0;
}
