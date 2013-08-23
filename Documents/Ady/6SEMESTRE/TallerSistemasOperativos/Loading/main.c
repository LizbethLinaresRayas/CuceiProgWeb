#include<stdio.h>
#include<conio.h>
#include<windows.h>

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

void delay(int x){
    int i;
    for(i=0;i<=x*1000000; i++);
}

void barra(){
    int i;

    system("COLOR f2");
    //printf("color(f color fondo --- 2 color letra)\n");
    for(i=30; i<60; i++){
        delay(200);
        gotoxy(i,10);printf("%c",219);
    }
    system("pause");
}

int main()
{
    gotoxy(10,10);
    printf("Cargando programa ");
    barra();
    delay(500);

    // fin del mientras
    return 0;
}
