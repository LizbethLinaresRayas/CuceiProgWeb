#include<stdio.h>
#include<conio.h>
#define x 30

main()
{
    char password[x];
    int i,c;
    printf("\nIngresa tu contrasena: ");
    while((c=_getch())!=13) //equivalente a '\r'
    {
        if(c==8){ //   si se tecleo backspace..
            password[i]='\0';//Corto el último caracter que se tecleó
            i--;//Decremento hacia el caracter anterior
            printf("\b \b");
        }
        else
        {
            printf("*");
            password[i]=c;
            i++;
        }
    }
    password[i]='\0';
    printf("%s\n",password);
}



