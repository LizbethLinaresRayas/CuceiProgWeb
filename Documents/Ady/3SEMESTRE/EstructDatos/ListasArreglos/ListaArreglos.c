#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "listaArreglos.h"

int main(void)
{
    char op;
    Lista l;
    TipoElemento x;
    posicion p;
    inicializa(&l);
    do
    {
        system("Cls");
        printf ("\n\t E L I G E    L A    O P C I O N    Q U E    D E S E A S ");
        printf ("\n\n\t M E N U   D E   O P C I O N E S\n ");
        printf ("\n\t (I) Insertar un elemento........................");
        printf ("\n\t (E) Eliminar un elemento........................");
        printf ("\n\t (M) Mostrar lista...............................");
        printf ("\n\t (S) Salir.......................................");
        printf ("\n\n\t\t\tOpcion:");
        fflush(stdin);
        scanf("%c", &op);
        op = toupper(op);
        system("Cls");
        switch(op)
        {
            case 'I':
                if(!estaLlena(&l))
                {
                    printf("\n\tDato a insertar: ");
                    fflush(stdin);
                    leeElemento(&x);
                    inserta(&x, fin(&l), &l);
                    printf("\tEl dato ha sido insertado\n\n");
                }
                else
                {
                    imprimeError("La lista está llena");
                }
            break;
            case 'E':
                if(!estaVacia(&l))
                {
                    printf("\n\tDame el elemento a eliminar: ");
                    fflush(stdin);
                    leeElemento(&x);
                    p = localiza(&x, &l);
                    if (p != fin(&l))
                    {
                        suprime(p, &l);
                        printf("\tEl elemento ha sido eliminado\n\n");
                    }
                    else
                    {
                        imprimeError("\tEl elemento no existe\n\n");
                    }
                }
                else
                {
                    imprimeError("La lista está vacía");
                }
            break;
            case 'M':
                if(!estaVacia(&l))
                {
                    imprimeLista(&l);
                }
                else
                {
                    imprimeError("La lista está vacía");
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
