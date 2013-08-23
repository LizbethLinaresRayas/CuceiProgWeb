#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <String.h>
#include <time.h>
#include <windows.h>
#define columna 8
#define fila 5

typedef int logico;

typedef struct
{
    int codigo;
    char nombre[11];
    float precio;
}Producto;

typedef struct
{
    int cod;
    int cont;
    struct Indice *sig;
}Indice;

typedef struct
{
    int codigo;
    int exisfisica;
    int exisinventario;
    char nombre[11];
    char Fecha[11];
    int faltantes;
}ProductoFaltante;

typedef struct nodo
{
    Indice indice;
    struct nodo *izq;
    struct nodo *der;
}Nodo;

typedef struct Nodo
{
    Indice indice;
    struct Nodo *sig;
}nodo;

typedef nodo *posicion;
typedef Indice *ListInd;

int gotoxy(short x, short y){

    COORD coord;
    HANDLE h_stdout;

    coord.X = x;
    coord.Y = y;

    if((h_stdout = GetStdHandle(STD_OUTPUT_HANDLE)) == INVALID_HANDLE_VALUE)
       return 0;

    if(SetConsoleCursorPosition(h_stdout, coord) == 0)
       return 0;

    return 1;
}

void inicializa(nodo **L)
{
     *L=NULL;
}

logico vacia(nodo *L)
{
    if(L == NULL)
        return 1;
    else
        return 0;
}

void inserta(posicion *L,Indice ind)
{
    posicion aux, ant;

    aux=(nodo*)malloc(1*sizeof(nodo));
    aux->indice=ind;
    if(vacia(*L) || (*L)->indice.cod > ind.cod)
    {
        aux->sig=*L;
        *L=aux;
    }
    else
    {
        ant=*L;
        while(ant->sig && ant->sig->indice.cod <= ind.cod)
            ant=ant->sig;
        aux->sig=ant->sig;
        ant->sig=aux;
    }
}


void cargaArbol(int fd,posicion *L)
{
    Producto prod;
    Indice ind;
    int cont=0;

    lseek(fd,0,0);

    while(read(fd,&prod,sizeof(prod)) == sizeof(prod))
    {
        ind.cod=prod.codigo;
        ind.cont=cont;
        cont++;
        inserta(L,ind);
    }
}

void cargaIndArch(int fd,posicion L){

    lseek(fd,0,0);

    if(vacia(L))
	{
	    printf("... No hay Datos ... ");
	}
	else
	{
		while(L != NULL)
		{
		    write(fd,&L->indice,sizeof(L->indice));
	   		L=L->sig;
        }
	}
}

int busquedaBinaria(int fdind,int codigo)
{
    int medio, inicio, fin;
    ListInd L=malloc(sizeof(Indice));
    inicio=lseek(fdind,0,0);;
    fin=lseek(fdind,0,2)/sizeof(Indice);

    while(inicio <= fin)
    {
        medio=(inicio+fin)/2;
        lseek(fdind,medio*sizeof(Indice),0);
        read(fdind,L,sizeof(Indice));
        if(codigo == L->cod)
        {
            return medio;
        }
        else
        {
            if(L->cod > codigo)
                fin=medio-1;
            else
                inicio=medio+1;
        }
    }
    return -1;

}

int busquedaBin(int fd,int codigo)
{
    int medio, inicio, fin;
    Indice ind;

    inicio=lseek(fd,0,0);;
    fin=lseek(fd,0,2)/sizeof(Indice);


    while(inicio <= fin)
    {
        medio=(inicio+fin)/2;
        lseek(fd,medio*sizeof(ind),0);
        read(fd,&ind,sizeof(ind));
        if(codigo == ind.cod)
        {
            return codigo;
        }
        else
        {
            if(ind.cod > codigo)
                fin=medio-1;
            else
                inicio=medio+1;
        }
    }
    return -1;

}

void encabezado()
{
    printf("\n\n\t1. Captura de Productos");
    printf("\n\n\t2. Captura de Existencia Fisica e Inventario");
    printf("\n\n\t3. Captura de Faltantes de la Semana por cada Producto");
    printf("\n\n\t4. Consulta de Lista de Faltantes por Semana");
    printf("\n\n\t5. Crear Archivo de Faltantes Semanal y Enviar");
    printf("\n\n\t6. Salir");
}

Producto CapturaProd(Producto prod)
{
    printf("\n\n\tCodigo: ");
    scanf("%d",&prod.codigo);
    printf("\n\n\tNombre: ");
    fflush(stdin);
    gets(prod.nombre);
    printf("\n\n\tPrecio: ");
    scanf("%f",&prod.precio);
    return prod;
}

int main()
{
    int opc=0,auxCod,aux,bnd,faltantes,codAuxiliar,i;
    int fdind,fdprod,fdfalt,fdfaltRep,fdReporte,fdind1,fdprod1,fdfalt1,fdfaltRep1,fdReporte1;
    char opsuc;
    char fechAux[11];
    Producto prod;
    ProductoFaltante pf,pf1;
    posicion E;
    system("cls");
    printf("\n\n\t\t>>>>>>> BIENVENIDO <<<<<<<");
    printf("\n\n\t<< ELIGE TU SUCURSAL >>");
    printf("\n\n\tG. GUADALAJARA");
    printf("\n\n\tM. MEXICO");
    printf("\n\n\tS. SALIR");
    printf("\n\n\t<< Elige tu Sucursal: ");
    scanf("%c",&opsuc);
    while(opc != 6)
    {
        switch(opsuc)
        {
            case 'G':
                fdprod=open("ProductosGdl.bin",O_CREAT|O_RDWR|O_BINARY,S_IRWXU);
                fdind=open("IndiceGdl.bin",O_CREAT|O_RDWR|O_BINARY,S_IRWXU);
                fdfalt=open("FaltantesGdl.bin",O_CREAT|O_RDWR|O_BINARY,S_IRWXU);
                fdfaltRep=open("FaltantesIIGdl.bin",O_CREAT|O_RDWR|O_BINARY,S_IRWXU);
                fdReporte=open("ReporteGdl.bin",O_CREAT|O_RDWR|O_BINARY,S_IRWXU);
                if((fdprod > 0) && (fdind > 0) && (fdfalt > 0) && (fdfaltRep) && (fdReporte > 0))
                {
                    do
                    {
                        system("cls");
                        printf("\n\n\t<< SUCURSAL GUADALAJARA >>");
                        encabezado();
                        printf("\n\n\t->Elige una Opcion: ");
                        scanf("%d",&opc);
                        switch(opc)
                        {
                            case 1:
                                system("cls");
                                printf("\n\t\t\t\t->SUCURSAL GUADALAJARA");
                                printf("\n\n\t<< CAPTURA DE PRODUCTOS >>");
                                printf("\n\n\tIngresa los siguientes datos del Producto:");
                                prod=CapturaProd(prod);
                                lseek(fdprod,0,2);
                                write(fdprod,&prod,sizeof(prod));
                                printf("\n\n\t... Los Datos han sido Guardados ...");
                                getch();
                            break;
                            case 2:
                                system("cls");
                                printf("\n\t\t\t\t->SUCURSAL GUADALAJARA");
                                printf("\n\n\t<< CAPTURA DE EXISTENCIA FISICA E INVENTARIO >>");
                                inicializa(&E);
                                cargaArbol(fdprod,&E);
                                cargaIndArch(fdind,E);
                                printf("\n\n\tIngresa el codigo: ");
                                scanf("%d",&auxCod);
                                printf("\n\n\tFecha dd/mm/aaa: ");
                                fflush(stdin);
                                gets(fechAux);
                                fechAux[11]='\0';
                                lseek(fdind,0,0);
                                aux=busquedaBinaria(fdind,auxCod);
                                if(aux != -1)
                                {
                                    lseek(fdprod,0,0);
                                    while(read(fdprod,&prod,sizeof(prod)))
                                    {
                                        if(prod.codigo == auxCod)
                                        {
                                            pf.codigo=prod.codigo;
                                            strcpy(pf.nombre,prod.nombre);
                                            strcpy(pf.Fecha,fechAux);
                                        }

                                    }
                                    printf("\n\n\t->Ingresa los siguientes datos\n");
                                    printf("\n\n\tTotal de existencias fisicas: ");
                                    scanf("%d",&pf.exisfisica);
                                    printf("\n\n\tTotal de existencias en inventario: ");
                                    scanf("%d",&pf.exisinventario);
                                    lseek(fdfalt,0,2);
                                    write(fdfalt,&pf,sizeof(pf));
                                    printf("\n...Tus datos han sido guardados...");
                                }
                                else
                                    printf("\n...Codigo no encontrado...");
                                getch();
                            break;
                            case 3:
                                system("cls");
                                printf("\n\t\t\t\t->SUCURSAL GUADALAJARA");
                                printf("\n\n\t<< CAPTURA DE FALTANTES DE LA SEMANA POR CADA PRODUCTO >>");
                                printf("\n\n\tIngresa fecha DD/MM/AAAA: ");
                                fflush(stdin);
                                gets(fechAux);
                                fechAux[11]='\0';
                                lseek(fdfalt,0,0);
                                while(read(fdfalt,&pf,sizeof(pf)))
                                {
                                    if(strcmp(fechAux,pf.Fecha) == 0)
                                    {
                                        if(pf.codigo != codAuxiliar)
                                        {
                                            faltantes=(pf.exisinventario-pf.exisfisica);
                                            if(faltantes > 0)
                                            {
                                                pf.faltantes=faltantes;
                                                strcpy(pf1.nombre,pf.nombre);
                                                pf1.codigo=pf.codigo;
                                                strcpy(pf1.Fecha,pf.Fecha);
                                                pf1.faltantes=pf.faltantes;
                                                lseek(fdfaltRep,0,2);
                                                write(fdfaltRep,&pf1,sizeof(ProductoFaltante));
                                                bnd=1;
                                            }
                                            codAuxiliar=pf.codigo;
                                        }
                                    }
                                }
                                if(bnd == 1)
                                    printf("\n\n\t... Cambios realizados ...");
                                else
                                    printf("\n\n\t... No se pudo hacer el calculo ...");

                                getch();
                            break;
                            case 4:
                                system("cls");
                                printf("\n\t\t\t\t->SUCURSAL GUADALAJARA");
                                printf("\n\n\t<< CONSULTA DE LISTA DE FALTANTES POR SEMANA >>");
                                printf("\n\n\tIngresa fecha DD/MM/AAAA: ");
                                fflush(stdin);
                                gets(fechAux);
                                fechAux[11]='\0';
                                bnd=0;
                                lseek(fdfaltRep,0,0);
                                i=0;
                                printf("\n\n\t\tFaltantes");
                                while(read(fdfaltRep,&pf,sizeof(pf)) == sizeof(pf))
                                {
                                    pf1=pf;
                                    pf1.Fecha[11]='\0';
                                    if(strcmp(fechAux,pf1.Fecha) == 0)
                                    {
                                        gotoxy(columna,fila+7);printf("FECHA");
                                        gotoxy(columna+15,fila+7);printf("CODIGO");
                                        gotoxy(columna+35,fila+7);printf("NOMBRE");
                                        gotoxy(columna+50,fila+7);printf("FALTANTES");
                                        gotoxy(columna,fila+10+i);printf("%s",pf.Fecha);
                                        gotoxy(columna+15,fila+10+i);printf("%d",pf.codigo);
                                        gotoxy(columna+35,fila+10+i);printf("%s",pf.nombre);
                                        gotoxy(columna+52,fila+10+i);printf("%d",pf.faltantes);
                                        i+=3;
                                        bnd=1;
                                    }
                                }
                                if(bnd == 0)
                                    printf("\n\n\t\t...NO EXISTE...");
                                getch();
                            break;
                            case 5:
                                system("cls");
                                printf("\n\n\t<< SUCURSAL GUADALAJARA >>");
                                printf("\n\n\t<< CREAR ARCHIVO DE FALTANTES SEMANAL Y ENVIAR >>");
                                printf("\n\n\tIngresa fecha DD/MM/AAAA: ");
                                fflush(stdin);
                                gets(fechAux);
                                fechAux[11]='\0';
                                lseek(fdfaltRep,0,0);
                                lseek(fdReporte,0,2);
                                bnd=0;
                                while(read(fdfaltRep,&pf,sizeof(pf)) == sizeof(pf))
                                {
                                    pf1=pf;
                                    pf1.Fecha[11]='\0';
                                    if(strcmp(fechAux,pf1.Fecha) == 0)
                                    {
                                        write(fdReporte,&pf,sizeof(pf));
                                        bnd=1;
                                    }
                                }
                                if(bnd == 1)
                                {
                                    i=0;
                                    printf("\n\n\t\tFALTANTES: ");
                                    lseek(fdReporte,0,0);
                                    while(read(fdReporte,&pf,sizeof(pf)) == sizeof(pf))
                                    {
                                        pf1=pf;
                                        pf1.Fecha[11]='\0';
                                        if(strcmp(fechAux,pf1.Fecha) == 0)
                                        {
                                            gotoxy(columna,fila+7);printf("FECHA");
                                            gotoxy(columna+15,fila+7);printf("CODIGO");
                                            gotoxy(columna+35,fila+7);printf("NOMBRE");
                                            gotoxy(columna+50,fila+7);printf("FALTANTES");
                                            gotoxy(columna,fila+10+i);printf("%s",pf.Fecha);
                                            gotoxy(columna+15,fila+10+i);printf("%d",pf.codigo);
                                            gotoxy(columna+35,fila+10+i);printf("%s",pf.nombre);
                                            gotoxy(columna+52,fila+10+i);printf("%d",pf.faltantes);
                                            i+=3;
                                        }
                                    }
                                    printf("\n\n\tENVIO CORRECTO");
                                }
                                else
                                    printf("\n\n\tENVIO FALLIDO");
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
                                printf("\n\n\t...Opcion Incorrecta...");
                                getch();
                        }
                    }while(opc != 6);
                }
                break;
                case 'M':
                    fdprod1=open("ProductosMex.bin",O_CREAT|O_RDWR|O_BINARY,S_IRWXU);
                    fdind1=open("IndiceMex.bin",O_CREAT|O_RDWR|O_BINARY,S_IRWXU);
                    fdfalt1=open("FaltantesMex.bin",O_CREAT|O_RDWR|O_BINARY,S_IRWXU);
                    fdfaltRep1=open("FaltantesMexII.bin",O_CREAT|O_RDWR|O_BINARY,S_IRWXU);
                    fdReporte1=open("ReporteMex.bin",O_CREAT|O_RDWR|O_BINARY,S_IRWXU);
                    if((fdprod1 > 0) && (fdind1 > 0) && (fdfalt1 > 0) && (fdind1 > 0))
                    {
                        do
                        {
                            system("cls");
                            printf("\n\n\t<< SUCURSAL MEXICO >>");
                            encabezado();
                            printf("\n\n\t->Elige una Opcion: ");
                            scanf("%d",&opc);
                            switch(opc)
                            {
                                case 1:
                                system("cls");
                                printf("\n\t\t\t\t->SUCURSAL MEXICO");
                                printf("\n\n\t<< CAPTURA DE PRODUCTOS >>");
                                printf("\n\n\tIngresa los siguientes datos del Producto:");
                                prod=CapturaProd(prod);
                                lseek(fdprod1,0,2);
                                write(fdprod1,&prod,sizeof(prod));
                                printf("\n\n\t... Los Datos han sido Guardados ...");
                                getch();
                            break;
                            case 2:
                                system("cls");
                                printf("\n\t\t\t\t->SUCURSAL MEXICO");
                                printf("\n\n\t<< CAPTURA DE EXISTENCIA FISICA E INVENTARIO >>");
                                inicializa(&E);
                                cargaArbol(fdprod1,&E);
                                cargaIndArch(fdind1,E);
                                printf("\n\n\tIngresa el codigo: ");
                                scanf("%d",&auxCod);
                                printf("\n\n\tFecha dd/mm/aaa: ");
                                fflush(stdin);
                                gets(fechAux);
                                fechAux[11]='\0';
                                lseek(fdind1,0,0);
                                aux=busquedaBinaria(fdind1,auxCod);
                                if(aux != -1)
                                {
                                    lseek(fdprod1,0,0);
                                    while(read(fdprod1,&prod,sizeof(prod)))
                                    {
                                        if(prod.codigo == auxCod)
                                        {
                                            pf.codigo=prod.codigo;
                                            strcpy(pf.nombre,prod.nombre);
                                            strcpy(pf.Fecha,fechAux);
                                        }

                                    }
                                    printf("\n\n\t->Ingresa los siguientes datos\n");
                                    printf("\n\n\tTotal de existencias fisicas: ");
                                    scanf("%d",&pf.exisfisica);
                                    printf("\n\n\tTotal de existencias en inventario: ");
                                    scanf("%d",&pf.exisinventario);
                                    lseek(fdfalt1,0,2);
                                    write(fdfalt1,&pf,sizeof(pf));
                                    printf("\n\n\t...Tus datos han sido guardados...");
                                }
                                else
                                    printf("\n\n\t...Codigo no encontrado...");
                                getch();
                            break;
                            case 3:
                                system("cls");
                                printf("\n\t\t\t\t->SUCURSAL MEXICO");
                                printf("\n\n\t<< CAPTURA DE FALTANTES DE LA SEMANA POR CADA PRODUCTO >>");
                                printf("\n\n\tIngresa fecha DD/MM/AAAA: ");
                                fflush(stdin);
                                gets(fechAux);
                                fechAux[11]='\0';
                                lseek(fdfalt1,0,0);
                                while(read(fdfalt1,&pf,sizeof(pf)))
                                {
                                    if(strcmp(fechAux,pf.Fecha) == 0)
                                    {
                                        if(pf.codigo != codAuxiliar)
                                        {
                                            faltantes=(pf.exisinventario-pf.exisfisica);
                                            if(faltantes > 0)
                                            {
                                                pf.faltantes=faltantes;
                                                strcpy(pf1.nombre,pf.nombre);
                                                pf1.codigo=pf.codigo;
                                                strcpy(pf1.Fecha,pf.Fecha);
                                                pf1.faltantes=pf.faltantes;
                                                lseek(fdfaltRep1,0,2);
                                                write(fdfaltRep1,&pf1,sizeof(ProductoFaltante));
                                                bnd=1;
                                            }
                                            codAuxiliar=pf.codigo;
                                        }
                                    }
                                }
                                if(bnd == 1)
                                    printf("\n\n\t... Cambios realizados ...");
                                else
                                    printf("\n\n\t... No se pudo hacer el calculo ...");

                                getch();
                            break;
                            case 4:
                                system("cls");
                                printf("\n\t\t\t\t->SUCURSAL MEXICO");
                                printf("\n\n\t<< CONSULTA DE LISTA DE FALTANTES POR SEMANA >>");
                                printf("\n\n\tIngresa fecha DD/MM/AAAA: ");
                                fflush(stdin);
                                gets(fechAux);
                                fechAux[11]='\0';
                                bnd=0;
                                lseek(fdfaltRep1,0,0);
                                i=0;
                                printf("\n\n\t\tFaltantes");
                                while(read(fdfaltRep1,&pf,sizeof(pf)) == sizeof(pf))
                                {
                                    pf1=pf;
                                    pf1.Fecha[11]='\0';
                                    if(strcmp(fechAux,pf1.Fecha) == 0)
                                    {
                                        gotoxy(columna,fila+7);printf("FECHA");
                                        gotoxy(columna+15,fila+7);printf("CODIGO");
                                        gotoxy(columna+35,fila+7);printf("NOMBRE");
                                        gotoxy(columna+50,fila+7);printf("FALTANTES");
                                        gotoxy(columna,fila+10+i);printf("%s",pf.Fecha);
                                        gotoxy(columna+15,fila+10+i);printf("%d",pf.codigo);
                                        gotoxy(columna+35,fila+10+i);printf("%s",pf.nombre);
                                        gotoxy(columna+52,fila+10+i);printf("%d",pf.faltantes);
                                        i+=3;
                                        bnd=1;
                                    }
                                }
                                if(bnd == 0)
                                    printf("\n\n\t\t...NO EXISTE...");
                                getch();
                            break;
                            case 5:
                                system("cls");
                                printf("\n\t\t\t\t->SUCURSAL MEXICO");
                                printf("\n\n\t<< CREAR ARCHIVO DE FALTANTES SEMANAL Y ENVIAR >>");
                                printf("\n\n\tIngresa fecha DD/MM/AAAA: ");
                                fflush(stdin);
                                gets(fechAux);
                                fechAux[11]='\0';
                                lseek(fdfaltRep1,0,0);
                                lseek(fdReporte1,0,2);
                                bnd=0;
                                while(read(fdfaltRep1,&pf,sizeof(pf)) == sizeof(pf))
                                {
                                    pf1=pf;
                                    pf1.Fecha[11]='\0';
                                    if(strcmp(fechAux,pf1.Fecha) == 0)
                                    {
                                        write(fdReporte1,&pf,sizeof(pf));
                                        bnd=1;
                                    }
                                }
                                if(bnd == 1)
                                {
                                    printf("\n\n\t\tFaltantes: ");
                                    lseek(fdReporte1,0,0);
                                    i=0;
                                    while(read(fdReporte1,&pf,sizeof(pf)) == sizeof(pf))
                                    {
                                        pf1=pf;
                                        pf1.Fecha[11]='\0';
                                        if(strcmp(fechAux,pf1.Fecha) == 0)
                                        {
                                            gotoxy(columna,fila+7);printf("FECHA");
                                            gotoxy(columna+15,fila+7);printf("CODIGO");
                                            gotoxy(columna+35,fila+7);printf("NOMBRE");
                                            gotoxy(columna+50,fila+7);printf("FALTANTES");
                                            gotoxy(columna,fila+10+i);printf("%s",pf.Fecha);
                                            gotoxy(columna+15,fila+10+i);printf("%d",pf.codigo);
                                            gotoxy(columna+35,fila+10+i);printf("%s",pf.nombre);
                                            gotoxy(columna+52,fila+10+i);printf("%d",pf.faltantes);
                                            i+=3;
                                        }
                                    }
                                    printf("\n\n\tENVIO CORRECTO");
                                }
                                else
                                    printf("\n\n\tENVIO FALLIDO");
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
                                printf("\n\n\t...Opcion Incorrecta...");
                                getch();
                            }
                        }while(opc != 6);
                    }
                break;
                case 'S':
                    printf("\n\n\t... Gracias por tu visita ...");
                break;
                default:
                    system("cls");
                    printf("\n\n\t...Opcion Incorrecta...");
                    getch();
            }
        }
    close(fdind);
    close(fdprod);
    close(fdfalt);
    close(fdfaltRep);
    close(fdind1);
    close(fdprod1);
    close(fdfalt1);
    close(fdfaltRep1);
    return 0;
}
