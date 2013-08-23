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
    register int i,j;
    int pivote,primero,ultimo;
    i=primero;
    j=ultimo;
    pivote=cartelera.movie.nombre[(primero+ultimo)/2];
    do
    {
        while(cartelera[i].movie.nombre<pivote)
        {
            i++;
        }
        while(cartelera[i].movie.nombre>pivote)
        {
            j--;
        }
        if(i<=j)
        {
            intercambia(&cartelera[i].movie.nombre,&cartelera[j].movie.nombre);
            i++;
            j--;
        }
    }while(i<=j);
    if(primero<j)
    {
        ordena(cartelera,primero,j);
    }
    if(ultimo>i)
    {
        ordena(cartelera,i,ultimo);
    }
}

void intercambia(int *valor1, int *valor2)
{
    if(valor1 != valor2)
    {
        int aux= *valor1;
        *valor1=*valor2;
        *valor2=aux;
    }
}
