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
        int genero[5];
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
    int i,agr_ho,n;
    printf("Agregar horario a Pelicula");
    for(i=0;i<30;i++)
        printf("\nPeliculas: ID Pelicula: %d Nombre Pelicula: %s",cartelera[i].movie.idPelicula,cartelera[i].movie.nombre);
    printf("\nIngrese el ID de la pelicula a la cual se le agregara un horario: ");
    scanf("%d",&agr_ho);
    printf("Pelicula a modificar: %d %s",cartelera[i].movie.idPelicula,cartelera[i].movie.nombre);
    if(agr_ho=cartelera[i].movie.idPelicula)
    {
        printf("Numero de horarios a agregar");
        scanf("%d",&n);
        int j;
        for(j=0;j<n;j++)
        {
            printf("Ingresa horario: ");
            gets(cartelera[j].horas[j].hora);
            printf("Ingresa la sala:");
            scanf("%s",&cartelera[j].horas[j].sala);
        }
    }
    else
        printf("\nLa pelicula no existe");
}
