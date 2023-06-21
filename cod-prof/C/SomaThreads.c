#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUMTHREADS  3
#define VETSIZE	    20

typedef struct {
	int idx, length;
} thread_arg, *ptr_thread_arg;

pthread_t   threads[NUMTHREADS];  // Threads do programa
thread_arg  arguments[NUMTHREADS];  // Argumentos das threads

int sum; // Soma geral dos dados


void *thread_func(void *arg) {
	ptr_thread_arg  argument = (ptr_thread_arg)arg;
	int i, localsum = 0, endidx;

	endidx = argument->idx + argument->length;  // Posicao do ultimo+1
	printf("Somando de %d ate %d\n", argument->idx, endidx);
	for(i = argument->idx; i < endidx; i++) {
		localsum += i;
	}
	printf("Soma local %d\n",localsum);
	sum += localsum; // Acumula a soma da thread na soma geral
}


int main(int argc, char **argv) {
	int i, length, remainder;  // remainder = resto

	sum = 0;
    length = VETSIZE / NUMTHREADS; // Tamanho dos dados de cada thread (divisao inteira)
	remainder = VETSIZE % NUMTHREADS; // Resto da divisao inteira
	// Criar todas as threads
	for(i = 0; i < NUMTHREADS; i++) {
		arguments[i].idx = i * length;
		arguments[i].length = length;
		if(i == (NUMTHREADS - 1)) // Testa se é ultima thread
			arguments[i].length += remainder; // A ultima recebe o resto, além dos dados
		pthread_create(&threads[i], NULL, thread_func, &arguments[i]);
	}
	// Aguardar todas as threads terminarem
	for(i=0; i<NUMTHREADS; i++) {
		pthread_join(threads[i], NULL);
	}
	printf("A soma dos numeros de 0 a %d eh %d\n", (VETSIZE-1), sum);

}


