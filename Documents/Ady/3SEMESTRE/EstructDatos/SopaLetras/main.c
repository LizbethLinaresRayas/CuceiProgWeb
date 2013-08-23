#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#define tam 25
#define pal 20
#define X 10
const char *color[pal] = { "AMARILLO","ORO","CAFE",
                           "MORADO","GRIS","NEGRO",
                           "ROJO","AZUL","VERDE",
                           "ROSA","GRISOXFORD","NARANJA",
                           "BLANCO","TINTO","MAGENTA",
                           "CAQUI","CORAL","PURPURA",
                           "FUCSIA","TURQUESA"};

const char *animal[pal] = { "VACA","OSO","TORO",
                            "VENADO","PERRO","GATO",
                            "JIRAFA","COCODRILO","TORTUGA",
                            "GARZA","ELEFANTE","AVESTRUZ",
                            "HIPOPOTAMO","RANA","BALLENA",
                            "FOCA","DELFIN","TIBURON",
                            "GALLINA","SERPIENTE"};

const char *frut[pal] = { "PLATANO","MANZANA","PAPAYA",
                          "MANGO","FRESA","GUAYABA",
                          "KIWI","MAMEY","JICAMA",
                          "PEPINO","TUNA","UVA",
                          "PERA","MELON","CIRUELA",
                          "COCO","MANDARINA","NARANJA",
                          "LIMA","TORANJA"};


void inicializa(char mat[tam][tam]){
    int i,j;

    for(i=0;i<tam;i++)
        for(j=0;j<tam;j++)
            mat[i][j]='\0';
}

void rellena(char mat[tam][tam]){
    int i,j;

    srand(time(0));
    for(i=0;i<tam;i++)
        for(j=0;j<tam;j++)
            if(mat[i][j]=='\0')
                mat[i][j]=rand()%26+65;
}

int valida(char mat[tam][tam], const char *s, int x, int y, int dx, int dy) {
    int i, v=1;

    for(i=0;i<strlen(s);i++,x+=dx,y+=dy)
        if(mat[y][x]!=s[i] &&  mat[y][x]!='\0' || x<0 || y<0 || x>= tam || y>=tam)
            v=0;
    return v;
}

void muestra(char mat[tam][tam]) {
    int i,j;

    printf("\n\n\n");
    for(i=0;i<tam;i++) {
        for(j=0;j<tam;j++)
            printf(" %c ",mat[i][j]);
        printf("\n\n");
    }
}

void agrega(char mat[tam][tam],const char *s){
    int i,x,y,dx,dy;

    srand(time(0));
    dx=rand()%3-1;
    dy=rand()%3-1;
    dx=dx==0?1:dx;
    while(!valida(mat, s, x = rand() % tam, y = rand() % tam, dx, dy)) ;
    for (i=0;i<strlen(s);i++,x+=dx,y+=dy)
        mat[y][x]=s[i];
}

int main()
{
    int i,k,y,opc,OP,op,opcnum;
    char mat[tam][tam];
    char palabUsu[pal][X];
    char ins;
    inicializa(mat);
    srand(time(0));
    printf("\n\n\t\t\" SOPA DE LETRAS \"");
    printf("\n\n\t\t ...BIENVENIDO...");
    do{
        printf("\n\n\t* * * * * * * * * * * * * * * * * * * * * ");
        printf("\n\n\n\t*\t    MENU PRINCIPAL      \t*");
        printf("\n\n\n\t*\t  1.INSTRUCCIONES\t\t*");
        printf("\n\n\t*\t  2.JUGAR        \t\t*");
        printf("\n\n\t*\t  3.SALIR        \t\t*");
        printf("\n\n\n\t* * * * * * * * * * * * * * * * * * * * * ");
        printf("\n\n\t->QUE DECEAS HACER...ELIGE UNA OPCION: ");
        scanf("%d",&opc);
        switch(opc){
            case 1:
                ("sys");
                do{
                    printf("\n\n\t* * * * * * * * * * * * * * * * * * * * *");
                    printf("\n\n\t*\t...INSTRUCCIONES...         \t*");
                    printf("\n\n\t*\t   1.VER                    \t*");
                    printf("\n\n\t*\t   2.SALIR               \t*");
                    printf("\n\n\t* * * * * * * * * * * * * * * * * * * * *");
                    printf("\n\n\t-> CUAL ELIGES: ");
                    scanf("%d",&y);
                    switch(y){
                        case 1:
                            printf("\n\n\t  _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _");
                            printf("\n\n\t|  ->DEBES ELEGIR EL TEMA QUE PREFIERAS.    \t|");
                            printf("\n\n\t|  ->CUANDO INICIAS A JUGAR:                \t|");
                            printf("\n\n\t|      DEBERAS BUSCAR EN LA SOPA DE LETRAS  \t|");
                            printf("\n\n\t|      LAS PALABRAS RELACIONADAS CON EL TEMA\t|");
                            printf("\n\n\t|      QUE ELEGISTE.                        \t|");
                            printf("\n\n\t|  ->TODOS LOS TEMAS CONSTAN DE 20 PALABRAS.\t|");
                            printf("\n\n\t|  ->CAPTURAS UNA PALABRA Y PRESIONAS ENTER.\t|");
                            printf("\n\n\t|  ->PODRAS REGRESAR AL MENU PARA VER DONDE \t|");
                            printf("\n\n\t|    SE ENCUENTRAN LAS PALABRAS OCULTAS.    \t|");
                            printf("\n\n\t|  ->ESTAS LISTO........                    \t|");
                            printf("\n\n\t|  ->QUE TE DIVIERTAS!!!                    \t|");
                            printf("\n\n\t| _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ |");
                        break;
                        case 2:
                            printf("\n\n\t<- REGRESARAS A MENU PRINCIPAL");
                        break;
                        default:
                            printf("\n\n\tOPCION INVALIDA");
                    }
                }while(y!=2);
            break;
            case 2:
                ("sys");
                do{
                    printf("\n\n\t* * * * * * * * * * * * * * * * * * * * * ");
                    printf("\n\n\t*\t.....JUGAR.....\t\t\t*");
                    printf("\n\n\t*  -> TEMAS\t\t\t\t*");
                    printf("\n\n\t*\t  1.ANIMALES \t\t\t*");
                    printf("\n\n\t*\t  2.COLORES \t\t\t*");
                    printf("\n\n\t*\t  3.FRUTAS \t\t\t*");
                    printf("\n\n\t*\t  4.SALIR \t\t\t*");
                    printf("\n\n\t* * * * * * * * * * * * * * * * * * * * * ");
                    printf("\n\n\t-> CUAL ELIGES: ");
                    scanf("%d",&OP);
                    switch(OP){
                        case 1:
                            ("sys");
                            do{
                                printf("\n\n\t* * * * * * * * * * * * * * * * * * * * * ");
                                printf("\n\n\t*\t.....ANIMALES.....\t\t*");
                                for(i=0;i<pal;i++)
                                    agrega(mat,animal[i]);
                                printf("\n\n\t*\t1.VER PALABRAS  \t\t*");
                                printf("\n\n\t*\t2.JUGAR  \t\t\t*");
                                printf("\n\n\t*\t3.SALIR  \t\t\t*");
                                printf("\n\n\t* * * * * * * * * * * * * * * * * * * * * ");
                                printf("\n\n\t -> ELIGE UNA OPCION: ");
                                scanf("%d",&opcnum);
                                switch(opcnum){
                                    case 1:
                                        ("sys");
                                        muestra(mat);
                                    break;
                                    case 2:
                                        ("sys");
                                        rellena(mat);
                                        muestra(mat);
                                        printf("\n\n\t* * * * * * * * * * * * * * * * * * * * * ");
                                        printf("\n\n\t -> -> AHORA BUSCA LAS PALABRAS \n");
                                        printf("\n\n\t\t\tSUERTE!!!!");
                                        printf("\n\n\tIngresa tus palabras: ");
                                        for(k=0;k<=20;k++){
                                            printf("\n\t%d ",k);
                                            gets(palabUsu[k]);
                                        }
                                    break;
                                    case 3:
                                        printf("\n\n\t  ...GRACIAS POR UTILIZAR EL JUEGO...");
                                        printf("\n\n\t<- REGRESARAS A MENU JUGAR\n");
                                    break;
                                    default:
                                        ("sys");
                                        printf("\n\n\tOPCION INVALIDA");
                                }
                            }while(opcnum!=3);
                        break;
                        case 2:
                            ("sys");
                            do{
                                printf("\n\n\t* * * * * * * * * * * * * * * * * * * * * ");
                                printf("\n\n\t*\t.....COLORES.....\t\t*");
                                for(i=0;i<pal;i++)
                                    agrega(mat,color[i]);
                                printf("\n\n\t*\t1.VER PALABRAS  \t\t*");
                                printf("\n\n\t*\t2.JUGAR  \t\t\t*");
                                printf("\n\n\t*\t3.SALIR  \t\t\t*");
                                printf("\n\n\t* * * * * * * * * * * * * * * * * * * * * ");
                                printf("\n\n\t -> ELIGE UNA OPCION: ");
                                scanf("%d",&opcnum);
                                switch(opcnum){
                                    case 1:
                                        ("sys");
                                        muestra(mat);
                                    break;
                                    case 2:
                                        ("sys");
                                        rellena(mat);
                                        muestra(mat);
                                        printf("\n\n\t* * * * * * * * * * * * * * * * * * * * * ");
                                        printf("\n\n\t -> -> AHORA BUSCA LAS PALABRAS \n");
                                        printf("\n\n\t\t\tSUERTE!!!!");
                                        printf("\n\n\tIngresa tus palabras: ");
                                        for(k=0;k<=20;k++){
                                            printf("\n\t%d ",k);
                                            gets(palabUsu[k]);
                                        }
                                    break;
                                    case 3:
                                        printf("\n\n\t  ...GRACIAS POR UTILIZAR EL JUEGO...");
                                        printf("\n\n\t<- REGRESARAS A MENU JUGAR\n");
                                    break;
                                    default:
                                        ("sys");
                                        printf("\n\n\tOPCION INVALIDA");
                                }
                            }while(opcnum!=3);
                        break;
                        case 3:
                            ("sys");
                            do{
                                printf("\n\n\t* * * * * * * * * * * * * * * * * * * * * ");
                                printf("\n\n\t*\t.....FRUTAS.....\t\t*");
                                for(i=0;i<pal;i++)
                                    agrega(mat,frut[i]);
                                printf("\n\n\t*\t1.VER PALABRAS  \t\t*");
                                printf("\n\n\t*\t2.JUGAR  \t\t\t*");
                                printf("\n\n\t*\t3.SALIR  \t\t\t*");
                                printf("\n\n\t* * * * * * * * * * * * * * * * * * * * * ");
                                printf("\n\n\t -> ELIGE UNA OPCION: ");
                                scanf("%d",&opcnum);
                                switch(opcnum){
                                    case 1:
                                        ("sys");
                                        muestra(mat);
                                    break;
                                    case 2:
                                        ("sys");
                                        rellena(mat);
                                        muestra(mat);
                                        printf("\n\n\t* * * * * * * * * * * * * * * * * * * * * ");
                                        printf("\n\n\t -> -> AHORA BUSCA LAS PALABRAS \n");
                                        printf("\n\n\t\t\tSUERTE!!!!");
                                        printf("\n\n\tIngresa tus palabras: ");
                                        for(k=0;k<=20;k++){
                                            printf("\n\t%d ",k);
                                            gets(palabUsu[k]);
                                        }
                                    break;
                                    case 3:
                                        printf("\n\n\t  ...GRACIAS POR UTILIZAR EL JUEGO...");
                                        printf("\n\n\t<- REGRESARAS A MENU JUGAR\n");
                                    break;
                                    default:
                                        ("sys");
                                        printf("\n\n\tOPCION INVALIDA");
                                }
                            }while(opcnum!=3);
                        break;
                        case 4:
                            printf("\n\n\t<- REGRESARAS A MENU PRINCIPAL\n");
                        break;
                    }
                }while(OP!=4);
            break;
            case 3:
                printf("\n\n\t<- GRACIAS POR TU VISITA!!\n");
            default:
                printf("\n\n\tOPCION INVALIDA");
        }
    }while(opc!=3);
}



