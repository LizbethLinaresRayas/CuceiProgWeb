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
    int a,i,band=0,b=1,j,n;

    n=strlen(clave);
    i=0;
    while((band == 0) && (i <= n))
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

void Descencripta(char cadena[12],int fd)
{
    char cad[12],cad2[12],cadena3[12];
    int op,tot,total,conex1,i,j;

    tot=strlen(cadena);
    conex1=creat("archivoNvodes.txt",755);
    if(conex1 > 0)
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
            write(conex1,&cad2,total);
        }
    }
    else
        perror("");
}

int main()
{
    int op,x,fd,conex;
    char nomArc[12],clave[10];

    do
    {
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
            case 3:
                printf("\n\n\t\t--- DESCENCRIPTAR ARCHIVO ---");
                fd=open("C:\\Users\\LINARES\\Desktop\\Pract2\\archivoNvo.txt",2);
                if(fd > 0)
                {
                    mostrarArc(fd);
                    printf("\n\n\tIngresa una palabra de minimo 8 digitos,\n\tsin que ninguna letra sea repetida:\n\t");
                    fflush(stdin);
                    gets(clave);
                    x=evaluaCve(clave);
                    if(x == 0)
                    {
                        if(fd > 0)
                        {
                            Descencripta(clave,fd);
                            printf("\n\n\t\tEl Archivo ha sido Descencriptado");
                        }
                        else
                            perror("");
                    }
                    else
                        printf("\n\n\t\t...La palabra tiene letras repetidas...");
                }
                else
                    perror("");
            break;
            case 4:
                printf("\n\n\t\t--- SALIR ---");
                printf("\n\n\t... GRACIAS POR TU VISITA ...");
            break;
            default:
                printf("\n\n\t\t... OPCION INCORRECTA ...");
        }
    }while(op != 4);
    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <String.h>

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
    int a,i,band=0,j,n;

    n=strlen(clave);
    i=0;
    while((band == 0) && (i <= n))
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

void Encriptar(char cadena[12],int fd,int conex)
{
    char cad[12],cad2[12],cadena3[12];
    int tot,total,i,j;

    tot=strlen(cadena);
    if(fd > 0)
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

void Descencripta(char cadena[12],int fd,int conex)
{
    char cad[12],cad2[12],cadena3[12];
    int tot,total,i,j;

    tot=strlen(cadena);
    if(fd > 0)
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
    int op,x,fd,fd1,fd2,conex,conex1;
    char clave[10];

    conex=creat("cuentas.cif",755);
    conex1=creat("Des.cif",755);
    fd=open("C:\\users\\LINARES\\desktop\\cuentas.cta",2);
    fd1=open("C:\\Users\\LINARES\\Desktop\\Practica2\\cuentas.cif",2);
    fd2=open("C:\\Users\\LINARES\\Desktop\\Practica2\\Des.cif",2);

    do
    {
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
                if(fd > 0)
                    mostrarArc(fd);
                else
                    perror("");
            break;
            case 2:
                printf("\n\n\t\t--- ENCRIPTAR ARCHIVO ---");
                if(fd > 0)
                {
                    printf("\n\n\tIngresa una palabra de minimo 8 digitos,\n\tsin que ninguna letra sea repetida:\n\t");
                    fflush(stdin);
                    gets(clave);
                    x=evaluaCve(clave);
                    if(x == 0)
                    {
                        if(conex > 0)
                        {
                            if(fd1 > 0)
                            {
                                Encriptar(clave,fd,conex);
                                printf("\n\n\t\tEl Archivo ha sido Encriptado");
                            }
                            else
                                perror("");
                        }
                        else
                            perror("");
                    }
                    else
                        printf("\n\n\t\t...La palabra tiene letras repetidas...");
                }
                else
                    perror("");
            break;
            case 3:
                printf("\n\n\t\t--- DESCENCRIPTAR ARCHIVO ---");
                if(fd1 > 0)
                {
                    printf("\n\n\tIngresa una palabra de minimo 8 digitos,\n\tsin que ninguna letra sea repetida:\n\t");
                    fflush(stdin);
                    gets(clave);
                    x=evaluaCve(clave);
                    if(x == 0)
                    {
                        if(conex1 > 0)
                        {
                            if(fd2 > 0)
                            {
                                Descencripta(clave,fd1,conex1);
                                printf("\n\n\t\tEl Archivo ha sido Descencriptado");
                                mostrarArc(fd2);
                            }
                            else
                                perror("");
                        }
                        else
                            perror("");
                    }
                    else
                        printf("\n\n\t\t...La palabra tiene letras repetidas...");
                }
                else
                    perror("");
            break;
            case 4:
                printf("\n\n\t\t--- SALIR ---");
                printf("\n\n\t... GRACIAS POR TU VISITA ...");
            break;
            default:
                printf("\n\n\t\t... OPCION INCORRECTA ...");
        }
    }while(op != 4);
    return 0;
}
*/
