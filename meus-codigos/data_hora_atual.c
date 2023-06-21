#include <stdio.h>
#include <time.h>

// Informações da struct tm
/*
struct tm {
    int tm_sec;     // segundos de 0 a 59
    int tm_min;     // minutos de 0 a 59
    int tm_hour;    // horas de 0 a 24
    int tm_mday;    // dia do mês de 1 a 31
    int tm_mon;     // meses do ano de 0 a 11
    int tm_year;    // ano a partir de 1900
    int tm_wday;    // dia da semana de 0 (domingo) até 6 (sábado)
    int tm_yday;    // dia do ano de 1 a 365
    int tm_isdst;   // indica horário de verão se for diferente de zero
};
*/

int main(int argc, char const *argv[])
{
    // Struct tm para armazenar as informações de data e hora
    struct tm *data_hora_atual;
  
    // variável do tipo time_t para armazenar o tempo em segundos  
    time_t timer = time(NULL);
  
    //A função localtime converte o tempo em segundos
    data_hora_atual = localtime(&timer);

    /*
    Imprimindo a data e hora atual
    Para retornar o mês correto deve-se somar +1
    para retornar o ano correto deve-se somar +1900
    */
    printf("Data atual > %d/%d/%d\n", data_hora_atual->tm_mday, data_hora_atual->tm_mon+1, data_hora_atual->tm_year+1900);

    printf("Dia do ano > %d\n", data_hora_atual->tm_yday);  
    printf("Dia da semana > %d\n", data_hora_atual->tm_wday);
    
    /* 
    Obtendo os valores da struct data_hora_atual  
    e formatando a saída de dados no formato :
        hora: minuto: segundo
    */
    printf("Hora atual > %d:%d:%d\n", data_hora_atual->tm_hour, data_hora_atual->tm_min, data_hora_atual->tm_sec);

  return 0;
}
