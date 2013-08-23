#include <stdio.h>
#include <conio.h>

typedef char tipo_dato;

typedef struct _nodo{
    tipo_dato elem;
    struct _nodo *sig;
}Nodo;

typedef Nodo *Pila;


void inicializa(Pila * p){
    *p = NULL;
}

int vacia (Pila p){
    return p == NULL;
}

void push (Pila *p, tipo_dato x){
    Pila aux;
    aux = (Pila)malloc(sizeof(Nodo));
    aux->elem = x;
    if ( vacia(*p))
    {
         aux->sig = NULL;
        *p = aux;
    }
    else{
        aux->sig = *p;
        *p = aux;
    }
}

void pop (Pila *p){
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

void mostrar(Pila p){
    Pila aux;
    aux = p;
    while(aux != NULL){
        printf("%c\n", aux->elem);
        aux = aux->sig;
    }
}

main(){
Pila p;
inicializa(&p);

}
