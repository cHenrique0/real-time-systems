#include <stdio.h>
#include <stdlib.h>

// Função para imprimir matriz:
/*
    void imprimeMatriz(tipo variavel[linha][coluna], int M, int N){
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j){
                printf("%d ", matriz[i][j])
            }
            printf("\n");
        }
    }
*/

// Multiplicação de matriz
/*
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
*/


int main(int argc, char const *argv[])
{
    int matriz[4][3];
    int i, j;
    
    // Montando a matriz
    for(i = 0; i < 4; i++){
        for(j = 0; j < 3; j++){
            printf("Digite o elemento [%d][%d]: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }

    // Imprimindo a matriz
    for(i = 0; i < 4; i++){
        for(j = 0; j < 3; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    return 0;
}
