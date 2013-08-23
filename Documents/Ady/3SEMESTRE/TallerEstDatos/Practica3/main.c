//Adriana Lizbeth Linares Rayas
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <String.h>
#include <windows.h>
#include <conio.h>
#define N 25
#define fila 1
#define columna 5

typedef struct
{
    char id_lib[6];
    char tit_libro[25];
    char isbn[12];
    char autor[20];
    char editorial[15];
    char num_pag[4];
    char edicion[9];
    char materia[12];
    char exist[5];
}Libro;

typedef struct nodo
{
    Libro libro;
    struct nodo *izq;
    struct nodo *der;
}Nodo;

typedef struct Nodo
{
    Libro libro;
    struct Nodo *sig;
}nodo;

typedef nodo *posicion;
typedef int logico;

int gotoxy(short x, short y)
{
   COORD coord;
   HANDLE h_stdout;

   coord.X = x;
   coord.Y = y;

   if ((h_stdout = GetStdHandle(STD_OUTPUT_HANDLE)) == INVALID_HANDLE_VALUE)
      return 0;

   if (SetConsoleCursorPosition(h_stdout, coord) == 0)
      return 0;

   return 1;
}

void inicializa(nodo **L)
{
     *L=NULL;
}

logico vacia(nodo *L)
{
    if(L == NULL)
        return 1;
    else
        return 0;
}

void inserta(posicion *L,Libro lib)
{
    posicion aux, ant;

    aux=(nodo*)malloc(1*sizeof(nodo));
    aux->libro=lib;
    if(vacia(*L) || strcmp((*L)->libro.tit_libro,lib.tit_libro) > 0)
    {
        aux->sig=*L;
        *L=aux;
    }
    else
    {
        ant=*L;
        while(ant->sig && ((strcmp(ant->sig->libro.tit_libro,lib.tit_libro) < 0) || (strcmp(ant->sig->libro.tit_libro,lib.tit_libro) == 0)))
            ant=ant->sig;
        aux->sig=ant->sig;
        ant->sig=aux;
    }
}

void imprimeEnc()
{
    gotoxy(fila+3,columna);    printf("Id");
    gotoxy(fila+9,columna);  printf("Titulo");
    gotoxy(fila+30,columna); printf("ISBN");
    gotoxy(fila+43,columna); printf("Autor");
    gotoxy(fila+59,columna); printf("Editorial");
    gotoxy(fila+73,columna); printf("# Pag.");
    gotoxy(fila+83,columna); printf("Edicion");
    gotoxy(fila+96,columna); printf("Materia");
    gotoxy(fila+110,columna);printf("Existencia");
}

void imprime(posicion L)
{
    int i=3,x,j;
	if(vacia(L))
	{
	    gotoxy(fila+50,columna+5);printf("... No hay Datos ... ");
	}
	else
	{
	    imprimeEnc();
		while(L != NULL)
		{
		    x=strlen(L->libro.id_lib);
		    for(j=5; j>x; j--)
		    {
                gotoxy(fila+(j-x),columna+i);printf("0");
		    }
		    gotoxy(fila+5,columna+i);  printf("%s",L->libro.id_lib);
            gotoxy(fila+9,columna+i);  printf("%s",L->libro.tit_libro);
            gotoxy(fila+30,columna+i); printf("%s",L->libro.isbn);
            gotoxy(fila+43,columna+i); printf("%s",L->libro.autor);
            gotoxy(fila+59,columna+i); printf("%s",L->libro.editorial);
            gotoxy(fila+73,columna+i); printf("%s",L->libro.num_pag);
            gotoxy(fila+83,columna+i); printf("%s",L->libro.edicion);
            gotoxy(fila+96,columna+i); printf("%s",L->libro.materia);
            gotoxy(fila+113,columna+i);printf("%s",L->libro.exist);
	   		L=L->sig;
	   		i++;
        }
	}
}

void EscArc(int fd, char cad[25])
{
    write(fd,cad,strlen(cad));
    write(fd,",",1);
}

void CargaLista(int fd,posicion *L)
{
    Libro lib;
    int i,ax,j,bnd=0;
    char car,cad[N];
    for(j=0; j<N; j++)
        cad[j]='\0';

    if(fd > 0)
    {
        i=0;
        ax=1;
        lseek(fd,0,0);
        while((read(fd,&car,1)) > 0)
        {
            if((car != '&') && (bnd == 0))
            {
                if(car != ',')
                {
                    if(car != '+')
                    {
                        cad[i]=car;
                        i++;
                    }
                    else
                    {
                        if(ax == 9)
                        {
                            strcpy(lib.exist,cad);
                            ax++;
                            i=0;
                        }
                        inserta(L,lib);
                        ax=1;
                    }
                }
                else
                {
                    switch(ax)
                    {
                        case 1:
                            strcpy(lib.id_lib,cad);
                        break;
                        case 2:
                            strcpy(lib.tit_libro,cad);
                        break;
                        case 3:
                            strcpy(lib.isbn,cad);
                        break;
                        case 4:
                            strcpy(lib.autor,cad);
                        break;
                        case 5:
                            strcpy(lib.editorial,cad);
                        break;
                        case 6:
                            strcpy(lib.num_pag,cad);
                        break;
                        case 7:
                            strcpy(lib.edicion,cad);
                        break;
                        case 8:
                            strcpy(lib.materia,cad);
                        break;
                    }
                    i=0;
                    ax++;
                    for(j=0; j<N; j++)
                        cad[j]='\0';
                }
            }
            else
            {
                bnd=1;
                if(car == '+')
                {
                    bnd=0;
                }
            }
        }
    }
}

int localiza(int fd,char id[5])
{
    int cnt,i,aux=0;
    char cad[10],car;
    if(fd > 0)
    {
        lseek(fd,0,0);
        i=0;
        cnt=0;
        while((read(fd,&car,1)) > 0)
        {
            if(car != ',')
            {
                if(car != '+')
                {
                    cad[i]=car;
                    i++;
                }
            }
            else
            {
                if((strcmp(cad,id)) == 0)
                {
                    aux=cnt;
                }
            }
            cnt++;
            i=0;
        }
    }
    return aux;
}

void Reescribe(int fd, int aux,int ent,int op)
{
    int i,cnt,existencia,band=0,j;
    char aux_id[5],aux_tit[25],aux_isbn[12],aux_autor[20],aux_edit[15],aux_np[4],aux_edi[9],aux_mat[12],aux_exi[5],car,cad[25];

    i=0;
    cnt=1;
    lseek(fd,(aux-1),0);
    while(read(fd,&car,1) > 0)
    {
        if(band == 0)
        {
            if(car != ',')
            {
                if(car != '+')
                {
                    cad[i]=car;
                    i++;
                }
                else
                {
                    band=1;
                    if(op == 1)
                    {
                        existencia=atoi(cad);
                        existencia+=ent;
                        itoa(existencia,aux_exi,10);
                    }
                    else
                    {
                        if(op == 2)
                        {
                            existencia=atoi(cad);
                            existencia-=ent;
                            if(existencia >= 0)
                                itoa(existencia,aux_exi,10);
                            else
                                printf("\n\t...Existencias insuficientes...");
                        }
                    }

                }
            }
            else
            {
                switch(cnt)
                {
                    case 1:
                        strcpy(aux_id,cad);
                    break;
                    case 2:
                        strcpy(aux_tit,cad);
                    break;
                    case 3:
                        strcpy(aux_isbn,cad);
                    break;
                    case 4:
                        strcpy(aux_autor,cad);
                    break;
                    case 5:
                        strcpy(aux_edit,cad);
                    break;
                    case 6:
                        strcpy(aux_np,cad);
                    break;
                    case 7:
                        strcpy(aux_edi,cad);
                    break;
                    case 8:
                        strcpy(aux_mat,cad);
                    break;
                }
                i=0;
                cnt++;
                for(j=0; j<N; j++)
                    cad[j]='\0';
            }
        }
    }
    lseek(fd,0,2);
    EscArc(fd,aux_id);
    EscArc(fd,aux_tit);
    EscArc(fd,aux_isbn);
    EscArc(fd,aux_autor);
    EscArc(fd,aux_edit);
    EscArc(fd,aux_np);
    EscArc(fd,aux_edi);
    EscArc(fd,aux_mat);
    write(fd,aux_exi,strlen(aux_exi));
    write(fd,"+",1);
}

int * reservaMemoriaVector(int n)
{
    int bytes = sizeof(int) * n, i = -1;
    int *vector = (int *)malloc(bytes);
    for (i = 0; i < n; i++)
	    vector[i] = 0;
    return vector;
}

void LeeDatos(int fd)
{
    char cad[25];

    lseek(fd,0,2);
    gotoxy(fila+8,columna+7);printf("Titulo:");
    fflush(stdin);
    gotoxy(fila+8,columna+9);gets(cad);
    strupr(cad);
    EscArc(fd,cad);
    gotoxy(fila+30,columna+7);printf("ISBN:");
    fflush(stdin);
    gotoxy(fila+30,columna+9);gets(cad);
    strupr(cad);
    EscArc(fd,cad);
    gotoxy(fila+43,columna+7);printf("Autor:");
    fflush(stdin);
    gotoxy(fila+43,columna+9);gets(cad);
    strupr(cad);
    EscArc(fd,cad);
    gotoxy(fila+59,columna+7);printf("Editorial:");
    fflush(stdin);
    gotoxy(fila+59,columna+9);gets(cad);
    strupr(cad);
    EscArc(fd,cad);
    gotoxy(fila+73,columna+7);printf("# Pag.:");
    fflush(stdin);
    gotoxy(fila+73,columna+9);gets(cad);
    EscArc(fd,cad);
    gotoxy(fila+83,columna+7);printf("Edicion:");
    fflush(stdin);
    gotoxy(fila+83,columna+9);gets(cad);
    strupr(cad);
    EscArc(fd,cad);
    gotoxy(fila+96,columna+7);printf("Materia:");
    fflush(stdin);
    gotoxy(fila+96,columna+9);gets(cad);
    strupr(cad);
    EscArc(fd,cad);
    gotoxy(fila+113,columna+7);printf("Existencia: ");
    fflush(stdin);
    gotoxy(fila+116,columna+9);gets(cad);
    write(fd,cad,strlen(cad));
    write(fd,"+",1);
    printf("\n\n");
}

int main()
{
    int opc,fd,ent,sal,aux,i,band=0,ID,*arreglo,valor;
    char cad[25],id[5],x;
    posicion E;

    do
    {
        fd=open("Archivo.txt",2);
        if(fd > 0)
            band=0;
        else
        {
            creat("Archivo.txt",755);
            band=1;
        }
    }while(band == 1);

    do
    {
        system("cls");
        printf("\n     +++++++++++++++++++++++++++++++");
        printf("\n\n\t\tMENU\n\n");
        printf("\n\t1. AGREGAR LIBRO NUEVO\n");
        printf("\n\t2. MOSTRAR LISTA DE LIBROS\n");
        printf("\n\t3. ENTRADA DE LIBRO\n");
        printf("\n\t4. SALIDA DE LIBRO\n");
        printf("\n\t5. SALIR\n");
        printf("\n     +++++++++++++++++++++++++++++++\n");
        printf("\n\n\t->Elige una opcion: ");
        scanf("%d",&opc);
        switch(opc)
        {
            case 1:
                do
                {
                    system("cls");
                    printf("\n\t\t\t\t\t\t\t<< AGREGAR LIBRO >>\n\n\n");
                    CargaLista(fd,&E);
                    if(!vacia(E))
                    {
                        i=0;
                        valor=0;
                        while(E != NULL)
                        {
                            ID=atoi(E->libro.id_lib);
                            reservaMemoriaVector(1);
                            arreglo[i]=ID;
                            if(valor < arreglo[i])
                                valor=arreglo[i];
                            i++;
                            E=E->sig;
                        }
                        valor++;
                    }
                    else
                        valor=1;
                    ID=valor;
                    itoa(ID,cad,10);
                    EscArc(fd,cad);
                    x=strlen(cad);
                    printf("\n\t-> Ingresa los siguientes datos del libro\n\n\n");
                    printf("\n\tId Libro: ");
                    for(i=5; i>x; i--)
                        printf("0");
                    printf("%d",ID);
                    printf("\n");
                    LeeDatos(fd);
                    gotoxy(fila+45,columna+13);printf("... Tus datos han sido guardados ...");
                    printf("\n\n\t->Agregar otro libro?: ");
                    scanf("%c",&x);
                }while((x == 's') || (x == 'S'));
            break;
            case 2:
                system("cls");
                printf("\n\t\t\t\t\t\t\t<< MOSTRAR LIBRO >>\n\n\n");
                inicializa(&E);
                CargaLista(fd,&E);
                imprime(E);
                getch();
            break;
            case 3:
                system("cls");
                printf("\n\t\t\t\t\t\t<< ENTRADA DE LIBRO >>\n\n\n");
                printf("\n\n\t\t-> Ingresa el ID del libro: ");
                fflush(stdin);
                gets(id);
                aux=localiza(fd,id);
                if(aux > 0)
                {
                    printf("\n\n\n\t\tNumero de Entradas: ");
                    scanf("%d",&ent);
                    Reescribe(fd,aux,ent,1);
                    lseek(fd,(aux-1),0);
                    write(fd,"&",1);
                    gotoxy(fila+50,columna+10);printf("... Cambios Guardados ... ");
                }
                else
                {
                    gotoxy(fila+50,columna+10);printf("... Libro No Encontrado ...");
                }
                getch();
            break;
            case 4:
                system("cls");
                printf("\n\t\t\t\t\t\t<< SALIDA DE LIBRO >>\n\n\n");
                printf("\n\n\t\t-> Ingresa el ID del libro: ");
                fflush(stdin);
                gets(id);
                aux=localiza(fd,id);
                if(aux > 0)
                {
                    printf("\n\n\n\t\tNumero de Bajas: ");
                    scanf("%d",&sal);
                    Reescribe(fd,aux,sal,2);
                    lseek(fd,(aux-1),0);
                    write(fd,"&",1);
                    gotoxy(fila+50,columna+10);printf("... Cambios Guardados ... ");
                }
                else
                {
                    gotoxy(fila+50,columna+10);printf("... Libro No Encontrado ...");
                }
                getch();
            break;
            case 5:
                system("cls");
                gotoxy(fila+50,columna+10);printf("... Gracias por tu Visita ...\n\n");
            break;
            default:
                gotoxy(fila+50,columna+10);printf("... Opcion Incorrecta ...\n\n");
        }
    }while(opc != 5);
    close(fd);
    return 0;
}
