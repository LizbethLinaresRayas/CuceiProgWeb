#include <stdio.h>
#include <stdlib.h>

int fibonacci(int n);

int main(void)
{
  int n;
  system("Cls");
  printf("limite de serie fibonacci : ");
  scanf("%d", &n);
  printf("la serie es: %d\n", fibonacci(n));
  //printf("El factorial de %d es: %d\n", n, factorialEstructurado(n));
  system("Pause");
  return 0;
}

int fibonacci(int n)
{
    if(n<2)
        return n;
    else
        return fibonacci(n-1)+fibonacci(n-2);
}
