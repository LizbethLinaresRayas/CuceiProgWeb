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
    int izq=0,der,medio,valor,i,n;
    der=n-1;
    for(i=0;i<30;i++)
        printf("\nPelicula %s %d",cartelera[i].movie.nombre,cartelera[i].movie.idPelicula);
    printf("\nIngresa el ID de la Pelicula a Buscar: ");
    scanf("%d",valor);
    while(izq<=der)
    {
        medio=(izq+der)/2;
        if(valor == cartelera[medio].movie.idPelicula)
        {
            return medio;
        }
        else
        {
            if(valor > cartelera[medio].movie.idPelicula)
            {
                izq=medio+1;
            }
            else
            {
                der=medio-1;
            }
        }
    }
    return cartelera[i].movie,cartelera[i].horas;
}
