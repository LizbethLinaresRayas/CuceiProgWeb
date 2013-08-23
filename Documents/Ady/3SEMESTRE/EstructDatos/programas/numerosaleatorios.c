#include <conio.h>
#include <stdio.h>
#include <time.h>
#define TAM 25
#define PAL 20

// Las palabras que se van a agregar a la sopa de letras
// Deben ser tantas palabras como la definción de PAL
// Escritas en mayúsculas para que se vean bien
const char *PALABRAS[PAL] = { "AMARILLO","ORO","CAFE",
                        "MORADO","GRIS","NEGRO",
                        "ROJO","AZUL","VERDE",
                        "ROSA","GRISOXFORD","NARANJA",
                         "BLANCO","TINTO","MAGENTA",
                        "CAQUI","CORAL","PURPURA",
                        "FUCSIA","TURQUESA"};

// Llena la matriz con caracteres /0
void inicializa(char m[TAM][TAM]) {
    int i, j;

    for (i=0;i<TAM;i++)
        for (j=0;j<TAM;j++)
            m[i][j]='\0';
}

// Llena los espacios vacíos con caracteres al azar
void rellena(char m[TAM][TAM]) {
    int i, j;

    for(i=0;i<TAM;i++)
        for(j=0;j<TAM;j++)
            if(m[i][j]=='\0')
                m[i][j]=rand()%26+65;
}

// Muestra la sopa de letras
void muestra(char m[TAM][TAM]) {
    int i, j;

    printf("\n\n\n");
    for(i=0;i<TAM;i++) {
        for(j=0;j<TAM;j++)
            printf("%c ",m[i][j]);
        printf("\n\n");
    }
}

// Valida que la palabra s se pueda agregar a la matriz m
// en la posición (x, y) y en la dirección (dx, dy)
int valida(char m[TAM][TAM], const char *s, int x, int y, int dx, int dy) {
    int i, v = 1;

    for(i=0;i<strlen(s);i++,x+=dx,y+=dy)
        if(m[y][x]!=s[i]&& m[y][x]!= '\0' || x<0 || y<0 || x>= TAM || y>=TAM)
            v=0;
    printf("\n%s puede agregarse (x%d, y%d, dx%d, dy%d): %d", s, x, y, dx, dy, v);

    return v;
}

// Agrega la palabra s a la sopa de letras
void agrega(char m[TAM][TAM], const char *s) {
    int i, x, y, dx, dy;

    dx=rand()%3-1;
    dy=rand()%3-1;
    dx=dx==0?1:dx;
    while(!valida(m, s, x = rand() % TAM, y = rand() % TAM, dx, dy)) ;
    for (i = 0; i < strlen(s); i++, x += dx, y += dy)
        m[y][x] = s[i];
}

int main() {
    ("sys");
    char m[TAM][TAM];
    int k,i;
    char palabUsu[PAL];
    srand(time(0));
    inicializa(m);
    for (i = 0; i < PAL; i++)
        agrega(m, PALABRAS[i]);
    muestra(m);
    rellena(m);
    muestra(m);
    printf("Ingresa tus palabras: ");
    for(k=0;k<=20;k++){
        gets(palabUsu[k]);
    }

    if(palabUsu[k]==PALABRAS[PAL])
        printf("FELICIDADES HAS GANADO");
    getch();

}

