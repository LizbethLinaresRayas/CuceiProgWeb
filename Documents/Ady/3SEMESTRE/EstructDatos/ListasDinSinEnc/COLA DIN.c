/*Lista Simplemente Ligada Lineal Sin Encabezado*/
#include <stdio.h>
#include <conio.h>
//#include <conio2.h>
#include <stdlib.h>

typedef int tipo_elem;

typedef struct nodo{
       tipo_elem elem;
       struct nodo * sig;
       int cont;
}nodo;


typedef struct nodo* posicion;
typedef int logico;




/*FUNCION INICIALIZA*/
void inicializa(nodo **L)
     {
    *L=NULL;
}

/*FUNCION INSERTA*/
void inserta(tipo_elem x, posicion p,nodo **L)
     {
     posicion aux;
     aux->cont=0;

     aux=(nodo *) malloc(1*sizeof(nodo));
     aux->elem=x;

       if(p==NULL){
           aux->sig=*L;
           *L=aux;
           aux->cont++;
	   }
       else{
           aux->sig=p->sig;
		   p->sig=aux;
		   aux->cont++;
	   }
}
/*FUNCION SUPRIME*/

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
	     return -1;
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
		inserta(x,(&E.cont+1),&E);
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

/*
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int main(void)
{
    char op = '0';
    Cola c;
    TipoElemento x;
    inicializa(&c);
    do
    {
        system("Cls");
        printf ("\n\t E L I G E    L A    O P C I O N    Q U E    D E S E A S ");
        printf ("\n\n\t M E N U   D E   O P C I O N E S\n ");
        printf ("\n\t (E) Encolar un elemento.........................");
        printf ("\n\t (D) Desencolar un elemento......................");
        printf ("\n\t (F) Frente de la cola...........................");
        printf ("\n\t (M) Mostrar toda la cola........................");
        printf ("\n\t (A) Anular o inicializar la cola................");
        printf ("\n\t (S) Salir.......................................");
        printf ("\n\n\t\t\tOpcion:");
        fflush(stdin);
        scanf("%c", &op);
        op = toupper(op);
        system("Cls");
        switch(op)
        {
            case 'E':
                if(!estaLlena(&c))
                {
                    printf("\n\tDato a encolar: ");
                    fflush(stdin);
                    leeElemento(&x);
                    encola(&x, &c);
                    printf("\tEl dato ha sido encolado\n");
                }
                else
                {
                    printf("\n\tLa cola está llena\n");
                }
            break;
            case 'D':
                if(!estaVacia(&c))
                {
                    printf("\n\tEl dato a desencolar es: ");
                    imprimeElemento(frente(&c));
                    desencola(&c);
                    printf("\tEl dato ha sido desencolado\n");
                }
                else
                {
                    imprimeError("La cola está vacía");
                }
            break;
            case 'F':
                if(!estaVacia(&c))
                {
                    printf("\n\tEl dato del frente es: ");
                    imprimeElemento(frente(&c));
                }
                else
                {
                    imprimeError("La cola está vacía");
                }
            break;
            case 'M':
                if(!estaVacia(&c))
                {
                    imprimeCola(&c);
                }
                else
                {
                    imprimeError("La cola está vacía");
                }
            break;
            case 'A':
                inicializa(&c);
                printf("\n\tLa cola ha sido inicializada\n");
            break;
            case 'S':
                printf("\n\n\t\tFIN DE PROGRAMA...\n\n");
            break;
            default:
                imprimeError("Opción inválida");
            break;
        }
        system("Pause");
    } while(op != 'S');
    return 0;
}

*/
