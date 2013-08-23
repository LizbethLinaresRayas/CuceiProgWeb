#include <stdio.h>
#include <stdlib.h>

int * reservaMemoriaVector(int n);
void llenaArreglo(int arreglo[], int n);
void imprimeArreglo(int arreglo[], int n);
int busquedaLineal(int arreglo[], int n, int valor);
int linealRecursiva(int arreglo[], int n, int valor, int posicion);
int busquedaLinealRecursiva(int arreglo[], int n, int valor);
int busquedaBinaria(int arreglo[], int n, int valor);
int binariaRecursiva(int arreglo[], int izquierda, int derecha, int valor);
int busquedaBinariaRecursiva(int arreglo[], int n, int valor);
void intercambia(int *valor1, int *valor2);
void quickSort(int arreglo[], int primero, int ultimo);

int main(void)
{
	int *arreglo, n, opcion, valor, posicion;
	system("Cls");
	printf("Total de elementos del arreglo: ");
	scanf("%d", &n);
	arreglo = reservaMemoriaVector(n);
	llenaArreglo(arreglo, n);
	printf("\nArreglo introducido\n\n");
	imprimeArreglo(arreglo, n);
	system("Pause");
	do
	{
        system("Cls");
        printf("\nMétodo de ordenamiento a utilizar\n\n");
        printf("1.- Búsqueda lineal simple\n2.- Búsqueda lineal recursiva\n");
        printf("3.- Búsqueda binaria simple\n4.- Búsqueda binaria recursiva\n");
        printf("Opción: ");
        scanf("%d", &opcion);
	} while (opcion < 1 || opcion > 4);
	printf("Valor a buscar en el arreglo: ");
    scanf("%d", &valor);
	switch (opcion)
	{
	    case 1:
	        posicion = busquedaLineal(arreglo, n, valor);
	        if (posicion >= n)
	        {
	            printf("\nEl valor %d no existe en el arreglo\n", valor);
            }
            else
            {
                printf("\nEl valor %d está en la posición %d\n" , valor, posicion);
            }
        break;
        case 2:
	        posicion = busquedaLinealRecursiva(arreglo, n, valor);
	        if (posicion == -1)
	        {
	            printf("\nEl valor %d no existe en el arreglo\n", valor);
            }
            else
            {
                printf("\nEl valor %d está en la posición %d\n" , valor, posicion);
            }
        break;
        case 3:
            quickSort(arreglo, 0, n - 1);
            printf("\nArreglo ordenado\n\n");
            imprimeArreglo(arreglo, n);
	        posicion = busquedaBinaria(arreglo, n, valor);
	        if (posicion == -1)
	        {
	            printf("\nEl valor %d no existe en el arreglo\n", valor);
            }
            else
            {
                printf("\nEl valor %d está en la posición %d\n" , valor, posicion);
            }
        break;
        case 4:
            quickSort(arreglo, 0, n - 1);
            printf("\nArreglo ordenado\n\n");
            imprimeArreglo(arreglo, n);
	        posicion = busquedaBinariaRecursiva(arreglo, n, valor);
	        if (posicion == -1)
	        {
	            printf("\nEl valor %d no existe en el arreglo\n", valor);
            }
            else
            {
                printf("\nEl valor %d está en la posición %d\n" , valor, posicion);
            }
        break;
        default:
            printf("\nOpción inválida\n");
        break;
	}
    system("Pause");
    return 0;
}

int * reservaMemoriaVector(int n)
{
    int bytes = sizeof(int) * n, i;
    int *vector = (int *)malloc(bytes);
    for (i = 0; i < n; i++)
	    vector[i] = 0;
    return vector;
}

void llenaArreglo(int arreglo[], int n)
{
	int i;
	printf("\nIntroduce los %d elementos del arreglo\n\n", n);
	for (i = 0; i < n; i++)
	{
		printf("Arreglo[%d] = ", i);
		scanf("%d", &arreglo[i]);
	}
}

void imprimeArreglo(int arreglo[], int n)
{
	int i;
	printf("\nElementos almacenados en el arreglo\n\n");
	for (i = 0; i < n; i++)
	{
		printf("Arreglo[%d] = %d\n", i, arreglo[i]);
	}
}

int busquedaLineal(int arreglo[], int n, int valor)
{
    int i = 0;
    while (i < n && valor != arreglo[i])
    {
        i++;
    }
    return i;
}

int linealRecursiva(int arreglo[], int n, int valor, int posicion)
{
    if (posicion >= n)
    {
        return -1;
    }
    else
    {
        if (valor == arreglo[posicion])
        {
            return posicion;
        }
        else
        {
            return linealRecursiva(arreglo, n, valor, ++posicion);
        }
    }
}

int busquedaLinealRecursiva(int arreglo[], int n, int valor)
{
    return linealRecursiva(arreglo, n, valor, 0);
}

int busquedaBinaria(int arreglo[], int n, int valor)
{
    int izquierda = 0, derecha = n - 1, medio;
    while (izquierda <= derecha)
    {
        medio = (izquierda + derecha) / 2;
        if (valor == arreglo[medio])
        {
            return medio;
        }
        else
        {
            if (valor > arreglo[medio])
            {
                izquierda = medio + 1;
            }
            else
            {
                derecha = medio - 1;
            }
        }
    }
    return -1;
}

int binariaRecursiva(int arreglo[], int izquierda, int derecha, int valor)
{
    int medio;
    if (izquierda > derecha)
    {
        return -1;
    }
    else
    {
        medio = (izquierda + derecha) / 2;
        if (valor == arreglo[medio])
        {
            return medio;
        }
        else
        {
            if (valor > arreglo[medio])
            {
                return binariaRecursiva(arreglo, medio + 1, derecha, valor);
            }
            else
            {
                return binariaRecursiva(arreglo, izquierda, medio - 1, valor);
            }
        }
    }
}

int busquedaBinariaRecursiva(int arreglo[], int n, int valor)
{
    return binariaRecursiva(arreglo, 0, n, valor);
}

void intercambia(int *valor1, int *valor2)
{
   if (valor1 != valor2)
   {
       int aux = *valor1;
       *valor1 = *valor2;
       *valor2 = aux;
   }
}

void quickSort(int arreglo[], int primero, int ultimo)
{
    register int i, j;
    int pivote;
    i = primero;
    j = ultimo;
    pivote = arreglo[(primero + ultimo) / 2];
    do
    {
        while(arreglo[i] < pivote)
        {
            i++;
        }
        while(arreglo[j] > pivote)
        {
            j--;
        }
        if (i <= j)
        {
            intercambia(&arreglo[i], &arreglo[j]);
            i++;
            j--;
        }
    } while (i <= j);
    if(primero < j)
    {
        quickSort(arreglo, primero, j);
    }
    if(ultimo > i)
    {
        quickSort(arreglo, i, ultimo);
    }
}
