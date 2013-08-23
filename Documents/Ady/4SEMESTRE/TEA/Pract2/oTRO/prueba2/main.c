#include <stdio.h>
#include <stdlib.h>

void mostrarArc(int fd)
{
    int total;
    char cadena[15];

    if(fd > 0)
    {
        printf("\n\n\t\t--- ARCHIVO---\n\n");
        while(total=read(fd,&cadena,1))
        {
            write(1,&cadena,total);
        }
        printf("\n\n");
    }
}

int evaluaCve(char clave[10])
{
    int a,i,band=0,b=1,j;

    i=0;
    while((band == 0) && (i<10))
    {
        a=clave[i];
        j=0;
        while((j<10) && (j != i))
        {
            if(a == clave[j])
                band=1;
            j++;
        }
        i++;
    }
    return band;
}

void Encriptar(char cadena[12],int fd)
{
    char cad[12],cad2[12],cadena3[12];
    int op,tot,total,conex,i,j;
    //printf("\n\tIngresa una palabra de almenos 8 digitos\n\ten la que ninguna letra sea repetida: ");
    //gets(cadena);
    tot=strlen(cadena);
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
}

int main()
{
    int op,x,fd;
    char nomArc[12],clave[10];
    printf("\n\n\t\tMENU");
    printf("\n\n\t1. MOSTRAR ARCHIVO");
    printf("\n\n\t2. ENCRIPTAR ARCHIVO");
    printf("\n\n\t3. DESCIFRAR ARCHIVO");
    printf("\n\n\t4. SALIR");
    printf("\n\n\t-Elige una opcion: ");
    scanf("%d",&op);
    switch(op)
    {
        case 1:
            printf("\n\n\t--- MOSTRAR ARCHIVO ---");
            fd=open("C:\\users\\LINARES\\desktop\\archivo.txt",2);
            mostrarArc(fd);
        break;
        case 2:
            printf("\n\n\t\t--- ENCRIPTAR ARCHIVO ---");
            printf("\n\n\tIngresa una palabra de minimo 8 digitos,\n\tsin que ninguna letra sea repetida:\n\t");
            fflush(stdin);
            gets(clave);
            x=evaluaCve(clave);
            if(x == 0)
            {
                fd=open("C:\\Users\\LINARES\\desktop\\archivo.txt",2);
                if(fd > 0)
                {
                    Encriptar(clave,fd);
                    printf("\n\n\t\tEl Archivo ha sido Encriptado");
                }
                else
                    perror("");
            }
            else
                printf("\n\n\t\t...La palabra tiene letras repetidas...");
        break;
    }
    return 0;
}
