#include <stdio.h>

int soma(int a, int b)
{
  // comandos
  return a+b;
}

typedef int (*ptrSoma)(int a, int b);
ptrSoma p;

int main() {
   int resultado;
   p = soma;
   resultado = p(3,7);
   printf("%d\n", resultado);
   return 0;
}