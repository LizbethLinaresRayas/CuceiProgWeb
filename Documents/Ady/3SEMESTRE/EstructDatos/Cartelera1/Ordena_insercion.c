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

    register int i,j,aux,n;
    for(i=1;i<n;i++)
    {
        aux=cartelera[i].movie.nombre;
        j=i-1;
        while(j>=0 && aux<cartelera[j].movie.nombre)
        {
            cartelera[j+1]=cartelera[j];
            j--;
        }
        cartelera[j].movie.nombre=aux;
    }
}


