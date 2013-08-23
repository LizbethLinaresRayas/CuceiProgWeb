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
        int duracion;
        int idGenero;
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
    int i,n,pel;
    ("sys");
    printf("\t\t\tAlta de Pelicula\n");
    printf("Numero de Peliculas a Registrar: ");
    scanf("%d",&pel);
    printf("\nIngresa los siguientes datos: \n\n");
    for(i=0;i<pel;i++)
    {
        cartelera[i].movie.idPelicula=i+1;
        printf("ID Pelicula: %d\n",cartelera[i].movie.idPelicula);
        printf("Nombre de Pelicula: ");
        gets(cartelera[i].movie.nombre);
        printf("Nombre del Director: ");
        gets(cartelera[i].movie.director);
        printf("Nombre del Productor: ");
        gets(cartelera[i].movie.productor);
        printf("Clasificacion: ");
        gets(cartelera[i].movie.clasif);
        printf("Generos:\n01.drama 02.comedia 03.romance 04.suspenso");
        printf("Ingresa el Id de Genero");
        scanf("%d",&cartelera[i].movie.idGenero);
        printf("Duracion en minutos: ");
        scanf("%d",&cartelera[i].movie.duracion);
        int j=0,h=1;
        printf("Numero de horarios q tendra la Pelicula: ");
        scanf("%d",&n);
        while(j<n)
        {
            printf("Horario %d: \n",h);
            printf("Hora: ");
            scanf("%s",&cartelera[i].horas[j].hora);
            printf("Sala: ");
            scanf("%d",&cartelera[i].horas[j].sala);
            h++;
            j++;
        }
    }
    return 0;
    getch();
}

