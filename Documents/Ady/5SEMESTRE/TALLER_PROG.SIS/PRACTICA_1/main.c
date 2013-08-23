#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int validaEtiqueta(char etiqueta[15])
{
    int cont=0;
    int contAux=1;
    int i;
    int aux=0;

    aux=strlen(etiqueta);
    if(aux < 8)
        cont++;
    if(cont == 1)
    {
        if(((etiqueta[0] > 64) && (etiqueta[0] < 91)) || ((etiqueta[0] > 96) && (etiqueta[0] < 123)))
            cont++;
    }
    if(cont == 2)
    {
        for(i=1; i<strlen(etiqueta); i++)
        {
            if(((etiqueta[i] > 64 && etiqueta[i] < 91) || ((etiqueta[i] > 96) && (etiqueta[i] < 123))) || (etiqueta[i] > 47 && etiqueta[i] < 58) || (etiqueta[i] == 95))
                contAux++;
        }
        if(aux == contAux)
            cont++;
    }
    return cont;
}

int validaCodop(char codop[10])
{
    int cont=0;
    int contAux=1;
    int aux=0;
    int contPunto=0;
    int i;

    aux=strlen(codop);
    if(aux < 5)
        cont++;
    if(cont == 1)
    {
        if(((codop[0] > 64) && (codop[0] < 91)) || ((codop[0] > 96) && (codop[0] < 123)))
            cont++;
    }
    if(cont == 2)
    {
        for(i=1; i<aux; i++)
        {
            if(codop[i] == '.')
                contPunto++;
        }
        if(contPunto <= 1)
            cont++;
    }
    if(cont == 3)
    {
        for(i=1; i<strlen(codop); i++)
        {
            if(((codop[i] > 64) && (codop[i] < 91)) || ((codop[i] > 96) && (codop[i] < 123)) || (codop[i] == 46))
                contAux++;
        }
        if(aux == contAux)
            cont++;
    }
    return cont;
}

int main()
{
    FILE *fd;
    int i=0,j=0,k=0;
    int cont=1,contop=1; //contadores
    int bEnd=0,band=0,bandComentario=0,bandOpe=0,bandcont=0; //banderas
    char etiqueta[15];
    char codop[12];
    char operando[40];
    char caracter;
    char cadena[50];

    for(i=0; i<15; i++)
        etiqueta[i]='\0';
    for(i=0; i<12; i++)
        codop[i]='\0';
    for(i=0; i<40; i++)
        operando[i]='\0';


    fd=fopen("P1ASM.txt","r");
    if(fd != NULL)
    {
        while(fgets(cadena,50,fd))
        {
            if(cadena[0] == ';')
            {
                printf("\n\nEs un comentario\n");
                bandComentario=1;
            }
            if(bandComentario == 0)
            {
                for(i=0; i<strlen(cadena); i++)
                {
                    caracter=cadena[i];
                    if((((caracter == ' ') || (caracter == '\t'))  && (band == 0)) && (bandOpe == 0))
                    {
                        if((cont == 1) || (cont == 2))
                        {
                            band=1;
                            j=0;
                            cont++;
                        }
                        if(cont == 3)
                            bandOpe=1;
                    }
                    else
                    {
                        if(((caracter != ' ') && (caracter != '\t')) && (bandOpe == 0))
                        {
                            band=0;
                            if(cont == 1)
                            {
                                etiqueta[j]=caracter;
                                j++;
                            }
                            else
                            {
                                if(cont == 2)
                                {
                                    codop[j]=caracter;
                                    j++;
                                }
                            }
                        }
                        else
                        {
                            if(bandOpe == 1)
                            {
                                if((caracter > 32) && (bandcont == 0))
                                    bandcont=1;
                                if(((caracter != '\0') && (caracter != '\n')) && (bandcont == 1))
                                {
                                    operando[j]=caracter;
                                    j++;
                                    contop++;
                                }
                            }
                        }
                    }
                }
                if(etiqueta[0] != '\0')
                {
                    for(k=0; k<strlen(etiqueta); k++)
                    {
                        if(etiqueta[k] == '\n')
                            etiqueta[k]='\0';
                    }
                    if(validaEtiqueta(etiqueta) == 0)
                    {
                        printf("\nETIQUETA: %s",etiqueta);
                        printf("\n\tError: La longitud maxima de una etiqueta es de 8 caracteres.");
                    }
                    else
                    {
                        for(k=0; k<strlen(etiqueta); k++)
                        {
                            if(etiqueta[k] == '\n')
                                etiqueta[k]='\0';
                        }
                        if(validaEtiqueta(etiqueta) == 1)
                        {
                            printf("\nETIQUETA: %s",etiqueta);
                            printf("\n\tError: La etiqueta debe de iniciar con una letra.");
                        }
                        else
                        {
                            for(k=0; k<strlen(etiqueta); k++)
                            {
                                if(etiqueta[k] == '\n')
                                    etiqueta[k]='\0';
                            }
                            if(validaEtiqueta(etiqueta) == 2)
                            {
                                printf("\nETIQUETA: %s",etiqueta);
                                printf("\n\tError: Los caracteres validos de una etiqueta son letras, digitos(0...9) y el guion bajo.");
                            }
                            else
                            {
                                for(k=0; k<strlen(etiqueta); k++)
                                {
                                    if(etiqueta[k] == '\n')
                                        etiqueta[k]='\0';
                                }
                                if(validaEtiqueta(etiqueta) == 3)
                                    printf("\nETIQUETA: %s",etiqueta);
                            }
                        }
                    }
                }
                else
                {
                    strcpy(etiqueta,"NULL");
                    printf("\nETIQUETA: %s",etiqueta);
                }
                if(codop[0] != '\0')
                {
                    for(k=0; k<strlen(codop); k++)
                    {
                        if(codop[k] == '\n')
                            codop[k]='\0';
                    }
                    if(validaCodop(codop) == 0)
                    {
                        printf("\nCODOP: %s",codop);
                        printf("\n\tError: La longitud maxima de un codigo de operacion es de 5 caracteres.");
                    }
                    else
                    {
                        for(k=0; k<strlen(codop); k++)
                        {
                            if(codop[k] == '\n')
                                codop[k]='\0';
                        }
                        if(validaCodop(codop) == 1)
                        {
                            printf("\nCODOP: %s",codop);
                            printf("\n\tError: El codigo de operacion debe de iniciar con una letra.");
                        }
                        else
                        {
                            for(k=0; k<strlen(codop); k++)
                            {
                                if(codop[k] == '\n')
                                    codop[k]='\0';
                            }
                            if(validaCodop(codop) == 2)
                            {
                                printf("\nCODOP: %s",codop);
                                printf("\n\tError: El codigo de operacion solo puede contener un punto.");
                            }
                            else
                            {
                                for(k=0; k<strlen(codop); k++)
                                {
                                    if(codop[k] == '\n')
                                        codop[k]='\0';
                                }
                                if(validaCodop(codop) == 3)
                                {
                                    printf("\nCODOP: %s",codop);
                                    printf("\n\tError: Los caracteres validos de un codigo de operacion son letras y un punto.");
                                }
                                else
                                {
                                    printf("\nCODOP: %s",codop);
                                    if((strcmp(codop,"END") == 0) || (strcmp(codop,"EnD") == 0) || (strcmp(codop,"End") == 0) || (strcmp(codop,"end") == 0) || (strcmp(codop,"enD") == 0) || (strcmp(codop,"eND") == 0))
                                        bEnd=1;
                                }
                            }
                        }
                    }
                }
                else
                {
                    strcpy(codop,"NULL");
                    printf("\nCODOP: %s",codop);
                    printf("\n\tError: Siempre debe de existir un codigo de operacion.");
                }
                if(operando[0] != '\0')
                {
                    for(k=0; k<strlen(operando); k++)
                    {
                        if(operando[k] == '\n')
                            operando[k]='\0';
                    }
                    printf("\nOPERANDO: %s\n",operando);
                }
                else
                {
                    strcpy(operando,"NULL");
                    printf("\nOPERANDO: %s\n",operando);
                }
                j=0;
                cont=1;
                contop=1;
                for(i=0; i<15; i++)
                    etiqueta[i]='\0';
                for(i=0; i<10; i++)
                    codop[i]='\0';
                for(i=0; i<40; i++)
                    operando[i]='\0';
            }
            bandComentario=0;
            bandOpe=0;
            bandcont=0;
            band=0;
            printf("\n\n");
        }
        if(bEnd == 0)
            printf("Error: No se encontro el END.");
    }
    else
        perror("");
    getch();
}
