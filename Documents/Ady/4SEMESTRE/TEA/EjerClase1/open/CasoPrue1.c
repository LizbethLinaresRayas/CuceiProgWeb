#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int conex;
    conex=open("C:\\Users\\LINARES\\Desktop\\archivo.txt",2);
    if(conex>0)
        printf("\n\tApertura exitosa\n");
    else
        perror("\n\tError\n");
    return 0;
}
