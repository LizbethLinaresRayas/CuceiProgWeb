//Adriana Lizbeth Linares Rayas Cod.210596378 Lic.Informatica
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAXIMO_ELEMENTOS 100
#define POSICION_INVALIDA -1
#define ELEMENTO_NULO NULL

typedef int posicion;
typedef char TipoElemento;

typedef struct{
    TipoElemento elementos[MAXIMO_ELEMENTOS];
    posicion tope;
}Pila;

typedef struct{
    TipoElemento elementos[MAXIMO_ELEMENTOS];
    posicion tope;
}Aux;

void inicializa(Pila *p){
    p->tope = POSICION_INVALIDA;
}

void imprimeError(const char mensaje[]){
    printf("%s\n", mensaje);
}

int estaVacia(Pila *p){

    return p->tope == POSICION_INVALIDA;
}

int estaLlena(Pila *p){

    return p->tope == MAXIMO_ELEMENTOS - 1;
}

void apila(TipoElemento *x, Pila *p){

    if(!estaLlena(p)){
        p->elementos[++p->tope] = *x;
    }
    else{
        imprimeError("\n\n\t\tLA PILA ESTA LLENA");
    }
}

void desapila(Pila *p){

    if(!estaVacia(p)){
        p->tope--;
    }
    else{
        imprimeError("\n\n\t\tLA PILA ESTA VACIA");
    }
}

TipoElemento * tope(Pila *p){

    if(!estaVacia(p)){
        return &p->elementos[p->tope];
    }
    else{
        return ELEMENTO_NULO;
    }
}

void imprimeElemento(TipoElemento *x){
    printf("%c", *x);
}

void imprimePila(Pila *p){
    posicion q;

    if(estaVacia(p)){
        imprimeError("\n\n\t\tLA PILA ESTA VACIA");
    }
    else{
        printf("\n\n\t\tFRASE:\n\n\t\t");
        q = p->tope;
        while(q != POSICION_INVALIDA){
            imprimeElemento(&p->elementos[q]);
            q--;
        }
    }
}

void leeElemento(TipoElemento *x){
    fflush(stdin);
    scanf("%c", x);
}

void compara(Pila *p, Pila *aux, int dig){
    posicion q,r;
    int x=0;

    q=p->tope;
    r=aux->tope;

    while(p->elementos[q] == aux->elementos[r]){
        x++;
        q--;
        r--;
    }
    if(x == dig)
        printf("\n\n\t\t->ES UN PALINDROMO");
    else
        printf("\n\n\t\t->NO ES UN PALINDROMO");
}

int main()
{
    Pila p;
    Pila aux;
    posicion q;
    TipoElemento x;
    inicializa(&aux);
    int i,j,dig,op,band=0;

    system("COLOR f8");
    do{
        system("cls");
        printf("\n\n\t\tMENU");
        printf("\n\n\t\t1. INICIALIZAR");
        printf("\n\n\t\t2. INSERTAR FRASE");
        printf("\n\n\t\t3. COMPARAR FRASE");
        printf("\n\n\t\t4. MOSTRAR FRASE");
        printf("\n\n\t\t5. ELIMINAR FRASE");
        printf("\n\n\t\t6. SALIR");
        printf("\n\n\t->ELIGE TU OPCION: ");
        scanf("%d",&op);
        switch(op){
            case 1:
                system("cls");
                if(band == 0){
                    inicializa(&p);
                    band=1;
                    printf("\n\n\t\tLA PILA HA SIDO INICIALIZADA");
                }
                else
                    printf("\n\n\t\tFUNCION INHABILITADA");
                getch();
            break;
            case 2:
                system("cls");
                printf("\n\n\t\tLONGITUD DE LA PALABRA: ");
                scanf("%d",&dig);
                printf("\n\n\t\tINGRESA TU PALABRA:");
                for(i=0; i<dig; i++){
                    printf("\n\n\t\t\t");
                    fflush(stdin);
                    leeElemento(&x);
                    apila(&x, &p);
                }
                q=p.tope;
                for(j=0; j<dig; j++){
                    apila(&p.elementos[q], &aux);
                    q--;
                }
                printf("\n\n\t->LA PALABRA HA SIDO GUARDADA");
                getch();
            break;
            case 3:
                system("cls");
                compara(&p, &aux, dig);
                getch();
            break;
            case 4:
                system("cls");
                imprimePila(&p);
                getch();
            break;
            case 5:
                system("cls");
                q=p.tope;
                for(i=0; i<=q; i++)
                    desapila(&p);
                printf("\n\n\t\tLA FRASE HA SIDO ELIMINADA");
                getch();
            break;
            case 6:
                system("cls");
                printf("\n\n\t\tGRACIAS POR TU VISITA\n\n");
                getch();
            break;
            default:
                system("cls");
                printf("\n\n\t\tOPCION INVALIDA");
                getch();
        }
    }while(op != 6);
    return 0;
    getch();
}
