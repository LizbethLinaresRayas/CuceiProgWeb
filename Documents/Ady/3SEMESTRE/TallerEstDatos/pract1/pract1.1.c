/*Practica 1.1
Adriana Lizbeth Linares Rayas
Cod. 210596378 Lic. Informatica
Taller de Estructura de Datos Secc. D-15*/
#include <stdio.h>
#include <conio.h>
#include <limits.h>
#include <float.h>
main()
{
    printf("\n\tLongitudes de Tipos de Datos en bytes\n\t\tRango Minimo y Maximo\n");
    printf("\n\t\tTipos de Datos\n");
    printf("\n   Dato\t\t Longitud\t\tRango\n");
    printf("\n    int  \t %d bytes  \t%d a %d\n",sizeof(int),INT_MIN,INT_MAX);
    printf("\n   long  \t %d bytes  \t%d a %d\n",sizeof(long),LONG_MIN,LONG_MAX);
    printf("\n   short \t %d bytes  \t    %d a %d\n",sizeof(short),SHRT_MIN,SHRT_MAX);
    printf("\nunsigned int\t %d bytes\t\t%d\n",sizeof(unsigned int),USHRT_MAX);
    printf("\nunsigned long\t %d bytes\t    %Nu\n",sizeof(unsigned long int),ULONG_MAX);
    printf("\nunsigned short\t %d bytes\t\t%d\n",sizeof(unsigned short),USHRT_MAX);
    printf("\n    char \t %d byte\t\t    %d a %d\n",sizeof(char),CHAR_MIN,CHAR_MAX);
    printf("\nunsigned char\t %d byte\t\t\t%d\n",sizeof(unsigned char),UCHAR_MAX);
    printf("\n    float\t %d byte\t\t   %d a %d\n",sizeof(float),FLT_MIN,FLT_MAX);
    printf("\n   double\t %d byte\t\t   %d a %d\n",sizeof(double),DBL_MIN,DBL_MAX);
    return 0;
    getch();
}
