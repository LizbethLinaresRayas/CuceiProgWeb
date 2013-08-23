#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void alta_peli(pelicula *movie, hora_sala *horas[]);
void alta_horarioPeli(pelicula *movie,hora_sala *horas[]);
void baja_peli(pelicula *movie,hora_sala *horas[]);
void baja_hora(pelicula *movie,hora_sala *horas[]);
int mod_pelicula(pelicula *movie);
int consulta_peli(pelicula *movie);
int consulta_hora(pelicula *movie,hora_sala *horas[]);
void ordena(pelicula *movie);
int ordena_insercion(pelicula *movie,int n);
int ordena_quicksore(pelicula *movie,int primero,int ultimo);
void intercambia(int *valor1, int *valor2);
main()
{
    int op;

    typedef struct pelicula
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

    typedef struct hora_sala
    {
        char hora;
        int sala;
    };

    typedef struct horario
    {
        struct pelicula movie;
        struct hora_sala horas[10];
    }cartelera[30];

    printf("Bienvenidos Cinema CUCEI");
    printf("Cartelera");
    printf("MENU: ");
    printf("1.Alta Pelicula\n2.Alta Horario a Pelicula ya Existente\n3.Baja Pelicula\n4.Baja Horario a Pelicula ya Existente\n5.Modificar Pelicula\6.Consultar pelicula\n7.Consultar Cartelera\n8.Ordenar los Elementos\n9.Salir");
    scanf("%d",&op);
    switch(op)
    {
        case 1: alta_peli(pelicula *movie,hora_sala *horas[]);
        break;
        case 2: alta_horarioPeli(pelicula *movie,hora_sala *horas[]);
        break;
        case 3: baja_peli(pelicula *movie,hora_sala *horas[]);
        break;
        case 4: baja_hora(pelicula *movie,hora_sala *horas[]);
        break;
        case 5: mod_pelicula(pelicula *movie);
        break;
        case 6: consulta_peli(pelicula *movie);
        break;
        case 7: consulta_hora(pelicula *movie,hora_sala *horas[]);
        break;
        case 8: ordena(pelicula *movie);
        break;
        case 9: printf("Cinema CUCEI agradece tu visita");
        break;
        default: printf("La opcion no fue encontrada");
    }
    return 0;
    getch();
}

void alta_peli(pelicula movie *pel)
{
    int i,n;
    printf("Alta de Pelicula");
    for(i=0;i<30;i++)
    {
        cartelera[i].movie.idPelicula=i+1;
        printf("ID Pelicula: %d",cartelera[i].movie.idPelicula);
        printf("Ingresa los siguientes datos: ");
        printf("Nombre de Pelicula:");
        gets(cartelera[i]->movie->nombre);
        printf("Nombre del Director: ");
        gets(cartelera[i]->movie->director);
        printf("Nombre del Productor: ");
        gets(cartelera[i]->movie->productor);
        printf("Clasificacion: ");
        gets(cartelera[i]->movie->clasif);
        printf("Duracion en segundos: ");
        scanf("%d",&cartelera[i]->movie->duracion);
        printf("Elige el genero: ");
        scanf("%d",&cartelera[i]->movie->genero);
        printf("Ingresa el numero de horarios que tiene la pelicula");
        scanf("%d",&n);
        int j=0,h=1;
        printf("Numero de horarios q tendra la Pelicula: ");
        scanf("%d",&n);
        for(j=0;j<n;j++)
        {
            printf("Horario %d: \n",h);
            printf("Hora: ");
            scanf("%s",&cartelera[i]->horas[j]->hora);
            printf("Sala: ");
            scanf("%d",&cartelera[i]->horas[j]->sala);
            h++;
            j++;
        }
    }
}

void alta_horarioPeli(pelicula *movie,hora_sala *horas[])
{
    int i,a,n;
    printf("Agregar horario a Pelicula");
    for(i=0;i<30;i++)
        printf("Peliculas: ID Pelicula: %d Nombre Pelicula: %s",cartelera[i].movie.idPelicula,cartelera[i].movie.nombre);
    printf("Ingrese el ID de la pelicula a la cual se le agregara un horario:");
    scanf("%d",&a);
    printf("Pelicula a modificar: %d %s",cartelera[i].movie.idPelicula,cartelera[i].movie.nombre);
    if(a=cartelera[i].movie.idPelicula)
    {
        printf("Numero de horarios a agregar");
        scanf("%d",&n);
        for(j=0;j<n;j++)
        {
            printf("Ingresa horario: ");
            gets(cartelera[j].horas[j].hora);
            printf("Ingresa la sala:");
            scanf("%s",&cartelera[j].horas[j].sala);
        }
    }
    else
        printf("La pelicula no existe");
}

void baja_peli(pelicula *movie,hora_sala *horas[])
{
    int i,x;
    printf("Se eliminara una Pelicula");
    printf("Ingrese el ID de la pelicula a eliminar");
    scanf("%d",&x);
    for(i=0;i>x;i++)
    {
        i--;
        gets(cartelera[i]->movie);
        gets(cartelera[i]->horas[]);
    }
}

void baja_hora(pelicula *movie,hora_sala *horas[])
{
    int i,x;
    printf("Se eliminara el horario de una Pelicula");
    printf("Ingrese el ID de la pelicula a eliminar");
    scanf("%d",&x);
    for(i=0;i>x;i++)
    {
        i--;
        gets(cartelera[i]->horas);
    }
}

int mod_pelicula(pelicula *movie)
{
    int i,x;
    printf("Modificar Pelicula");
    printf("Seleccione el ID de Pelicula a modificar");
    scanf("%d",&x);
    if(x=cartelera[i]->movie->idPelicula)
    {
        printf("Ingrese los Nuevos Datos");
        printf("Nombre de Pelicula:");
        gets(cartelera[i]->movie->nombre);
        printf("Nombre del Director: ");
        gets(cartelera[i]->movie->director);
        printf("Nombre del Productor: ");
        gets(cartelera[i]->movie->productor);
        printf("Clasificacion: ");
        gets(cartelera[i]->movie->clasif);
        printf("Duracion en segundos: ");
        scanf("%d",&cartelera[i]->movie->duracion);
        printf("Elige el genero: ");
        scanf("%d",&cartelera[i]->movie->genero);
    }
    else
        printf("La pelicula no existe");
}

int consulta_peli(cartelera[],int valor)
{
    int izq=0,der,medio,i,n;
    der=n-1;
    for(i=0;i<30;i++)
        printf("Pelicula %d %s",cartelera[i].movie.nombre,cartelera[i].movie.idPelicula);
    printf("Ingresa el ID de la Pelicula");
    scanf("%d",valor)
    while(izq<=der)
    {
        medio=(izq+der)/2;
        if(valor==cartelera[medio])
        {
            return medio;
        }
        else
        {
            if(valor>cartelera[medio])
            {
                izq=medio+1;
            }
            else
            {
                der=medio-1;
            }
        }
    }
    return cartelera[i];
}

}

int consulta_horapelicula *movie,hora_sala *horas[])
{
    int i;
    for(i=0;i<30;i++)
    {
        printf("ID: %d Nombre: %s",cartelera[i].movie.idPelicula,cartelera[i].movie.nombre);
        for(i=0;i<10;i++)
            printf("Horarios: %s",cartelera[i].horas.hora,cartelera[i].horas.sala);
    }
void ordena(pelicula *movie)
{
    int x;
    printf("1.Metodo Insertar\n2.Metodo Rapido");
    printf("Elige un metodo de Ordenacion: ");
    scanf("%d",&x);
    if(x==1)
        ordena_insercion(struct pelicula movie,int n);
    else
        ordena_quicksore(struct pelicula movie,int primero,int ultimo);
}

int ordena_insercion(pelicula *movie,int n)
{
    register int i,j,aux;
    for(i=1;i<n;i++)
    {
        aux=cartelera[i];
        j=i-1;
        while(j>=0 && aux<cartelera[j])
        {
            cartelera[j+1]=cartelera[j];
            j--;
        }
        cartelera[j+1]=aux;
    }

int ordena_quicksore(pelicula *movie,int primero,int ultimo)
{
    register int i,j;
    int pivote;
    i=primero;
    j=ultimo;
    pivote=cartelera[(primero+ultimo)/2];
    do
    {
        while(cartelera[i]<pivote)
        {
            i++;
        }
        while(cartelera[i]>pivote)
        {
            j--;
        }
        if(i<=j)
        {
            intercambia(&cartelera[i],&cartelera[j]);
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


