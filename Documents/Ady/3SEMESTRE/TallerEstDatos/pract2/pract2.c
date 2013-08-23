/*Practica 2
Adriana Lizbeth Linares Rayas
Cod. 210596378 Lic. Informatica
Taller de Estructura de Datos Secc. D-15*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <conio2.h>
#define n 4

void captura(int matriz[n][n])
{
    int i,j;
    printf("\n\nInserta un numero para la posicion");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("\n\n\t%d,%d: ",i,j);
            scanf("%d",&matriz[i][j]);
        }
    }
    printf("\n   \"Se han capturado los datos en la matriz\"");
}

void imprime(int matriz[n][n])
{
    int i,j;
    printf("\n** Valores de la Matriz **\n\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("%d\t",matriz[i][j]);
        }
        printf("\n");
    }
}


void transpuesta(int matriz[n][n])
{
    int i,j;
    printf("-->Matriz transpuesta:\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("%d\t",matriz[j][i]);
        }
        printf("\n");
    }
}

void imprimetrans(int matriz[n][n])
{
    int i,j,k,m;
    printf("\n\n\nMatriz original:\n\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("%d\t",matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n\nMatriz transpuesta:\n\n");
    for(k=0;k<n;k++){
        for(m=0;m<n;m++){
            printf("%d\t",matriz[m][k]);
        }
        printf("\n");
    }
}

main()
{
    textbackground(BLUE);
    textcolor(WHITE);
    int matriz[n][n],op,band;
    printf("\n\t ** Matriz 4X4 **\n");
    do{
        printf("\n\n\t  --> MENU <--\n");
        printf("\n\t1. Capturar Valores\n");
        printf("\n\t2. Mostrar Valores\n");
        printf("\n\t3. Transpuesta\n");
        printf("\n\t4. Salir\n");
        printf("\n-->Elige una opcion: ");
        scanf("%d",&op);
        switch(op){
            case 1:
                band=1;
                printf("\n\t---> Captura de Datos\n");
                captura(matriz);
            break;
            case 2:
                printf("\n\t---> Mostrar Datos\n");
                if(band==1)
                    imprime(matriz);
                else
                    if(band==2)
                      imprimetrans(matriz);
                    else
                        printf("\n   \"No se han Capturado Datos\"");
            break;
            case 3:
                if(band==1)
                {
                    printf("\n\n\t---> Transpuesta de una Matriz\n");
                    transpuesta(matriz);
                }
                else
                    printf("\n   \"No se han Capturado Datos\"");
                band=2;
            break;
            case 4:
                printf("\n   \"Gracias por Utilizar el Programa\"");
            break;
            default:
                printf("\n   \"Opcion Incorrecta\"");
        }
    }while(op!=4);
    getch();
    return 0;
}
