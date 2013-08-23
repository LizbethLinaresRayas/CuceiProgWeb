#include <stdio.h>
#include <stdlib.h>

int factorial(int n);
int factorialEstructurado(int n);

int main(void)
{
  int n;
  system("Cls");
  printf("Valor a calcular su factorial: ");
  scanf("%d", &n);
  printf("El factorial de %d es: %d\n", n, factorial(n));
  //printf("El factorial de %d es: %d\n", n, factorialEstructurado(n));
  system("Pause");
  return 0;
}

int factorial(int n)
{
    if (n < 2) // ya que 1! = 1
        return 1;
    return n * factorial(n - 1);
}

int factorialEstructurado(int n)
{
    int resultado;
    if (n == 0)
    {
        resultado = 1;
    }
    else
    {
        resultado = n * factorial(n - 1);
    }
    return resultado;
}
