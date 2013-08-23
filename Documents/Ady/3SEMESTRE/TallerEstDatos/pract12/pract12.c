/*Adriana Lizbeth Linares Rayas Cod. 210596378
Secc. D-15 Pract. No.12 08-NOV-2011*/
#include <stdio.h>
#include <conio.h>
#include <string.h>
#define TAM 100

typedef char TipoDato;

typedef struct{
    TipoDato nombre[15];
    struct Nodo *sig;
}Nodo;

typedef struct{
    Nodo postre[TAM];
    int cont;
}ListaP;

typedef Nodo Ingrediente;
typedef Ingrediente posicion;

void inicializa(ListaP *l){
    int i;

    for(i=1; i<TAM; i++)
        l->postre->sig=NULL;
    l->cont=-1;
}

Ingrediente *creanodo(){
    Nodo *aux;

    aux=(Ingrediente*)malloc(sizeof(Nodo));
    return aux;
}

void insertaIngrediente(Nodo **Ingrediente, TipoDato dato[15]){
    posicion *aux;
    posicion p;
    p.sig=NULL;

    aux=creanodo();
    strcpy(aux->nombre,dato);
    if(p.sig == NULL){
        aux->sig=*Ingrediente;
        *Ingrediente=aux;
    }
	else{
		aux->sig=p.sig;
		p.sig=aux->sig;
	}
}

void insertaPostre(ListaP *l, TipoDato dato[15]){

    l->cont++;
    strcpy(l->postre[l->cont].nombre,dato);

}

int busquedaLineal(ListaP l, TipoDato dato[15]){
    int i = 0;

    while (i< l.cont && strcmp(dato,l.postre[i].nombre) != 0){
        i++;
    }
    return i;
}

void mostrarPostre(ListaP l){
    int i, cont;

    for(i=0; i <= l.cont; i++){
        printf("\n\n\t\t");
        for(cont=0; cont<30; cont++)
            printf("-");
        printf("\n");
        printf("\n\n\t\t\t%s",l.postre[i].nombre);
        if(l.postre[i].sig == NULL)
            printf("\n\n\t\t\tNO HAY INGREDIENTES");
        else
            printf("\n\n\t\t\t%s",l.postre[i].sig);
    }
}

void suprimePostre(ListaP *l, int pos){

    strcpy(l->postre[pos].nombre, l->postre[pos+1].nombre);
    l->cont--;
}


int main()
{
    system("COLOR f2");
    int op,opc,pos,b=0;
    ListaP l;
    Nodo I;
    inicializa(&l);
    TipoDato Dato[15];

    do{
        system("cls");
        printf("\n\n\t\t\t    MENU");
        printf("\n\n\t\t\t1. AGREGAR");
        printf("\n\n\t\t\t2. ELIMINAR");
        printf("\n\n\t\t\t3. CONSULTAR");
        printf("\n\n\t\t\t4. MOSTRAR");
        printf("\n\n\t\t\t5. SALIR");
        printf("\n\n\t\t*ELIGE TU OPCION: ");
        scanf("%d",&opc);
        switch(opc){
            case 1:
                do{
                    system("cls");
                    printf("\n\n\t\t\t<< AGREGAR >>\n");
                    printf("\n\n\t\t\t1. POSTRE");
                    printf("\n\n\t\t\t2. INGREDIENTE");
                    printf("\n\n\t\t\t3. REGRESAR MENU PRINCIPAL");
                    printf("\n\n\t\t*ELIGE TU OPCION: ");
                    scanf("%d",&op);
                    switch(op){
                        case 1:
                            system("cls");
                            printf("\n\n\t\t\t<< AGREGAR POSTRE >>\n");
                            printf("\n\n\t\t*NOMBRE DEL POSTRE: ");
                            fflush(stdin);
                            gets(Dato);
                            strupr(Dato);
                            pos=busquedaLineal(l, Dato);
                            insertaPostre(&l,Dato);
                            printf("\n\n\t\t\t...SE HAN GUARDADO LOS DATOS...");
                            getch();
                        break;
                        case 2:
                            system("cls");
                            printf("\n\n\t\t\t<< AGREGAR INGREDIENTE >>\n");
                            printf("\n\n\t\t\t*INGRESA EL NOMBRE DEL POSTRE: ");
                            fflush(stdin);
                            gets(Dato);
                            strupr(Dato);
                            pos=busquedaLineal(l, Dato);
                            if(pos != -1){
                                printf("\n\n\t\t\t*NOMBRE DEL INGREDIENTE: ");
                                fflush(stdin);
                                gets(Dato);
                                strupr(Dato);
                                insertaIngrediente(&l.postre[pos].sig,Dato);
                                printf("\n\n\t\t\t...SE HAN GUARDADO LOS DATOS...");
                            }
                            else
                                printf("\n\n\t\t\tEL POSTRE NO EXISTE");
                            getch();
                        break;
                        case 3:
                            system("cls");
                            printf("\n\n\t\t\t...REGRESAR MENU PRINCIPAL...");
                            getch();
                        break;
                    }
                }while(op != 3);
            break;
            case 2:
                do{
                    system("cls");
                    printf("\n\n\t\t\t<< ELIMINAR >>");
                    printf("\n\n\t\t\t1. POSTRE");
                    printf("\n\n\t\t\t2. REGRESAR AL MENU PRINCIPAL");
                    printf("\n\n\t\t*ELIGE TU OPCION: ");
                    scanf("%d",&op);
                    switch(op){
                        case 1:
                            system("cls");
                            printf("\n\n\t\t\t<< ELIMINAR POSTRE >>");
                            printf("\n\n\t\t\t*INGRESA EL NOMBRE DEL POSTRE: ");
                            fflush(stdin);
                            gets(Dato);
                            pos=busquedaLineal(l, Dato);
                            if(pos != -1){
                                suprimePostre(&l, pos);
                                printf("\n\n\t\t\t...EL POSTRE HA SIDO ELIMINADO...");
                            }
                            getch();
                        break;
                        case 2:
                            system("cls");
                            printf("\n\n\t\t\t...REGRESAR MENU PRINCIPAL...");
                            getch();
                        break;
                    }
                }while(op != 2);
            break;
            case 3:
                system("cls");
                printf("\n\n\t\t\t<< CONSULTAR >>\n");
                printf("\n\n\t\t*INGRESA EL NOMBRE DEL POSTRE: ");
                fflush(stdin);
                gets(Dato);
                strupr(Dato);
                if(busquedaLineal(l, Dato) != -1)
                    mostrarPostre(l);
                getch();
            break;
            case 4:
                system("cls");
                printf("\n\n\t\t\t<< MOSTRAR >>");
                printf("\n\n\t\t------------------------------");
                printf("\n\n\t\t\tLISTA DE POSTRES");
                mostrarPostre(l);
                getch();
            break;
            case 5:
                system("cls");
                printf("\n\n\t\t\t...GRACIAS POR SU VISITA...\n");
                getch();
            break;
            default:
                printf("\n\n\t\t\tOPCION INCORRECTA");
        }
    }while(opc != 5);
    return 0;
    getch();

}
