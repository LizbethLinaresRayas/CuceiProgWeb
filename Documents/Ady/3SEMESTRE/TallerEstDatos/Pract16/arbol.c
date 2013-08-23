#include <stdio.H>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "funcArbol.h"

int main(){

   system("COLOR f6");
   int N, OP;
   int b=0,band=0;
   POSICION TEMP;

   do{
      system("cls");
      printf("\n\n\t\t\t\tMENU");

      printf("\n\n\t\t1.INICIALIZAR");
      printf("\n\n\t\t2.INSERTAR");
      printf("\n\n\t\t3.BUSCAR UN ELEMENTO");
      printf("\n\n\t\t4.ELIMINAR UN ELEMENTO");
      printf("\n\n\t\t5.RECORRIDO PREORDEN");
      printf("\n\n\t\t6.RECORRIDO ENORDEN");
      printf("\n\n\t\t7.RECORRIDO POSTORDEN");
      printf("\n\n\t\t8.MOSTRAR");
      printf("\n\n\t\t0.SALIR");
      printf("\n\n\t\tELIGE TU OPCION: ");
      scanf("%d",&OP);
      switch(OP){
          case 1:
            system("cls");
            if(b == 0){
                printf("\n\n\t\tINICIALIZAR");
                INICIALIZA(&R);
                printf("\n\n\t\t...ARBOL INICIALIZADO...");
                b++;
            }
            else
                printf("\n\n\t\t...EL ARBOL YA HA SIDO INICIALIZADO...");
            getch();
          break;
          case 2:
            system("cls");
            if(b == 1){
                printf("\n\n\t\tINSERTAR UN ELEMENTO");
                printf("\n\n\t\tDAME EL ELEMENTO A INSERTAR: ");
                scanf("%d",& N);
                INSERTA(N,&R);
            }
            else
                printf("\n\n\t\t...EL ARBOL NO HA SIDO INICIALIZADO...");
            getch();
         break;
         case 3:
            system("cls");
            if(b == 1){
                printf("\n\n\t\tBUSCAR UN ELEMENTO");
                printf("\n\n\t\tDAME EL ELEMENTO: ");
                scanf("%d",& N);
                TEMP=BUSCAR(N,R);
                if(TEMP==NULL)
                   printf("\n\n\t\tELEMENTO NO ENCONTRADO");
                else{
                   printf("\n\n\t\t...ELEMENTO ENCONTRADO...");
                   printf("\n\n\t\tELEMENTO EN LA POSICION %p",TEMP);
                }
            }
            else
                printf("\n\n\t\t...EL ARBOL NO HA SIDO INICIALIZADO...");
            getch();
         break;
         case 4:
            system("cls");
            if(b == 1){
                printf("\n\n\t\tELIMINAR UN ELEMENTO");
                printf("\n\n\t\tDAME EL ELEMENTO: ");
                scanf ("%d",& N);
                ELIMINAR(N,&R);
            }
            else
                printf("\n\n\t\t...EL ARBOL NO HA SIDO INICIALIZADO...");
            getch();
         break;
         case 5:
            system("cls");
            if(b == 1){
                printf("\n\n\t\tRECORRIDO PREORDEN");
                printf("\n\n");
                PREORDEN(R);
            }
            else
                printf("\n\n\t\t...EL ARBOL NO HA SIDO INICIALIZADO...");
            getch();
         break;
         case 6:
            system("cls");
            if(b == 1){
                printf("\n\n\t\tRECORRIDO ENORDEN");
                printf("\n\n");
                ENORDEN(R);
            }
            else
                printf("\n\n\t\t...EL ARBOL NO HA SIDO INICIALIZADO...");
            getch();
         break;
         case 7:
            system("cls");
            if(b == 1){
                printf("\n\n\t\tRECORRIDO POSTORDEN");
                printf("\n\n");
                POSTORDEN(R);
            }
            else
                printf("\n\n\t\t...EL ARBOL NO HA SIDO INICIALIZADO...");
            getch();
         break;
         case 8:
            system("cls");
            if(b == 1){
                printf("\n\n\t\tMOSTRAR");
                printf("\n\n\t\tARBOL:\n");
                printf("\n\n");
                MOSTRAR(R);
            }
            else
                printf("\n\n\t\t...EL ARBOL NO HA SIDO INICIALIZADO...");
            getch();
         break;
      }
   } while(OP != 0);
   getch();
}
