#include <stdio.h>
#include <stdlib.h>

int hanoi(int discos, int torreInicial, int torreAuxiliar, int torreFinal);

int main(void)
{
    int n, movimientos;
    system("Cls");
	printf("Cantidad de discos a mover: ");
	scanf("%d", &n);
	printf("\nLa serie de movimientos a realizar es: \n\n");
	//1 es la torre inicial, 2 la torre auxiliar y 3 la torre final
	movimientos = hanoi(n, 1, 2, 3);
	printf("\nSe realizaron en total %d movimientos\n", movimientos);
	system("Pause");
	return 0;
}

int hanoi(int n, int torreInicial, int torreAuxiliar, int torreFinal)
{
    static int movimientos = 0;
	if(n == 1) // sólo hay un disco
	{
		printf("Mover el disco superior de la torre %d a la torre %d\n", torreInicial, torreFinal);
		movimientos++;
	}
	else // más de un disco
	{
		hanoi(n - 1, torreInicial, torreFinal, torreAuxiliar);
		printf("Mover el disco superior de la torre %d a la torre %d\n", torreInicial, torreFinal);
		movimientos++;
		hanoi(n - 1, torreAuxiliar, torreInicial, torreFinal);
	}
	return movimientos;
}
