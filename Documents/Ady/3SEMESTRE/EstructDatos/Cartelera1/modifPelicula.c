#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pelicula
    {
        char nombre[20];
        char director[35];
        char productor[35];
        char clasif[3];
        char genero;
        int duracion;
        int Idgenero;
        int idPelicula;
    };

    struct hora_sala
    {
        char hora[15];
        int sala;
    };

    struct horario
    {
        struct pelicula movie;
        struct hora_sala horas[10];
    }cartelera[30];

main()
{
    int i,x;
    printf("\t\tModificar Pelicula\n");
    printf("Ingrese el ID de Pelicula a modificar");
    scanf("%d",&x);
    if(x=cartelera[i].movie.idPelicula)
    {
        printf("Ingrese los Nuevos Datos");
        printf("Nombre de Pelicula:");
        gets(cartelera[i].movie.nombre);
        printf("Nombre del Director: ");
        gets(cartelera[i].movie.director);
        printf("Nombre del Productor: ");
        gets(cartelera[i].movie.productor);
        printf("Clasificacion: ");
        gets(cartelera[i].movie.clasif);
        printf("Duracion en segundos: ");
        scanf("%d",&cartelera[i].movie.duracion);
        printf("Elige el genero: ");
        scanf("%d",&cartelera[i].movie.genero);
    }
    else
        printf("La pelicula no existe");
}
