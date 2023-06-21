/*
Crie um programa multithread para calcular o produto de duas matrizes
inteiras quadradas de ordem 4. Devem ser criadas dezesseis threads, cada uma
para calcular um dos dezesseis elementos da matriz resultante.
*/

#include <stdio.h>
#include <stdlib.h>

int mat_A[4][4] = {
                    {25, 33, 49, 39},
                    {17, 16, 7, 26},
                    {46, 20, 32, 30},
                    {42, 22, 4, 45},
                  };
int mat_B[4][4] = {
                    {19, 12, 5, 8},
                    {1, 11, 27, 29},
                    {10, 31, 21, 14},
                    {9, 48, 34, 36},
                  };
    
int mat_C[4][4] = {0};

void *times_matriz(void *arg){
    int lin, col, i, soma;

    for(lin=0; lin<4; lin++){
        for(col=0; col<4; col++){
            soma = 0;
            for(i=0; i<4; i++){
                soma += mat_A[lin][i] * mat_B[i][col];
            }
            mat_C[lin][col] = soma;
        }
    }
}

int main(int argc, char const *argv[])
{

    // Imprime a matriz resultante
    int lin, col;
    for(lin=0; lin<4; lin++){
        for(col=0; col<4; col++){
            printf("%d ", mat_C[lin][col]);
        }
        printf("\n");
    }

    
    return 0;
}
