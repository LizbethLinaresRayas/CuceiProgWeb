#include <stdio.h>
#include <stdlib.h>
#include <String.h>
#include <math.h>

int main()
{
    //octal
    int numero=0;
    int i;
    int cont=0;
    int longitud;
    int aux=0;
    int aux1=0;
    int j;
    int numero_total=0;
    char cadena[10];
    char caracter;

    printf("\n\tIngresa un numero: ");
    fflush(stdin);
    gets(cadena);
    aux=strlen(cadena);
    j=aux-1;
    for(i=0; i<longitud; i++)
    {
        caracter=cadena[i];
        switch(caracter)
        {
            case 0:
                numero=0;
            break;
            case 1:
                numero=1;
            break;
            case 2:
                numero=2;
            break;
            case 3:
                numero=3;
            break;
            case 4:
                numero=4;
            break;
            case 5:
                numero=5;
            break;
            case 6:
                numero=6;
            break;
            case 7:
                numero=7;
            break;
        }

        aux=pow(numero,j);
        aux1=aux * numero;
        numero_total+=aux1;
        j--;
    }

    printf("Entero: %d",numero_total);


    return 0;
}
