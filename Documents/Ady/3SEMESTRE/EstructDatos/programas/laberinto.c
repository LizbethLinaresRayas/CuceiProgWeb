#include <stdio.h>
#include <conio.h>
#include <dos.h>
int mat[20][20];

void llenado()
{
int i,o;

//llenado de la matriz
for (i=0;i<20;i++)
 {
  for (o=0;o<20;o++)
   {
     mat[i][o]=1;
   }
 }
//dejando los caminos
i=1;
mat[1][i]=0;
for(o=14;o<17;o++)
mat[o][i]=0;
mat[5][i]=0;
mat[10][i]=0;

i=2;
mat[10][i]=0;
mat[14][i]=0;
mat[16][i]=0;
for(o=1;o<9;o++)
mat[o][i]=0;

i=3;
mat[1][i]=0;
for(o=8;o<15;o++)
mat[o][i]=0;
mat[5][i]=0;
mat[16][i]=0;

i=4;
mat[1][i]=0;
mat[2][i]=0;
mat[5][i]=0;
mat[8][i]=0;
mat[16][i]=0;
mat[17][i]=0;
mat[18][i]=0;

i=5;
for(o=11;o<15;o++)
mat[o][i]=0;
mat[2][i]=0;
mat[5][i]=0;
mat[8][i]=0;

i=6;
for(o=7;o<12;o++)
mat[o][i]=0;
for(o=14;o<19;o++)
mat[o][i]=0;
mat[2][i]=0;
mat[4][i]=0;
mat[5][i]=0;

i=7;
mat[2][i]=0;
mat[4][i]=0;
mat[7][i]=0;
mat[11][i]=0;
mat[14][i]=0;
mat[18][i]=0;

i=8;
mat[2][i]=0;
mat[4][i]=0;
mat[7][i]=0;
for(o=9;o<15;o++)
mat[o][i]=0;
mat[17][i]=0;
mat[18][i]=0;

i=9;
mat[9][i]=0;
mat[17][i]=0;
for(o=2;o<8;o++)
mat[o][i]=0;

i=10;
mat[3][i]=0;
mat[7][i]=0;
mat[9][i]=0;
for(o=14;o<19;o++)
mat[o][i]=0;

i=11;
mat[18][i]=0;
for(o=3;o<8;o++)
mat[o][i]=0;
for(o=9;o<15;o++)
mat[o][i]=0;

i=12;
mat[3][i]=0;
mat[7][i]=0;
mat[9][i]=0;
mat[14][i]=0;
mat[18][i]=0;

i=13;
mat[1][i]=0;
mat[2][i]=0;
mat[3][i]=0;
mat[7][i]=0;
mat[9][i]=0;
mat[18][i]=0;
for(o=11;o<15;o++)
mat[o][i]=0;

i=14;
mat[3][i]=0;
mat[7][i]=0;
mat[8][i]=0;
mat[9][i]=0;
mat[11][i]=0;
for(o=16;o<19;o++)
mat[o][i]=0;

i=15;
mat[3][i]=0;
mat[5][i]=0;
mat[6][i]=0;
mat[7][i]=0;
mat[11][i]=0;
mat[12][i]=0;
mat[16][i]=0;

i=16;
mat[3][i]=0;
mat[5][i]=0;
mat[7][i]=0;
mat[12][i]=0;
mat[16][i]=0;

i=17;
for(o=1;o<6;o++)
mat[o][i]=0;
for(o=7;o<11;o++)
mat[o][i]=0;
for(o=12;o<15;o++)
mat[o][i]=0;
for(o=16;o<19;o++)
mat[o][i]=0;

i=18;
mat[1][i]=0;
mat[5][i]=0;
mat[14][i]=0;
mat[18][i]=0;
mat[10][i]=0;
i=19;
mat[1][i]=0;
mat[5][i]=0;
mat[10][i]=0;
mat[14][i]=0;
mat[18][i]=0;
}//fin de la funcion llenado

void main()
{
char a,num,salir;
int x,y,val,k,j,l,i;
("sys");
printf("Bienvenido a Laberinto V.1.1");

m:
;
do
{
("sys");
printf ("SI DESEA JUGAR PRESIONE 1");
printf ("SI DESEA SALIR PRESIONE 2");
printf ("            ");
salir=getch();

}while (salir!=1 && salir!=2);
e:
;
("sys");

//laberinto
printf("ллллллллллллллл лллл");
printf("л ллл лллл ллл   ллл");
printf("л        л ллл л ллл");
printf("л ллл лл       л ллл");
printf("л  лл лл ллллллл   л");
printf("лл лл лл лл    ллллл");
printf("лл л  л     лл     л");
printf("лл л лл ллл лл ллл л");
printf("лл л лл л      лл  л");
printf("лл      л ллллллл лл");
printf("ллл ллл л лллл     л");
printf("ллл     л      ллл л");
printf("ллл ллл л лллл ллл л");
printf("л   ллл л л    ллл л");
printf("ллл ллл   л лллл   л");
printf("ллл л   ллл  ллл ллл");
printf("ллл л л лллл ллл ллл");
printf("л     л    л   л   л");
printf("л ллл лллл ллл ллл л");
printf("л ллл лллл ллл ллл л");
printf(" 1   2    3   4   5 ");
//posesiona la figura en una de las entradas
do
{
printf("Seleccione su entrada (Presione 1, 2, 3, 4 o 5)");
num=getch();
}while (num!='1' && num!='2' && num!='3' && num!='4' && num!='5');
("sys");

printf("ллллллллллллллл лллл");
printf("л ллл лллл ллл   ллл");
printf("л        л ллл л ллл");
printf("л ллл лл       л ллл");
printf("л  лл лл ллллллл   л");
printf("лл лл лл лл    ллллл");
printf("лл л  л     лл     л");
printf("лл л лл ллл лл ллл л");
printf("лл л лл л      лл  л");
printf("лл      л ллллллл лл");
printf("ллл ллл л лллл     л");
printf("ллл     л      ллл л");
printf("ллл ллл л лллл ллл л");
printf("л   ллл л л    ллл л");
printf("ллл ллл   л лллл   л");
printf("ллл л   ллл  ллл ллл");
printf("ллл л л лллл ллл ллл");
printf("л     л    л   л   л");
printf("л ллл лллл ллл ллл л");
printf("л ллл лллл ллл ллл л");
printf("лллллллллллллллллллл");
printf("LABERINTO V.1.1");
switch (num)
{
case '1':

x=31;
y=21;

break;
case '2':

x=35;
y=21;

break;
case '3':

x=40;
y=21;

break;
case '4':

x=44;
y=21;

break;
case '5':

x=48;
y=21;

break;
}

//Lugar de entrada


llenado();

val=0;

//comienzo de el movimiento
do
{
f:
;

a=getch();
switch (a)
{
case 72:
l=1;
printf(" ");
y=y-1;
printf("");

break;
case 80:
l=2;
printf(" ");
y=y+1;
printf("");

break;
case 75:
l=3;
printf(" ");
x=x-1;
printf("");

break;
case 77:
l=4;
printf(" ");
x=x+1;
printf("");

break;
}

k=x-30;
j=y-2;

if (mat[k][j]==1)
{
val=1;
}

}while(val!=1);
//fin del movimiento

if (k==15 && j==0)
{
for(i=1;i<16;i++)
{
("sys");
printf("Creado por Luis Sandoval");
printf("Gracias por usar Laberinto V.1.1");
printf("GANASTE");
}
goto m;
}
else
{
if (mat[k][j]==1)
{

x=k+30;
y=j+2;
printf("л");
switch(l)
{
case 1:
y=y+1;
printf("");
break;
case 2:
y=y-1;
printf("");
break;
case 3:
x=x+1;
printf("");
break;
case 4:
x=x-1;
printf("");
break;
}
}

}
getch();
;
} //void main
