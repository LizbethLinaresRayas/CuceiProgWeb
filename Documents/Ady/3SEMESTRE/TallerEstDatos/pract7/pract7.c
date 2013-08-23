#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define Max 100
#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_DOWN 80
#define KEY_RIGHT 77
#define INICIO 6
#define COLUMNA 46
int band=0;

typedef struct{
    char Nombre[20];
    char ApellidoP[15];
    char ApellidoM[15];
    int Edad;
    float Promedio;
    int Semestre;
}Alumno;

typedef union {
    char nombre[20];
    char ap[15];
    char am[15];
    int edad;
    float prom;
    int sem;
}aux;

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

void Captura(Alumno A[Max], int *cont){
    int columna=10,fila=15;

    gotoxy(columna+31,fila-3);printf("Ingresa los Siguientes Datos del Alumno:");
    gotoxy(columna,fila);printf("Apellido Paterno");
    fflush(stdin);
    gotoxy(columna+2,fila+2);gets(A[*cont].ApellidoP);
    strupr(A[*cont].ApellidoP);
    gotoxy(columna+20,fila);printf("Apellido Materno");
    fflush(stdin);
    gotoxy(columna+22,fila+2);gets(A[*cont].ApellidoM);
    strupr(A[*cont].ApellidoM);
    gotoxy(columna+45,fila);printf("Nombre");
    fflush(stdin);
    gotoxy(columna+41,fila+2);gets(A[*cont].Nombre);
    strupr(A[*cont].Nombre);
    gotoxy(columna+62,fila);printf("Edad");
    gotoxy(columna+63,fila+2);scanf("%d",&A[*cont].Edad);
    gotoxy(columna+72,fila);printf("Promedio");
    gotoxy(columna+74,fila+2);scanf("%f",&A[*cont].Promedio);
    gotoxy(columna+84,fila);printf("Semestre");
    gotoxy(columna+86,fila+2);scanf("%d",&A[*cont].Semestre);
    (*cont) ++;
    band=1;
    gotoxy(columna+40,fila+8);printf("...DATOS CAPTURADOS...");
}

void intercambia(Alumno A[Max], int cont1, int cont2){
    aux Aux;

    if (A[cont1].Edad != A[cont2].Edad){
        strcpy(Aux.nombre,A[cont1].Nombre);
        strcpy(A[cont1].Nombre,A[cont2].Nombre);
        strcpy(A[cont2].Nombre,Aux.nombre);
        strcpy(Aux.ap,A[cont1].ApellidoP);
        strcpy(A[cont1].ApellidoP,A[cont2].ApellidoP);
        strcpy(A[cont2].ApellidoP,Aux.ap);
        strcpy(Aux.am,A[cont1].ApellidoM);
        strcpy(A[cont1].ApellidoM,A[cont2].ApellidoM);
        strcpy(A[cont2].ApellidoM,Aux.am);
        Aux.edad = A[cont1].Edad;
        A[cont1].Edad = A[cont2].Edad;
        A[cont2].Edad = Aux.edad;
        Aux.prom = A[cont1].Promedio;
        A[cont1].Promedio = A[cont2].Promedio;
        A[cont2].Promedio = Aux.prom;
        Aux.sem = A[cont1].Semestre;
        A[cont1].Semestre = A[cont2].Semestre;
        A[cont2].Semestre = Aux.sem;
    }
}

void seleccionEdad(Alumno A[Max], int cont){
    register int i = -1, j = -1, menor = -1;

    for(i=0; i<cont-1; i++){
        menor=i;
        for(j=i+1; j<cont; j++){
            if (A[j].Edad > A[menor].Edad){
                menor = j;
            }
        }
        if (i != menor){
		    intercambia(A,menor,i);
        }
    }
}

void shellSortSem(Alumno A[Max], int cont){
    register int i=-1, j=-1, incremento=-1;
    int paso=2,edad,sem;
    char nom[20],ap[15],am[15];
    float prom;

    incremento=cont/paso;
    while(incremento>0){
        for(i=incremento; i<cont; i++){
            j=i;
            strcpy(nom,A[i].Nombre);
            strcpy(ap,A[i].ApellidoP);
            strcpy(am,A[i].ApellidoM);
            edad=A[i].Edad;
            prom=A[i].Promedio;
            sem=A[i].Semestre;
            while(j >= incremento && (A[j-incremento].Semestre < sem)){
                strcpy(A[j].Nombre,A[j-incremento].Nombre);
                strcpy(A[j].ApellidoP,A[j-incremento].ApellidoP);
                strcpy(A[j].ApellidoM,A[j-incremento].ApellidoM);
                A[j].Edad=A[j-incremento].Edad;
                A[j].Promedio=A[j-incremento].Promedio;
                A[j].Semestre=A[j-incremento].Semestre;
                j=j-incremento;
            }
            strcpy(A[j].Nombre,nom);
            strcpy(A[j].ApellidoP,ap);
            strcpy(A[j].ApellidoM,am);
            A[j].Edad=edad;
            A[j].Promedio=prom;
            A[j].Semestre=sem;
        }
        incremento /= paso;
    }
}

void quickSortAP(Alumno A[Max], int primero, int ultimo){
    register int i=primero, j=ultimo;
    char pivote[15];
    strcpy(pivote,A[(primero+ultimo) / 2].ApellidoP);

    do{
        while(strcmp(A[i].ApellidoP,pivote) < 0){
            i++;
        }
        while(strcmp(A[j].ApellidoP,pivote) > 0){
            j--;
        }
        if(i <= j){
            intercambia(A,i,j);
            i++;
            j--;
        }
    }while(i <= j);
    if(primero < j){
        quickSortAP(A, primero, j);
    }
    if(ultimo > i){
        quickSortAP(A, i, ultimo);
    }
}

void burbujaMejoradoAM(Alumno A[Max], int cont){
    register int i=-1, j=-1, band=0;

    i = 0;
    while (i<cont-1 && !band){
        band=1;
        for(j=0; j<cont-1; j++){
            if(strcmp(A[j].ApellidoM,A[j+1].ApellidoM)  > 0){
                intercambia(A,j,(j+1));
                band = 0;
            }
        }
        i++;
    }
}

void insercionNom(Alumno A[Max],int cont){
    register int i=-1, j=-1;
    aux Aux;

    for (i=1; i<cont; i++){
        strcpy(Aux.nombre,A[i].Nombre);
        j=i-1;
        while((j >= 0) && strcmp(Aux.nombre,A[j].Nombre) < 0){
            intercambia(A,(j+1),j);
            j--;
        }
        strcpy(A[j+1].Nombre,Aux.nombre);
    }
}

int busquedaBinaria(Alumno A[Max], int n, char ap[20], char nom[15]){
    int izquierda=0, derecha=n-1, medio;

    while(izquierda <= derecha){
        medio=(izquierda + derecha)/2;
        if((strcmp(A[medio].ApellidoP,ap) == 0) && (strcmp(A[medio].Nombre,nom) == 0)){
            return medio;
        }
        else{
            if((strcmp(A[medio].ApellidoP,ap) > 0) && (strcmp(A[medio].Nombre,nom) > 0)){
                izquierda=medio+1;
            }
            else{
                derecha=medio-1;
            }
        }
    }
    return -1;
}

void mostrarAlum(Alumno A[Max], int i){
    int columna=15,fila=10;

    gotoxy(columna,fila);printf("Apellido Paterno");
    gotoxy(columna+20,fila);printf("Apellido Materno");
    gotoxy(columna+42,fila);printf("Nombre");
    gotoxy(columna+60,fila);printf("Edad");
    gotoxy(columna+70,fila);printf("Promedio");
    gotoxy(columna+80,fila);printf("semestre");
    gotoxy(columna,fila+(i+2));printf("%s",A[i].ApellidoP);
    gotoxy(columna+22,fila+(i+2));printf("%s",A[i].ApellidoM);
    gotoxy(columna+42,fila+(i+2));printf("%s",A[i].Nombre);
    gotoxy(columna+61,fila+(i+2));printf("%d",A[i].Edad);
    gotoxy(columna+71,fila+(i+2));printf("%.2f",A[i].Promedio);
    gotoxy(columna+82,fila+(i+2));printf("%d",A[i].Semestre);
}

void Eliminar(Alumno A[Max], int *cont,int i, char nombre[20], char ap[15]){
    int columna=10,fila=20;
    char op;

    if((strcmp(A[i].Nombre,nombre) == 0) && (strcmp(A[i].ApellidoP,ap) == 0)){
        system("cls");
        gotoxy(48,6);printf("DATOS CORRECTOS");
        mostrarAlum(A,i);
        gotoxy(columna,fila-3);printf("ESTA SEGURO QUE DECEA ELIMINAR A ESTE ALUMNO S o N: ");
        scanf("%s",&op);
        if((op == 's') || (op == 'S')){
            A[i].Edad=0;
            gotoxy(columna+35,fila+20);printf("...ALUMNO ELIMINADO...");
            (*cont)--;
        }
        else{
            if((op == 'n') || (op == 'N'))
                gotoxy(columna+35,fila+20);printf("...NO SE REALIZO NINGUNA MODIFICACION...");
        }
    }
    else{
        system("cls");
        if((strcmp(A[i].Nombre,nombre) != 0) && (strcmp(A[i].ApellidoP,ap) != 0))
            gotoxy(48,6);printf("...EL VIDEO NO EXISTE...");
    }
}

void MenuPrincipal(){

    system("cls");
    gotoxy(COLUMNA+3,INICIO); printf("MENU");
    gotoxy(COLUMNA,INICIO+3); printf("* AGREGAR");
    gotoxy(COLUMNA,INICIO+6); printf("* ELIMINAR");
    gotoxy(COLUMNA,INICIO+9); printf("* MOSTRAR");
    gotoxy(COLUMNA,INICIO+12);printf("* BUSCAR");
    gotoxy(COLUMNA,INICIO+15);printf("* SALIR");
}

void opciones(int f){

    system("cls");
    MenuPrincipal();
    gotoxy(COLUMNA,f);
    if(f==INICIO+3)
        printf("* AGREGAR");
    else
        if(f==INICIO+6)
            printf("* ELIMINAR");
        else
            if(f==INICIO+9)
                printf("* MOSTRAR");
            else
                if(f==INICIO+12)
                    printf("* BUSCAR");
                else
                    if(f==INICIO+15)
                        printf("* SALIR");
}

int menu(int *f){
    int op,i,opcion,x,columna=43,fila=6;
    int pos;
    char nombre[20];
    char aapp[15];
    static  Alumno Alum[Max];
    static int contAlum=0;

    system("cls");
    switch(*f){
        case INICIO+3:
            system("cls");
            gotoxy(50,10);printf("AGREGAR ALUMNO");
            Captura(Alum,&contAlum);
            gotoxy(43,27);printf("...PRESIONA UNA TECLA PARA CONTINUAR...");
            getch();
        break;
        case INICIO+6:
            system("cls");
            if(band == 1){
                gotoxy(columna,fila+3);printf("ELIMINAR ALUMNO");
                gotoxy(columna-25,fila+6);printf("APELLIDO PATERNO ");
                fflush(stdin);
                gotoxy(columna-23,fila+8);gets(aapp);
                strupr(aapp);
                gotoxy(columna+5,fila+6);printf("NOMBRE ");
                fflush(stdin);
                gotoxy(columna,fila+8);gets(nombre);
                strupr(nombre);
                for(i=0; i<contAlum; i++)
                    if(Alum[i].Edad != 0)
                        Eliminar(Alum,&contAlum,i,nombre,aapp);
                    else
                        gotoxy(columna,fila+24);printf("EL ALUMNO NO EXISTE");
                gotoxy(40,27);printf("...PRESIONA UNA TECLA PARA CONTINUAR...");
                getch();
            }
            else{
                gotoxy(40,7);printf("...NO HAY DATOS CAPTURADOS...");
                getch();
            }
        break;
        case INICIO+9:
            if(band == 1){
                do{
                    system("cls");
                    gotoxy(columna,fila+3);printf("MOSTRAR ALUMNO");
                    gotoxy(columna,fila+6);printf("1. NOMBRE");
                    gotoxy(columna,fila+9);printf("2. APELLIDO PATERNO");
                    gotoxy(columna,fila+12);printf("3. APELLIDO MATERNO");
                    gotoxy(columna,fila+15);printf("4. EDAD");
                    gotoxy(columna,fila+18);printf("5. SEMESTRE");
                    gotoxy(columna,fila+21);printf("6. SALIR");
                    gotoxy(columna,fila+24);printf("Elige una Opcion: ");
                    scanf("%d",&opcion);
                    switch(opcion){
                        case 1:
                            system("cls");
                            gotoxy(columna+5,fila);printf("ALUMNOS");
                            insercionNom(Alum,contAlum);
                            i=0;
                            do{
                                mostrarAlum(Alum,i);
                                i++;
                            }while(i<contAlum);
                            gotoxy(columna,fila+(i+15));printf("...PRESIONA UNA TECLA PARA CONTINUAR...");
                            getch();
                        break;
                        case 2:
                            system("cls");
                            gotoxy(columna+5,fila);printf("ALUMNOS");
                            quickSortAP(Alum,0,(contAlum-1));
                            for(i=0; i<contAlum; i++)
                                mostrarAlum(Alum,i);
                            gotoxy(columna,fila+(i+15));printf("...PRESIONA UNA TECLA PARA CONTINUAR...");
                            getch();
                        break;
                        case 3:
                            system("cls");
                            gotoxy(columna+5,fila);printf("ALUMNOS");
                            burbujaMejoradoAM(Alum,contAlum);
                            for(i=0; i<contAlum; i++)
                                mostrarAlum(Alum,i);
                            gotoxy(columna,fila+(i+15));printf("...PRESIONA UNA TECLA PARA CONTINUAR...");
                            getch();
                        break;
                        case 4:
                            system("cls");
                            gotoxy(columna+5,fila);printf("ALUMNOS");
                            seleccionEdad(Alum,contAlum);
                            for(i=0; i<contAlum; i++)
                                mostrarAlum(Alum,i);
                            gotoxy(columna,fila+(i+15));printf("...PRESIONA UNA TECLA PARA CONTINUAR...");
                            getch();
                        break;
                        case 5:
                            system("cls");
                            gotoxy(columna+5,fila);printf("ALUMNOS");
                            shellSortSem(Alum,contAlum);
                            for(i=0; i<contAlum; i++)
                                mostrarAlum(Alum,i);
                            gotoxy(columna,fila+(i+15));printf("...PRESIONA UNA TECLA PARA CONTINUAR...");
                            getch();
                        break;
                        case 6:
                            system("cls");
                            gotoxy(columna+5,fila);printf("ABANDONAR MENU MOSTRAR...");
                            gotoxy(columna,fila+(i+15));printf("...PRESIONA UNA TECLA PARA CONTINUAR...");
                            getch();
                        break;
                        default:
                            system("cls");
                            gotoxy(columna+5,fila);printf("OPCION INCORRECTA");
                            gotoxy(columna,fila+(i+15));printf("...PRESIONA UNA TECLA PARA CONTINUAR...");
                            getch();
                    }
                }while(opcion != 6);
            }
            else{
                gotoxy(40,7);printf("...NO HAY DATOS CAPTURADOS...");
                getch();
            }
        break;
        case INICIO+12:
            if(band == 1){
                system("cls");
                gotoxy(columna,fila+3);printf("BUSQUEDA");
                gotoxy(columna-25,fila+6);printf("APELLIDO PATERNO");
                fflush(stdin);
                gotoxy(columna-23,fila+8);gets(aapp);
                strupr(aapp);
                gotoxy(columna-10,fila+6);printf("NOMBRE:");
                fflush(stdin);
                gotoxy(columna-10,fila+6);gets(nombre);
                strupr(nombre);
                pos=busquedaBinaria(Alum,contAlum,aapp,nombre);
                if(x != -1){
                    if(Alum[pos].Edad != 0){
                        system("cls");
                        printf("ALUMNOS ENCONTRADOS");
                        mostrarAlum(Alum,pos);
                        gotoxy(40,7);printf("...PRESIONA UNA TECLA PARA CONTINUAR...");
                        getch();
                    }
                    else
                        gotoxy(43,23);printf("ALUMNO NO ENCONTRADO");
                }
                else
                    gotoxy(43,23);printf("ALUMNO NO ENCONTRADO");
                gotoxy(40,7);printf("...PRESIONA UNA TECLA PARA CONTINUAR...");
                getch();
            }
            else{
                gotoxy(40,7);printf("...NO HAY DATOS CAPTURADOS...");
                getch();
            }
        break;
        case INICIO+15:
            system("cls");
            gotoxy(columna+15,fila);printf("...ABANDONAR PROGRAMA...");
            gotoxy(columna+5,fila+2);printf("...PRESIONA UNA TECLA PARA CONTINUAR...\n");
            getch();
            return 27;
        break;
    }
    return 0;
}

void Flechas(char *tecla, int *f){

    switch(*tecla){
            case KEY_UP:
                *f=*f-3;
                if(*f <= INICIO){
                    *f=INICIO+15;
                    gotoxy(COLUMNA,*f);
                }
            break;
            case KEY_DOWN:
                *f=*f+3;
                if(*f >=INICIO+18){
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


int main()
{
    system("COLOR F3");
    int f=INICIO+3;
    char tecla;

    while(tecla!=27){
        opciones(f);
        gotoxy(COLUMNA,f);
        tecla=getch();
        Flechas(&tecla,&f);
    }
    getch();
    return 0;
}
