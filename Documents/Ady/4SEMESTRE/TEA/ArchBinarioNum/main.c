#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

void captura(int fd, double num)
{
    lseek(fd,0,2);
    write(fd,&num,sizeof(num));
}

void mostrar(int fd)
{
    double numero;

    lseek(fd,0,0);
    while(read(fd,&numero,sizeof(double)) == sizeof(double))
    {
        printf("\n\t%.2lf",numero);
    }
}

double suma(int fd)
{
    double numero, suma=0;

    lseek(fd,0,0);
    while(read(fd,&numero,sizeof(double)) == sizeof(double))
    {
        suma+=numero;
    }
    return suma;
}

int main()
{
    int fd,opc;
    double num;
    char op;

    fd=open("Archivo.num",O_CREAT|O_RDWR|O_BINARY,S_IRWXU);
    if(fd > 0)
    {
        do
        {
            system("cls");
            printf("\n\n\t\tMENU");
            printf("\n\n\t1. Capturar");
            printf("\n\n\t2. Mostar");
            printf("\n\n\t3. Suma");
            printf("\n\n\t4. Salir");
            printf("\n\n\tElige tu opcion: ");
            scanf("%d",&opc);
            switch(opc)
            {
                case 1:
                    system("cls");
                    printf("\n\n\tCaptura\n");
                    do
                    {
                        printf("\n\n\tIngresa un numero: ");
                        scanf("%lf",&num);
                        captura(fd,num);
                        printf("\n\n\tNumero Guardado");
                        printf("\n\n\tAgregar otro numero: s/n");
                        scanf("%c",&op);
                    }while(op == 's');
                    getch();
                break;
                case 2:
                    system("cls");
                    printf("\n\n\tMostrar\n");
                    mostrar(fd);
                    getch();
                break;
                case 3:
                    system("cls");
                    printf("\n\n\tSuma de numeros\n");
                    printf("\n\n\tTotal de la suma: %.2lf",suma(fd));
                    getch();
                break;
            }
        }while(opc != 4);
    }
    else
        perror("");
    close(fd);
    return 0;
}
