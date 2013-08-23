#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <String.h>

void mostrarArch(int fd)
{
    char car;
    printf("\n\n\n");
    lseek(fd,0,0);
    while(read(fd,&car,1))
    {
        printf("%c",car);
    }
}

void encripta(int fd,int fd1,char clave[8])
{
    int tot,cont,i,j,k,z=8;
    char car,cad[8],cadena[8];

    for(i=0; i<z; i++)
    {
        cad[i]='\0';
        cadena[i]='\0';
    }

    tot=strlen(clave);
    lseek(fd,0,0);
    while(read(fd,cad,tot))
    {
        for(i=0; i<tot; i++)
        {
            car=clave[i];
            cont=0;
            for(j=0; j<tot; j++)
            {
                if(car > clave[j])
                    cont++;
            }
            cadena[cont]=cad[i];
        }
        k=strlen(cadena);
        write(fd1,cadena,k);
        for(i=0; i<tot; i++)
            cad[i]=32;
    }
}

void descifra(int fd1,int fd2,char clave[8])
{
    int tot,cont,i,j,k,z=8;
    char car,cad[6],cadena[6];

    for(i=0; i<z; i++)
    {
        cad[i]='\0';
        cadena[i]='\0';
    }

    tot=strlen(clave);
    lseek(fd1,0,0);
    while(read(fd1,cad,tot))
    {
        for(i=0; i<tot; i++)
        {
            car=clave[i];
            cont=0;
            for(j=0; j<tot; j++)
            {
                if(car > clave[j])
                    cont++;
            }
            cadena[i]=cad[cont];
        }
        k=strlen(cadena);
        write(fd2,cadena,k);

    }
}

int evaluaCve(char clave[8])
{
    int a,i,band=0,j,n;

    n=strlen(clave);
    i=0;
    while((band == 0) && (i <= n))
    {
        a=clave[i];
        j=0;
        while((j<n) && (j != i))
        {
            if(a == clave[j])
                band=1;
            j++;
        }
        i++;
    }
    return band;
}

int main()
{
    int fd,fd1,fd2,conex,conex1,opc,op,band=0;
    char clave[8];

    fd=open("cuentas.cta",2);
    if(fd > 0)
    {
        do
        {
            system("cls");
            printf("\n\n\t\t<< MENU >>\n");
            printf("\n\n\t1. Mostrar Archivo");
            printf("\n\n\t2. Encriptar Archivo");
            printf("\n\n\t3. Descifrar Archivo");
            printf("\n\n\t4. Salir");
            printf("\n\n\tElige una opcion: ");
            scanf(  "%d",&opc);
            switch(opc)
            {
                case 1:
                    do
                    {
                        system("cls");
                        printf("\n\n\t\t<< Mostrar Archivo >>\n");
                        printf("\n\n\t\t1. Archivo Original");
                        printf("\n\n\t\t2. Archivo Encriptado");
                        printf("\n\n\t\t3. Regresar");
                        printf("\n\n\t\tElige una opcion: ");
                        scanf("%d",&op);
                        switch(op)
                        {
                            case 1:
                                system("cls");
                                printf("\n\n\t\t<< Archivo Original >>\n");
                                mostrarArch(fd);
                                getch();
                            break;
                            case 2:
                                system("cls");
                                printf("\n\n\t\t<< Archivo Encriptado >>\n");
                                if(band == 1)
                                {
                                    if(fd1 > 0)
                                        mostrarArch(fd1);
                                    else
                                        perror("");
                                }
                                else
                                    printf("\n\n\t\t... No se ha encriptado el archivo ...");
                                getch();
                            break;
                            case 3:
                                system("cls");
                                printf("\n\n\t\t... Regresar Menu Principal ...\n");
                                getch();
                            break;
                            default:
                                system("cls");
                                printf("\n\n\t\t... Opcion Incorrecta ...\n");
                                getch();
                        }
                        getch();
                    }while(op != 3);
                break;
                case 2:
                    system("cls");
                    printf("\n\n\t\t<< Encriptar Archivo >>\n");
                    conex=creat("archivo.cif",755);
                    if(conex > 0)
                    {
                        fd1=open("archivo.cif",2);
                        if(fd1 > 0)
                        {
                            printf("\n\n\t\tIngresa la palabra clave: ");
                            fflush(stdin);
                            gets(clave);
                            if(evaluaCve(clave) == 0)
                            {
                                encripta(fd,fd1,clave);
                                band=1;
                                printf("\n\n\t\t... El archivo ha sido Encriptado ...");
                            }
                            else
                                printf("\n\n\t\t... La clave tiene letras repetidas ...");
                        }
                        else
                            perror("");
                    }
                    else
                        perror("");
                    getch();
                break;
                case 3:
                    system("cls");
                    printf("\n\n\t\t<< Descifrar Archivo >>\n");
                    if(fd1 > 0)
                    {
                        conex1=creat("Des.cif",755);
                        if(conex1 > 0)
                        {
                            fd2=open("Des.cif",2);
                            if(fd2 > 0)
                            {
                                printf("\n\n\t\tIngresa la palabra clave: ");
                                fflush(stdin);
                                gets(clave);
                                if(evaluaCve(clave) == 0)
                                {
                                    descifra(fd1,fd2,clave);
                                    mostrarArch(fd2);
                                }
                                else
                                    printf("\n\n\t\t... La clave tiene letras repetidas ...");
                            }
                            else
                                perror("");
                        }
                        else
                            perror("");
                    }
                    else
                        perror("");
                    getch();
                break;
                case 4:
                    system("cls");
                    printf("\n\n\t\t... Gracias por tu visita ...\n");
                    getch();
                break;
                default:
                    system("cls");
                    printf("\n\n\t\t... Opcion Incorrecta ...\n");
                    getch();
            }
        }while(opc != 4);
    }
    else
        perror("");
    close(fd);
    close(fd1);
    close(fd2);
    return 0;
}
