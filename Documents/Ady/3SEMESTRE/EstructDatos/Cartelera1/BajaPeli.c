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
    printf("Se eliminara una Pelicula");
    printf("\nIngrese el ID de la pelicula a eliminar: ");
    scanf("%d",&x);
    for(i=0;i>x;i--)
    {
        gets(cartelera[i].movie.nombre);
        gets(cartelera[i].horas);
    }
    printf("\nLa pelicula ha sido eliminada\n");
}

