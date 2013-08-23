#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*int main()
{
    int conex;
    conex=open("I:\\arc.txt",2);
    if(conex>0)
        printf("\n\tApertura exitosa\n");
    else
        perror("\n\tError\n");
    return 0;
}*/

int main()
{
    FILE *ap;
    ap=fopen("I:\\arc.txt","w+");
    if(ap != NULL)
        printf("\n\tCreacion exitosa\n");
    else
        perror("\n\tError\n");
    return 0;
}
