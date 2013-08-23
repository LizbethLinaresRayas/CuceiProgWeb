/*Adriana Lizbeth Linares Rayas
Lic. Informatica Cod. 210596378*/
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "AGENDA.h"

int main(void)
{
    system("COLOR 8F");
    int columna=43,fila=10,band=0;
    int op,opcion,opc,x,y;
    char apodo[12];
    char nombre[30];
    char dir[25];
    long tel;
    Lista l;
    Tipodato datos;
    posicion p;
    posicion p1;
    inicializa(&l);

    do{
        system("cls");
        gotoxy(columna+3,fila);  printf("MENU");
        gotoxy(columna,fila+2);  printf("1. INSERTAR");
        gotoxy(columna,fila+4);  printf("2. ELIMINAR");
        gotoxy(columna,fila+6);  printf("3. MOSTRAR");
        gotoxy(columna,fila+8);  printf("4. MODIFICAR");
        gotoxy(columna,fila+10); printf("5. CONSULTA");
        gotoxy(columna,fila+12); printf("6. SALIR");
        gotoxy(columna,fila+14); printf("ELIGE UNA OPCION: ");
        gotoxy(columna+19,fila+14);scanf("%d",&op);
        switch(op){
            case 1:
                system("cls");
                if(!estaLlena(&l)){
                    printf("\n\n\t\t\t<< INSERTAR >>");
                    printf("\n\n\t\tINGRESA LOS SIGUIENTES DATOS: ");
                    fflush(stdin);
                    datos=Capturar(datos);
                    if(band == 1){
                        printf("\n\n\t\tINDICA POSICION A INSERTAR: \n\n\t\t1. INICIO\n\n\t\t2. FIN ");
                        scanf("%d",&x);
                        if(x == 1){
                            inserta(&datos, 0, &l);
                            printf("\n\n\t\t->DATOS CAPTURADOS");
                        }
                        else{
                            if(x == 2)
                                inserta(&datos, fin(&l), &l);
                        }
                    }
                    band=1;
                    printf("\n\n\t\t->DATOS CAPTURADOS");
                }
                else
                    imprimeError("\n\n\t\tLA LISTA ESTA LLENA");
                getch();
            break;
            case 2:
                system("cls");
                if(!estaVacia(&l)){
                    printf("\n\n\t\t<< ELIMINAR >>");
                    printf("\n\n\t\t1.PRIMERA POSICION\n\n\t\t2. ULTIMA POSICION\n\n\t\t3. APODO");
                    printf("\n\n\t\tELIGE TU OPCION: ");
                    scanf("%d",&opcion);
                    switch(opcion){
                        case 1:
                            suprime(0, &l);
                            printf("\n\n\t\t->ELEMENTO ELIMINADO");
                        break;
                        case 2:
                            suprime(fin(&l), &l);
                            printf("\n\n\t\t->ELEMENTO ELIMINADO");
                        break;
                        case 3:
                            printf("\n\n\t\tINGRESA EL APODO: ");
                            fflush(stdin);
                            gets(apodo);
                            strupr(apodo);
                            fflush(stdin);
                            p = CompApodo(&l,apodo);
                            if (p != -1){
                                suprime(p, &l);
                                printf("\n\n\t\t->ELEMENTO ELIMINADO");
                            }
                            else{
                                imprimeError("\n\n\t\tEL ELEMENTO NO EXISTE");
                            }
                        break;
                    }
                }
                else
                    imprimeError("\n\n\t\tLA LISTA ESTA VACIA");
                getch();
            break;
            case 3:
                system("cls");
                printf("\n\n\t\t<< MOSTRAR >>");
                if(!estaVacia(&l)){
                    imprimeLista(&l);
                }
                else{
                    imprimeError("\n\n\t\tLA LISTA ESTA VACIA");
                }
                getch();
            break;
            case 4:
                system("cls");
                printf("\n\n\t\t<< MODIFICAR >>");
                if(!estaVacia(&l)){
                    printf("\n\n\t\tINGRESA NOMBRE: ");
                    fflush(stdin);
                    gets(nombre);
                    strupr(nombre);
                    p=CompNombre(&l, nombre);
                    printf("\n\n\t\tMODIFICAR: \n\n\t\t1. DIRECCION\n\n\t\t2. APODO\n\n\t\t3. TELEFONO");
                    printf("\n\n\t\tELIGE TU OPCION: ");
                    scanf("%d",&opc);
                    switch(opc){
                        case 1:
                            printf("\n\n\t\tINGRESA LA NUEVA DIRECCION: ");
                            fflush(stdin);
                            gets(dir);
                            strupr(dir);
                            modifDir(&l, p, dir);
                            printf("\n\n\t\tCAMBIOS REALIZADOS");
                        break;
                        case 2:
                            printf("\n\n\t\tINGRESA EL NUEVO APODO: ");
                            fflush(stdin);
                            gets(apodo);
                            strupr(apodo);
                            modifApod(&l, p, apodo);
                            printf("\n\n\t\t->CAMBIOS REALIZADOS");
                        break;
                        case 3:
                            printf("\n\n\t\tINGRESA EL NUEVO TELEFONO: ");
                            scanf("%ld",&tel);
                            modifTel(&l, p, tel);
                            printf("\n\n\t\t->CAMBIOS REALIZADOS");
                        break;
                    }
                }
                else
                    imprimeError("\n\n\t\tLA LISTA ESTA VACIA");
                getch();
            break;
            case 5:
                do{
                    system("cls");
                    printf("\n\n\t\t<< CONSULTA >>");
                    printf("\n\n\t\t1. PRIMERO\t2. ANTERIOR\t3. SIGUIENTE\t4. ULTIMO\t5. SALIR ");
                    scanf("%d",&y);
                    switch(y){
                        case 1:
                            p=primero(&l);
                            imprimeElemento(recupera(p1,&l));
                        break;
                        case 2:
                            p=anterior(p,&l);
                            imprimeElemento(recupera(p,&l));
                        break;
                        case 3:
                            p=siguiente(p,&l);
                            imprimeElemento(recupera(p,&l));
                        break;
                        case 4:
                            p=ultimo(&l);
                            imprimeElemento(recupera(p,&l));
                        break;
                        default:
                            printf("OPCION INCORRECTA");
                    }
                }while(y != 4);
                getch();
            break;
            case 6:
                system("cls");
                printf("\n\n\t\tGRACIAS POR TU VISITA");
                getch();
            break;
            default:
                printf("\n\n\t\tOPCION INCORRECTA");
        }
    }while(op != 6);
    return 0;
}
