#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <String.h>
#include <time.h>
typedef int logico;

typedef enum{
    domingo,
    lunes,
    martes,
    miercoles,
    jueves,
    viernes,
    sabado
}Dias;

typedef struct{
    int dia;
    int mes;
    int year;
    Dias dia_sem;
    int hora;
    int min;
    int sec;
}Fecha;

typedef struct
{
    Fecha fecha;
    int codigo;
    char nombre[10];
    float precio;
}Producto;

typedef struct
{
    int cont;
    int cod;
}Indice;

typedef struct nodo
{
    Indice indice;
    struct nodo *izq,*der;
}Nodo;

typedef Nodo *posicion;
posicion R;
Nodo **RR;

Fecha capturaFecha(){
    Fecha fecha;
    time_t segundos;
    struct tm *fecha_sistem;
    segundos = time(NULL);
    fecha_sistem = localtime(&segundos);
    system("Cls");
    fecha.dia = fecha_sistem->tm_mday;
    fecha.mes = ++ fecha_sistem->tm_mon;
    fecha.year = 1900 + fecha_sistem->tm_year;
    fecha.dia_sem = fecha_sistem->tm_wday;
    fecha.hora = fecha_sistem->tm_hour;
    fecha.min = fecha_sistem->tm_min;
    fecha.sec = fecha_sistem->tm_sec;
    return fecha;
}

void inicializa(posicion *R2)
{
    *R2=NULL;
}

void inserta(Indice ind,posicion *R2){
    if(*R2 == NULL)
    {
        *R2=(Nodo*)malloc(sizeof(Nodo));
        (*R2)->indice=ind;
        (*R2)->izq=NULL;
        (*R2)->der=NULL;
    }
    else
    {
        if(ind.cod > (*R2)->indice.cod)
            inserta(ind,&((*R2)->der));
        else
            if(ind.cod < (*R2)->indice.cod)
                inserta(ind,&(*R2)->izq);
            else
                printf("ELEMENTO DUPLICADO");
    }
}

/*int busquedaBinaria(int fd,int n,int cod)
{
    int menor=0,mayor=cont-1,medio,auxcod;
    lseek(fd,0,2);
    while(menor <= mayor)
    {
        medio=(menor+mayor)/2;
        if(cod == auxcod)
        {
            return medio;
        }
        else
        {
            if(cod > auxcod)
            {
                menor=medio+1;
            }
            else
            {
                mayor=medio-1;
            }
        }
    }
    return -1;
}*/

void imprime(posicion Raiz)
{
    if(Raiz != NULL)
    {
        imprime(Raiz->izq);
        printf("%d\n",Raiz->indice.cont);
        printf("%d\n",Raiz->indice.cod);
        imprime(Raiz->der);
    }
}

cargaArbol(int fd,int fd1)
{
    Producto prod;
    Indice ind;
    int cont=0;

    inicializa(&R);
    lseek(fd,0,2);
    while(read(fd,&prod,sizeof(prod)) == sizeof(prod))
    {
        /*ind.cod=prod.codigo;
        ind.cont=cont;
        cont++;
        inserta(ind,&R);
        imprime(R);*/
        printf("%d",prod.codigo);
        printf("%s",prod.nombre);
        printf("%.2f",prod.precio);
    }
}



int main()
{
    int opc,fd,conex,fd1;
    Producto prod;


    fd=open("Productos.depend",O_CREAT|O_RDWR|O_BINARY,S_IRWXU);
    fd1=open("Indice.depend",O_CREAT|O_RDWR|O_BINARY,S_IRWXU);
    if(fd > 0)
    {
        do
        {
            system("cls");
            printf("\n\n\t\t<< SUCURSAL >>");
            printf("\n\n\t1. Captura de Productos");
            printf("\n\n\t2. Captura de Existencia Fisica e Inventario");
            printf("\n\n\t3. Captura de Faltantes de la Semana por cada Producto");
            printf("\n\n\t4. Consulta de Lista de Faltantes por Semana");
            printf("\n\n\t5. Crear Archivo de Faltantes Semanal y Enviar");
            printf("\n\n\t6. Salir");
            printf("\n\n\t->Elige una Opcion: ");
            scanf("%d",&opc);
            switch(opc)
            {
                case 1:
                    system("cls");
                    printf("\n\n\t<< CAPTURA DE PRODUCTOS >>");
                    printf("\n\n\tIngresa los siguientes datos del Producto:");
                    prod.fecha=capturaFecha();
                    printf("\nFecha: %d/%d/%d  Hora: %d:%d:%d",prod.fecha.dia,prod.fecha.mes,prod.fecha.year,
                        prod.fecha.hora,prod.fecha.min,prod.fecha.sec);
                    printf("\n\n\tCodigo: ");
                    scanf("%d",&prod.codigo);
                    printf("\n\n\tNombre: ");
                    fflush(stdin);
                    gets(prod.nombre);
                    strupr(prod.nombre);
                    printf("\n\n\tPrecio: ");
                    scanf("%f",&prod.precio);
                    lseek(fd,0,2);
                    write(fd,&prod,sizeof(prod));
                    printf("\n\n\t... Los Datos han sido Guardados ...");
                    getch();
                break;
                case 2:
                    system("cls");
                    printf("\n\n\t<< CAPTURA DE EXISTENCIA FISICA E INVENTARIO >>");
                    if(fd1 > 0)
                        cargaArbol(fd,fd1);
                    getch();
                break;
                case 3:
                    system("cls");
                    printf("\n\n\t<< CAPTURA DE FALTANTES DE LA SEMANA POR CADA PRODUCTO >>");
                    getch();
                break;
                case 4:
                    system("cls");
                    printf("\n\n\t<< CONSULTA DE LISTA DE FALTANTES POR SEMANA >>");
                    getch();
                break;
                case 5:
                    system("cls");
                    printf("\n\n\t<< CREAR ARCHIVO DE FALTANTES SEMANAL Y ENVIAR >>");
                    getch();
                break;
                case 6:
                    system("cls");
                    printf("\n\n\t<< SALIR >>");
                    printf("\n\n\t... Gracias por tu visita ...");
                    getch();
                break;
                default:
                    system("cls");
                    printf("\n\n\t... La opcion es Incorrecta ...");
                    getch();
            }
        }while(opc != 6);
    }
    else
        perror("");
    return 0;
}
