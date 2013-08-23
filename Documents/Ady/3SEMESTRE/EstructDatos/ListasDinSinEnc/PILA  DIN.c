/*Lista Simplemente Ligada Lineal Sin Encabezado*/
#include <stdio.h>
#include <conio.h>
//#include <conio2.h>
#include <stdlib.h>

typedef int tipo_elem;

struct nodo{
       tipo_elem elem;
       nodo * sig;
       };

typedef nodo* posicion;
typedef int logico;

/*FUNCION INICIALIZA*/
void inicializa(nodo **L)
     {
     *L=NULL;
}

void inserta(tipo_elem x, posicion p,nodo **L)
     {
     posicion aux;

     aux=(nodo *) malloc(1*sizeof(nodo));
     aux->elem=x;
       if(p==NULL){
	  aux->sig=*L;
	  *L=aux;
	  }
	else{
		aux->sig=p->sig;
		p->sig=aux;
	}
}

void suprimir(posicion p,nodo **L){
	posicion aux,aux2;

	if(p==*L){
		aux=(*L)->sig;
		free(*L);
		*L=aux;
	}
	else{
		aux=*L;
		while(aux->sig!=NULL && aux->sig!=p)
			aux=aux->sig;
		if(aux->sig==p)
		{
			aux2=p->sig;
			free(p);
			aux->sig=aux2;
		}
		else
			printf("No se encontro");
	}
}



/*FUNCION VACIA*/
logico vacia(nodo *L)
       {
       if(L==NULL)
	  return 1;
       else
	  return 0;
}

/*FUNCION LOCALIZA*/
posicion localiza(tipo_elem x, nodo *L){
	if(vacia(L)){
		return 0;
	}
	else{
	 while (L!=NULL && L->elem!=x)
	       L=L->sig;
	 if (L==NULL)
	       return NULL;
	 else
	       return L;
	}
}

/*FUNCION RECUPERA*/
tipo_elem recupera(posicion p)
	  {
	  if (p!=NULL)
	     return (p->elem);
	  else
	     return -1;   /*valor invalido*/
}


/*FUNCION IMPRIME*/
void imprimir(posicion L)
     {
	if(vacia(L))
		printf("Lista Vacia");
	else{
		while (L!=NULL){
	   		printf("%d\n",L->elem);
	   		L=L->sig;
     		}
	}
}

/*FUNCION ANULA*/
void anula(nodo **L)
     {
	posicion aux;

	     while (*L!=NULL)
		{
		aux=(*L)->sig;
		free(*L);
		*L=aux;
	}
}


/*Main*/

int main (){
tipo_elem x;
posicion E;
posicion pun;
int n, i,opc;
inicializa (&E);

do{
("sys");
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
		inserta(x,NULL,&E);
		break;
	case 2:
		printf ("\nDame numero a suprimir.....\n");
		scanf ("%d",& x);
		suprimir(localiza(x,E),&E);
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
        	imprimir(E);
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
		anula(&E);
		printf("La lista fue anulada");
		getch();
                break;
	default:
		printf("Opcion No Valida");
}
} while(opc!=7);
return 0;
}
