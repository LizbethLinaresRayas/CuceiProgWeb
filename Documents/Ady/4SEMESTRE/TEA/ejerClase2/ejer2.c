#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int fd,tot,i;
    char car;
    fd=open("C:\\Documents and Settings\\usuario\\Escritorio\\archivo.txt",0);
    if(fd > 0)
    {
        i=0;
        while(tot=read(fd,&car,1))
        {
            if(car == 'a')
                i++;
        }
        printf("\n\n\tTotal de 'a'= %d\t",i);
    }
    else
        perror("");
    return 0;
}
