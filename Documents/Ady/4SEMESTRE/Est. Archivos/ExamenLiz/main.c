//Adriana Lizbeth Linares Rayas
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int fd,cont=0,aux=0,tot=0;
    char car,car1,car2,car3;

    fd=open("archivo.exa",2);
    if(fd > 0)
    {
        lseek(fd,0,0);
        while(read(fd,&car,1))
        {
            cont++;
        }
        aux=cont/2;
        tot=cont;
        cont=0;
        lseek(fd,0,0);
        while(read(fd,&car,1))
        {
            cont++;
            if(cont == 1)
                car1=car;
            else
            {
                if(cont == aux)
                    car2=car;
                else
                {
                    if(cont == tot)
                        car3=car;
                }
            }
        }
        lseek(fd,0,0);
        write(fd,&car2,1);
        lseek(fd,(aux-1),0);
        write(fd,&car3,1);
        lseek(fd,(tot-1),0);
        write(fd,&car1,1);
        printf("\n\n\tCambios realizados");
    }
    printf("\n\t");
    lseek(fd,0,0);
    while(read(fd,&car,1))
        printf("%c",car);

    return 0;
}
