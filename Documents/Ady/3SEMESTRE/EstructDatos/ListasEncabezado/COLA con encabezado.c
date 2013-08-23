//Lista Simplemente Ligada Lineal Con Encabezado
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

typedef int logico;
typedef int tipo_elem;

struct Nodo{
       tipo_elem elem;
       Nodo *sig;
       };

struct encabezado{
    struct nodo;
	char desc[50];
	int num_elems;
	Nodo *sig;
};

//FUNCION INICIALIZA
void inicializa (struct encabezado **L)
     {
     *L=new encabezado;
     (*L)->sig=NULL;
     (*L)->num_elems=0;
     strcpy("Lista Simple Lineal C/E",(*L)->desc);
}

//FUNCION INSERTA
void inserta (tipo_elem x, Nodo * p)
     {
     Nodo *aux;
     aux=new Nodo;
     aux->elem=x;
     aux->sig=p->sig;
     p->sig=aux;

}

//FUNCION SUPRIME
void suprimir (Nodo * p)
     {
     Nodo*aux;
     aux=p->sig->sig;
     delete(p->sig);
     p->sig=aux;
}

//FUNCION VACIA
logico vacia(Nodo * p)
       {
       if (p->sig==NULL)
	  return 1;
       else
	  return 0;
}

//FUNCION LOCALIZA
Nodo * localiza(tipo_elem x, Nodo * L)
	 {
	 Nodo*p;
	 p=L;
	 while (p->sig!=NULL && p->sig->elem!=x)
	       p=p->sig;
	 if (p->sig==NULL)
	       return NULL;
	 else
	       return p;
}

//FUNCION RECUPERA
tipo_elem recupera (Nodo * p)
	  {
	  if (p->sig!=NULL)
	     return (p->sig->elem);
	  else
	     return -1;   /*valor invalido*/
}


//FUNCION IMPRIME
void imprime (Nodo * L)
     {
     Nodo*p;
     if(!vacia(L))
     {
     	p=L;
     	while (p->sig!=NULL){
	   printf("%d\n",p->sig->elem);
	   p=p->sig;
	}
     }
     else
	printf("Lista Vacia");
}

//FUNCION ANULA
void anula (Nodo * L)
     {
     while (L->sig!=NULL)
	   suprimir (L);
}


//Main

int main (){

tipo_elem x;
struct Nodo * pun;
struct encabezado * E;
int n, i,opc;
inicializa (&E);

do{
clrscr();
printf ("...........Menu............\n");
printf ("1-Inserta.....\n");
printf ("2-Suprime.....\n");
printf ("3-Localiza....\n");
printf ("4-Imprime.....\n");
printf ("5-Vacia.......\n");
printf ("6-Anula.......\n");
printf ("7-Salir.......\n");
printf ("Elige una opcion:....\n");
scanf ("%d", &opc);
switch(opc){
	case 1:
		printf ("\nDame numero a insertar.....\n");
		scanf("%d",& x);
		inserta(x,E);
		break;
	case 2:
		printf ("\nDame numero a suprimir.....\n");
		scanf ("%d",& x);
		suprimir(localiza(x,E));
		break;
	case 3:
               printf ("\nDame numero a localizar.....\n");
	       scanf ("%d",& x);
	       pun=localiza(x,E);
	       if(pun==NULL)
			printf("Numero no encontrado");
	       else
			printf("%p\n",pun);
	       getch();
	       break;
	case 4:
		clrscr();
 	    imprime(E);
		getch();
		break;
	case 5:
		if(vacia(E))
			printf("SI");
		else
			printf("NO");
		getch();
		break;
	case 6:
		anula(E);
		printf("La lista fue anulada");
		getch();
		break;
}
} while(opc!=7);
getch();
return 0;
}
