/*Adriana Lizbeth Linares Rayas Cod. 210596378
  Seccion D-11 Taller de Estructura de archivos*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int fd,n,total;
    char dir;
    char cadena[12];
    printf("\n\nIntroduce un numero menor a 12: ");
    scanf("%d",&n);
    if(n < 12)
    {
        fd=open("c:\\Documents and Settings\\usuario\\Mis documentos\\archivo1.txt",2);
        if(fd > 0)
        {
            printf("\n\n\tArchivo:\n\n");
            while(total=read(fd,&cadena,n))
            {
                write(1,&cadena,total);
            }
            printf("\n\n");
        }
        else
            perror("error");
    }
    else
    {
        if(n == 12)
            printf("\nEl numero es igual a 12");
        else
            printf("\nEl numero es mayor a 12");
    }
    return 0;
}
