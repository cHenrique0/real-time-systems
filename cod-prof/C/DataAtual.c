#include <stdio.h>
#include <time.h>

int main()
{
    struct tm *local;

    /* Pega a data atual, em segundos de acordo com o relógio Unix, a partir do relógio do sistema */
    time_t timer = time(NULL);

    /* Converte o tempo em segundos para o tempo local */
    local = localtime(&timer);

    printf("A data atual e' %d/%d/%d\n", local->tm_mday, local->tm_mon+1, local->tm_year+1900);

    /* Converte o valor de time t para uma string com um formato igual ao de asctime */
    printf("A data atual formatada e' %s\n", ctime(&timer));
}
