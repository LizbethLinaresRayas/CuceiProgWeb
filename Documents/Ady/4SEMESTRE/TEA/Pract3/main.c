#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <String.h>

typedef struct
{
    char tit_libro[25];
    char isbn[12];
    char autor[20];
    char editorial[15];
    char num_pag[4];
    char edicion[9];
    char materia[12];
}Libro;

typedef struct
{
    Libro libro;
    nodo *sig;
    nodo *ant;
}Nodo;

typedef Nodo *posicion;

typedef int logico;

//FUNCION INICIALIZA
void inicializa(posicion *L)
{
    *L=new Nodo;
	(*L)->sig=*L;
	(*L)->ant=*L;
}

//FUNCION INSERTA
void inserta(Libro lib, posicion p)
{
    Nodo *aux;
    aux=new Nodo;
    aux->libro=lib;
    aux->sig=p->sig;
    aux->ant=p;
    p->sig=aux;
    aux->sig->ant=aux;
}

//FUNCION SUPRIME
void suprimir(posicion p)
{
    Nodo *aux;
    if(p != NULL)
    {
        aux=p->sig;
        p->sig=p->sig->sig;
        p->sig->ant=p;
        delete(aux);
     }
     else
        printf("Direccion inválida");
}

//FUNCION VACIA
logico vacia(posicion p)
{
    if(p->sig == p)
        return 1;
	return 0;
}

//FUNCION LOCALIZA
posicion localiza(Libro lib, posicion L)
{
    Nodo *q;
	q=L;
    while(q->sig != L && q->sig->libro != lib)
        q=q->sig;
    if(q->sig == L)
        return NULL;
    else
        return q;
}

//FUNCION RECUPERA
tipo_elem recupera(posicion p)
{
    if (p->sig != p)
        return (p->sig->libro);
    else
        return -1;   /*valor invalido*/
}

/*//FUNCION IMPRIME AL REVES
void imprimir_R(posicion L)
{
    Nodo *p;
    if(L->sig != L)
    {
        p=L;
        while(p->ant != L)
        {
            printf("%d\n",p->ant->elem);
            p=p->ant;
        }
    }
    else
        printf("Lista Vacia");
}

//FUNCION IMPRIME
void imprime(posicion L)
{
    posicion q;
    if(L->sig != L)
    {
        q=L;
        while(q->sig != L)
        {
            printf("%d\n",q->sig->elem);
            q=q->sig;
        }
    }
    else
        printf("Lista Vacia");
}*/

//FUNCION ANULA
void anula(posicion L)
{
    while(L->sig != L)
        suprimir (L);
}

void EscArc(int fd, char cad[25])
{
    write(fd,cad,strlen(cad));
    write(fd,",",1);
}

int main()
{
    int opc,fd,conex,id;
    char cad[25],x;
    conex=creat("Archivo.txt",755);
    if(conex > 1)
        fd=open("Archivo.txt",2);
    else
        perror("");
    id=0;
    do
    {
        system("sys");
        printf("\n\tMENU");
        printf("\n\t1. AGREGAR LIBRO NUEVO");
        printf("\n\t2. MOSTRAR LISTA DE LIBROS");
        printf("\n\t3. ENTRADA DE LIBRO");
        printf("\n\t4. SALIDA DE LIBRO");
        printf("\n\t5. SALIR");
        printf("\n\tElige una opcion: ");
        scanf("%d",&opc);
        switch(opc)
        {
            case 1:
                system("sys");
                printf("\n\t<<AGREGAR LIBRO");
                if(fd > 0)
                {
                    do
                    {
                        lseek(fd,0,2);
                        printf("\n\tIngresa los siguientes datos:");
                        printf("\n\tTitulo del libro: ");
                        fflush(stdin);
                        gets(cad);
                        EscArc(fd,cad);
                        printf("\n\tISBN: ");
                        fflush(stdin);
                        gets(cad);
                        EscArc(fd,cad);
                        printf("\n\tAutor: ");
                        fflush(stdin);
                        gets(cad);
                        EscArc(fd,cad);
                        printf("\n\tEditorial: ");
                        fflush(stdin);
                        gets(cad);
                        EscArc(fd,cad);
                        printf("\n\tNumero de Paginas: ");
                        fflush(stdin);
                        gets(cad);
                        EscArc(fd,cad);
                        printf("\n\tEdicion: ");
                        fflush(stdin);
                        gets(cad);
                        EscArc(fd,cad);
                        printf("\n\tMateria: ");
                        fflush(stdin);
                        gets(cad);
                        write(fd,cad,strlen(cad));
                        write(fd,"*",1);
                        printf("\n\t...Tus datos han sido guardados...");
                        printf("\n\tDeceas Agregar otro libro?");
                        scanf("%c",&x);
                    }while((x == 's') || (x == 'S'));
                }
                else
                    perror("");
            break;
            case 2:
                system("sys");
                printf("\n\tMOSTRAR LIBRO");
            break;
            case 3:
                system("sys");
                printf("\n\tENTRADA DE LIBRO");
            break;
            case 4:
                system("sys");
                printf("\n\tSALIDA DE LIBRO");
            break;
            case 5:
                system("sys");
                printf("\n\t...GRACIAS POR TU VISITA");
            break;
            default:
                printf("\n\tOPCION INCORRECTA");
        }
    }while(opc != 5);
    return 0;
}
