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

typedef struct
{
    int codigo;
    int exisfisica;
    int exisinventario;
    char nombre[11];
    char Fecha[11];
    int faltantes;
}ProductoFaltante;

typedef struct
{
    int codigo;
    char nombre[11];
    char Fecha[11];
    int faltantes;
    char sucursal[12];
}ProdConcentrado;

typedef struct
{
    int codigo;
    char nombre[11];
    float precio;
}Producto;

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

int concentrar(int fdReporte, int fdReporte1, int fdConcentrado)
{
    ProductoFaltante pf;
    ProdConcentrado pc,pc1;
    int b=0,bnd=0,bandera=0;

    //Guadalajara
    lseek(fdReporte,0,0);
    while(read(fdReporte,&pf,sizeof(pf)))
    {
        pc1.codigo=pf.codigo;
        strcpy(pc1.Fecha,pf.Fecha);
        strcpy(pc1.nombre,pf.nombre);
        strcpy(pc1.sucursal,"Guadalajara");
        pc1.faltantes=pf.faltantes;
        lseek(fdConcentrado,0,0);
        while(read(fdConcentrado,&pc,sizeof(pc)))
        {
            b=1;
            if((strcmp(pc.Fecha,pf.Fecha) == 0) && (bnd != 2))
            {
                if(pc.codigo != pf.codigo)
                    bnd=1;
                else
                    bnd=2;
            }
            else
            {
                if(bnd == 0)
                    bnd=1;
            }
        }
        if(b == 0)
            bnd=1;
        if(bnd == 1)
        {
            lseek(fdConcentrado,0,2);
            write(fdConcentrado,&pc1,sizeof(pc1));
            bandera=1;
            bnd=0;
        }
        bnd=0;
    }

    //Mexico
    b=0;
    bnd=0;
    lseek(fdReporte1,0,0);
    while(read(fdReporte1,&pf,sizeof(pf)))
    {
        pc1.codigo=pf.codigo;
        strcpy(pc1.Fecha,pf.Fecha);
        strcpy(pc1.nombre,pf.nombre);
        strcpy(pc1.sucursal,"Mexico");
        pc1.faltantes=pf.faltantes;
        lseek(fdConcentrado,0,0);
        while(read(fdConcentrado,&pc,sizeof(pc)))
        {
            b=1;
            if((strcmp(pc.Fecha,pf.Fecha) == 0) && (bnd != 2))
            {
                if(pc.codigo != pf.codigo)
                    bnd=1;
                else
                    bnd=2;
            }
            else
            {
                if(bnd == 0)
                    bnd=1;
            }
        }
        if(b == 0)
            bnd=1;
        if(bnd == 1)
        {
            lseek(fdConcentrado,0,2);
            write(fdConcentrado,&pc1,sizeof(pc1));
            bandera=1;
            bnd=0;
        }
        bnd=0;
    }
    return bandera;
}

void localizaFalt(int fdConcent,char fecha[10],char suc[12])
{
    ProdConcentrado pc,pc1;
    int bnd=0,i=0;

    lseek(fdConcent,0,0);
    fecha[11]='\0';
    pc.Fecha[11]='\0';
    suc[12]='\0';
    i=0;
    gotoxy(columna+30,fila+1);printf("<< FALTANTES >>");
    while(read(fdConcent,&pc,sizeof(pc)))
    {
        pc1=pc;
        pc1.Fecha[11]='\0';
        if((strcmp(fecha,pc1.Fecha) == 0) && (pc1.codigo != -1))
        {
            if(strcmp(suc,pc1.sucursal) == 0)
            {
                gotoxy(columna,fila+4);printf("FECHA");
                gotoxy(columna+17,fila+4);printf("CODIGO");
                gotoxy(columna+35,fila+4);printf("NOMBRE");
                gotoxy(columna+50,fila+4);printf("FALTANTES");
                gotoxy(columna+66,fila+4);printf("SUCURSAL");
                gotoxy(columna,fila+7+i);printf("%s",pc1.Fecha);
                gotoxy(columna+17,fila+7+i);printf("%d",pc1.codigo);
                gotoxy(columna+35,fila+7+i);printf("%s",pc1.nombre);
                gotoxy(columna+53,fila+7+i);printf("%d",pc1.faltantes);
                gotoxy(columna+65,fila+7+i);printf("%s",pc1.sucursal);
                i+=3;
                bnd=1;
            }
        }

    }
    if(bnd == 0)
        printf("\n\n\n\t\t... No hay Faltantes ...");
}


void localizaProd(int fdConcent,char fecha[10],char suc[12],int cod)
{
    ProdConcentrado pc,pc1;
    int bnd=0,i=0;

    lseek(fdConcent,0,0);
    fecha[11]='\0';
    pc.Fecha[11]='\0';
    suc[12]='\0';
    i=0;
    gotoxy(columna+30,fila+1);printf("<< PRODUCTO >>");
    while(read(fdConcent,&pc,sizeof(pc)))
    {
        pc1=pc;
        pc1.Fecha[11]='\0';
        if((strcmp(fecha,pc1.Fecha) == 0) && (pc1.codigo != -1))
        {
            if(strcmp(suc,pc1.sucursal) == 0)
            {
                if(cod == pc1.codigo)
                {
                    gotoxy(columna+2,fila+4);printf("FECHA");
                    gotoxy(columna+17,fila+4);printf("CODIGO");
                    gotoxy(columna+35,fila+4);printf("NOMBRE");
                    gotoxy(columna+50,fila+4);printf("FALTANTES");
                    gotoxy(columna+66,fila+4);printf("SUCURSAL");
                    gotoxy(columna,fila+7+i);printf("%s",pc1.Fecha);
                    gotoxy(columna+18,fila+7+i);printf("%d",pc1.codigo);
                    gotoxy(columna+36,fila+7+i);printf("%s",pc1.nombre);
                    gotoxy(columna+53,fila+7+i);printf("%d",pc1.faltantes);
                    gotoxy(columna+66,fila+7+i);printf("%s",pc1.sucursal);
                    i+=3;
                    bnd=1;
                }
            }
        }

    }
    if(bnd == 0)
        printf("\n\n\n\t\t... No Existe el Producto ...");
}
int Elimina(int fdConcent,char fecha[10],char suc[12])
{
    ProdConcentrado pc,pc1;
    int cont=0,bnd=0;
    char sucAux[12];

    lseek(fdConcent,0,0);
    fecha[11]='\0';
    pc.Fecha[11]='\0';
    suc[12]='\0';
    while(read(fdConcent,&pc,sizeof(pc)))
    {
        pc1=pc;
        if(strcmp(suc,pc1.sucursal) == 0)
        {
            if(strcmp(fecha,pc1.Fecha) == 0)
            {
                lseek(fdConcent,-sizeof(pc1),1);
                strcpy(sucAux,"-1");
                write(fdConcent,&pc.Fecha,sizeof(pc1));
                bnd=1;
            }
        }

        cont++;
    }
    return bnd;
}

int Reenviar(int fdRep,int fdConcent,char fecha[10],int suc)
{
    ProductoFaltante pf,pf1;
    ProdConcentrado pc;
    int bnd=0;

    fecha[11]='\0';
    pf.Fecha[12]='\0';
    lseek(fdRep,0,0);
    lseek(fdConcent,0,2);
    while(read(fdRep,&pf,sizeof(pf)))
    {
        pf1=pf;
        if(strcmp(fecha,pf1.Fecha) == 0)
        {
            strcpy(pc.nombre,pf.nombre);
            strcpy(pc.Fecha,pf.Fecha);
            pc.codigo=pf.codigo;
            pc.faltantes=pf.faltantes;
            if(suc == 1)
                strcpy(pc.sucursal,"Guadalajara");
            if(suc == 2)
                strcpy(pc.sucursal,"Mexico");
            write(fdConcent,&pc,sizeof(pc));
            bnd=1;
        }
    }
    return bnd;
}


int main()
{
    int opc,fdConcent,fdReporte,fdReporte1,bnd=0,bnd1=0,codAux,i,suc;
    char fechAux[11],sucAux[12];

    fdConcent=open("Concentrado.bin",O_CREAT|O_RDWR|O_BINARY,S_IRWXU);

    do
    {
        system("cls");
        printf("\n\n\t\t<CORPORATIVO>>");
        printf("\n\n\t1. CONCENTRAR FALTANTES DE SUCURSAL");
        printf("\n\n\t2. REENVIAR");
        printf("\n\n\t3. ELIMINAR UN ENVIO");
        printf("\n\n\t4. CONSULTAR FALTANTES POR ORDEN DE FECHA Y SUCURSAL");
        printf("\n\n\t5. CONSULTAR PRODUCTO");
        printf("\n\n\t6. SALIR");
        printf("\n\n\t->ELIGE TU OPCION: ");
        scanf("%d",&opc);
        if(fdConcent > 0)
        {
            switch(opc)
            {
                case 1:
                    system("cls");
                    printf("\n\n\t\t<< CONCENTRAR FALTANTES DE SUCURSAL >>");
                    fdReporte=open("ReporteGdl.bin",O_RDWR|O_BINARY,S_IRWXU);
                    fdReporte1=open("ReporteMex.bin",O_RDWR|O_BINARY,S_IRWXU);
                    if((fdReporte > 0) || (fdReporte1 > 0))
                    {
                        bnd=concentrar(fdReporte,fdReporte1,fdConcent);
                        if(bnd == 1)
                            printf("\n\n\n\n\t\t... ARCHIVO CONCENTRADO ...");
                        else
                            printf("\n\n\n\n\t\t... NO HAY ARCHIVO POR CONCENTRAR ...");
                    }
                    else
                        perror("");
                    close(fdReporte);
                    close(fdReporte1);
                    getch();
                break;
                case 2:
                    system("cls");
                    printf("\n\n\t\t<< REENVIAR >>");
                    fdReporte=open("ReporteGdl.bin",O_RDWR|O_BINARY,S_IRWXU);
                    fdReporte1=open("ReporteMex.bin",O_RDWR|O_BINARY,S_IRWXU);
                    if((fdReporte > 0) || (fdReporte1 > 0))
                    {
                        printf("\n\n\tIngresa fecha DD/MM/AAAA: ");
                        fflush(stdin);
                        gets(fechAux);
                        fechAux[11]='\0';
                        for(i=0; i<12; i++)
                            sucAux[i]='\0';
                        printf("\n\n\t   Sucursal: ");
                        printf("\n\n\t1. Guadalajara");
                        printf("\n\n\t2. Mexico");
                        printf("\n\n\tElige tu opcion: ");
                        scanf("%d",&suc);
                        if(suc == 1)
                        {
                            bnd=Reenviar(fdReporte,fdConcent,fechAux,1);
                            if(bnd == 1)
                                printf("\n\n\n\n\t\t... Reporte Reenviado ...");
                            else
                                printf("\n\n\n\n\t\t...No hay Reporte por Reenviar...");
                        }
                        if(suc == 2)
                        {
                            bnd1=Reenviar(fdReporte1,fdConcent,fechAux,2);
                            if(bnd1 == 1)
                                printf("\n\n\n\n\t\t...Reporte Reenviado...");
                            else
                                printf("\n\n\n\n\t\t...No hay Reporte por Reenviar...");
                        }
                    }
                    else
                        perror("");
                    close(fdReporte);
                    close(fdReporte1);
                    getch();
                break;
                case 3:
                    system("cls");
                    printf("\n\n\t\t<< ELIMINAR UN ENVIO >>");
                    printf("\n\n\tIngresa Fecha: ");
                    fflush(stdin);
                    gets(fechAux);
                    for(i=0; i<12; i++)
                        sucAux[i]='\0';
                    printf("\n\n\t  Sucursal: ");
                    printf("\n\n\t1. Guadalajara");
                    printf("\n\n\t2. Mexico");
                    printf("\n\n\tElige tu opcion: ");
                    scanf("%d",&suc);
                    if(suc == 1)
                        strcpy(sucAux,"Guadalajara");
                    if(suc == 2)
                        strcpy(sucAux,"Mexico");
                    bnd=0;
                    bnd=Elimina(fdConcent,fechAux,sucAux);
                    if(bnd == 1)
                        printf("\n\n\n\n\t\t... Reporte Eliminado ...");
                    else
                        printf("\n\n\n\n\t\t... El Reporte no Existe ...");
                    getch();
                break;
                case 4:
                    system("cls");
                    gotoxy(columna+12,fila-2);printf("<< CONSULTAR FALTANTES POR ORDEN DE FECHA Y SUCURSAL >>");
                    if(fdConcent > 0)
                    {
                        printf("\n\n\n\tIngresa la Fecha de Consulta: ");
                        fflush(stdin);
                        gets(fechAux);
                        for(i=0; i<12; i++)
                            sucAux[i]='\0';
                        printf("\n\n\t   Sucursal: ");
                        printf("\n\n\t1. Guadalajara");
                        printf("\n\n\t2. Mexico");
                        printf("\n\n\tElige tu opcion: ");
                        scanf("%d",&suc);
                        if(suc == 1)
                            strcpy(sucAux,"Guadalajara");
                        if(suc == 2)
                            strcpy(sucAux,"Mexico");
                        system("cls");
                        gotoxy(columna+12,fila-2);printf("<< CONSULTAR FALTANTES POR ORDEN DE FECHA Y SUCURSAL >>");
                        localizaFalt(fdConcent,fechAux,sucAux);
                    }
                    else
                        perror("");
                    getch();
                break;
                case 5:
                    system("cls");
                    printf("\n\n\t\t\t\t<< CONSULTAR PRODUCTO >>");
                    if(fdConcent > 0)
                    {
                        printf("\n\n\tIngresa los siguientes Datos de la Consulta: ");
                        printf("\n\n\n\tFecha: ");
                        fflush(stdin);
                        gets(fechAux);
                        printf("\n\n\tCodigo de Producto: ");
                        scanf("%d",&codAux);
                        for(i=0; i<12; i++)
                            sucAux[i]='\0';
                        printf("\n\n\t   Sucursal: ");
                        printf("\n\n\t1. Guadalajara");
                        printf("\n\n\t2. Mexico");
                        printf("\n\n\tElige tu opcion: ");
                        scanf("%d",&suc);
                        if(suc == 1)
                            strcpy(sucAux,"Guadalajara");
                        if(suc == 2)
                            strcpy(sucAux,"Mexico");
                        system("cls");
                        printf("\n\n\t\t\t\t   << CONSULTAR PRODUCTO >>");
                        localizaProd(fdConcent,fechAux,sucAux,codAux);
                    }
                    else
                        perror("");
                    getch();
                break;
                case 6:
                    system("cls");
                    printf("\n\n\t\t\t<< SALIR >>");
                    printf("\n\n\n\n\t\t... Gracias por tu visita ...\n\n");
                    getch();
                break;
                default:
                    printf("\n\n\n\n\t\t... Opcion Incorrecta ...\n\n");
            }
        }
        else
            perror("");
    }while(opc != 6);
    return 0;
    close(fdConcent);
}

