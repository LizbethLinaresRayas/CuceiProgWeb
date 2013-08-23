#include <stdio.h>
#include <stdlib.h>

int * reservaMemoriaVector(int n);
void llenaArreglo(int arreglo[], int n);
void imprimeArreglo(int arreglo[], int n);
void intercambia(int *valor1, int *valor2);
void burbujaMenor(int arreglo[], int n);
void burbujaMayor(int arreglo[], int n);
void burbujaMejorado(int arreglo[], int n);
void insercion(int arreglo[], int n);
void seleccion(int arreglo[], int n);
void mezcla(int arreglo[], int izquierda, int derecha);
void shellSort(int arreglo[], int n, int paso);
void quickSort(int arreglo[], int primero, int ultimo);

int main(void)
{
	int *arreglo, n, opcion;
	system("Cls");
	printf("Total de elementos a ordenar: ");
	scanf("%d", &n);
	arreglo = reservaMemoriaVector(n);
	llenaArreglo(arreglo, n);
	printf("\nArreglo original\n\n");
	imprimeArreglo(arreglo, n);
	system("Pause");
	do
	{
        system("Cls");
        printf("\nMétodo de ordenamiento a utilizar\n\n");
        printf("1.- Burbuja menor\n2.- Burbuja mayor\n3.- Burbuja mejorado\n");
        printf("4.- Inserción\n5.- Selección\n6.- Mezcla\n");
        printf("7.- Shell Sort\n8.- Quick Sort\n");
        printf("Opción: ");
        scanf("%d", &opcion);
	} while (opcion < 1 || opcion > 8);
	switch (opcion)
	{
	    case 1:
	        burbujaMenor(arreglo, n);
        break;
        case 2:
	        burbujaMayor(arreglo, n);
        break;
        case 3:
	        burbujaMejorado(arreglo, n);
        break;
        case 4:
	        insercion(arreglo, n);
        break;
        case 5:
	        seleccion(arreglo, n);
        break;
        case 6:
	        mezcla(arreglo, 0, n - 1);
        break;
        case 7:
	        shellSort(arreglo, n, 2);
        break;
        case 8:
	        quickSort(arreglo, 0, n - 1);
        break;
        default:
            printf("Opción incorrecta");
        break;
	}
	printf("\nArreglo ordenado\n\n");
	imprimeArreglo(arreglo, n);
	system("Pause");
    return 0;
}

int * reservaMemoriaVector(int n)
{
    int bytes = sizeof(int) * n, i = -1;
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

void intercambia(int *valor1, int *valor2)
{
   if (valor1 != valor2)
   {
       int aux = *valor1;
       *valor1 = *valor2;
       *valor2 = aux;
   }
}

void burbujaMenor(int arreglo[], int n)
{
    register int i, j;
    for (i = 1; i < n; i++)
    {
        for (j = n - 1; j >= i; j--)
        {
            if (arreglo[j - 1] > arreglo[j])
            {
                intercambia(&arreglo[j - 1], &arreglo[j]);
            }
        }
    }
}

void burbujaMayor(int arreglo[], int n)
{
    register int i, j;
    for (i = n - 2; i >= 0; i--)
    {
        for (j = 0; j <= i; j++)
        {
            if (arreglo[j] > arreglo[j + 1])
            {
                intercambia(&arreglo[j], &arreglo[j + 1]);
            }
        }
    }
}

void burbujaMejorado(int arreglo[], int n)
{
    register int i, j, band;
    i = 0;
    band = 0;
    while (i < n - 1 && !band)
    {
        band = 1;
        for (j = 0; j < n - 1; j++)
        {
            if (arreglo[j] > arreglo[j + 1])
            {
                intercambia(&arreglo[j], &arreglo[j + 1]);
                band = 0;
            }
        }
        i++;
    }
}

void insercion(int arreglo[], int n)
{
    register int i, j, aux;
    for (i = 1; i < n; i++)
    {
        aux = arreglo[i];
        j = i - 1;
        while (j >= 0 && aux < arreglo[j])
        {
            arreglo[j + 1] = arreglo[j];
            j--;
        }
        arreglo[j + 1] = aux;
    }
}

void seleccion(int arreglo[], int n)
{
    int i, j, menor;
    for(i = 0; i < n - 1; i++)
    {
        menor = i;
        for(j = i + 1; j < n; j++)
        {
            if (arreglo[j] < arreglo[menor])
            {
                menor = j;
            }
        }
        if (i != menor)
        {
		    intercambia(&arreglo[menor], &arreglo[i]);
        }
    }
}

void mezcla(int arreglo[], int izquierda, int derecha)
{
    register int i, j, k, medio;
    static int *aux;
    aux = (int *)malloc(sizeof(int) * (derecha + 1));
    if (derecha > izquierda)
    {
        medio = (derecha + izquierda) / 2;
        mezcla(arreglo, izquierda, medio);
        mezcla(arreglo, medio + 1, derecha);
        for (i = medio + 1; i > izquierda; i--)
        {
            aux[i - 1] = arreglo[i - 1];
        }
        for (j = medio; j < derecha; j++)
        {
            aux[derecha + medio - j] = arreglo[j + 1];
        }
        for (k = izquierda; k <= derecha; k++)
        {
            arreglo[k] = (aux[i] < aux[j])?aux[i++]:aux[j--];
        }
    }
}

void shellSort(int arreglo[], int n, int paso)
{
    register int i, j, incremento, aux;
    incremento = n / paso;
    while (incremento > 0)
    {
        for (i = incremento; i < n; i++)
        {
            j = i;
            aux = arreglo[i];
            while (j >= incremento && arreglo[j - incremento] > aux)
            {
                arreglo[j] = arreglo[j - incremento];
                j = j - incremento;
            }
            arreglo[j] = aux;
        }
        incremento /= paso;
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
