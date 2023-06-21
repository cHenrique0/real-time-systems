#include <stdio.h>
#include <time.h>
#include <unistd.h>



void funcao_qualquer(int n){
    sleep(n);
}

int main(int argc, char const *argv[])
{
    clock_t start_time, end_time, var_time;
    double elapsed_time;

    start_time = clock();
    funcao_qualquer(5);
    end_time = clock();

    var_time = end_time - start_time;
    elapsed_time = (double)var_time / CLOCKS_PER_SEC;

    printf("Tempo decorrido: %f s\n", elapsed_time);
    
    return 0;
}
