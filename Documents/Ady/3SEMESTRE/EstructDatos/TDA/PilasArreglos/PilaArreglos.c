#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "PilaArreglos.h"

int main(void)
{
    char op = '0';
    Pila p;
    TipoElemento x;
    inicializa(&p);
    do
    {
        system("Cls");
        printf ("\n\t E L I G E    L A    O P C I O N    Q U E    D E S E A S ");
        printf ("\n\n\t M E N U   D E   O P C I O N E S\n ");
        printf ("\n\t (A) Apilar un elemento..........................");
        printf ("\n\t (D) Desapilar un elemento.......................");
        printf ("\n\t (T) Tope de la pila.............................");
        printf ("\n\t (M) Mostrar toda la pila........................");
        printf ("\n\t (S) Salir.......................................");
        printf ("\n\n\t\t\tOpcion:");
        fflush(stdin);
        scanf("%c", &op);
        op = toupper(op);
        system("Cls");
        switch(op)
        {
            case 'A':
                if(!estaLlena(&p))
                {
                    printf("\n\tDato a apilar: ");
                    fflush(stdin);
                    leeElemento(&x);
                    apila(&x, &p);
                    printf("\tEl dato ha sido apilado\n\n");
                }
                else
                {
                    imprimeError("La pila está llena");
                }
            break;
            case 'D':
                if(!estaVacia(&p))
                {
                    printf("\n\tEl dato a desapilar es: ");
                    imprimeElemento(tope(&p));
                    desapila(&p);
                    printf("\tEl dato ha sido desapilado\n");
                }
                else
                {
                    imprimeError("La pila está vacía");
                }
            break;
            case 'T':
                if(!estaVacia(&p))
                {
                    printf("\n\tEl dato en el tope es: ");
                    imprimeElemento(tope(&p));
                }
                else
                {
                    imprimeError("La pila está vacía");
                }
            break;
            case 'M':
                if(!estaVacia(&p))
                {
                    imprimePila(&p);
                }
                else
                {
                    imprimeError("La pila está vacía");
                }
            break;
            case 'S':
                printf("\n\n\t\tFIN DE PROGRAMA...\n\n");
            break;
            default:
                imprimeError("Opción inválida");
            break;
        }
        system("Pause");
    } while(op != 'S');
    return 0;
}











