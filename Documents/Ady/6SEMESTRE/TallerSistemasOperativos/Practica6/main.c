#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#define CAPACIDAD 50

typedef int posicion;
typedef char TipoElemento;

typedef struct P
{
    int estado;
    int tDormido;
    int cantElem;
}P;

typedef struct C
{
    int estado;
    int tDormido;
    int cantElem;
}C;

typedef struct P Productor;
typedef struct C Consumidor;

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

void delay(int x)
{
    int i;
    for(i=0; i<=x*1000000; i++);
}

void imprimeMarco()
{
    int i=0;
    int j=0;

    //Celdas Primera Línea
    for(i=0; i<125; i+=5)
    {
        //imprime celda
        gotoxy(4+i,12);printf("%c",201);
        gotoxy(5+i,12);printf("%c",205);
        gotoxy(6+i,12);printf("%c",205);
        gotoxy(7+i,12);printf("%c",205);
        gotoxy(8+i,12);printf("%c",205);
        gotoxy(4+i,13);printf("%c",186);
        gotoxy(4+i,14);printf("%c",200);
        gotoxy(5+i,14);printf("%c",205);
        gotoxy(6+i,14);printf("%c",205);
        gotoxy(7+i,14);printf("%c",205);
        gotoxy(8+i,14);printf("%c",205);
        gotoxy(9+i,12);printf("%c",187);
        gotoxy(9+i,13);printf("%c",186);
        gotoxy(9+i,14);printf("%c",188);
    }

    //Celdas Segunda Línea
    for(i=0; i<125; i+=5)
    {
        //imprime celda
        gotoxy(4+i,22);printf("%c",201);
        gotoxy(5+i,22);printf("%c",205);
        gotoxy(6+i,22);printf("%c",205);
        gotoxy(7+i,22);printf("%c",205);
        gotoxy(8+i,22);printf("%c",205);
        gotoxy(4+i,23);printf("%c",186);
        gotoxy(4+i,24);printf("%c",200);
        gotoxy(5+i,24);printf("%c",205);
        gotoxy(6+i,24);printf("%c",205);
        gotoxy(7+i,24);printf("%c",205);
        gotoxy(8+i,24);printf("%c",205);
        gotoxy(9+i,22);printf("%c",187);
        gotoxy(9+i,23);printf("%c",186);
        gotoxy(9+i,24);printf("%c",188);
    }

    for(i=0; i<125; i+=5)
    {
        j++;
        gotoxy(6+i,15);printf("%d",j);
    }
    for(i=0; i<125; i+=5)
    {
        j++;
        gotoxy(6+i,25);printf("%d",j);
    }
}

int produceElemento()
{
    int num;

    num = 33 + rand() % 126;
    return num;
}

int detTiempo()
{
    int tiempo;

    tiempo = rand() % 5 + 1;
    return tiempo;
}

int detCantElem()
{
    int cantElem;

    cantElem = rand() % 6;
    return cantElem;
}

int insertaElemento(char contenedor[],posicion pos,TipoElemento elemento)
{

    if(pos < CAPACIDAD)
    {
        contenedor[pos] = elemento;
        pos++;
    }
    else
    {
        pos = 0;
        contenedor[pos] = elemento;
        pos++;
    }
    return pos;

}

int extraeElemento(char contenedor[],posicion pos)
{

    if(pos < CAPACIDAD)
    {
        contenedor[pos] = '\0';
        pos++;
    }
    else
    {
        pos = 0;
        contenedor[pos] = '\0';
        pos++;
    }
    return pos;

}

void mostrarElementos(posicion pos,char contenedor[])
{
    int i=0;
    int j=0;
    int k=0;

    for(i=0; i < (5*pos); i+=5)
    {
        if(j < 25)
        {
            gotoxy(6+i,13);printf("%c",contenedor[j]);
            j++;
        }
    }
    k=pos-25;
    if((j >= 25) && (j < 50))
    {
        for(i=0; i < (5*k); i+=5)
        {
            gotoxy(6+i,23);printf("%c",contenedor[j]);
            j++;
        }
    }
}

int vacio(char contenedor[])
{
    if(contenedor[0] == '\0')
        return 1;
    else
        return 0;
}

void estado(int productor, int consumidor)
{
    switch(productor)
    {
        case 0:
            gotoxy(2,5);printf("Productor:                ");
            gotoxy(2,5);printf("Productor:   Dormido");
        break;
        case 1:
            gotoxy(2,5);printf("Productor:                ");
            gotoxy(2,5);printf("Productor:   Trabajando");
        break;
        case 2:
            gotoxy(2,5);printf("Productor:                ");
            gotoxy(2,5);printf("Productor:   Intentando");
        break;
    }

    switch(consumidor)
    {
        case 0:
            gotoxy(2,7);printf("Consumidor:                ");
            gotoxy(2,7);printf("Consumidor:  Dormido");
        break;
        case 1:
            gotoxy(2,7);printf("Consumidor:                ");
            gotoxy(2,7);printf("Consumidor:  Trabajando");
        break;
        case 2:
            gotoxy(2,7);printf("Consumidor:                ");
            gotoxy(2,7);printf("Consumidor:  Intentando");
        break;
    }
}

int main()
{
    char contenedor[CAPACIDAD];
    int bndIni = 0;
    char tecla;
    int posProductor = 0;
    int posConsumidor = 0;
    int opc;
    int i=0;

    for(i=0; i<50; i++)
        contenedor[i] = '\0';


    Productor productor;
    Consumidor consumidor;
    TipoElemento elemento;
    //imprime encabezados
    gotoxy(50,2);printf("Productor - Consumidor");
    imprimeMarco();

    productor.estado=0;
    consumidor.estado=0;
    consumidor.tDormido = detTiempo();
    consumidor.cantElem = 0;
    //Primera vez que entra al sistema

    estado(productor.estado,consumidor.estado);
    while(tecla != 27)
    {
        if(kbhit())
            tecla=getch();
        if(bndIni == 0)
        {
            productor.cantElem = detCantElem();
            if(productor.cantElem == 0)
                productor.cantElem = 1;
            gotoxy(30,5);printf("Cant. Elementos:   %d",productor.cantElem);
            gotoxy(30,7);printf("Cant. Elementos:   %d",consumidor.cantElem);
            while(productor.cantElem > 0)
            {
                productor.estado = 1;
                elemento = produceElemento();
                posProductor = insertaElemento(contenedor,posProductor,elemento);
                mostrarElementos(posProductor,contenedor);
                delay(150);
                productor.cantElem--;
                if(consumidor.estado == 0)
                {
                    consumidor.tDormido--;
                    if(consumidor.tDormido == 0)
                        consumidor.estado = 2;
                }
                estado(productor.estado,consumidor.estado);
            }
            gotoxy(30,5);printf("Cant. Elementos:   %d",productor.cantElem);
            productor.tDormido = detTiempo();
            productor.estado = 0;
            bndIni = 1;
        }

        if(productor.estado == 2)
        {
            if(consumidor.estado == 0)
            {
                productor.cantElem = detCantElem();
                if(productor.cantElem == 0)
                    productor.cantElem=1;
                gotoxy(30,5);printf("Cant. Elementos:   %d",productor.cantElem);
                while(productor.cantElem > 0)
                {
                    productor.estado = 1;
                    elemento = produceElemento();
                    posProductor = insertaElemento(contenedor,posProductor,elemento);
                    mostrarElementos(posProductor,contenedor);
                    delay(150);
                    productor.cantElem--;
                    if(consumidor.estado == 0)
                    {
                        consumidor.tDormido--;
                        if(consumidor.tDormido == 0)
                            consumidor.estado = 2;
                    }
                    estado(productor.estado,consumidor.estado);
                }
                gotoxy(30,5);printf("Cant. Elementos:   %d",productor.cantElem);
                productor.tDormido = detTiempo();
                productor.estado = 0;
            }
        }
        else
        {
            if(consumidor.estado == 2)
            {
                if(productor.estado == 0)
                {
                    consumidor.cantElem = detCantElem();
                    if(consumidor.cantElem == 0)
                        consumidor.cantElem=1;
                    gotoxy(30,7);printf("Cant. Elementos:   %d",consumidor.cantElem);
                    while(consumidor.cantElem > 0)
                    {
                        consumidor.estado = 1;
                        posConsumidor = extraeElemento(contenedor,posConsumidor);
                        mostrarElementos(posConsumidor,contenedor);
                        delay(150);
                        consumidor.cantElem--;
                        if(productor.estado == 0)
                        {
                            productor.tDormido--;
                            if(productor.tDormido == 0)
                                productor.estado = 2;
                        }
                        estado(productor.estado,consumidor.estado);
                    }
                    gotoxy(30,7);printf("Cant. Elementos:   %d",consumidor.cantElem);
                    consumidor.tDormido = detTiempo();
                    consumidor.estado = 0;
                }
            }
            else
            {
                if(productor.estado == 0)
                {
                    productor.tDormido--;
                    if(productor.tDormido == 0)
                        productor.estado = 2;
                }
                estado(productor.estado,consumidor.estado);
                if(consumidor.estado == 0)
                {
                    consumidor.tDormido--;
                    if(consumidor.tDormido == 0)
                        consumidor.estado = 2;
                }
                estado(productor.estado,consumidor.estado);

                if((productor.estado == 2) && (consumidor.estado == 2))
                {
                    opc = rand() % 2 + 1;
                    if(opc == 1)
                    {
                        productor.estado=0;
                        productor.tDormido = detTiempo();
                    }
                    else
                    {
                        consumidor.estado = 0;
                        consumidor.tDormido = detTiempo();
                    }
                }
            }
        }
    }
    gotoxy(10,30);printf("");
    return 0;
    getch();
}
