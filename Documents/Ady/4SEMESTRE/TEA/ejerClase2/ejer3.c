#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int conex,tot;
    char car,nombre[10];
    printf("\n\tIngresa tu nombre: ");
    gets(nombre);
    tot=strlen(nombre);
    conex=open("C:\\users\\LINARES\\desktop\\archivo.txt",1);
    if(conex > 0)
    {
        lseek(conex,0,0);
        write(conex,nombre,tot);
    }
    else
        perror("");
    return 0;
}
