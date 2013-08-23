#include <stdio.h>
#include <conio.h>
//#include <conio2.h>

typedef int TIPO_ELEM;
typedef int LOGICO;
struct NODO{
 TIPO_ELEM INFO;
 NODO *IZQ,*DER;
 };
typedef NODO NODO;
typedef NODO *POSICION;
POSICION R;
struct NODO **RR;

void INICIALIZA(POSICION *R2){
 *R2=NULL;
 }
void INSERTA(TIPO_ELEM X,POSICION *R2){
 if(*R2==NULL){
  *R2=new NODO;
  (*R2)->INFO=X;
  (*R2)->IZQ=NULL;
  (*R2)->DER=NULL;
  }
 else{
  if(X>(*R2)->INFO)
   INSERTA(X,&((*R2)->DER));
  else
   if(X<(*R2)->INFO)
    INSERTA(X,&(*R2)->IZQ);
   else
   {
    printf("ELEMENTO DUPLICADO");
    getch();
    }
 }
}
POSICION BUSCAR(TIPO_ELEM X,POSICION R){
POSICION P;
 P=R;
 if((P==NULL) || (X==P->INFO))
  return P;
 else {
  if(X<P->INFO)
   return BUSCAR(X,P->IZQ);
  else
   return BUSCAR(X,P->DER);
       }
}

void ELIMINAR(TIPO_ELEM X,POSICION *R2){
POSICION AUX,AUX1,OTR;
int BORRADO;
 if((*R2)!=NULL){
  if(X<(*R2)->INFO)
   ELIMINAR(X,&(*R2)->IZQ);
  else
   if(X>(*R2)->INFO)
    ELIMINAR(X,&(*R2)->DER);
   else{
    OTR=*R2;
    if(OTR->DER ==NULL)
	*R2=OTR->IZQ;
    else{
	if(OTR->IZQ ==NULL)
		*R2=OTR->DER;
	else{
		AUX=(*R2)->IZQ;
		BORRADO=0;
		while(AUX->DER!=NULL){
			AUX1=AUX;
			AUX=AUX->DER;
			BORRADO=1;
		}
		(*R2)->INFO=AUX->INFO;
		OTR=AUX;
		if(BORRADO==1)
			AUX1->DER=AUX->IZQ;
		else
			(*R2)->IZQ=AUX->IZQ;
	}/*ELSE*/
    }/*ELSE*/
    delete(OTR);
   }
      }
  else
  {
   printf("ARBOL VACIO");
   getch();
   }
}

TIPO_ELEM MAXIMO (POSICION P){
  while (P->DER !=NULL)
    P =P->DER;
   return P-> INFO;
}
 TIPO_ELEM MINIMO (POSICION P){
while (P->IZQ !=NULL)
  P=P->IZQ;
return P-> INFO;
}


void PREORDEN(POSICION RAIZ){
 if(RAIZ!=NULL){
  printf("%d\n",RAIZ->INFO);
  PREORDEN(RAIZ->IZQ);
  PREORDEN(RAIZ->DER);
 }
}
void ENORDEN (POSICION RAIZ)
{
    if (RAIZ !=NULL){
    ENORDEN (RAIZ->IZQ);
    printf("%d\n",RAIZ->INFO);
    ENORDEN(RAIZ->DER);
    }
}
void POSTORDEN(POSICION RAIZ)
{
    if(RAIZ != NULL){
   POSTORDEN(RAIZ->IZQ);
   POSTORDEN(RAIZ->DER);
   printf("%d\n",RAIZ->INFO);
    }
}

//*Anula


int main(){
int N, OP;
POSICION TEMP;
INICIALIZA(&R);
getch();
do{
("sys");
printf ("ARBOLES DE BUSQUEDA BINARIA\n");
printf ("\n1. INSERTAR UN ELEMENTO");
printf ("\n2. BUSCAR UN ELEMENTO");
printf ("\n3. ELIMINAR UN ELEMENTO");
printf ("\n4. MAXIMO");
printf ("\n5. MINIMO");
printf ("\n6. RECORRIDO PREORDEN");
printf ("\n7. RECORRIDO ENORDEN");
printf ("\n8. RECORRIDO POSTORDEN");
printf ("\n9. ANULA");
printf ("\n0. SALIR");
printf ("\n\nELIGE TU OPCI¢N... ");
scanf ("%d",&OP);
switch (OP){

case 1 : {
  ("sys");
  printf ("INSERTAR UN ELEMENTO\n");
  printf ("DAME EL ELEMENTO A INSERTAR\n ");
  scanf ("%d",& N);
  INSERTA(N,&R);
  }
  break;
case 2 : { ("sys");
  printf ("BUSCAR UN ELEMENTO\n");
  printf ("DAME EL ELEMENTO\n ");
  scanf ("%d",& N);
  TEMP=BUSCAR(N,R);
  if (TEMP==NULL)
  printf("ELEMENTO NO ENCONTRADO");
  else
  printf("%p",TEMP);
  getch();
  }
  break;
case 3 : { ("sys");
  printf ("ELIMINAR UN ELEMENTO\n");
  printf ("DAME EL ELEMENTO\n ");
  scanf ("%D",& N);
  ELIMINAR(N,&R);
  getch();
  }
  break;
case 4 : { clrscr();
    printf ("EL ELEMENTO MAXIMO DEL ARBOL ES: %d\n",MAXIMO(R));
    getch();
 }
 break;
case 5 : { clrscr();
  printf ("EL ELEMENTO MINIMO DEL ARBOL ES: %d\n",MINIMO(R));
    getch();
 }
 break;
case 6 :{ clrscr();
 printf("RECORRIDO PREORDEN\n");
 PREORDEN(R);
 getch();
 }
 break;
case 7 :{ clrscr();
 printf("RECORRIDO ENORDEN\n");
 ENORDEN(R);
 getch();
 }
 break;
case 8 :{ clrscr();
 printf("RECORRIDO POSTORDEN\n");
 POSTORDEN(R);
 getch();
 }
 break;
 case 9 :{ clrscr();
 //ANULA(&R);
 printf("LISTA ANULADA\n");
 getch();
 }
 break;
} //SW
} while(OP!=0);
}
//GETCH ();
