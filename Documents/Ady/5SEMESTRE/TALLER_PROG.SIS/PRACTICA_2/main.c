#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct{
	char instruccion[6];
	char ope[3];
	char direccionamiento[8];
	char codMaq[5];
	char bytes_calculados;
	char bytes_por_calcular;
	char bytes_suma;
}TAB_OP;


int validaLongEtiqueta(char etiqueta[15])
{
	int band=0;
	int aux=0;

	aux=strlen(etiqueta);
    if(aux <= 8)
        band=1;
	return band;
}

int validaIniEtiqueta(char etiqueta[15])
{
	int band=0;

	if(((etiqueta[0] > 64) && (etiqueta[0] < 91)) || ((etiqueta[0] > 96) && (etiqueta[0] < 123)))
		band=1;
	return band;
}

int validaCarEtiqueta(char etiqueta[15])
{
	int band=0;
	int i=0;
	int contAux=1;
	int aux=0;

	aux=strlen(etiqueta);
	for(i=1; i<strlen(etiqueta); i++)
	{
		if(((etiqueta[i] > 64 && etiqueta[i] < 91) || ((etiqueta[i] > 96) && (etiqueta[i] < 123))) || (etiqueta[i] > 47 && etiqueta[i] < 58) || (etiqueta[i] == 95))
			contAux++;
	}
	if(aux == contAux)
		band=1;
	return band;
}

int validaLongCodop(char codop[10])
{
	int band=0;
    int aux=0;

    aux=strlen(codop);
    if(aux <= 5)
        band=1;
	return band;
}

int validaIniCodop(char codop[10])
{
    int band=0;

    if(((codop[0] > 64) && (codop[0] < 91)) || ((codop[0] > 96) && (codop[0] < 123)))
		band=1;
    return band;
}

int validaPuntoCodop(char codop[10])
{
    int band=0;
    int aux=0;
    int contPunto=0;
    int i;

	aux=strlen(codop);
    for(i=1; i<aux; i++)
    {
		if(codop[i] == '.')
			contPunto++;
	}
	if(contPunto <= 1)
		band=1;
	return band;
}
int validaCarCodop(char codop[10])
{
    int band=0;
    int contAux=1;
    int aux=0;
    int i;

	aux=strlen(codop);
    for(i=1; i<aux; i++)
	{
		if(((codop[i] > 64) && (codop[i] < 91)) || ((codop[i] > 96) && (codop[i] < 123)) || (codop[i] == 46))
			contAux++;
	}
	if(aux == contAux)
		band=1;
    return band;
}

int existeCodOp(FILE * fdTabOp,char codop[12])
{
    char instruccion[6];
	int i=0,j=0;
	int cont=0;
	int bandera=0;
	char cadena[50];
	int aux=0,aux1=0;

	for(i=0; i<50; i++)
		cadena[i]='\0';

    fseek(fdTabOp,0,0);
	while(fgets(cadena,50,fdTabOp))
	{
		for(i=0; i<6; i++)
			instruccion[i]='\0';
		cont=0;

		for(i=0; i<strlen(cadena); i++)
		{
			if((cadena[i] != '\t') && (cadena[i] != '\n'))
			{
				switch(cont)
				{
					case 0:
						instruccion[j]=cadena[i];
						j++;
					break;
				}
			}
			else
			{
				if(cadena[i] == '\t')
				{
					cont++;
					j=0;
				}
			}
		}

		aux=0;
		aux=strlen(instruccion);
		instruccion[aux+1]='\0';
		aux=strlen(codop);
		codop[aux+1]='\0';
		aux=0;
		aux=strcmp(instruccion,codop);
		if(aux == 0)
            bandera=1;
        if((strcmp(codop,"END") == 0) || (strcmp(codop,"EnD") == 0) || (strcmp(codop,"End") == 0) || (strcmp(codop,"end") == 0) || (strcmp(codop,"enD") == 0) || (strcmp(codop,"eND") == 0))
            bandera=1;
	}
	return bandera;
}

int validaCodigoOperacion(FILE * fdTabOp,char codop[12])
{
    TAB_OP TABOP;
	int i=0,j=0;
	int cont=0;
	int bandera=0;
	char cadena[50];
	char caracter;
	int aux=0,aux1=0;
	int bandEncabezado=0;

	for(i=0; i<50; i++)
		cadena[i]='\0';

    fseek(fdTabOp,0,0);
	while(fgets(cadena,50,fdTabOp))
	{
		for(i=0; i<6; i++)
			TABOP.instruccion[i]='\0';
		for(i=0; i<3; i++)
			TABOP.ope[i]='\0';
		for(i=0; i<8; i++)
			TABOP.direccionamiento[i]='\0';
		for(i=0; i<5; i++)
			TABOP.codMaq[i]='\0';
		TABOP.bytes_calculados=0;
		TABOP.bytes_por_calcular=0;
		TABOP.bytes_suma=0;
		caracter='\0';
		cont=0;

		for(i=0; i<strlen(cadena); i++)
		{
			caracter=cadena[i];
			if((caracter != '\t') && (caracter != '\n'))
			{
				switch(cont)
				{
					case 0:
						TABOP.instruccion[j]=caracter;
						j++;
					break;
					case 1:
						TABOP.ope[j]=caracter;
						j++;
					break;
					case 2:
						TABOP.direccionamiento[j]=caracter;
						j++;
					break;
					case 3:
						TABOP.codMaq[j]=caracter;
						j++;
					break;
					case 4:
						TABOP.bytes_calculados=caracter;
					break;
					case 5:
						TABOP.bytes_por_calcular=caracter;
						break;
					case 6:
						TABOP.bytes_suma=caracter;
					break;
				}
			}
			else
			{
				if(caracter == '\t')
				{
					cont++;
					j=0;
				}
			}
		}

		aux=0;
		aux=strlen(TABOP.instruccion);
		TABOP.instruccion[aux+1]='\0';
		aux=strlen(codop);
		codop[aux+1]='\0';
		aux=0;
		aux=strcmp(TABOP.instruccion,codop);
		if(aux == 0)
		{
		    if(bandEncabezado == 0)
            {
                printf("\n\n     MODO DE \t   CODIGO\t   BYTES\tBYTES POR\tSUMA TOTAL");
                printf("\nDIRECCIONAMIENTO   MAQUINA\tCALCULADOS\tCALCULAR\t DE BYTES");
                bandEncabezado=1;
            }
            printf("\n\t%s",TABOP.direccionamiento);
            printf("\t     %s",TABOP.codMaq);
            printf("\t\t    %c",TABOP.bytes_calculados);
            printf("\t\t   %c",TABOP.bytes_por_calcular);
            printf("\t\t    %c\n",TABOP.bytes_suma);

			aux1=strcmp(TABOP.ope,"SI");
			if(aux1 == 0)
				bandera=1;
			else
				bandera=0;
		}
	}
	return bandera;
}

int main()
{
    FILE *fd;
    FILE *fdTabOp;
    int i=0,j=0,k=0;
    int cont=1,contop=1,contEtiqueta=0,contCodop=0; //contadores
    int bEnd=0,band=0,bandComentario=0,bandOpe=0,bandcont=0; //banderas
    int bandOperando=0,bandAuxOperando=0,banderaAux=0;
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

    fd=fopen("P2ASM.txt","r");
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
                    printf("\nETIQUETA: %s",etiqueta);
                    if(validaLongEtiqueta(etiqueta) == 1)
						contEtiqueta++;
					else
						printf("\n\tError: La longitud maxima de una etiqueta es de 8 caracteres.");
					if(validaIniEtiqueta(etiqueta) == 1)
						contEtiqueta++;
					else
						printf("\n\tError: La etiqueta debe de iniciar con una letra.");
					if(validaCarEtiqueta(etiqueta) == 1)
						contEtiqueta++;
					else
						printf("\n\tError: Los caracteres validos de una etiqueta son letras, digitos(0...9) y el guion bajo.");
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
                    printf("\nCODOP: %s",codop);
                    if(validaLongCodop(codop) == 1)
                        contCodop++;
                    else
                        printf("\n\tError: La longitud maxima de un codigo de operacion es de 5 caracteres.");
                    if(validaIniCodop(codop) == 1)
						contCodop++;
                    else
						printf("\n\tError: El codigo de operacion debe de iniciar con una letra.");
                    if(validaPuntoCodop(codop) == 1)
						contCodop++;
					else
						printf("\n\tError: El codigo de operacion solo puede contener un punto.");
					if(validaCarCodop(codop) == 1)
						contCodop++;
					else
						printf("\n\tError: Los caracteres validos de un codigo de operacion son letras y un punto.");
					if(contCodop == 4)
					{
						fdTabOp=fopen("TABOP.txt","r");
						if(fdTabOp != NULL)
						{
							if(validaCodigoOperacion(fdTabOp,codop) == 1)
								bandOperando=1;
						}
					}
					if(contCodop == 4)
					{
						if((strcmp(codop,"END") == 0) || (strcmp(codop,"EnD") == 0) || (strcmp(codop,"End") == 0) || (strcmp(codop,"end") == 0) || (strcmp(codop,"enD") == 0) || (strcmp(codop,"eND") == 0))
							bEnd=1;
					}
				}
                else
                {
                    strcpy(codop,"NULL");
                    printf("\nCODOP: %s",codop);
                    printf("\n\tError: Siempre debe de existir un codigo de operacion.");
                }
                if(existeCodOp(fdTabOp,codop) == 0)
                {
                    banderaAux=1;
                    printf("\n\tError: El codigo de operacion no fue encontrado.");
                }
                if(operando[0] != '\0')
                {
                	bandAuxOperando=1;
                    for(k=0; k<strlen(operando); k++)
                    {
                        if(operando[k] == '\n')
                            operando[k]='\0';
                    }
                    printf("\nOPERANDO: %s\n",operando);
                }
                else
                {
                	bandAuxOperando=0;
                    strcpy(operando,"NULL");
                    printf("\nOPERANDO: %s\n",operando);
                }
                if((bandOperando == 0) && (bandAuxOperando == 1))
                {
                	if((bEnd == 0) && (banderaAux == 0))
						printf("\n\tError: El CODOP no debe de tener operando");
                }
				if((bandOperando == 1) && (bandAuxOperando == 0))
				{
					if((bEnd == 0) && (banderaAux == 0))
						printf("\n\tError: El CODOP debe de tener operando");
				}
                j=0;
                cont=1;
                contop=1;
                contEtiqueta=0;
                contCodop=0;
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
            bandOperando=0;
            bandAuxOperando=0;
            banderaAux=0;
        }
        if(bEnd == 0)
            printf("Error: No se encontro el END.");
    }
    else
        perror("");
    getch();
}

