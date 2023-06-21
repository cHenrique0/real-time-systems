#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    typedef struct
    {
        int horas;
        int minutos;
        int segundos;
    }horario;

    horario agora;

    agora.horas = 15;
    agora.minutos = 17;
    agora.segundos = 30;

    printf("%d:%d:%d", agora.horas, agora.minutos, agora.segundos);
    
    return 0;
}
