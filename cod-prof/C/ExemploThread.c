#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/*Rotina que será executada*/
void *routine(void *arg)
{
    char *s = (char *)arg;
	/*exibe o argumento recebido*/
	printf("Argumento: %s\n", s);
	/*finaliza a função retornando o argumento que foi recebido*/
	pthread_exit(arg);
}


int main (int argc, char *argv[])
{
	pthread_t  thread_id; // Identificador da thread
	void *thread_res; // Obter o valor de retorno
	int rstatus; // Status da thread (create/join); 0 -> sucesso / 1 -> problema

	/*tenta iniciar o thread, indicando a função 'routine' e passando como argumento a string "Minha primeira Thread!"*/
	rstatus = pthread_create (&thread_id, NULL, routine, (void *)("Minha primeira Thread!"));

	/*verificar se ocorreu algum erro na chamada de pthread_create*/
	if (rstatus != 0)
	{
		printf ("Erro ao criar o thread.\n");
		exit(EXIT_FAILURE); // Encerra o programa e passa pro SO o código
	}
	printf ("Thread criado com sucesso!\n");

	/*aguarda finalização do thread identificado por thread_id. O retorno é passado pelo ponteiro thread_res*/
	rstatus = pthread_join(thread_id, &thread_res);

	/*verificar se ocorreu algum erro na chamada de pthread_join*/
	if (rstatus != 0)
	{
		printf ("Erro ao aguardar finalização do thread.\n");
		exit(EXIT_FAILURE); // Encerra o programa e passa pro SO o código
	}

	/*exibe o valor de retorno da função 'routine'*/
	printf("Thread finalizado! Retorno = %s\n", (char *)thread_res);

	system("PAUSE");
	return 0;
}

