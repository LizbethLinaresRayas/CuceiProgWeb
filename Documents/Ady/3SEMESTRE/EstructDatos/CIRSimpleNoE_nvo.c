/*Lista Simplemente Ligada Circular Sin encabezado*/
#include <STDIO.H>
#include <conio.h>

#include <stdlib.h>

typedef int tipo_elem;

struct nodo{
	tipo_elem elem;
	nodo*sig;
	};

typedef nodo *posicion;
typedef int logico;


void inicializa(posicion *L) {
	*L=NULL;

}
void inserta(tipo_elem x, posicion p, posicion *L){
	posicion aux,temp;

	aux=(nodo *) malloc(sizeof(nodo));
	aux->elem=x;
	aux->sig=aux;
	if(*L==NULL)
	       *L=aux;
	else{
		if (p==NULL){
			temp=*L;
			while(temp->sig!=*L)
				temp=temp->sig;
			temp->sig=aux;
			aux->sig=*L;
			*L=aux;
		}
		else{aux->sig= p->sig;
			p->sig = aux;}
		}
}

void suprimir(posicion p, posicion *L){
	posicion aux,aux2;
	if (p==*L){
		aux=(*L)->sig;
		while(aux->sig!=*L)
			aux=aux->sig;
		aux->sig=(*L)->sig;
		free(*L);
		*L=aux->sig;
	}
	else{
		aux=*L;
		while(aux->sig!=*L && aux->sig!=p)
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
logico vacia(posicion L)
       {
       if(L==NULL)
	  return 1;
       else
	  return 0;
}

posicion localiza(tipo_elem x, posicion L){
posicion aux;
	if(vacia(L))
		return 0;
	else{
		if(L->elem==x)
			return(L);
		else{
			aux=L->sig;
			while(aux->sig !=L && aux->elem != x)
				aux=aux->sig;
			if(aux->elem==x)
				return aux;
			else{
				printf("No se encontro");
				return 0;
			}
		}
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

void imprime(posicion L){
	posicion aux;

	("sys");
	if (L==NULL)
		printf("Lista vacia");
	else{
		printf("\nLISTA COMPLETA\n\n");
		aux=L;
		while(aux->sig!=L){
			printf("%d\n",aux->elem);
			aux=aux->sig;
        }

		printf("%d\n",aux->elem);
		}
getch();}

void imprimeInv(posicion L){ /*Imprime al reves*/
	posicion aux;

	("sys");
	if (L==NULL)
		printf("Lista vacia");
	else{
		printf("\nLISTA COMPLETA\n\n");
		aux=L;
		while(aux->sig!=L){
			printf("%d\n",imprimeInv(aux->sig);
        }


		}
getch();}

/*FUNCION ANULA*/
void anula(posicion *L)
     {
	     while ((*L)->sig!=*L)
		suprimir(*L,L);
	     free(*L);
	     inicializa(L);

}

int main (){
tipo_elem x;
posicion E, pun;
int n, i,opc;
inicializa (&E);


do{
printf ("...........Menu............\n");
printf ("1-Inserta.....\n");
printf ("2-Suprime.....\n");
printf ("3-Localiza....\n");
printf ("4-Imprime.....\n");
printf ("5-Imprime al reves...\n");
printf ("6-Vacia.......\n");
printf ("7-Anula.......\n");
printf ("8-Salir.......\n");
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
           imprime(E);
		getch();
		break;
	case 5:
           imprimeInv(E);
        getch();
        break;
	case 6:
		if(vacia(E))
			printf("SI");
		else
			printf("NO");
		getch();
		break;
	case 7:
		anula(&E);
		printf("La lista fue anulada");
		getch();
        break;
	default:
		printf("Opcion No Valida");
}
} while(opc!=8);
return 0;
}

