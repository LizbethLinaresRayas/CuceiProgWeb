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
    int i;
    for(i=0;i<30;i++)
    {
        printf("\nID: %d Nombre: %s",cartelera[i].movie.idPelicula,cartelera[i].movie.nombre);
        int j;
        for(j=0;j<10;j++)
            printf("Horarios: Hora: %s Sala %d ",cartelera[i].horas[j].hora,cartelera[i].horas[j].sala);
    }

}

