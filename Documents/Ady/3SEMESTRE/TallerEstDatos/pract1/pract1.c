/*Adriana Lizbeth Linares Rayas
  210596378 Lic. Informatica
  Taller de Estructura de Datos Secc. D.15*/

#include <stdio.h>
#include <conio.h>

void grados(){

     int grados;
     float result;
     printf("\nConversor de grados Centigrados a Fahrenheit");
     printf("\nIntroduce los grados Centigrados que deceas convertir: ");
     scanf("%d",&grados);
     result=1.8*grados+32;
     printf("%.2f grados Fahrenheit",result);
}

void factorial(){

     int num,fact,i;
     printf("\nFactorial de un numero");
     printf("\nIntroduce un numero: ");
     scanf("%d",&num);
     fact=num;
     for(i=1;i<num;i++)
          fact=fact*i;
     printf("\nEl factorial de %d es %d",num,fact);
}

void numeros(){
     int num1,num2,num3;
     printf("\nIntroduce 3 numeros: ");
     printf("\nNumero 1: ");
     scanf("%d",&num1);
     printf("\nNumero 2: ");
     scanf("%d",&num2);
     printf("\nNumero 3: ");
     scanf("%d",&num3);
     if(num1==num2){
          if(num1==num3)
               printf("\nLos tres numeros son iguales");
          else
               printf("\nEl numero 1 y 2 son iguales");
     }
     else{
         if(num2==num3)
             printf("\nEl numero 2 es igual al numero 3");
         else
             printf("\nLos tres numeros son diferentes");
     }

}

main(){
       int op;
       do{
           printf("\n\n\tMENU");
           printf("\n1.Convertir grados Centigrados a Fahrenheit");
           printf("\n2.Calcular el factorial de un numero N");
           printf("\n3.Comparar Numeros");
           printf("\n4.Salir");
           printf("\n\nElige una opcion: ");
           scanf("%d",&op);
           switch(op){
                case 1:
                     grados();
                break;
                case 2:
                     factorial();
                break;
                case 3:
                     numeros();
                break;
                default:
                        printf("Gracias por su visita");
           }
       }while(op!=4);
       return 0;
}







