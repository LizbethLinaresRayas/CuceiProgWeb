/* Animales (C) Diciembre de 1.996 */
/* El ordenador intentar  adivinar en que animal esta pensando el jugador.
   Ejemplo de aplicación de arboles binarios, y como almacenarlos y
   recuperarlos de fichero.
   Es además una forma básica de sistema experto. Por medio de preguntas
   el programa es capaz de diagnosticar averias, o en este caso adivinar
   el animal en que el jugador esta pensando. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

/* Definicion de tipo para arbol de conocimiento */
typedef struct _Nodo
{
   char Texto[80];			/* Pregunta si es rama, respuesta si es hoja */
   struct _Nodo *Si, *No;  /* Ramas para respuestas afirmativas y positivas
   								respectivamente. Si ambas NULL, se trata de una
                           respuesta */
} Nodo;

Nodo *Raiz;						/* Nodo raiz del arbol */
Nodo *Q, *P;					/* Punteros a nodos auxiliares */

char Linea[80];				/* variable global para la funcion de LeerArbol
									que es recursiva, definida como global evitamos que
                           se defina una nueva en cada llamada recursiva */
int n, i;						/* Variable gobales para VerArbol, que tambien
									es recursiva */

/* Funciones prototipo */
int Respuesta(void);
void Borrar(Nodo *A);
Nodo *Cargar(void);
Nodo *LeeArbol(FILE *fe);
void Salvar(Nodo *A);
void EscribeArbol(FILE *fs, Nodo *A);
void VerArbol(Nodo *A);

/* Funcion principal, cuerpo de programa */
int main()
{
   int Salir = FALSE;		/* Mientras Salir sea FALSE se continuara jugando */
   int Resp2;					/* Almacena respuestas para añadir nodos al arbol */
	int Resp;					/* Almacena respuestas Si/No, TRUE/FALSE, respec. */
   char Nuevo[80];			/* Nombre de animal nuevo */
   char Pregunta[80];		/* Pregunta para distinguir animal nuevo */

   Raiz = Cargar();			/* Leer el arbol desde disco */

   do
   {
   	/* Muestra mensaje y espera a que el jugador este preparado */
      printf("Piensa en un animal y yo intentar‚ adivinarlo.\n");
      printf("Pulsa una tecla para comenzar.\n");
      Respuesta();

      P = Raiz;				/* P apunta al nodo raiz, P sera siempre el nodo
      							actual */

      do							/* Bucle, se permanece en este bucle mientras
      							no se alcance una hoja, (es decir una respuesta)*/
      {
			Q = P;				/* Guardamos un puntero a P, para preguntar en el
         						do...while */
         if(P->Si)         /* Si existen nodos en cualquiera de las ramas
         						se trata de una pregunta, si no es una respuesta */
            printf("%s?\n", P->Texto);	/* Muestra la pregunta al jugador */
         else
            printf("Se trata de: %s\n", P->Texto); /* Muestra la respuesta */

			Resp = Respuesta(); /* Lee la respuesta del jugador */

         if(P->Si)			/* Si aun hay nodos, moverse a la rama adecuada */
            if(Resp) P = P->Si; else P = P->No;/* Dependiendo de la respuesta */
      }
      while(Q->Si);			/* do...while, miestras haya preguntas por hacer */

      if(Resp)					/* Si la ultima respuesta fue Si, el programa ha
      							adivinado el animal */
         printf("Lo he adivinado!!!\n");
      else						/* En caso contrario, es que no lo conoce */
      {
         printf("No conozco este animal, pero si me respondes a unas\n");
         printf("preguntas lo incluire en mi lista.\n");
         do						/* Este bucle asegura que no se añadiran nodos
         						con errores */
         {
            printf("\nDe que animal se trata?\n");
            fgets(Nuevo, 80, stdin);	/* Lee el nombre del animal */
			   while(Nuevo[strlen(Nuevo) - 1] < ' ')
            	Nuevo[strlen(Nuevo) - 1] = 0; /* Elimina retorno de linea */
            printf("Dame una pregunta que sirva para distinguir un/a\n");
            printf("%s\nde un/a\n%s\n", P->Texto, Nuevo);
            printf("a la que se pueda contestar si o no:\n");
            fgets(Pregunta, 80, stdin);/* Lee la progunta para distinguir el
         						nuevo animal del ultimo que se pregunto */
			   while(Pregunta[strlen(Pregunta) - 1] < ' ')
            	Pregunta[strlen(Pregunta) - 1] = 0; /* Elimina retorno de linea */
            printf("Que respuesta se ha de dar a esta pregunta:\n");
            printf("%s?\n", Pregunta);
            printf("Para obtener: %s\n", Nuevo);
            printf("como respuesta: Si o No:\n");
            Resp = Respuesta();			/* Lee la respuesta adecuada a la
            									pregunta leida */

				/* Muestra al jugador los datos leidos para que verifique si
            son correctos */
            printf("Veamos si lo he entendido bien:\n");
            printf("A la pregunta: %s?\n", Pregunta);
            if(Resp)
            {
               printf("Si se responde SI se trata de un %s\n", Nuevo);
               printf("y si se responde NO de un %s\n", P->Texto);
            }
            else
            {
               printf("Si se responde SI se trata de un %s\n", P->Texto);
               printf("y si se responde NO de un %s\n", Nuevo);
            }
            printf("Es correcto?");
		      Resp2 = Respuesta();	/* Si Resp2==TRUE, los datos son correctos */
         }
         while(!Resp2);		/* Repite el proceso hasta que el jugador de el
         						visto bueno */

      	/* Ahora hemos de añadir el nodo nuevo
         Estado anterior:
         		+-----------+
         P-->  | Animal 1  +
               +-----------+
              NO |       | SI
                 |       |
                NULL    NULL

         Estado final puede ser:
         a) Si Resp = SI
         		+-----------+
         P-->  | Pregunta  +
               +-----------+
              NO |       | SI
                 |       |
    		+-----------+ +--------------+
   		| Animal 1  + | Nuevo Animal +
         +-----------+ +--------------+
         b) Si Resp = NO
         		+-----------+
         P-->  | Pregunta  +
               +-----------+
              SI |       | NO
                 |       |
    		+-----------+ +--------------+
   		| Animal 1  + | Nuevo Animal +
         +-----------+ +--------------+
         */

         Q = malloc(sizeof(Nodo)); 	/* Creamos un nodo nuevo */
         strcpy(Q->Texto, P->Texto);/* Copiamos el Animal 1 al nuevo Nodo */
         Q->Si = NULL;					/* Como es un nodo hoja, Q->Si */
         Q->No = NULL;					/* y  Q->No seran NULL */
         if(Resp) P->No = Q;			/* Caso a) Rama de P->No es el animal 1 */
         	else P->Si = Q;         /* Caso b) Rama de P->Si es el animal 1 */

         Q = malloc(sizeof(Nodo));	/* Creamos un nuevo nodo */
         strcpy(Q->Texto, Nuevo);   /* para el nuevo animal */
         Q->Si = NULL;					/* que también es un nodo hoja */
         Q->No = NULL;
         if(Resp) P->Si = Q;			/* Caso a) Rama de P->Si es el animal nuevo */
         else P->No = Q;				/* Caso b) Rama de P->No es el animal nuevo */

         strcpy(P->Texto, Pregunta);/* El nodo Original es ahora la pregunta */
      }

      /* Pregunta al jugador si quiere seguir jugando */
      printf("Deseas terminar el juego y salir? (S/N)");
      Salir = Respuesta();
   }
   while(!Salir);	/* Permanece jugando mientras se responda que si */

   /* Salie del juego */
   Salvar(Raiz);				/* Guarda el arrbol en disco */
	VerArbol(Raiz);			/* Solo en depuracion, ver arbol en pantalla */
   Borrar(Raiz);				/* Borra memoria dinamica */
   return 0;					/* Sale con cero */
}

/* int Respuesta(void):
   Lee respuestas del tipo Si/No, retorna con TRUE para Si y
   con FALSE para No */
int Respuesta(void)
{
   char Respuesta[10];     /* Variable para recoger respuestas del tipo Si/No */

   /* Lee la respuesta del jugador */
	fgets(Respuesta, 9, stdin);	/* Sobran caracteres, pero mejor prevenir... */

   return Respuesta[0] == 'S' || Respuesta[0] == 's';
}

/* void Borrar(Nodo *A):
	Funcion recursiva, borra todos los nodos a partir de A, inclusive.
   Si hay nodos en la rama de Si, se llama a Borrar con el primer nodo
   de esa rama.
   Si hay nodos en la rama de No, se llama a Borrar con el primer nodo
   de esa rama.
   finalmente se borra el nodo A */
void Borrar(Nodo *A)
{
   if(A->Si) Borrar(A->Si);	/* Borrar rama A->Si */
   if(A->No) Borrar(A->No);   /* Borrar rama A->No */
   free(A);                   /* Borrar nodo A */
}

/* Nodo *Cargar(void):
	Si existe el fichero Data.pan, lee el arbol desde el
   si no existe crea un nodo con el "Caballo" como unico animal */
Nodo *Cargar(void)
{
   FILE *fe;					/* Fichero de datos de entrada */
   Nodo *A;						/* Variable auxiliar de nodo */

   fe = fopen("Data.pan", "r");	/* Abre el fichero en modo lectura */
   if(fe)						/* Si existe... */
   {
      A = LeeArbol(fe);		/* Lee el arbol */
      fclose(fe);				/* Cierra el fichero */
   }
   else
   {
      A = malloc(sizeof(Nodo));	/* Crea un nodo hoja para el Caballo */
      strcpy(A->Texto, "Caballo");
      A->Si = NULL;
      A->No = NULL;
   }
   return(A);					/* Retorna un puntero al nodo raiz */
}

/* Nodo *LeeArbol(FILE*):
	Funcion recusiva de lectura de un arbol desde fichero */
Nodo *LeeArbol(FILE *fe)
{
   Nodo *A;						/* Variable auxiliar para nodos */

//   A = NULL;					/* Inicialmente NULL */
   fgets(Linea, 80, fe);	/* Lee una linea desde el fichero fe */
   								/* Eliminamos retornos de linea */
   while(Linea[strlen(Linea) - 1] < ' ') Linea[strlen(Linea) - 1] = 0;

   A = malloc(sizeof(Nodo));		/* Inserta un nuevo nodo */
   strcpy(A->Texto, &Linea[1]);  /* Con la pregunta leida, quitamos la letra
   										inicial 'P' para pregunta o 'R' para
                                 respuesta */

   if(Linea[0] == 'P')		/* es un nodo pregunta */
   {
      A->Si = LeeArbol(fe);			/* Leemos rama de "si" */
      A->No = LeeArbol(fe);         /* Leemos rama de "no" */
   }
   else							/* es un nodo respuesta */
   {
      A->Si = NULL;						/* rama de "si" es NULL */
      A->No = NULL;	   	   	   /* rama de "no" es NULL */
   }

   return(A);
}

/* void Salvar(Nodo *A):
	Guarda el arbol que comienza en el nodo A en el fichero Data.pan */
void Salvar(Nodo *A)
{
   FILE *fs;					/* Fichero de salida */

   fs = fopen("Data.pan", "w");	/* Abre o crea el fichero de salida */

   EscribeArbol(fs, A);		/* Escribe en fs el arbol que empieza en A */
   fclose(fs);					/* Cierra el fichero */
}

/* vois EscribeArbol(FILE*, Nodo *A):
	Funcion recusiva de escritura de un arbol a fichero */
void EscribeArbol(FILE *fs, Nodo *A)
{
	if(A->Si)					/* Si es un nodo pregunta */
   {
   	fprintf(fs, "P%s\n", A->Texto);	/* Escribe 'P'+ pregunta en fs*/
      EscribeArbol(fs, A->Si);			/* Escribe rama de Si */
      EscribeArbol(fs, A->No);         /* Escribe rama de No */
   }
   else							/* Es un nodo hoja */
   	fprintf(fs, "R%s\n", A->Texto);	/* Escribe 'R'+ repuesta en fs*/
}

/* void VerArbol(Nodo *A)
	Para depuracion, permite visualizar arboles en pantalla */
void VerArbol(Nodo *A)
{
	for(i = 0; i < n; i++) putchar(' ');
	n += 3;
   printf(">%s\n", A->Texto);
   if(A->Si) {printf("S "); VerArbol(A->Si);}
   if(A->No) {printf("N "); VerArbol(A->No);}
	n -= 3;
}
