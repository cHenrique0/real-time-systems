#include <stdio.h>
#include <time.h>

int main()
{
    struct tm *local;
    time_t timer = time(NULL);

    /* Converte o tempo em segundos para o tempo local */
    local = localtime(&timer);

    printf("Hora atual %d:%d:%d\n",local->tm_hour, local->tm_min, local->tm_sec);
    printf("ctime is %s\n", ctime(&timer));

    return 0;
}
