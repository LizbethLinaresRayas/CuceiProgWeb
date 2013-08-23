#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void altaPelicula();
void altaHorario();
void bajaPeli();
void consultCartelera();
void consult_Peli();
void modifPelicula();

struct pelicula
    {
        char nombre[20];
        char director[35];
        char productor[35];
        char clasif[3];
        char genero;
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
    int op;
    printf("\n\t\t\tBienvnido Cinema CUCEI\n");
    do{
        printf("\n\t\t\tMenu Principal\n");
        printf("\n1.Alta de Pelicula");
        printf("\n2.Alta de Horario");
        printf("\n3.Baja Pelicula");
        printf("\n4.Consulta Cartelera");
        printf("\n5.Consulta Pelicula");
        printf("\n6.Modificar Pelicula");
        printf("\n7.Salir");
        printf("\nElige una opcion: ");
        scanf("%d",&op);
        switch(op)
        {
            case 1: altaPelicula();
                    break;
            case 2: altaHorario();
                    break;
            case 3: bajaPeli();
                    break;
            case 4: consultCartelera();
                    break;
            case 5: modifPelicula();
                    break;
            default: printf("Cinema CUCEI agradece su visita");
                    break;
        }
    }while(op!=6);
}

void altaPelicula()
{
    int i,n,pel;
    ("sys");
    printf("\t\t\t\nAlta de Pelicula\n");
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
        printf("\nIngresa el Id de Genero: ");
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
}

void altaHorario()
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

void bajaPeli()
{
    int i,x;
    printf("\nSe eliminara una Pelicula");
    printf("\nIngrese el ID de la pelicula a eliminar: ");
    scanf("%d",&x);
    for(i=0;i>x;i--)
    {
        gets(cartelera[i].movie.nombre);
        gets(cartelera[i].horas);
    }
    printf("\nLa pelicula ha sido eliminada\n");
}

void consultCartelera()
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

void consult_Peli()
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

void modifPelicula()
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
