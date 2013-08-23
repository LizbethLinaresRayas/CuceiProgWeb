#include <STDIO.H>
#include <stdlib.h>
#include <conio.h>

typedef char tipo_dato;

struct nodo{
       tipo_dato elem;
       struct nodo *sig;
};
typedef struct nodo Nodo;

typedef struct COLA{
        Nodo *frente;
        Nodo *final;
}Cola;

void inicializar(Cola *C){
          Nodo *aux;
          aux = (Nodo*)malloc(sizeof(Nodo));
          aux->elem=-1;
          aux->sig=NULL;
          C->final=aux;
          C->frente=aux;
}

int vacia(Cola *C){
    return (C->frente==C->final);// if(C->frente->sig == NULL)
}

void insertar(Cola *C, int x){
     Nodo *aux;
     aux=(Nodo*)malloc(sizeof(Nodo));
     aux->elem=x;
     aux->sig=NULL;
     C->final->sig=aux;
     C->final=aux;
}
int eliminar(Cola *C){
     int x;
     if(vacia(C))
         puts("\nLa estructura esta Vacia...\n");
     else{
           Nodo *aux;
           aux=C->frente->sig;
           x=C->frente->sig->elem;
           C->frente=C->frente->sig;
           free(aux);
           return x;
           }
}
int frente(Cola *C){
     if(vacia(C)){
        puts("ERROR: Cola Vacia...");
        exit(-1);}
     else
         return C->frente->sig->elem;

}
int final(Cola *C){
     if(vacia(C)){
        puts("ERROR: Cola Vacia...");
        exit(-1);}
     else
         return C->final->elem;

}
void mostrar(Cola *C){
    if(vacia(C))
            puts("\nLa Estructura esta Vacia...\n");
    else{
         Nodo *aux;
         aux=C->frente->sig;
         while(aux==C->final){  //while(aux->sig == NULL)
            printf("\n  %d  ",aux->elem);
            aux=aux->sig;
         }
    }
}

main(){
   Cola C;
   inicializar(&C);
   printf("COLA INICIALIZADA");
   printf(" %x  %x\n",C.frente,C.final);
   insertar(&C,9);
   printf("Inserta 9  frente:%x  final%x\n",C.frente,C.final);

   printf("\nconsultar frente: %d", frente(&C));
   printf("\nconsultar final: %d  \n\nMostrar toda la Cola\n", final(&C));
   mostrar(&C);
   printf("\n\nEl elemento eliminado es %d",eliminar(&C));

   mostrar(&C);
   getch();
}
