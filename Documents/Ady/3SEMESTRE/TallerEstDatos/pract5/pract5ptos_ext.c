/*Adriana Lizbeth Linares Rayas
Cod. 210596378 Lic. Informatica*/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#define x 15

void passwd(char password[],char usuario[]){
    int i,c;
    printf("\n\n\t\tIngresa Nombre de Usuario: ");
    scanf("%s",&usuario);
    printf("\n\n\t\tIngresa Contrasena: ");
    i=0;
    while((c=_getch())!=13){
        if(c==8){
            password[i]='\0';
            i--;
            printf("\b\b");
        }
        else
        {
            printf("*");
            password[i]=c;
            i++;
        }
    }
    password[i]='\0';
}
