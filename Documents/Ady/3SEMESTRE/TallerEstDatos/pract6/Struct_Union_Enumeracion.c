/*Adriana Lizbeth Linares Rayas
Cod. 210596378 Lic. Informatica
Secc. D-15 Estructura de Datos*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

union t_union{
    char c;
    int i;
    float f;
    double d;
};

struct t_struct{
    char c;
    int i;
    float f;
    double d;
};

enum t_enumeracion{
    cero,
    uno,
    dos,
    tres,
};

int *puntero;

//fflush(stdin);
//
main()
{
    union t_union tipoUnion;
    struct t_struct tipoStruct;
    enum t_enumeracion e;
    printf("\n\n\t\tEstructura, Union y Enumeracion\n\n");
    printf("\n\t  - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("\n\t |\t\tIngresa un Caracter: \t    |\n\n\t\t\t\t");
    scanf("%c",&tipoUnion.c);
    tipoStruct.c=tipoUnion.c;
    printf("\n\t |\t\tIngresa un Entero:          |\n\n\t\t\t\t");
    scanf("%i",&tipoUnion.i);
    tipoStruct.i=tipoUnion.i;
    printf("\n\t |\t\tIngresa un Real:            |\n\n\t\t\t\t");
    scanf("%f",&tipoUnion.f);
    tipoStruct.f=tipoUnion.f;
    printf("\n\t |\t\tIngresa un Doble:           |\n\n\t\t\t\t");
    scanf("%lf",&tipoUnion.d);
    tipoStruct.d=tipoUnion.d;
    printf("\n\t  - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("\n\n");
    printf("\n\t->Tamaño de la Union \t\t%d Bytes \n", sizeof(tipoUnion));
    printf("\n\t->Tamaño de la Estrcutura\t%d Bytes \n", sizeof(tipoStruct));
    printf("\n\t->Tamaño de la Enumeracion \t%d Bytes \n", sizeof(e));
    printf("\n\n\t>>*puntero Tamaño          \t%d Bytes \n",sizeof(int));
    printf("\n\n");
    printf("\n\n\t\t<<Datos de la Union>>\n\n");
    printf("\n\tTipo de Dato\t  Dato   \tDireccion\n\n");
    printf("\n\tCaracter \t    %c \t        %x\n",tipoUnion.c,&tipoUnion.c);
    printf("\n\tEntero\t\t    %d \t        %x\n",tipoUnion.i,&tipoUnion.i);
    printf("\n\tReal\t           %.2f \t%x\n",tipoUnion.f,&tipoUnion.f);
    printf("\n\tDoble\t          %lf \t%x\n\n",tipoUnion.d,&tipoUnion.d);
    printf("\n\n");
    printf("\n\n\t\t<<Datos de la Estructura>>\n\n");
    printf("\n\tTipo de Dato\t  Dato   \tDireccion\n\n");
    printf("\n\tCaracter \t    %c \t        %x\n",tipoStruct.c,&tipoStruct.c);
    printf("\n\tEntero\t\t   %d \t\t%x\n",tipoStruct.i,&tipoStruct.i);
    printf("\n\tReal\t           %.2f \t%x\n",tipoStruct.f,&tipoStruct.f);
    printf("\n\tDoble\t         %lf \t%x\n",tipoStruct.d,&tipoStruct.d);
    printf("\n\n");
    e=dos;
    printf("\n\n\t\t<<Datos de la Enumeracion>>\n\n");
    printf("\n\tTipo de Dato\t  Dato   \tDireccion\n\n");
    printf("\n\tCaracter \t    %d \t        %x\n",e,&e);
    getch();

}
