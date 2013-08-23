#include<stdio.h>
#include<conio.h>
#define x 30

main()
{
    char password[x];
    char usuario[x];
    int i,c;
    printf("Introduce nombre de usuario: ");
    scanf("%s",&usuario);
    printf("\nIngresa tu contrasena: ");
    i=0;
    while((c=_getch())!=13)
    {
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
    printf("\n%s",password);
}



