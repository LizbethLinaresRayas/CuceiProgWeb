#include<stdio.h>
#include<conio.h>
#include<windows.h>

#define KEY_UP 'w'//72
#define KEY_LEFT 75
#define KEY_DOWN 'z'//80
#define KEY_RIGHT 77
#define INICIO 8
#define COLUMNA 8

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

void minimenu(){
        system("cls");
        gotoxy(COLUMNA,INICIO);printf("USA LAS FLECHAS Y PRESIONA ENTER PARA ELEGIR");
        gotoxy(COLUMNA,INICIO+1);printf("1.-A");
        gotoxy(COLUMNA,INICIO+2);printf("2.-B");
        gotoxy(COLUMNA,INICIO+3);printf("3.-C");
        gotoxy(COLUMNA,INICIO+4);printf("4.-D");
        gotoxy(COLUMNA,INICIO+5);printf("5.-SALIR ");
}

void opciones(int f){

    system("cls");
    minimenu();
    gotoxy(COLUMNA,f);
    if(f==INICIO+1)
        printf("1.-A");
    else
        if(f==INICIO+2)
            printf("2.-B");
        else
            if(f==INICIO+3)
                printf("3.-C");
            else
                if(f==INICIO+4)
                    printf("4.-D");
                else
                    if(f==INICIO+5)
                        printf("5.-SALIR ");
}

int menu(int *f){
    system("cls");
    switch (*f){
        case INICIO+1:printf("elegiste la opcion A");
                break;
        case INICIO+2:printf("elegiste la opcion B");
                break;
        case INICIO+3:printf("elegiste la opcion C");
                break;
        case INICIO+4:printf("elegiste la opcion D");
                break;
        case INICIO+5: printf("fin del programa");
                return 27;
                break;
    }
    return 0;
}


void flechas(char *tecla, int *f){
    switch (*tecla){
            case KEY_UP://w
                *f=*f-1;
                if ( *f <= INICIO)
                {
                    *f=INICIO+5;
                    gotoxy(COLUMNA,*f);
                }
                break;
                case KEY_DOWN://z
                    *f=*f+1;
                    if (*f >=INICIO+6)
                    {
                        *f=INICIO+1;
                        gotoxy(COLUMNA,*f);
                    }
                break;
                case KEY_RIGHT:
                    *c=*c+1;
                    if (*c >=INICIO+6)
                    {
                        *f=INICIO+1;
                        gotoxy(COLUMNA,*f);
                    }
            case 13: *tecla = menu(f);
                    getch();
            break;

    }//fin del switch
}

void delay(int x){
    int i;
    for(i=0;i<=x*1000000; i++);
}

void barra(){
    int i;
    for(i=30; i<60; i++){
        delay(200);
        gotoxy(i,10);printf("| ");
    }
}

int main(){
    int f=INICIO+1;
    char tecla;
    //gotoxy(10,10);printf("Cargando programa ");
    //barra();
    //delay(500);

    while(tecla!=27){
        opciones(f);//funcion que muestra las opciones del menu
        gotoxy(COLUMNA,f);
        tecla = getch();
        flechas(&tecla,&f);//funcion para utilizar las flechas
    }// fin del mientras
    return 0;
}


