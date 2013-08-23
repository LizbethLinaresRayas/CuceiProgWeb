#include <stdio.h>
#include <conio.h>
#include <string.h>
main()
{
    int i;
    struct domicilio{
        char calle[20];
        char col[15];
        char mun[3];
        int num_ext;
        int num_int;
        int cp;
    };
    struct veterinaria{
        char animal[8];
        char nombre[10];
        char duenio[35];
        char raza[10];
        int edad;
        struct domicilio dom;
    }animales[50];

    for(i=0;i<50;i++)
    {
        printf("Introduce los siguientes datos del animal:\n");
        printf("Tipo de animal: ");
        gets(animales[i].animal);
        printf("Nombre: ");
        gets(animales[i].nombre);
        printf("Edad en meses: ");
        scanf("%d",&animales[i].edad);
        printf("Raza: ");
        gets(animales[i].raza);
        printf("Datos de dueño: ");
        printf("Nombre: ");
        gets(animales[i].duenio);
        printf("Domicilio: ");
        printf("Calle: ");
        gets(animales[i].dom.calle);
        printf("Numero interior y exterior: ");
        scanf("%d %d",&animales[i].dom.num_int,&animales[i].dom.num_ext);
        printf("Colonia: ");
        gets(animales[i].dom.col);
        printf("Municipio: ");
        gets(animales[i].dom.mun);
        printf("Codigo Postal: ");
        scanf("%d",&animales[i].dom.cp);
        printf("Los datos son los siguientes: ");
        printf("Datos del animal: ");
        printf("Tipo: %s",animales[i].animal);
        printf("Nombre: %s",animales[i].nombre);
        printf("Edad: %d meses",animales[i].edad);
        printf("Raza: %s",animales[i].raza);
        printf("Datos de dueño: ");
        printf("Nombre: %s",animales[i].duenio);
        printf("Domicilio:\nCalle: %s",animales[i].dom.calle);
        printf("Numero interior: %d y exterior: %d",animales[i].dom.num_int,animales[i].dom.num_ext);
        printf("Colonia: %s",animales[i].dom.col);
        printf("Domicilio:\nCalle: %s",animales[i].dom.col);
        printf("Municipio: %s",animales[i].dom.mun);
    }
    getch();
}
