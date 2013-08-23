/*Adriana Lizbeth Linares Rayas Cod. 210596378
  Secc. D-15 Pract.11 01/Nov/2011*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#define MAXIMO_ELEMENTOS 10
#define PRIMERA_POSICION 0
#define ULTIMA_POSICION MAXIMO_ELEMENTOS - 1
#define POSICION_INVALIDA -1
#define ELEMENTO_NULO NULL

typedef int posicion;
typedef int TipoElemento;
posicion columna=43,fila=10,z=2;

typedef struct{
    TipoElemento elementos[MAXIMO_ELEMENTOS];
    posicion inicio;
    posicion final;
}Cola;

int gotoxy(short x, short y){
   COORD coord;
   HANDLE h_stdout;

   coord.X = x;
   coord.Y = y;

   if ((h_stdout = GetStdHandle(STD_OUTPUT_HANDLE)) == INVALID_HANDLE_VALUE)
      return 0;

   if (SetConsoleCursorPosition(h_stdout, coord) == 0)
      return 0;

   return 1;
}

void inicializa(Cola *c){

    c->inicio = PRIMERA_POSICION;
    c->final = ULTIMA_POSICION;
}

int estaVacia(Cola *c){

    return (c->final + 1 == c->inicio)
        || (c->final == ULTIMA_POSICION && c->inicio == PRIMERA_POSICION);
}

int estaLlena(Cola *c){

    return (c->inicio == PRIMERA_POSICION + 1 && c->final == ULTIMA_POSICION)
        || (c->inicio == PRIMERA_POSICION && c->final == ULTIMA_POSICION - 1)
        || (c->final + 2 == c->inicio);
}

TipoElemento * frente(Cola *c){

    if(!estaVacia(c))
        return &c->elementos[c->inicio];
    else
        return ELEMENTO_NULO;
}

TipoElemento * fin(Cola *c){

    if(!estaVacia(c))
        return &c->elementos[c->final];
    else
        return ELEMENTO_NULO;
}

void imprimeError(const char mensaje[]){

    printf("%s\n", mensaje);
}

void encola(TipoElemento *x, Cola *c){
    if(!estaLlena(c)){
        if (c->final == ULTIMA_POSICION){
            c->final = PRIMERA_POSICION;
        }
        else
            c->final++;
        c->elementos[c->final] = *x;
    }
    else{
        gotoxy(columna+4,fila+9);imprimeError("LA COLA ESTA LLENA");
    }
}

void desencola(Cola *c){

    if (!estaVacia(c)){
        if (c->inicio == ULTIMA_POSICION){
            c->inicio = PRIMERA_POSICION;
        }
        else{
            c->inicio++;
        }
    }
    else{
        gotoxy(columna+4,fila+9);imprimeError("LA COLA ESTA VACIA");
    }
}

void imprimeElemento(TipoElemento *x){

    printf("%d\n", *x);
}

void imprimeCola(Cola *c){
    posicion p, q;

    if (!estaVacia(c)){
        p = c->inicio;
        if(p <= c->final){
            q = c->final;
        }
        else{
            q = ULTIMA_POSICION;
        }
        while(p <= q){
            gotoxy(columna+9,fila+(z+=2));printf("DATO[%d]: ", p);
            imprimeElemento(&c->elementos[p]);
            p++;
        }
        if(c->final < c->inicio){
            p = PRIMERA_POSICION;
            while(p <= c->final){
                gotoxy(columna+9,fila+(z+=2));printf("DATO[%d]: ", p);
                imprimeElemento(&c->elementos[p]);
                p++;
            }
        }
    }
    else{
        gotoxy(columna+4,fila+9);imprimeError("LA COLA ESTA VACIA");
    }
}

void leeElemento(TipoElemento *x){

    scanf("%d", x);
}

int main(){

    system("COLOR f9");
    int op,i;
    Cola c;
    TipoElemento x;
    inicializa(&c);

    do{
        system("cls");
        i=-2;
        while(i<=17){
            gotoxy(columna-4,fila+i);printf("|");
            gotoxy(columna+28,fila+i);printf("|");
            i++;
        }
        gotoxy(columna-3,fila-3);printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _");
        gotoxy(columna+6,fila);printf("MENU");
        gotoxy(columna,fila+2);printf("1. ENCOLAR");
        gotoxy(columna,fila+4);printf("2. DESENCOLAR");
        gotoxy(columna,fila+6);printf("3. MOSTRAR");
        gotoxy(columna,fila+8);printf("4. ANULAR");
        gotoxy(columna,fila+10);printf("5. CONSULTAR FRENTE");
        gotoxy(columna,fila+12);printf("6. CONSULTAR FIN");
        gotoxy(columna,fila+14);printf("7. SALIR");
        gotoxy(columna,fila+16);printf("ELIGE TU OPCION: ");
        gotoxy(columna-3,fila+17);printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _");
        gotoxy(columna+17,fila+16);scanf("%d",&op);
        switch(op){
            case 1:
                system("cls");
                gotoxy(columna+5,fila);printf("<< ENCOLAR ELEMENTO >>");
                if(!estaLlena(&c)){
                    gotoxy(columna+7,fila+3);printf("DATO A ENCOLAR: ");
                    fflush(stdin);
                    leeElemento(&x);
                    encola(&x, &c);
                    gotoxy(columna+4,fila+9);printf("EL DATO HA SIDO ENCOLADO");
                }
                else{
                    gotoxy(columna+5,fila+9);printf("LA COLA ESTA LLENA");
                }
                getch();
            break;
            case 2:
                system("cls");
                gotoxy(columna+5,fila);printf("<< DESENCOLAR ELEMENTO >>");
                if(!estaVacia(&c)){
                    gotoxy(columna+6,fila+3);printf("EL DATO A DESENCOLAR ES: ");
                    imprimeElemento(frente(&c));
                    desencola(&c);
                    gotoxy(columna+4,fila+9);printf("EL DATO HA SIDO DESENCOLADO");
                }
                else{
                    gotoxy(columna+5,fila+9);imprimeError("LA COLA ESTA VACIA");
                }
                getch();
            break;
            case 3:
                system("cls");
                gotoxy(columna+5,fila);printf("<< MOSTRAR COLA >>");
                if(!estaVacia(&c))
                    imprimeCola(&c);
                else{
                    gotoxy(columna+4,fila+9);imprimeError("LA COLA ESTA VACIA");
                }
                getch();
            break;
            case 4:
                system("cls");
                gotoxy(columna+5,fila);printf("<< ANULAR COLA >>");
                inicializa(&c);
                gotoxy(columna+7,fila);printf("LA COLA SE HA INICIALIZADO");
                getch();
            break;
            case 5:
                system("cls");
                gotoxy(columna+5,fila);printf("<< FRENTE DE LA COLA >>");
                if(!estaVacia(&c)){
                    gotoxy(columna+6,fila+3);printf("EL DATO DEL FRENTE ES: ");
                    imprimeElemento(frente(&c));
                }
                else{
                    gotoxy(columna+4,fila+9);imprimeError("LA COLA ESTA VACIA");
                }
                getch();
            break;
            case 6:
                system("cls");
                gotoxy(columna+5,fila);printf("<< FIN DE LA COLA >>");
                if(!estaVacia(&c)){
                    gotoxy(columna+6,fila+3);printf("EL DATO DEL FIN ES: ");
                    imprimeElemento(fin(&c));
                }
                else{
                    gotoxy(columna+4,fila+9);imprimeError("LA COLA ESTA VACIA");
                }
                getch();
            break;
            case 7:
                system("cls");
                gotoxy(columna+4,fila+9);printf("GRACIAS POR TU VISITA");
                getch();
            break;
            default:
                gotoxy(columna+4,fila+9);printf("...OPCION INCORRECTA...");
                getch();
        }
        gotoxy(columna,fila+25);system("pause");
    }while(op != 7);
    return 0;
    getch();
}
