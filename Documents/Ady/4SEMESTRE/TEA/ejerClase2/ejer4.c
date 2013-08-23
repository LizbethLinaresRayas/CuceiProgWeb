#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int conex,i;
    char car,cadena[20];
    conex=open("C:\\users\\LINARES\\desktop\\archivo.txt",1);
    if(conex > 0)
    {
        lseek(conex,0,2);
        for(i=0; i<5; i++)
        {
            printf("\nCapture una palabra: ");
            gets(cadena);
            write(conex,cadena,strlen(cadena));
            write(conex,";",1);
        }
        lseek(conex,0,0);
        while((read(conex,&car,1)) > 0)
            write(1,&car,1);
        close(conex);
    }
    else
        perror("");
    return 0;
}
