/*ADRIANA LIZBETH LINARES RAYAS COD. 210596378 LIC. INFORMATICA SECC D-15*/
#include <stdio.h>
#include <stdlib.h>
#include "PILA.h"

int main(void)
{
    system("COLOR f1");
    int op,band=0,y=5,i,b=0;
    Pila p;
    TipoElemento x;
    posicion columna=35,fila=5;
    gotoxy(20,10);printf("CARGANDO PROGRAMA");
    barra();
    delay(500);
    do{
        system("cls");
        if(band == 1){
            imprimePila(&p);
            gotoxy(columna,fila+1);printf("TOPE->");
        }
        i=22;
        while(i<=34){
            gotoxy(columna-3,fila+i);printf("|");
            gotoxy(columna+27,fila+i);printf("|");
            i++;
        }
        gotoxy(columna-2,fila+21);printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _");
        gotoxy(columna+7,fila+23);printf("MENU");
        gotoxy(columna+5,fila+25);printf("1. INICIALIZAR");
        gotoxy(columna+5,fila+27);printf("2. AGREGAR");
        gotoxy(columna+5,fila+29);printf("3. ELIMINAR");
        gotoxy(columna+5,fila+31);printf("4. SALIR");
        gotoxy(columna+3,fila+33);printf("->ELIGE TU OPCION:");
        gotoxy(columna-2,fila+34);printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _");
        gotoxy(columna+22,fila+33);scanf("%d",&op);
        switch(op){
            case 1:
                system("cls");
                if(b == 0){
                    inicializa(&p);
                    b=1;
                    gotoxy(columna+7,fila);printf("HA SIDO INICIALIZADA LA PILA");
                }
                else{
                    gotoxy(columna+12,fila);printf("...OPCION INCORRECTA...");
                    gotoxy(columna+7,fila+2);printf("LA PILA YA HABIA SIDO INICIALIZADA");
                }
            break;
            case 2:
                system("cls");
                if(!estaLlena(&p)){
                    gotoxy(columna+7,fila);printf("<< AGREGAR ELEMENTO >>");
                    gotoxy(columna+7,fila+3);printf("INGRESA EL ELEMENTO: ");
                    leeElemento(&x);
                    apila(&x, &p);
                    gotoxy(columna+4,fila+9);printf("->EL ELEMENTO HA SIDO AGREGADO");
                    band=1;
                }
                else{
                    gotoxy(columna+4,fila+9);imprimeError("->LA PILA ESTA LLENA");
                }
                getch();
            break;
            case 3:
                system("cls");
                if(!estaVacia(&p)){
                    gotoxy(columna+3,fila);printf("<<ELIMINAR ELEMENTO >>");
                    gotoxy(columna+4,fila+3);printf("ELEMENTO A ELIMINAR: ");
                    imprimeElemento(tope(&p),&y);
                    desapila(&p);
                    gotoxy(columna+1,fila+9);printf("->EL ELEMENTO SE HA ELIMINADO");
                    if(estaVacia(&p))
                        band=0;
                }
                else{
                    gotoxy(columna+4,fila+9);imprimeError("->LA PILA ESTA VACIA");
                }
                getch();
            break;
            case 4:
                system("cls");
                gotoxy(columna+4,fila+9);printf("GRACIAS POR TU VISITA\n");
                getch();
            break;
            default:
                gotoxy(columna+4,fila+9);printf("->OPCION INCORRECTA\n");
        }
        gotoxy(columna,fila+12);system("pause");
    }while(op != 4);
    return 0;
}
