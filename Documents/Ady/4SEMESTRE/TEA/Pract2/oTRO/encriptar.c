#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    char cadena[12],cad[12],cad2[12],cadena3[12];
    int op,tot,fd,total,conex,i,j;
    printf("\n\tIngresa una palabra de almenos 8 digitos\n\ten la que ninguna letra sea repetida: ");
    gets(cadena);
    tot=strlen(cadena);
    fd=open("C:\\Users\\LINARES\\desktop\\archivo.txt",2);
    if(fd > 0)
    {
        conex=creat("archivoNvo.txt",755);
        if(conex > 0)
        {
            while(total=read(fd,&cad,tot))
            {
                strcpy(cadena3,cad);
                i=tot-1;
                j=0;
                while((i < tot) && (i >= 0))
                {
                    cad2[j]=cadena3[i];
                    i--;
                    j++;
                }
                write(conex,&cad2,total);
            }
        }
        else
            perror("");



    }*/
    return 0;
}
