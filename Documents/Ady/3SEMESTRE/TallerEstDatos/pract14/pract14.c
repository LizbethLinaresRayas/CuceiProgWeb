/*ADRIANA LIZBETH LINARES RAYAS SECC.D-15
COD.210596378 LIC. INFORMATICA
PRACT. 14 22/NOVIEMBRE/2011*/
#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_DOWN 80
#define KEY_RIGHT 77
#define INICIO 6
#define COLUMNA 30

typedef int tipo_dato;

typedef struct _nodo{
    tipo_dato elem;
    struct _nodo *sig;
}Nodo;

typedef Nodo *Pila;

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

void inicializa(Pila *p){

    *p = NULL;
}

int vacia(Pila p){

    return p == NULL;
}

void push(Pila *p, tipo_dato x){
    Pila aux;

    aux = (Pila)malloc(sizeof(Nodo));
    aux->elem = x;
    if ( vacia(*p)){
         aux->sig = NULL;
        *p = aux;
    }
    else{
        aux->sig = *p;
        *p = aux;
    }
}

void pop(Pila *p){
    Pila aux;

    aux = *p;
    if(aux->sig == NULL)
        *p = NULL;
    else
        *p = aux->sig;
    free(aux);
}

tipo_dato tope (Pila p){

    return p->elem;
}

void imprimeElemento(tipo_dato x, int cont){

    gotoxy(COLUMNA+15,(INICIO+10)+cont);printf(" �������ͻ");
    gotoxy(COLUMNA+15,(INICIO+10)+(1+cont));printf(" �   %d   �",x);
    gotoxy(COLUMNA+15,(INICIO+10)+(2+cont));printf(" �������ͼ");

}

void mostrar(Pila p){
    Pila aux;
    int y=0;

    aux = p;
    gotoxy(COLUMNA+18,INICIO+8);printf("PILA");
    while(aux != NULL){
        imprimeElemento(aux->elem,y);
        aux = aux->sig;
        y+=2;
    }
}

void miniMarco(){
    int i;

    gotoxy(COLUMNA-12,INICIO);printf   (" ������������������������������������������ͻ\n");
        for(i=1; i<=12; i++){
            if((i!=3) && (i!=6) && (i!=9)){
                gotoxy(COLUMNA-12,INICIO+i);printf (" �                                          �\n");
            }
        }
    gotoxy(COLUMNA-12,INICIO+12);printf(" ������������������������������������������ͼ \n\n\n");
}

void passwd(char password[],char usuario[]){
    int i,c;
    gotoxy(COLUMNA+17,INICIO+6);printf("INGRESA: ");
    gotoxy(COLUMNA+8,INICIO+9);printf("NOMBRE DE USUARIO: ");
    scanf("%s",&usuario);
    gotoxy(COLUMNA+8,INICIO+12);printf("PASSWORD: ");
    i=0;
    while((c=_getch())!=13){
        if(c==8){
            password[i]='\0';
            i--;
            printf("\b\b");
        }
        else
        {
            printf("*");
            password[i]=c;
            i++;
        }
    }
    password[i]='\0';
}

void Marco(){
    int i;

    gotoxy(COLUMNA-12,INICIO-3); printf(" ������������������������������������������ͻ\n");
        for(i=-2; i<=21; i++){
            if((i!=0) && (i!=3) && (i!=6) && (i!=9) && (i!=12) && (i!=15) && (i!=18)){
                gotoxy(COLUMNA-12,INICIO+i);printf (" �                                          �\n");
            }
        }
    gotoxy(COLUMNA-12,INICIO+21);printf(" ������������������������������������������ͼ \n\n\n");
}

void MenuPrincipal(){
    system("cls");
    Marco();
    gotoxy(COLUMNA-12,INICIO);   printf(" �             MENU                         �");
    gotoxy(COLUMNA-12,INICIO+3); printf(" �          INICIALIZAR                     �");
    gotoxy(COLUMNA-12,INICIO+6); printf(" �          INSERTAR                        �");
    gotoxy(COLUMNA-12,INICIO+9); printf(" �          ELIMINAR                        �");
    gotoxy(COLUMNA-12,INICIO+12);printf(" �          MOSTRAR                         �");
    gotoxy(COLUMNA-12,INICIO+15);printf(" �          CONSULTAR TOPE                  �");
    gotoxy(COLUMNA-12,INICIO+18);printf(" �          SALIR                           �");
}

void opciones(int f){

    system("cls");
    MenuPrincipal();
    gotoxy(COLUMNA,f);
    if(f == INICIO+3)
        printf("INICIALIZAR");
    else
        if(f == INICIO+6)
            printf("INSERTAR");
        else
            if(f == INICIO+9)
                printf("ELIMINAR");
            else
                if(f == INICIO+12)
                    printf("MOSTRAR");
                else
                    if(f == INICIO+15)
                        printf("CONSULTAR TOPE");
                    else
                        if(f == INICIO+18)
                            printf("SALIR");
}

void Flechas(char *tecla, int *f){

    switch(*tecla){
        case KEY_UP:
            *f=*f-3;
            if(*f <= INICIO){
                *f=INICIO+18;
                gotoxy(COLUMNA,*f);
            }
        break;
        case KEY_DOWN:
            *f=*f+3;
            if(*f >= INICIO+21){
                *f=INICIO+3;
                gotoxy(COLUMNA,*f);
            }
        break;
        case 13:
            *tecla=menu(f);
            getch();
        break;
    }
}

int menu(int *f){
    int columna=43,fila=6;
    int op,i,j;
    static bnd=0;
    static Pila p;
    tipo_dato x;

    system("cls");
    switch(*f){
        case INICIO+3:
            system("cls");
            gotoxy(COLUMNA+10,INICIO);  printf(" ������������������ͻ\n");
            gotoxy(COLUMNA+10,INICIO+1);printf(" �    INICIALIZAR   �\n");
            gotoxy(COLUMNA+10,INICIO+2);printf(" ������������������ͼ \n\n\n");
            if(bnd == 0){
                inicializa(&p);
                gotoxy(COLUMNA,INICIO+8);printf(" �������������������������������������������������ͻ\n");
                gotoxy(COLUMNA,INICIO+9);printf(" �       ...LA PILA HA SIDO INICIALIZADA...        �\n");
                gotoxy(COLUMNA,INICIO+10);printf(" �������������������������������������������������ͼ \n\n\n");
                bnd=1;
            }
            else{
                while(!vacia(p)){
                    pop(&p);
                }
                gotoxy(COLUMNA,INICIO+8);printf(" �������������������������������������������������ͻ\n");
                gotoxy(COLUMNA,INICIO+9);printf(" �       ...LA PILA HA SIDO INICIALIZADA...        �\n");
                gotoxy(COLUMNA,INICIO+10);printf(" �������������������������������������������������ͼ \n\n\n");
            }
            getch();
        break;
        case INICIO+6:
            system("cls");
            gotoxy(COLUMNA+10,INICIO);  printf(" ������������������ͻ\n");
            gotoxy(COLUMNA+10,INICIO+1);printf(" �     INSERTAR     �\n");
            gotoxy(COLUMNA+10,INICIO+2);printf(" ������������������ͼ \n\n\n");
            if(bnd == 1){
                gotoxy(COLUMNA+12,INICIO+4);printf("\n\n\t\tINGRESA EL ELEMENTO A INSERTAR: ");
                scanf("%d",&x);
                push(&p,x);
                gotoxy(COLUMNA,INICIO+13);printf(" �������������������������������������������������ͻ\n");
                gotoxy(COLUMNA,INICIO+14);printf(" �              ... ELEMENTO INSERTADO ...         �\n");
                gotoxy(COLUMNA,INICIO+15);printf(" �������������������������������������������������ͼ \n\n\n");
            }
            else{
                gotoxy(COLUMNA,INICIO+13);printf(" �������������������������������������������������ͻ\n");
                gotoxy(COLUMNA,INICIO+14);printf(" �       ... NO SE HA INICIALIZADO LA PILA ...     �\n");
                gotoxy(COLUMNA,INICIO+15);printf(" �������������������������������������������������ͼ \n\n\n");
            }
            getch();
        break;
        case INICIO+9:
            system("cls");
            gotoxy(COLUMNA+10,INICIO);  printf(" ������������������ͻ\n");
            gotoxy(COLUMNA+10,INICIO+1);printf(" �     ELIMINAR     �\n");
            gotoxy(COLUMNA+10,INICIO+2);printf(" ������������������ͼ \n\n\n");
            if(!vacia(p)){
                gotoxy(COLUMNA+9,INICIO+6);printf("ELEMENTO A ELIMINAR: ");
                imprimeElemento(tope(p),0);
                pop(&p);
                gotoxy(COLUMNA,INICIO+19);printf(" �������������������������������������������������ͻ\n");
                gotoxy(COLUMNA,INICIO+20);printf(" �             ... ELEMENTO ELIMINADO...           �\n");
                gotoxy(COLUMNA,INICIO+21);printf(" �������������������������������������������������ͼ \n\n\n");
            }
            else{
                gotoxy(COLUMNA,INICIO+13);printf(" �������������������������������������������������ͻ\n");
                gotoxy(COLUMNA,INICIO+14);printf(" �                  ... PILA VACIA ...             �\n");
                gotoxy(COLUMNA,INICIO+15);printf(" �������������������������������������������������ͼ \n\n\n");
            }
            getch();
        break;
        case INICIO+12:
            system("cls");
            gotoxy(COLUMNA+10,INICIO);  printf(" ������������������ͻ\n");
            gotoxy(COLUMNA+10,INICIO+1);printf(" �      MOSTRAR     �\n");
            gotoxy(COLUMNA+10,INICIO+2);printf(" ������������������ͼ \n\n\n");
            if(!vacia(p)){
                mostrar(p);
            }
            else{
                gotoxy(COLUMNA,INICIO+13);printf(" �������������������������������������������������ͻ\n");
                gotoxy(COLUMNA,INICIO+14);printf(" �                  ... PILA VACIA ...             �\n");
                gotoxy(COLUMNA,INICIO+15);printf(" �������������������������������������������������ͼ \n\n\n");
            }
            getch();
        break;
        case INICIO+15:
            system("cls");
            gotoxy(COLUMNA+10,INICIO);  printf(" ������������������ͻ\n");
            gotoxy(COLUMNA+10,INICIO+1);printf(" �  CONSULTAR TOPE  �\n");
            gotoxy(COLUMNA+10,INICIO+2);printf(" ������������������ͼ \n\n\n");
            if(!vacia(p)){
                gotoxy(COLUMNA+11,INICIO+7);printf("TOPE DE LA PILA: ");
                imprimeElemento(tope(p),0);
            }
            else{
                gotoxy(COLUMNA,INICIO+13);printf(" �������������������������������������������������ͻ\n");
                gotoxy(COLUMNA,INICIO+14);printf(" �                  ... PILA VACIA ...             �\n");
                gotoxy(COLUMNA,INICIO+15);printf(" �������������������������������������������������ͼ \n\n\n");
            }
            getch();
        break;
        case INICIO+18:
            system("cls");
            gotoxy(COLUMNA+10,INICIO);  printf(" ������������������ͻ\n");
            gotoxy(COLUMNA+10,INICIO+1);printf(" �       SALIR      �\n");
            gotoxy(COLUMNA+10,INICIO+2);printf(" ������������������ͼ \n\n\n");
            gotoxy(COLUMNA-8,INICIO+20);printf(" �������������������������������������������������ͻ\n");
            gotoxy(COLUMNA-8,INICIO+21);printf(" �          ... REGRESAR A MENU INICIAL ...        �\n");
            gotoxy(COLUMNA-8,INICIO+22);printf(" �������������������������������������������������ͼ \n\n\n");
            return 27;
            getch();
        break;
    }
    return 0;
}

void PantallaPrincipal(){
    system("COLOR f5");
    system("cls");
    gotoxy(COLUMNA+3,INICIO);printf("...BIENVENIDO...");
    gotoxy(COLUMNA-14,INICIO+18);printf(" �������������������������������������������������ͻ\n");
    gotoxy(COLUMNA-14,INICIO+19);printf(" �  SI DECEAS INGRESAR NECESITAS TENER UNA CUENTA  �\n");
    gotoxy(COLUMNA-14,INICIO+20);printf(" �������������������������������������������������ͼ \n\n\n");
    gotoxy(COLUMNA-12,INICIO+3); printf(" �          ENTRAR                          �\n");
    gotoxy(COLUMNA-12,INICIO+6); printf(" �          CREAR UNA CUENTA                �\n");
    gotoxy(COLUMNA-12,INICIO+9); printf(" �          SALIR                           �\n");
}

void opcPantalla(int fl){

    system("cls");
    PantallaPrincipal();
    miniMarco();
    gotoxy(COLUMNA,fl);
    if(fl == INICIO+3)
        printf("ENTRAR");
    else
        if(fl == INICIO+6)
            printf("CREAR UNA CUENTA");
        else
            if(fl == INICIO+9)
                printf("SALIR");
}

void FlePant(char *tecla, int *fl){

    switch(*tecla){
        case KEY_UP:
            *fl=*fl-3;
            if(*fl <= INICIO){
                *fl=INICIO+9;
                gotoxy(COLUMNA,*fl);
            }
        break;
        case KEY_DOWN:
            *fl=*fl+3;
            if(*fl >= INICIO+12){
                *fl=INICIO+3;
                gotoxy(COLUMNA,*fl);
            }
        break;
        case 13:
            *tecla=menuPant(fl);
            getch();
        break;
    }
}

int menuPant(int *fl){
    system("COLOR f5");
    static char password[15], usuario[15];
    static char pass[15],usu[15];
    char tecla1;
    int f=INICIO+3;
    int columna=43,fila=6;
    static int i=0,b=0,opcion;

    system("cls");
    switch(*fl){
        case INICIO+3:
            system("cls");
            gotoxy(COLUMNA+10,INICIO);  printf(" ������������������ͻ\n");
            gotoxy(COLUMNA+10,INICIO+1);printf(" �       ENTRAR     �\n");
            gotoxy(COLUMNA+10,INICIO+2);printf(" ������������������ͼ \n\n\n");
            if(b == 1){
                do{
                    passwd(pass,usu);
                    if(strcmp(pass,password) == 0 && strcmp(usu,usuario) == 0){
                        system("COLOR f6");
                        while(tecla1 != 27){
                            opciones(f);
                            gotoxy(COLUMNA,f);
                            tecla1=getch();
                            Flechas(&tecla1,&f);
                        }
                    }
                    else{
                        gotoxy(COLUMNA-10,INICIO+16);printf(" �������������������������������������������������ͻ\n");
                        gotoxy(COLUMNA-10,INICIO+17);printf(" �           ...PASSWORD INCORRECTO...             �\n");
                        gotoxy(COLUMNA-10,INICIO+18);printf(" �������������������������������������������������ͼ \n\n\n");
                        i++;
                    }
                }while(i>3);
            }
            else{
                gotoxy(COLUMNA,INICIO+6);printf(" �������������������������������������������������ͻ\n");
                gotoxy(COLUMNA,INICIO+7);printf(" �         ...NO HAY CUENTA EXISTENTE...           �\n");
                gotoxy(COLUMNA,INICIO+8);printf(" �������������������������������������������������ͼ \n\n\n");
            }
            getch();
        break;
        case INICIO+6:
            system("cls");
            gotoxy(COLUMNA+10,INICIO);  printf(" ������������������ͻ\n");
            gotoxy(COLUMNA+10,INICIO+1);printf(" �   CREAR CUENTA   �\n");
            gotoxy(COLUMNA+10,INICIO+2);printf(" ������������������ͼ \n\n\n");
            if(b == 0){
                passwd(password,usuario);
                gotoxy(COLUMNA-7,INICIO+20);printf(" �������������������������������������������������ͻ\n");
                gotoxy(COLUMNA-7,INICIO+21);printf(" �        ... LA CUENTA HA SIDO CREADA ...         �\n");
                gotoxy(COLUMNA-7,INICIO+22);printf(" �������������������������������������������������ͼ \n\n\n");
                b=1;
            }
            else{
                gotoxy(COLUMNA-5,INICIO+10);printf(" YA EXISTE UNA CUENTA DECEAS CAMBIARLA? 1.SI 2.NO ");
                scanf("%d",&opcion);
                if(opcion == 1){
                    system("cls");
                    gotoxy(COLUMNA+10,INICIO);  printf(" ������������������ͻ\n");
                    gotoxy(COLUMNA+10,INICIO+1);printf(" � MODIFICAR CUENTA �\n");
                    gotoxy(COLUMNA+10,INICIO+2);printf(" ������������������ͼ \n\n\n");
                    passwd(password,usuario);
                    gotoxy(COLUMNA-7,INICIO+20);printf(" �������������������������������������������������ͻ\n");
                    gotoxy(COLUMNA-7,INICIO+21);printf(" �      ... LOS CAMBIOS HAN SIDO GUARDADOS ...     �\n");
                    gotoxy(COLUMNA-7,INICIO+22);printf(" �������������������������������������������������ͼ \n\n\n");
                }
                else{
                    gotoxy(COLUMNA-7,INICIO+20);printf(" �������������������������������������������������ͻ\n");
                    gotoxy(COLUMNA-7,INICIO+21);printf(" �        ... NO SE REALIZO NINGUN CAMBIO ...      �\n");
                    gotoxy(COLUMNA-7,INICIO+22);printf(" �������������������������������������������������ͼ \n\n\n");
                }
            }
            getch();
        break;
        case INICIO+9:
            system("cls");
            gotoxy(COLUMNA-6,INICIO+14);printf(" �������������������������������������������������ͻ\n");
            gotoxy(COLUMNA-6,INICIO+15);printf(" �          ... GRACIAS POR TU VISITA ...          �\n");
            gotoxy(COLUMNA-6,INICIO+16);printf(" �������������������������������������������������ͼ \n\n\n");
            return 27;
            getch();
    }
}

int main(){
    system("COLOR f5");
    int f=INICIO+3;
    int fl=INICIO+3;
    char tecla;

    while(tecla != 27){
        opcPantalla(fl);
        gotoxy(COLUMNA,fl);
        tecla=getch();
        FlePant(&tecla,&fl);
    }
    getch();
    return 0;
}
