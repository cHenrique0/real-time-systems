#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>


typedef struct {
	int idx, length;
} thread_arg, *ptr_thread_arg;

pthread_t threads[3];

void *thread_func(void *arg) {
	ptr_thread_arg targ = (ptr_thread_arg)arg;
	int i;

	for(i = targ->idx; i < (targ->idx + targ->length); i++) {
        // Imprime os dados indices recebidos
        printf("Thread %d - value %d\n", pthread_self(), i);
	}
}

int main(int argc, char **argv) {
	thread_arg  arguments[3];  // { {idx,length} , {idx,length}, {idx,length} }
	int i;

	// Criar todas as threads
	for(i = 0; i < 3; i++) {
		arguments[i].idx = i * 10; // idx => 0, 10, 20
		arguments[i].length = 10;  // Cada thread processa QTDD dados
		// Cria cada uma das threads
		pthread_create(&threads[i], NULL, thread_func, &arguments[i]);
	}
	// Aguardar todas as threads terminarem
	for(i=0; i<3; i++) {
		pthread_join(threads[i], NULL);
	}
    printf("Processamento paralelo encerrado\n");
}
