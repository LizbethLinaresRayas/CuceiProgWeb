#include <stdio.H>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "cola.h"

int main(){
    system("COLOR b5");
    int f=INICIO+3;
    int fl=INICIO+3;
    char tecla;
    PantallaPrincipal();
    miniMarco();

    while(tecla != 27){
        opcPantalla(fl);
        gotoxy(COLUMNA,fl);
        tecla=getch();
        FlePant(&tecla,&fl);
    }
    getch();
    return 0;
}
