#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ColaCircularArreglos.h"

int main(void)
{
    char op = '0';
    Cola c;
    TipoElemento x;
    inicializa(&c);
    do
    {
        system("Cls");
        printf ("\n\t E L I G E    L A    O P C I O N    Q U E    D E S E A S ");
        printf ("\n\n\t M E N U   D E   O P C I O N E S\n ");
        printf ("\n\t (E) Encolar un elemento.........................");
        printf ("\n\t (D) Desencolar un elemento......................");
        printf ("\n\t (F) Frente de la cola...........................");
        printf ("\n\t (M) Mostrar toda la cola........................");
        printf ("\n\t (A) Anular o inicializar la cola................");
        printf ("\n\t (S) Salir.......................................");
        printf ("\n\n\t\t\tOpcion:");
        fflush(stdin);
        scanf("%c", &op);
        op = toupper(op);
        system("Cls");
        switch(op)
        {
            case 'E':
                if(!estaLlena(&c))
                {
                    printf("\n\tDato a encolar: ");
                    fflush(stdin);
                    leeElemento(&x);
                    encola(&x, &c);
                    printf("\tEl dato ha sido encolado\n");
                }
                else
                {
                    printf("\n\tLa cola está llena\n");
                }
            break;
            case 'D':
                if(!estaVacia(&c))
                {
                    printf("\n\tEl dato a desencolar es: ");
                    imprimeElemento(frente(&c));
                    desencola(&c);
                    printf("\tEl dato ha sido desencolado\n");
                }
                else
                {
                    imprimeError("La cola está vacía");
                }
            break;
            case 'F':
                if(!estaVacia(&c))
                {
                    printf("\n\tEl dato del frente es: ");
                    imprimeElemento(frente(&c));
                }
                else
                {
                    imprimeError("La cola está vacía");
                }
            break;
            case 'M':
                if(!estaVacia(&c))
                {
                    imprimeCola(&c);
                }
                else
                {
                    imprimeError("La cola está vacía");
                }
            break;
            case 'A':
                inicializa(&c);
                printf("\n\tLa cola ha sido inicializada\n");
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
