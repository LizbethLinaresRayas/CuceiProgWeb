#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

typedef struct{
	char instruccion[6];
	char ope[3];
	char direccionamiento[8];
	char codMaq[5];
	char bytes_calculados;
	char bytes_por_calcular;
	char bytes_suma;
}TAB_OP;

typedef struct{
	int INH;
	char sumaBytesINH;
	int IMM;
	char bytesCalcular;
	char sumaBytesIMM;
	int DIR;
	char sumaBytesDIR;
	int EXT;
	char sumaBytesEXT;
	int REL;
	char sumaBytesREL;
	int IDX;
	char sumaBytesIDX;
	int IDX1;
	char sumaBytesIDX1;
	int IDX2;
	char sumaBytesIDX2;
	int _IDX2;
	char sumaBytes_IDX2;
	int DIDX;
	char sumaBytesDIDX;
}MOD_DIRECCIONAMIENTO;


typedef struct{
	int INH;
	char codmaqINH[5];
	int IMM;
	char bytesCalcularIMM;
	char codmaqIMM[5];
	int DIR;
	char codmaqDIR[6];
	int EXT;
	char codmaqEXT[6];
	int REL;
	char codmaqREL[6];
	int IDX;
	char codmaqIDX[6];
	int IDX1;
	char codmaqIDX1[6];
	int IDX2;
	char codmaqIDX2[6];
	int DIDX;
	int _IDX2;
	char codmaq_IDX2[8];
	char codmaqDIDX[6];
	int bandera;
}COD_MAQ;

typedef struct
{
    int DIR_INIC;
    int Valor;
    int bandera;
    char CONTLOC[5];
    char DIR_EQU[5];
}ARCH_AUX;

typedef struct
{
    char xb[3];
}ValXB;

ARCH_AUX archAux;
int ORG=0;

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
	int aux=0;

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
			aux1=strcmp(TABOP.ope,"SI");
			if(aux1 == 0)
				bandera=1;
			else
				bandera=0;
		}
	}
	return bandera;
}

int hexadecimal(char cadena[6])
{
    int cont=0;
    int aux=0;
    int i;
    int bandera=0,band=0;

    aux=strlen(cadena);
    if(aux > 1)
    {
        for(i=0; i<aux; i++)
        {
            if(cadena[0] == '$')
                band=1;
            if(band == 1)
            {
                if(((cadena[i] >= 65) && (cadena[i] <= 70)) || ((cadena[i] >= 48) && (cadena[i] <= 57)))
                    cont++;
            }
        }
        if(aux == (cont+1))
            bandera=1;
    }
    else
        bandera=2;
    return bandera;
}

int decimal(char cadena[6])
{
    int cont=0;
    int aux=0;
    int i;
    int bandera=0;

    aux=strlen(cadena);
    for(i=0; i<aux; i++)
    {
        if((cadena[i] >= 48) && (cadena[i] <= 57))
            cont++;
    }
    if(aux == cont)
        bandera=1;
    return bandera;
}

int octal(char cadena[6])
{
    int cont=0;
    int aux=0;
    int i;
    int bandera=0,band=0;

    aux=strlen(cadena);
    if(aux > 1)
    {
        for(i=0; i<aux; i++)
        {
            if(cadena[0] == '@')
                band=1;
            if(band == 1)
            {
                if((cadena[i] >= 48) && (cadena[i] <= 55))
                    cont++;
            }
        }
        if(aux == (cont+1))
            bandera=1;
    }
    else
        bandera=2;
    return bandera;
}

int binario(char cadena[6])
{
    int cont=0;
    int aux=0;
    int i;
    int bandera=0,band=0;

    aux=strlen(cadena);
    if(aux > 1)
    {
        for(i=0; i<aux; i++)
        {
            if(cadena[0] == '%')
                band=1;
            if(band == 1)
            {
                if((cadena[i] == 48) || (cadena[i] == 49))
                    cont++;
            }
        }
        if(aux == (cont+1))
            bandera=1;
    }
    else
        bandera=2;
    return bandera;
}

int convierteOctalDecimal(char cadena[6])
{
    int numero=0;
    int i=0;
    int longitud=0;
    int aux=0;
    int aux1=0;
    int j=0;
    int numero_total=0;
    char caracter;

    longitud=strlen(cadena);
    j=longitud-1;
    for(i=0; i<longitud; i++)
    {
        caracter=cadena[i];
        switch(caracter)
        {
            case '0':
                numero=0;
            break;
            case '1':
                numero=1;
            break;
            case '2':
                numero=2;
            break;
            case '3':
                numero=3;
            break;
            case '4':
                numero=4;
            break;
            case '5':
                numero=5;
            break;
            case '6':
                numero=6;
            break;
            case '7':
                numero=7;
            break;
        }

        aux=pow(8,j);
        aux1=aux * numero;
        numero_total+=aux1;
        j--;
    }

    return numero_total;
}

int convierteHexadecimalDecimal(char cadena[6])
{
    int numero=0;
    int i=0;
    int longitud=0;
    int aux=0;
    int aux1=0;
    int j=0;
    int numero_total=0;
    char caracter;

    longitud=strlen(cadena);
    j=longitud-1;
    for(i=0; i<longitud; i++)
    {
        caracter=cadena[i];
        if(caracter != '$')
        {
            switch(caracter)
            {
                case '0':
                    numero=0;
                break;
                case '1':
                    numero=1;
                break;
                case '2':
                    numero=2;
                break;
                case '3':
                    numero=3;
                break;
                case '4':
                    numero=4;
                break;
                case '5':
                    numero=5;
                break;
                case '6':
                    numero=6;
                break;
                case '7':
                    numero=7;
                break;
                case '8':
                    numero=8;
                break;
                case '9':
                    numero=9;
                break;
                case 'A':
                    numero=10;
                break;
                case 'B':
                    numero=11;
                break;
                case 'C':
                    numero=12;
                break;
                case 'D':
                    numero=13;
                break;
                case 'E':
                    numero=14;
                break;
                case 'F':
                    numero=15;
                break;
            }

            aux=pow(16,j-1);
            aux1=aux * numero;
            numero_total+=aux1;
            j--;
        }
    }

    return numero_total;
}

int convierteBinarioDecimal(char cadena[6])
{
    int numero=0;
    int i=0;
    int longitud=0;
    int aux=0;
    int aux1=0;
    int j=0;
    int numero_total=0;
    char caracter;

    longitud=strlen(cadena);
    j=longitud-1;
    for(i=0; i<longitud; i++)
    {
        caracter=cadena[i];
        switch(caracter)
        {
            case '0':
                numero=0;
            break;
            case '1':
                numero=1;
            break;
        }

        aux=pow(2,j);
        aux1=aux * numero;
        numero_total+=aux1;
        j--;
    }
    return numero_total;
}

int validaModoInmediato(char operando[10],int banderaAux)
{
    char cadena[10];
    int i=0;
    int j=0;
    int aux=0;
    int bandera=0;
    int band=0;
    int b=0;
    int valoperando=0;
    int bandSigno=0;

    for(i=0; i<10;i++)
        cadena[i]='\0';

    aux=strlen(operando);
    if(operando[1] == '-')
        bandSigno=1;
    for(i=0; i < aux; i++)
    {
        if(operando[i] == '#')
            band=1;
        if((band == 1) && (operando[i] != '#') && (operando[i] != '\t') && (operando[i] != '-'))
        {
            cadena[j]=operando[i];
            j++;
        }
    }

    if(cadena[0] == '$')
    {
        bandera=hexadecimal(cadena);
        if(bandera == 1)
        {
            valoperando=convierteHexadecimalDecimal(cadena);
            if(banderaAux == 1)
            {
                if(bandSigno == 1)
                    valoperando*=-1;
                if((valoperando >= 0) && (valoperando <= 255))
                    b=1;
                else
                    printf("\n\tError: El valor del operando esta fuera del Rango: 0 a 255");
            }
            if(banderaAux == 2)
            {
                if((valoperando >= 0) && (valoperando <= 65535))
                    b=2;
                else
                    printf("\n\tError: El valor del operando esta fuera del Rango: 0 a 65535");
            }
        }
        else
        {
            if(bandera == 2)
                printf("\n\tError: El Signo $ debe Estar Acompanado de un Numero.");
            else
                printf("\n\tError: Base Numerica Hexadecimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F");
        }
    }
    else
    {
        if(cadena[0] == '@')
        {
            bandera=octal(cadena);
            if(bandera == 1)
            {
                valoperando=convierteOctalDecimal(cadena);
                if(banderaAux == 1)
                {
                    if(bandSigno == 1)
                        valoperando*=-1;
                    if((valoperando >= 0) && (valoperando <= 255))
                        b=1;
                    else
                        printf("\n\tError: El valor del operando esta fuera del Rango: 0 a 255");
                }
                if(banderaAux == 2)
                {
                    if((valoperando >= 0) && (valoperando <= 65535))
                        b=2;
                    else
                        printf("\n\tError: El valor del operando esta fuera del Rango: 0 a 65535");
                }
            }
            else
            {
                if(bandera == 2)
                    printf("\n\tError: El Signo @ debe Estar Acompanado de un Numero.");
                else
                    printf("\n\tError: Base Numerica Octal Invalida,Caracteres validos 0,1,2,3,4,5,6,7");
            }
        }
        else
        {
            if(cadena[0] == '%')
            {
                bandera=binario(cadena);
                if(bandera == 1)
                {
                    valoperando=convierteBinarioDecimal(cadena);
                    if(banderaAux == 1)
                    {
                        if(bandSigno == 1)
                            valoperando*=-1;
                        if((valoperando >= 0) && (valoperando <= 255))
                            b=1;
                        else
                            printf("\n\tError: El valor del operando esta fuera del Rango: 0 a 255");
                    }
                    if(banderaAux == 2)
                    {
                        if((valoperando >= 0) && (valoperando <= 65535))
                            b=2;
                        else
                            printf("\n\tError: El valor del operando esta fuera del Rango: 0 a 65535");
                    }
                }
                else
                {
                    if(bandera == 2)
                        printf("\n\tError: El Signo de Porciento debe estar Acompanado de un Numero.");
                    else
                        printf("\n\tError: Base Numerica Binaria Invalida,Caracteres validos 0,1");
                }
            }
            else
            {
                if((cadena[0] >= 48) && (cadena[0] <= 57))
                    bandera=decimal(cadena);
                if(bandera == 1)
                {
                    valoperando=atoi(cadena);
                    if(bandSigno == 1)
                        valoperando*=-1;
                    if(banderaAux == 1)
                    {
                        if((valoperando >= 0) && (valoperando <= 255))
                            b=1;
                        else
                            printf("\n\tError: El valor del operando esta fuera del Rango: 0 a 255");
                    }
                    if(banderaAux == 2)
                    {
                        if((valoperando >= 0) && (valoperando <= 65535))
                            b=2;
                        else
                            printf("\n\tError: El valor del operando esta fuera del Rango: 0 a 65535");
                    }
                }
                else
                    printf("\n\tError: Base Numerica Decimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9");
            }
        }
    }
    return b;
}

int validaModoDirectoExtendido(char cadena[6],int bandDirecto,int bandExtendido)
{
    int bandera=0;
    int b=0;
    int valoperando;
    int bandSigno=0;
    int i=0;
    int k=0;
    int contEtiqueta=0;
    int bandEtiqueta=0;

    for(i=0; i<2; i++)
    {
        if(cadena[i] == '-')
            bandSigno=1;
    }
    if(cadena[0] == '$')
    {
        bandera=hexadecimal(cadena);
        if(bandera == 1)
        {
            valoperando=convierteHexadecimalDecimal(cadena);
            if(bandDirecto == 1)
            {
                if(bandSigno == 1)
                    valoperando*=-1;
                if((valoperando >= 0) && (valoperando <= 255))
                    b=1;
            }
            if((bandExtendido == 1) && (b != 1))
            {
                if(bandSigno == 1)
                    valoperando*=-1;
                if((valoperando >= 256) && (valoperando <= 65535))
                    b=2;
                else
                    printf("\n\tError: El valor del operando esta fuera del Rango: 256 a 65535");
            }
            if((b != 1) && (b != 2))
                printf("\n\tError: El valor del operando esta fuera del Rango: 0 a 255");
        }
        else
        {
            if(bandera == 2)
                printf("\n\tError: El Signo $ debe Estar Acompanado de un Numero.");
            else
                printf("\n\tError: Base Numerica Hexadecimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F");
        }
    }
    else
    {

        if(cadena[0] == '@')
        {
            bandera=octal(cadena);
            if(bandera == 1)
            {
                valoperando=convierteOctalDecimal(cadena);
                if(bandDirecto == 1)
                {
                    if(bandSigno == 1)
                        valoperando*=-1;
                    if((valoperando >= 0) && (valoperando <= 255))
                        b=1;
                }
                if((bandExtendido == 1) && (b != 1))
                {
                    if(bandSigno == 1)
                        valoperando*=-1;
                    if((valoperando >= 256) && (valoperando <= 65535))
                        b=2;
                    else
                        printf("\n\tError: El valor del operando esta fuera del Rango: 256 a 65535");
                }
                if((b != 1) && (b != 2))
                    printf("\n\tError: El valor del operando esta fuera del Rango: 0 a 255");
            }
            else
            {
                if(bandera == 2)
                    printf("\n\tError: El Signo @ debe Estar Acompanado de un Numero.");
                else
                    printf("\n\tError: Base Numerica Octal Invalida,Caracteres validos 0,1,2,3,4,5,6,7");
            }
        }
        else
        {
            if(cadena[0] == '%')
            {
                bandera=binario(cadena);
                if(bandera == 1)
                {
                    valoperando=convierteBinarioDecimal(cadena);
                    if(bandDirecto == 1)
                    {
                        if(bandSigno == 1)
                            valoperando*=-1;
                        if((valoperando >= 0) && (valoperando <= 255))
                            b=1;
                    }
                    if((bandExtendido == 1) && (b != 1))
                    {
                        if(bandSigno == 1)
                            valoperando*=-1;
                        if((valoperando >= 256) && (valoperando <= 65535))
                            b=2;
                        else
                            printf("\n\tError: El valor del operando esta fuera del Rango: 256 a 65535");
                    }
                    if((b != 1) && (b != 2))
                        printf("\n\tError: El valor del operando esta fuera del Rango: 0 a 255.");
                }
                else
                {
                    if(bandera == 2)
                        printf("\n\tError: El Signo de Porciento debe estar Acompanado de un Numero.");
                    else
                        printf("\n\tError: Base Numerica Binaria Invalida,Caracteres validos 0,1.");
                }
            }
            else
            {
                if((cadena[0] >= 48) && (cadena[0] <= 57))
                    bandera=decimal(cadena);
                if(bandera == 1)
                {
                    valoperando=atoi(cadena);
                    if(bandDirecto == 1)
                    {
                        if(bandSigno == 1)
                            valoperando*=-1;
                        if((valoperando >= 0) && (valoperando <= 255))
                            b=1;
                    }
                    if((bandExtendido == 1) && (b != 1))
                    {
                        if(bandSigno == 1)
                            valoperando*=-1;
                        if((valoperando >= 256) && (valoperando <= 65535))
                            b=2;
                        else
                            printf("\n\tError: El valor del operando esta fuera del Rango: 256 a 65535.");
                    }
                    if((b != 1) && (b != 2))
                        printf("\n\tError: El valor del operando esta fuera del Rango: 0 a 255.");
                }
                else
                {
                    if((cadena[0] >= 65) || (cadena[0] >= 97))
                    {
                        for(k=0; k<strlen(cadena); k++)
                        {
                            if((cadena[k] == '\n') || (cadena[k] == '\t'))
                                cadena[k]='\0';
                        }
                        if(validaLongEtiqueta(cadena) == 1)
                            contEtiqueta++;
                        else
                            printf("\n\tError: La longitud maxima de una etiqueta es de 8 caracteres.");
                        if(validaIniEtiqueta(cadena) == 1)
                            contEtiqueta++;
                        else
                            printf("\n\tError: La etiqueta debe de iniciar con una letra.");
                        if(validaCarEtiqueta(cadena) == 1)
                            contEtiqueta++;
                        else
                            printf("\n\tError: Los caracteres validos de una etiqueta son letras, digitos(0...9) y el guion bajo.");
                        bandEtiqueta=1;
                    }
                    if(contEtiqueta == 3)
                        b=2;
                    else
                    {
                        if(bandEtiqueta == 0)
                            printf("\n\tError: Base Numerica Decimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9.");
                    }
                }

            }
        }
    }
    return b;
}

int validaModoIDX(char cadena[6],int bandIDX,int bandIDX1,int bandIDX2)
{
    int i=0;
    int j=0;
    int k=0;
    char cad_numero[6];
    char registro[4];
    char cadenaregistro[4];
    char preregistro;
    char cadAux[6];
    int bandComa=0;
    int bandNumero=0;
    int band_signo=0;
    int bandCadNum=0;
    int bandRegistro=0;
    int bandera=0;
    int numeroAux;
    int bandInd5=0;
    int bandAcumulador=0;
    int bandpreRegistro=0;
    int bandprepos=0;
    int bandPreDec=0;
    int bandPostDec=0;
    int bandPreInc=0;
    int bandPostInc=0;
    int AcumError=0;
    int bandAuxIDX1=0;
    int bandAuxIDX2=0;
    int bandSigno=0;
    int contprepost=0;
    int bandErrorBase=0;

    for(i=0; i<6; i++)
        cad_numero[i]='\0';
    for(i=0; i<4; i++)
        registro[i]='\0';
    for(i=0; i<4; i++)
        cadenaregistro[i]='\0';
    for(i=0; i<6; i++)
        cadAux[i]='\0';

    if(((cadena[0] == 65) || (cadena[0] == 97)) || ((cadena[0] == 66) || (cadena[0] == 98)) || ((cadena[0] == 68) || (cadena[0] == 100)))
        bandAcumulador=1;

    if(cadena[0] == '-')
        bandSigno=1;
    if(bandSigno == 1)
    {
        for(i=0; i<strlen(cadena); i++)
        {
            if((cadena[i] == '+') || (cadena[i] == '-'))
                contprepost++;
        }
        if(contprepost == 2)
            bandprepos=1;
    }
    else
    {
        for(i=0; i<strlen(cadena); i++)
        {
            if((cadena[i] == '+') || (cadena[i] == '-'))
                bandprepos=1;
        }
    }

    if((bandAcumulador == 0) && (bandprepos == 0))
    {
        for(i=0; i<strlen(cadena); i++)
        {
            if(cadena[i] == ',')
            {
                bandComa=1;
            }
            if(bandComa == 0)
            {
                cad_numero[j]=cadena[i];
                j++;
            }
            else
            {
                if(cadena[i] != ',')
                {
                    registro[k]=cadena[i];
                    k++;
                }
            }
        }
        j=0;
        for(i=0; i<strlen(cad_numero); i++)
        {
            if(cad_numero[i] == '-')
                band_signo=1;
            else
            {
                cadAux[j]=cad_numero[i];
                j++;
            }
        }
        if((cadAux[0] != '%') && (cadAux[0] != '$') && (cadAux[0] != '@'))
        {
            bandCadNum=decimal(cadAux);
            if((bandCadNum == 1) && (band_signo == 0))
                numeroAux=atoi(cadena);
            else
            {
                if((bandCadNum == 1) && (band_signo == 1))
                {
                    numeroAux=atoi(cadena);
                }
            }
            if(bandCadNum == 0)
                printf("\n\tError: Base Numerica Decimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9");
        }
        else
        {
            bandErrorBase=1;
            printf("\n\tError: Este Operando solo Permite Base Decimal");
        }
        if((bandIDX == 1) && (bandErrorBase == 0))
        {
           if((numeroAux >= -16) && (numeroAux <= 15))
            bandNumero=1;
            else
                AcumError=1;
            registro[strlen(registro)]='\0';
            if(((strcmp(registro,"X")) == 0) || ((strcmp(registro,"x")) == 0))
                bandRegistro=1;
            else
            {
                if(((strcmp(registro,"Y")) == 0) || ((strcmp(registro,"y")) == 0))
                    bandRegistro=1;
                else
                {
                    if(((strcmp(registro,"SP")) == 0) || ((strcmp(registro,"Sp")) == 0) || ((strcmp(registro,"sP")) == 0) || ((strcmp(registro,"sp")) == 0))
                        bandRegistro=1;
                    else
                    {
                        if(((strcmp(registro,"PC")) == 0) || ((strcmp(registro,"Pc")) == 0) || ((strcmp(registro,"pC")) == 0) || ((strcmp(registro,"pc")) == 0))
                            bandRegistro=1;
                        else
                        {
                            if(registro[0] == '\0')
                                AcumError=6;
                            else
                                AcumError=2;
                        }
                    }
                }
            }
        }
        if((bandNumero == 1) && (bandRegistro == 1))
        {
            bandera=1;
            bandInd5=1;
        }
        else
        {
            bandNumero=0;
            bandRegistro=0;
            if((bandIDX1 == 1) && (bandInd5 == 0) && (bandErrorBase == 0))
            {
                if(((numeroAux >= -256) && (numeroAux <= -17)) || ((numeroAux >= 16) && (numeroAux <= 255)))
                    bandNumero=1;
                else
                    AcumError=3;
                registro[strlen(registro)]='\0';
                if(((strcmp(registro,"X")) == 0) || ((strcmp(registro,"x")) == 0))
                bandRegistro=1;
            else
            {
                if(((strcmp(registro,"Y")) == 0) || ((strcmp(registro,"y")) == 0))
                    bandRegistro=1;
                else
                {
                    if(((strcmp(registro,"SP")) == 0) || ((strcmp(registro,"Sp")) == 0) || ((strcmp(registro,"sP")) == 0) || ((strcmp(registro,"sp")) == 0))
                        bandRegistro=1;
                    else
                    {
                        if(((strcmp(registro,"PC")) == 0) || ((strcmp(registro,"Pc")) == 0) || ((strcmp(registro,"pC")) == 0) || ((strcmp(registro,"pc")) == 0))
                                bandRegistro=1;
                            else
                            {
                                if(registro[0] == '\0')
                                    AcumError=7;
                                else
                                    AcumError=4;
                            }
                        }
                    }
                }
            }
            if((bandNumero == 1) && (bandRegistro == 1))
            {
                bandera=4;
                bandAuxIDX1=1;
            }
            else
            {
                bandNumero=0;
                bandRegistro=0;
                if((bandIDX2 == 1) && (bandInd5 == 0) && (bandAuxIDX1 == 0) && (bandErrorBase == 0))
                {
                    if((numeroAux >= 256) && (numeroAux <= 65535))
                        bandNumero=1;
                    else
                        printf("\n\tError: El valor del operando esta fuera del Rango: 256 a 65535");
                    registro[strlen(registro)]='\0';
                    if(((strcmp(registro,"X")) == 0) || ((strcmp(registro,"x")) == 0))
                        bandRegistro=1;
                    else
                    {
                        if(((strcmp(registro,"Y")) == 0) || ((strcmp(registro,"y")) == 0))
                            bandRegistro=1;
                        else
                        {
                            if(((strcmp(registro,"SP")) == 0) || ((strcmp(registro,"Sp")) == 0) || ((strcmp(registro,"sP")) == 0) || ((strcmp(registro,"sp")) == 0))
                                bandRegistro=1;
                            else
                            {
                                if(((strcmp(registro,"PC")) == 0) || ((strcmp(registro,"Pc")) == 0) || ((strcmp(registro,"pC")) == 0) || ((strcmp(registro,"pc")) == 0))
                                    bandRegistro=1;
                                else
                                {
                                    if(registro[0] == '\0')
                                        printf("\n\tError: Debe Existir Un Registro.");
                                    else
                                        printf("\n\tError: Los Registros Validos son X,Y,SP,PC");
                                }
                            }
                        }
                    }
                }
                if((bandNumero == 1) && (bandRegistro == 1))
                {
                    bandera=5;
                    bandAuxIDX2=1;
                }
                else
                {
                    if((bandNumero == 1) && (bandRegistro == 1))
                    {
                        bandera=4;
                        bandAuxIDX1=1;
                    }
                    else
                    {
                        if((bandAuxIDX1 == 0) && (bandAuxIDX2 == 0))
                        {
                            if(AcumError == 1)
                                printf("\n\tError: El valor del operando esta fuera del Rango: -16 a 15");
                            else
                            {
                                if(AcumError == 2)
                                    printf("\n\tError: Los Registros Validos son X,Y,SP,PC");
                                else
                                {
                                    if(AcumError == 6)
                                        printf("\n\tError: Debe Existir Un Registro.");
                                }
                            }
                        }
                        else
                        {
                            if(bandAuxIDX2 == 0)
                            {
                                if(AcumError == 3)
                                    printf("\n\tError: El valor del operando esta fuera del Rango: -256 a -17 y 16 a 255");
                                else
                                {
                                    if(AcumError == 4)
                                        printf("\n\tError: Los Registros Validos son X,Y,SP,PC");
                                    else
                                    {
                                        if(AcumError == 8)
                                            printf("\n\tError: Debe Existir Un Registro.");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        if((bandprepos == 1) && (bandInd5 == 0) && (bandAuxIDX1 == 0) && (bandErrorBase == 0))
        {
            for(i=0; i<strlen(cadena); i++)
            {
                if(cadena[i] == ',')
                {
                    bandComa=1;
                }
                if(bandComa == 0)
                {
                    cad_numero[j]=cadena[i];
                    j++;
                }
                else
                {
                    if(cadena[i] != ',')
                    {
                        cadenaregistro[k]=cadena[i];
                        k++;
                    }
                }
            }
            bandCadNum=decimal(cad_numero);
            if(bandCadNum == 1)
                numeroAux=atoi(cad_numero);
            if((numeroAux >= 1) && (numeroAux <= 8))
                bandNumero=1;
            cadenaregistro[strlen(cadenaregistro)]='\0';
            j=0;
            for(i=0; i<strlen(cadenaregistro); i++)
            {
                if(cadenaregistro[0] == '-')
                    bandPreDec=1;
                else
                {
                    if(cadenaregistro[0] == '+')
                        bandPreInc=1;
                }
                if((cadenaregistro[i] != '+') && (cadenaregistro[i] != '-'))
                {
                    registro[j]=cadenaregistro[i];
                    j++;
                }
                else
                {
                    if(i != 0)
                    {
                        if(cadenaregistro[i] == '+')
                            bandPostInc=1;
                        else
                        {
                            if(cadenaregistro[i] == '-')
                                bandPostDec=1;
                        }
                    }
                }
            }
            if(registro[0] == '\0')
                printf("\n\tError: El Pre/Post Incremento/Decremento debe ser Acompañado por un Registro");
            else
            {
                registro[strlen(registro)]='\0';
                if(((strcmp(registro,"X")) == 0) || ((strcmp(registro,"x")) == 0))
                    bandRegistro=1;
                else
                {
                    if(((strcmp(registro,"Y")) == 0) || ((strcmp(registro,"y")) == 0))
                        bandRegistro=1;
                    else
                    {
                        if(((strcmp(registro,"SP")) == 0) || ((strcmp(registro,"Sp")) == 0) || ((strcmp(registro,"sP")) == 0))
                            bandRegistro=1;
                        else
                        {
                            if(registro[0] == '\0')
                                printf("\n\tError: Debe Existir Un Registro.");
                            else
                                printf("\n\tError: Los Registros Validos son X,Y,SP");
                        }
                    }
                }
            }
            if((bandNumero == 1) && (bandRegistro == 1))
            {
                bandera=2;
                bandprepos=1;
            }
            else
            {
                if(bandNumero == 0)
                    printf("\n\tError: El valor del operando esta fuera del Rango: 1 a 8");
            }
        }
        else
        {
            if((bandAcumulador == 1) && (bandprepos == 0))
            {
                preregistro=cadena[0];
                if(cadena[1] == ',')
                    bandComa=1;
                j=0;
                for(i=2; i<4; i++)
                {
                    registro[j]=cadena[i];
                    j++;
                }
                if((preregistro == 'A') || (preregistro == 'a'))
                    bandpreRegistro=1;
                else
                {
                    if((preregistro == 'B') || (preregistro == 'b'))
                        bandpreRegistro=1;
                    else
                    {
                        if((preregistro == 'D') || (preregistro == 'd'))
                            bandpreRegistro=1;
                        else
                        {
                            if(preregistro == '\0')
                                printf("\n\tError: Debe Existir un Registro al Inicio.");
                            else
                                printf("\n\tError: Los Primeros Registros Validos son A,B,D");
                        }
                    }
                }
                registro[strlen(registro)]='\0';
                if(((strcmp(registro,"X")) == 0) || ((strcmp(registro,"x")) == 0))
                        bandRegistro=1;
                else
                {
                    if(((strcmp(registro,"Y")) == 0) || ((strcmp(registro,"y")) == 0))
                        bandRegistro=1;
                    else
                    {
                        if(((strcmp(registro,"SP")) == 0) || ((strcmp(registro,"Sp")) == 0) || ((strcmp(registro,"sP")) == 0) || ((strcmp(registro,"sp")) == 0))
                            bandRegistro=1;
                        else
                        {
                            if(((strcmp(registro,"PC")) == 0) || ((strcmp(registro,"Pc")) == 0) || ((strcmp(registro,"pC")) == 0) || ((strcmp(registro,"pc")) == 0))
                                bandRegistro=1;
                            else
                            {
                                if(registro[0] == '\0')
                                    printf("\n\tError: Debe Existir un Registro.");
                                else
                                    printf("\n\tError: Los Registros Validos son X,Y,SP,PC");
                            }
                        }
                    }
                }
                if((bandpreRegistro == 1) && (bandRegistro == 1))
                {
                    bandera=3;
                    bandAcumulador=1;
                }
            }
        }
    }

    return bandera;
}

int validaModoIndizadoIndirecto16(char cadena[6])
{
    int i=0;
    int j=0;
    int k=0;
    char cad_numero[6];
    char registro[4];
    char cadAux[6];
    int bandComa=0;
    int bandNumero=0;
    int bandCadNum=0;
    int bandRegistro=0;
    int bandera=0;
    int numeroAux;

    for(i=0; i<6; i++)
        cad_numero[i]='\0';
    for(i=0; i<4; i++)
        registro[i]='\0';
    for(i=0; i<6; i++)
        cadAux[i]='\0';

    for(i=0; i<strlen(cadena); i++)
    {
        if(cadena[i] == ',')
        {
            bandComa=1;
        }
        if((bandComa == 0) && (cadena[i] != '[') && (cadena[i] != ']'))
        {
            cad_numero[j]=cadena[i];
            j++;
        }
        else
        {
            if((cadena[i] != ',') && (cadena[i] != '[') && (cadena[i] != ']'))
            {
                registro[k]=cadena[i];
                k++;
            }
        }
    }
    bandCadNum=decimal(cad_numero);
    if(bandCadNum == 1)
        numeroAux=atoi(cad_numero);
    if((numeroAux >= 0) && (numeroAux <= 65535))
        bandNumero=1;
    else
        printf("\n\tError: El valor del operando esta fuera del Rango: 0 a 65535");

    registro[strlen(registro)]='\0';
    if(((strcmp(registro,"X")) == 0) || ((strcmp(registro,"x")) == 0))
        bandRegistro=1;
    else
    {
        if(((strcmp(registro,"Y")) == 0) || ((strcmp(registro,"y")) == 0))
            bandRegistro=1;
        else
        {
            if(((strcmp(registro,"SP")) == 0) || ((strcmp(registro,"Sp")) == 0) || ((strcmp(registro,"sP")) == 0) || ((strcmp(registro,"sp")) == 0))
                bandRegistro=1;
            else
            {
                if(((strcmp(registro,"PC")) == 0) || ((strcmp(registro,"Pc")) == 0) || ((strcmp(registro,"pC")) == 0) || ((strcmp(registro,"pc")) == 0))
                    bandRegistro=1;
                else
                {
                    if(registro[0] == '\0')
                        printf("\n\tError: Debe Existir un Registro.");
                    else
                        printf("\n\tError: Los Registros Validos son X,Y,SP,PC");
                }
            }
        }
    }
    if((bandNumero == 1) && (bandRegistro == 1))
        bandera=1;
    return bandera;
}

int validaModoAcumuladorIndirecto(char cadena[6])
{
    int i=0;
    int j=0;
    int k=0;
    char reg1[4];
    char registro[4];
    char cadAux[4];
    int bandComa=0;
    int bandreg1=0;
    int bandRegistro=0;
    int bandera=0;

    for(i=0; i<4; i++)
        reg1[i]='\0';
    for(i=0; i<4; i++)
        registro[i]='\0';
    for(i=0; i<4; i++)
        cadAux[i]='\0';

    for(i=0; i<strlen(cadena); i++)
    {
        if(cadena[i] == ',')
        {
            bandComa=1;
        }
        if((bandComa == 0) && (cadena[i] != '[') && (cadena[i] != ']'))
        {
            reg1[j]=cadena[i];
            j++;
        }
        else
        {
            if((cadena[i] != ',') && (cadena[i] != '[') && (cadena[i] != ']'))
            {
                registro[k]=cadena[i];
                k++;
            }
        }
    }
    reg1[strlen(reg1)]='\0';
    if(((strcmp(reg1,"D")) == 0) || ((strcmp(reg1,"d")) == 0))
        bandreg1=1;
    else
    {
        if(reg1[0] == '\0')
            printf("\n\tError: Debe Existir un Registro D al Inicio.");
        else
            printf("\n\tError: Unico Registro Valido: D");
    }
    registro[strlen(registro)]='\0';
    if(((strcmp(registro,"X")) == 0) || ((strcmp(registro,"x")) == 0))
        bandRegistro=1;
    else
    {
        if(((strcmp(registro,"Y")) == 0) || ((strcmp(registro,"y")) == 0))
            bandRegistro=1;
        else
        {
            if(((strcmp(registro,"SP")) == 0) || ((strcmp(registro,"Sp")) == 0) || ((strcmp(registro,"sP")) == 0) || ((strcmp(registro,"sp")) == 0))
                bandRegistro=1;
            else
            {
                if(((strcmp(registro,"PC")) == 0) || ((strcmp(registro,"Pc")) == 0) || ((strcmp(registro,"pC")) == 0) || ((strcmp(registro,"pc")) == 0))
                    bandRegistro=1;
                else
                {
                    if(registro[0] == '\0')
                        printf("\n\tError: Debe Existir un Registro.");
                    else
                        printf("\n\tError: Los Registros Validos son X,Y,SP,PC");
                }
            }

        }
    }
    if((bandreg1 == 1) && (bandRegistro == 1))
        bandera=1;
    return bandera;
}

int Recupera(FILE * fdTabOp,char codop[12],char operando[10],char etiqueta[10],int bandTemporal,FILE * fdTemp,int bandTabsim,FILE * fdTabsim)
{
    TAB_OP TABOP;
    MOD_DIRECCIONAMIENTO MODODIRECCIONAMIENTO;
	int i=0;
	int j=0;
	int k=0;
	int n=0;
	int cont=0;
	int aux=0;
	int byte=0;
	int banderaAux=0;
	int longOperando=0;
	int bandModoDirExt=0;
	int bandModoInh=0;
	int bandModoDir=0;
	int bandModoExt=0;
	int bandModoImm=0;
	int bandAuxModoDir=0;
	int bandAuxModoExt=0;
	int bandAuxModoIDX=0;
	int bandAuxModoIDX5=0;
	int bandAuxModoIDXPre=0;
	int bandAuxModoIDXAcum=0;
	int bandAuxModoIDX1=0;
	int bandAuxModoIDX2=0;
	int bandIDX=0;
	int bandIDX1=0;
	int bandIDX2=0;
	int band_IDX2=0;
	int bandDIDX=0;
	int bandAuxInd=0;
	int bandAuxAcumInd=0;
	int bandAuxRel=0;
	int contEtiqueta=0;
	int bandRelativo=0;
	int bandRelativo8=0;
	int bandRelativo16=0;
	int contAuxInd=0;
	int bandErrorLong=0;
	int bandErrorLong1=0;
	int bandImm=0;
	int band=0;
	int pre=0;
	int post=0;
	int bandIndexados=0;
	char cadena[50];
	char caracter;
	char cadAuxOp[4];

	for(i=0; i<50; i++)
		cadena[i]='\0';

    fseek(fdTabOp,0,0);
	while((fgets(cadena,50,fdTabOp)) && (banderaAux == 0))
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
		    if(strcmp(TABOP.direccionamiento,"INH") == 0)
		    {
                MODODIRECCIONAMIENTO.INH=1;
                MODODIRECCIONAMIENTO.sumaBytesINH=TABOP.bytes_suma;
		    }
            else
            {
                if(strcmp(TABOP.direccionamiento,"IMM") == 0)
                {
                    MODODIRECCIONAMIENTO.IMM=1;
                    MODODIRECCIONAMIENTO.bytesCalcular=TABOP.bytes_por_calcular;
                    MODODIRECCIONAMIENTO.sumaBytesIMM=TABOP.bytes_suma;
                }
                else
                {
                    if(strcmp(TABOP.direccionamiento,"DIR") == 0)
                    {
                        MODODIRECCIONAMIENTO.DIR=1;
                        MODODIRECCIONAMIENTO.sumaBytesDIR=TABOP.bytes_suma;
                    }
                    else
                    {
                        if(strcmp(TABOP.direccionamiento,"EXT") == 0)
                        {
                            MODODIRECCIONAMIENTO.EXT=1;
                            MODODIRECCIONAMIENTO.sumaBytesEXT=TABOP.bytes_suma;
                        }
                        else
                        {
                            if(strcmp(TABOP.direccionamiento,"REL") == 0)
                            {
                                MODODIRECCIONAMIENTO.REL=1;
                                MODODIRECCIONAMIENTO.sumaBytesREL=TABOP.bytes_suma;
                            }
                            else
                            {
                                if(strcmp(TABOP.direccionamiento,"IDX") == 0)
                                {
                                    MODODIRECCIONAMIENTO.IDX=1;
                                    MODODIRECCIONAMIENTO.sumaBytesIDX=TABOP.bytes_suma;
                                }
                                else
                                {
                                    if(strcmp(TABOP.direccionamiento,"IDX1") == 0)
                                    {
                                        MODODIRECCIONAMIENTO.IDX1=1;
                                        MODODIRECCIONAMIENTO.sumaBytesIDX1=TABOP.bytes_suma;
                                    }
                                    else
                                    {
                                        if(strcmp(TABOP.direccionamiento,"IDX2") == 0)
                                        {
                                            MODODIRECCIONAMIENTO.IDX2=1;
                                            MODODIRECCIONAMIENTO.sumaBytesIDX2=TABOP.bytes_suma;
                                        }
                                        else
                                        {
                                            if(strcmp(TABOP.direccionamiento,"[IDX2]") == 0)
                                            {
                                                MODODIRECCIONAMIENTO._IDX2=1;
                                                MODODIRECCIONAMIENTO.sumaBytes_IDX2=TABOP.bytes_suma;
                                            }
                                            else
                                            {
                                                if(strcmp(TABOP.direccionamiento,"[D,IDX]") == 0)
                                                {
                                                    MODODIRECCIONAMIENTO.DIDX=1;
                                                    MODODIRECCIONAMIENTO.sumaBytesDIDX=TABOP.bytes_suma;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
		}
	}
	aux=0;
	aux=strlen(operando);
	for(i=0; i<aux; i++)
	{
	    if(operando[i] == ',')
            bandIndexados=1;
	}
    if(bandIndexados == 1)
    {
        if(strlen(operando) < 2)
            bandIndexados=2;
    }
    if(bandIndexados == 2)
        printf("\n\tError: La Coma No Puede Estar Sola Como Un Operando.");
	for(i=0; i<aux; i++)
	{
	    if(operando[i] == '[')
            contAuxInd++;
        if(operando[i] == ']')
            contAuxInd+=2;
	}
	if(contAuxInd == 3)
	{
	    if(aux > 2)
            bandAuxInd=1;
        else
            bandErrorLong=1;
	}
	if(aux < 2)
        bandErrorLong1=1;
	if(bandErrorLong == 1)
        printf("\n\tError: Los Corchetes no Pueden Estar Vacios en un Operando.") ;
    else
    {
        if(contAuxInd == 1)
        {
            printf("\n\tError: Falta el Simbolo ] para completar el Operando.");
            if(bandErrorLong1 == 1)
                printf("\n\tError: Los Corchetes no Pueden Estar Vacios en un Operando.") ;
            bandErrorLong=1;
        }
        else
        {
            if(contAuxInd == 2)
            {
                printf("\n\tError: Falta el Simbolo [ para completar el Operando.");
                if(bandErrorLong1 == 1)
                    printf("\n\tError: Los Corchetes no Pueden Estar Vacios en un Operando.") ;
                bandErrorLong=1;
            }
        }
    }
	if(bandAuxInd == 1)
	{
	    if(operando[1] > 65)
            bandAuxAcumInd=1;
	}
	if(operando[0] >= 65)
        bandAuxRel=1;

    if((MODODIRECCIONAMIENTO.INH == 1) && (bandIndexados == 0) && (bandAuxInd == 0))
    {
        if(strcmp(operando,"NULL") == 0)
        {
            printf("\n\n\tInherente, de %c bytes ",MODODIRECCIONAMIENTO.sumaBytesINH);
            bandModoInh=1;
            banderaAux=1;
            archAux.CONTLOC[4]='\0';
            if(bandTemporal == 1)
            {
                fseek(fdTemp,0,2);
                fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
            }
            if(strcmp(etiqueta,"NULL") != 0)
            {
                if(bandTabsim == 1)
                {
                    fseek(fdTabsim,0,2);
                    fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                }
            }
            switch(MODODIRECCIONAMIENTO.sumaBytesINH)
            {
                case '1':
                    byte=1;
                break;
                case '2':
                    byte=2;
                break;
                case '3':
                    byte=3;
                break;
                case '4':
                    byte=4;
                break;
            }
            archAux.Valor+=byte;
            itoa(archAux.Valor,cadAuxOp,16);
            strupr(cadAuxOp);
            longOperando=strlen(cadAuxOp);
            n= 4 - longOperando;
            if(n > 0)
            {
                k=0;
                for(i=0; i < n; i++)
                {
                    archAux.CONTLOC[i]='0';
                    k++;
                }
                j=0;
                for(i=k; i<4 ; i++)
                {
                    archAux.CONTLOC[i]=cadAuxOp[j];
                    j++;
                }
            }
            else
                strcpy(archAux.CONTLOC,cadAuxOp);
        }
        else
        {
            printf("\n\tError: No Debe de Existir Un Operando");
            bandModoInh=1;
        }
    }
	if((MODODIRECCIONAMIENTO.IMM == 1) && (bandModoInh == 0) && (bandIndexados == 0) && (bandAuxInd == 0))
    {
        if(operando[0] == '#')
        {
            if(strlen(operando) >= 2)
                bandImm=1;
            if(bandImm == 1)
            {
                if(MODODIRECCIONAMIENTO.bytesCalcular == '1')
                    band=1;
                else
                {
                    if(MODODIRECCIONAMIENTO.bytesCalcular == '2')
                        band=2;
                }
                bandModoImm=validaModoInmediato(operando,band);
                if(bandModoImm == 1)
                {
                    printf("\n\n\tInmediato de 8 bits, de %c bytes ",MODODIRECCIONAMIENTO.sumaBytesIMM);
                    banderaAux=1;
                    archAux.CONTLOC[4]='\0';
                    if(bandTemporal == 1)
                    {
                        fseek(fdTemp,0,2);
                        fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                    }
                    if(strcmp(etiqueta,"NULL") != 0)
                    {
                        if(bandTabsim == 1)
                        {
                            fseek(fdTabsim,0,2);
                            fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                        }
                    }
                    switch(MODODIRECCIONAMIENTO.sumaBytesIMM)
                    {
                        case '1':
                            byte=1;
                        break;
                        case '2':
                            byte=2;
                        break;
                        case '3':
                            byte=3;
                        break;
                        case '4':
                            byte=4;
                        break;
                    }
                    archAux.Valor+=byte;
                    itoa(archAux.Valor,cadAuxOp,16);
                    strupr(cadAuxOp);
                    longOperando=strlen(cadAuxOp);
                    n= 4 - longOperando;
                    if(n > 0)
                    {
                        k=0;
                        for(i=0; i < n; i++)
                        {
                            archAux.CONTLOC[i]='0';
                            k++;
                        }
                        j=0;
                        for(i=k; i<4 ; i++)
                        {
                            archAux.CONTLOC[i]=cadAuxOp[j];
                            j++;
                        }
                    }
                    else
                        strcpy(archAux.CONTLOC,cadAuxOp);
                }
                else
                {
                    if(bandModoImm == 2)
                    {
                        printf("\n\n\tInmediato de 16 bits, de %c bytes ",MODODIRECCIONAMIENTO.sumaBytesIMM);
                        banderaAux=1;
                        archAux.CONTLOC[4]='\0';
                        if(bandTemporal == 1)
                        {
                            fseek(fdTemp,0,2);
                            fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                        }
                        if(strcmp(etiqueta,"NULL") != 0)
                        {
                            if(bandTabsim == 1)
                            {
                                fseek(fdTabsim,0,2);
                                fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                            }
                        }
                        switch(MODODIRECCIONAMIENTO.sumaBytesIMM)
                        {
                            case '1':
                                byte=1;
                            break;
                            case '2':
                                byte=2;
                            break;
                            case '3':
                                byte=3;
                            break;
                            case '4':
                                byte=4;
                            break;
                        }
                        archAux.Valor+=byte;
                        itoa(archAux.Valor,cadAuxOp,16);
                        strupr(cadAuxOp);
                        longOperando=strlen(cadAuxOp);
                        n= 4 - longOperando;
                        if(n > 0)
                        {
                            k=0;
                            for(i=0; i < n; i++)
                            {
                                archAux.CONTLOC[i]='0';
                                k++;
                            }
                            j=0;
                            for(i=k; i<4 ; i++)
                            {
                                archAux.CONTLOC[i]=cadAuxOp[j];
                                j++;
                            }
                        }
                        else
                            strcpy(archAux.CONTLOC,cadAuxOp);
                    }
                }
            }
            else
            {
                printf("\n\tError: El Simbolo # debe Contener Un Valor Numerico.");
                banderaAux=1;
                bandModoImm=1;
            }
            banderaAux=1;
            bandModoImm=1;
        }
        else
            bandModoImm=0;
    }
    if((((MODODIRECCIONAMIENTO.DIR == 1) && (bandModoInh == 0) && (bandModoImm == 0)) && (MODODIRECCIONAMIENTO.EXT == 1)) && (bandIndexados == 0) && (bandAuxInd == 0) && (bandErrorLong == 0))
    {
        if(MODODIRECCIONAMIENTO.DIR == 1)
            bandAuxModoDir=1;
        if(MODODIRECCIONAMIENTO.EXT == 1)
            bandAuxModoExt=1;
        bandModoDirExt=validaModoDirectoExtendido(operando,bandAuxModoDir,bandAuxModoExt);
        if(bandModoDirExt == 1)
        {
            printf("\n\n\tDirecto, de %c bytes",MODODIRECCIONAMIENTO.sumaBytesDIR);
            bandModoDir=1;
            banderaAux=1;
            archAux.CONTLOC[4]='\0';
            if(bandTemporal == 1)
            {
                fseek(fdTemp,0,2);
                fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
            }
            if(strcmp(etiqueta,"NULL") != 0)
            {
                if(bandTabsim == 1)
                {
                    fseek(fdTabsim,0,2);
                    fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                }
            }
            switch(MODODIRECCIONAMIENTO.sumaBytesDIR)
            {
                case '1':
                    byte=1;
                break;
                case '2':
                    byte=2;
                break;
                case '3':
                    byte=3;
                break;
                case '4':
                    byte=4;
                break;
            }
            archAux.Valor+=byte;
            itoa(archAux.Valor,cadAuxOp,16);
            strupr(cadAuxOp);
            longOperando=strlen(cadAuxOp);
            n= 4 - longOperando;
            if(n > 0)
            {
                k=0;
                for(i=0; i < n; i++)
                {
                    archAux.CONTLOC[i]='0';
                    k++;
                }
                j=0;
                for(i=k; i<4 ; i++)
                {
                    archAux.CONTLOC[i]=cadAuxOp[j];
                    j++;
                }
            }
            else
                strcpy(archAux.CONTLOC,cadAuxOp);
        }
        else
        {
            if(bandModoDirExt == 2)
            {
                printf("\n\n\tExtendido, de %c bytes",MODODIRECCIONAMIENTO.sumaBytesEXT);
                bandModoExt=1;
                banderaAux=1;
                archAux.CONTLOC[4]='\0';
                if(bandTemporal == 1)
                {
                    fseek(fdTemp,0,2);
                    fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                }
                if(strcmp(etiqueta,"NULL") != 0)
                {
                    if(bandTabsim == 1)
                    {
                        fseek(fdTabsim,0,2);
                        fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                    }
                }
                switch(MODODIRECCIONAMIENTO.sumaBytesEXT)
                {
                    case '1':
                        byte=1;
                    break;
                    case '2':
                        byte=2;
                    break;
                    case '3':
                        byte=3;
                    break;
                    case '4':
                        byte=4;
                    break;
                }
                archAux.Valor+=byte;
                itoa(archAux.Valor,cadAuxOp,16);
                strupr(cadAuxOp);
                longOperando=strlen(cadAuxOp);
                n= 4 - longOperando;
                if(n > 0)
                {
                    k=0;
                    for(i=0; i < n; i++)
                    {
                        archAux.CONTLOC[i]='0';
                        k++;
                    }
                    j=0;
                    for(i=k; i<4 ; i++)
                    {
                        archAux.CONTLOC[i]=cadAuxOp[j];
                        j++;
                    }
                }
                else
                    strcpy(archAux.CONTLOC,cadAuxOp);
            }
        }
    }
    if((((MODODIRECCIONAMIENTO.IDX == 1) || (MODODIRECCIONAMIENTO.IDX1 == 1) || (MODODIRECCIONAMIENTO.IDX2 == 1))  && ((bandModoDir == 0) && (bandAuxModoExt == 0) && (bandModoInh == 0))) && (bandIndexados == 1) && (bandAuxInd == 0) && (bandErrorLong == 0))
    {
        if(MODODIRECCIONAMIENTO.IDX == 1)
            bandIDX=1;
        if(MODODIRECCIONAMIENTO.IDX1 == 1)
            bandIDX1=1;
        if(MODODIRECCIONAMIENTO.IDX2 == 1)
            bandIDX2=1;
        bandAuxModoIDX=validaModoIDX(operando,bandIDX,bandIDX1,bandIDX2);
        if(bandAuxModoIDX == 1)
        {
            printf("\n\n\tIndizado de 5 bits, %c bytes",MODODIRECCIONAMIENTO.sumaBytesIDX);
            bandAuxModoIDX5=1;
            banderaAux=1;
            archAux.CONTLOC[4]='\0';
            if(bandTemporal == 1)
            {
                fseek(fdTemp,0,2);
                fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
            }
            if(strcmp(etiqueta,"NULL") != 0)
            {
                if(bandTabsim == 1)
                {
                    fseek(fdTabsim,0,2);
                    fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                }
            }
            switch(MODODIRECCIONAMIENTO.sumaBytesIDX)
            {
                case '1':
                    byte=1;
                break;
                case '2':
                    byte=2;
                break;
                case '3':
                    byte=3;
                break;
                case '4':
                    byte=4;
                break;
            }
            archAux.Valor+=byte;
            itoa(archAux.Valor,cadAuxOp,16);
            strupr(cadAuxOp);
            longOperando=strlen(cadAuxOp);
            n= 4 - longOperando;
            if(n > 0)
            {
                k=0;
                for(i=0; i < n; i++)
                {
                    archAux.CONTLOC[i]='0';
                    k++;
                }
                j=0;
                for(i=k; i<4 ; i++)
                {
                    archAux.CONTLOC[i]=cadAuxOp[j];
                    j++;
                }
            }
            else
                strcpy(archAux.CONTLOC,cadAuxOp);
        }
        else
        {
            if(bandAuxModoIDX == 4)
            {
                printf("\n\n\tIndizado de 9 bits, %c bytes",MODODIRECCIONAMIENTO.sumaBytesIDX1);
                bandAuxModoIDX1=1;
                banderaAux=1;
                archAux.CONTLOC[4]='\0';
                if(bandTemporal == 1)
                {
                    fseek(fdTemp,0,2);
                    fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                }
                if(strcmp(etiqueta,"NULL") != 0)
                {
                    if(bandTabsim == 1)
                    {
                        fseek(fdTabsim,0,2);
                        fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                    }
                }
                switch(MODODIRECCIONAMIENTO.sumaBytesIDX1)
                {
                    case '1':
                        byte=1;
                    break;
                    case '2':
                        byte=2;
                    break;
                    case '3':
                        byte=3;
                    break;
                    case '4':
                        byte=4;
                    break;
                }
                archAux.Valor+=byte;
                itoa(archAux.Valor,cadAuxOp,16);
                strupr(cadAuxOp);
                longOperando=strlen(cadAuxOp);
                n= 4 - longOperando;
                if(n > 0)
                {
                    k=0;
                    for(i=0; i < n; i++)
                    {
                        archAux.CONTLOC[i]='0';
                        k++;
                    }
                    j=0;
                    for(i=k; i<4 ; i++)
                    {
                        archAux.CONTLOC[i]=cadAuxOp[j];
                        j++;
                    }
                }
                else
                    strcpy(archAux.CONTLOC,cadAuxOp);
            }
            else
            {
                if(bandAuxModoIDX == 5)
                {
                    printf("\n\n\tIndizado de 16 bits, %c bytes",MODODIRECCIONAMIENTO.sumaBytesIDX2);
                    bandAuxModoIDX2=1;
                    banderaAux=1;
                    archAux.CONTLOC[4]='\0';
                    if(bandTemporal == 1)
                    {
                        fseek(fdTemp,0,2);
                        fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                    }
                    if(strcmp(etiqueta,"NULL") != 0)
                    {
                        if(bandTabsim == 1)
                        {
                            fseek(fdTabsim,0,2);
                            fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                        }
                    }
                    switch(MODODIRECCIONAMIENTO.sumaBytesIDX2)
                    {
                        case '1':
                            byte=1;
                        break;
                        case '2':
                            byte=2;
                        break;
                        case '3':
                            byte=3;
                        break;
                        case '4':
                            byte=4;
                        break;
                    }
                    archAux.Valor+=byte;
                    itoa(archAux.Valor,cadAuxOp,16);
                    strupr(cadAuxOp);
                    longOperando=strlen(cadAuxOp);
                    n= 4 - longOperando;
                    if(n > 0)
                    {
                        k=0;
                        for(i=0; i < n; i++)
                        {
                            archAux.CONTLOC[i]='0';
                            k++;
                        }
                        j=0;
                        for(i=k; i<4 ; i++)
                        {
                            archAux.CONTLOC[i]=cadAuxOp[j];
                            j++;
                        }
                    }
                    else
                        strcpy(archAux.CONTLOC,cadAuxOp);
                }
                else
                {
                    if(bandAuxModoIDX == 2)
                    {
                        if(operando[strlen(operando) - 1] == '+')
                            post+=2;
                        else
                        {
                            if(operando[strlen(operando) - 1] == '-')
                                post++;
                        }
                        for(i=0; i<strlen(operando); i++)
                        {
                            if((operando[i] == '+') && (operando[strlen(operando) - 1] != '+'))
                                pre+=2;
                            else
                            {
                                if((operando[i] == '-') && (operando[strlen(operando) - 1] != '-'))
                                    pre++;
                            }
                        }
                        if(post == 1)
                        {
                            printf("\n\n\tIndizado de Auto Post Decremento, %c bytes",MODODIRECCIONAMIENTO.sumaBytesIDX);
                            bandAuxModoIDXPre=1;
                            banderaAux=1;
                            archAux.CONTLOC[4]='\0';
                            if(bandTemporal == 1)
                            {
                                fseek(fdTemp,0,2);
                                fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                            }
                            if(strcmp(etiqueta,"NULL") != 0)
                            {
                                if(bandTabsim == 1)
                                {
                                    fseek(fdTabsim,0,2);
                                    fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                }
                            }
                            switch(MODODIRECCIONAMIENTO.sumaBytesIDX)
                            {
                                case '1':
                                    byte=1;
                                break;
                                case '2':
                                    byte=2;
                                break;
                                case '3':
                                    byte=3;
                                break;
                                case '4':
                                    byte=4;
                                break;
                            }
                            archAux.Valor+=byte;
                            itoa(archAux.Valor,cadAuxOp,16);
                            strupr(cadAuxOp);
                            longOperando=strlen(cadAuxOp);
                            n= 4 - longOperando;
                            if(n > 0)
                            {
                                k=0;
                                for(i=0; i < n; i++)
                                {
                                    archAux.CONTLOC[i]='0';
                                    k++;
                                }
                                j=0;
                                for(i=k; i<4 ; i++)
                                {
                                    archAux.CONTLOC[i]=cadAuxOp[j];
                                    j++;
                                }
                            }
                            else
                                strcpy(archAux.CONTLOC,cadAuxOp);
                        }
                        else
                        {
                            if(post == 2)
                            {
                                printf("\n\n\tIndizado de Auto Post Imncremento, %c bytes",MODODIRECCIONAMIENTO.sumaBytesIDX);
                                bandAuxModoIDXPre=1;
                                banderaAux=1;
                                archAux.CONTLOC[4]='\0';
                                if(bandTemporal == 1)
                                {
                                    fseek(fdTemp,0,2);
                                    fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                }
                                if(strcmp(etiqueta,"NULL") != 0)
                                {
                                    if(bandTabsim == 1)
                                    {
                                        fseek(fdTabsim,0,2);
                                        fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                    }
                                }
                                switch(MODODIRECCIONAMIENTO.sumaBytesIDX)
                                {
                                    case '1':
                                        byte=1;
                                    break;
                                    case '2':
                                        byte=2;
                                    break;
                                    case '3':
                                        byte=3;
                                    break;
                                    case '4':
                                        byte=4;
                                    break;
                                }
                                archAux.Valor+=byte;
                                itoa(archAux.Valor,cadAuxOp,16);
                                strupr(cadAuxOp);
                                longOperando=strlen(cadAuxOp);
                                n= 4 - longOperando;
                                if(n > 0)
                                {
                                    k=0;
                                    for(i=0; i < n; i++)
                                    {
                                        archAux.CONTLOC[i]='0';
                                        k++;
                                    }
                                    j=0;
                                    for(i=k; i<4 ; i++)
                                    {
                                        archAux.CONTLOC[i]=cadAuxOp[j];
                                        j++;
                                    }
                                }
                                else
                                    strcpy(archAux.CONTLOC,cadAuxOp);
                            }
                            else
                            {
                                if(pre == 2)
                                {
                                    printf("\n\n\tIndizado de Auto Pre Incremento, %c bytes",MODODIRECCIONAMIENTO.sumaBytesIDX);
                                    bandAuxModoIDXPre=1;
                                    banderaAux=1;
                                    archAux.CONTLOC[4]='\0';
                                    if(bandTemporal == 1)
                                    {
                                        fseek(fdTemp,0,2);
                                        fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                    }
                                    if(strcmp(etiqueta,"NULL") != 0)
                                    {
                                        if(bandTabsim == 1)
                                        {
                                            fseek(fdTabsim,0,2);
                                            fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                        }
                                    }
                                    switch(MODODIRECCIONAMIENTO.sumaBytesIDX)
                                    {
                                        case '1':
                                            byte=1;
                                        break;
                                        case '2':
                                            byte=2;
                                        break;
                                        case '3':
                                            byte=3;
                                        break;
                                        case '4':
                                            byte=4;
                                        break;
                                    }
                                    archAux.Valor+=byte;
                                    itoa(archAux.Valor,cadAuxOp,16);
                                    strupr(cadAuxOp);
                                    longOperando=strlen(cadAuxOp);
                                    n= 4 - longOperando;
                                    if(n > 0)
                                    {
                                        k=0;
                                        for(i=0; i < n; i++)
                                        {
                                            archAux.CONTLOC[i]='0';
                                            k++;
                                        }
                                        j=0;
                                        for(i=k; i<4 ; i++)
                                        {
                                            archAux.CONTLOC[i]=cadAuxOp[j];
                                            j++;
                                        }
                                    }
                                    else
                                        strcpy(archAux.CONTLOC,cadAuxOp);
                                }
                                else
                                {
                                    if(pre == 1)
                                    {
                                        printf("\n\n\tIndizado de Auto Pre Decremento, %c bytes",MODODIRECCIONAMIENTO.sumaBytesIDX);
                                        bandAuxModoIDXPre=1;
                                        banderaAux=1;
                                        archAux.CONTLOC[4]='\0';
                                        if(bandTemporal == 1)
                                        {
                                            fseek(fdTemp,0,2);
                                            fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                        }
                                        if(strcmp(etiqueta,"NULL") != 0)
                                        {
                                            if(bandTabsim == 1)
                                            {
                                                fseek(fdTabsim,0,2);
                                                fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                            }
                                        }
                                        switch(MODODIRECCIONAMIENTO.sumaBytesIDX)
                                        {
                                            case '1':
                                                byte=1;
                                            break;
                                            case '2':
                                                byte=2;
                                            break;
                                            case '3':
                                                byte=3;
                                            break;
                                            case '4':
                                                byte=4;
                                            break;
                                        }
                                        archAux.Valor+=byte;
                                        itoa(archAux.Valor,cadAuxOp,16);
                                        strupr(cadAuxOp);
                                        longOperando=strlen(cadAuxOp);
                                        n= 4 - longOperando;
                                        if(n > 0)
                                        {
                                            k=0;
                                            for(i=0; i < n; i++)
                                            {
                                                archAux.CONTLOC[i]='0';
                                                k++;
                                            }
                                            j=0;
                                            for(i=k; i<4 ; i++)
                                            {
                                                archAux.CONTLOC[i]=cadAuxOp[j];
                                                j++;
                                            }
                                        }
                                        else
                                            strcpy(archAux.CONTLOC,cadAuxOp);
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        if(bandAuxModoIDX == 3)
                        {
                            printf("\n\n\tIndizado de Acumulador, %c bytes",MODODIRECCIONAMIENTO.sumaBytesIDX);
                            bandAuxModoIDXAcum=1;
                            banderaAux=1;
                            archAux.CONTLOC[4]='\0';
                            if(bandTemporal == 1)
                            {
                                fseek(fdTemp,0,2);
                                fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                            }
                            if(strcmp(etiqueta,"NULL") != 0)
                            {
                                if(bandTabsim == 1)
                                {
                                    fseek(fdTabsim,0,2);
                                    fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                }
                            }
                            switch(MODODIRECCIONAMIENTO.sumaBytesIDX)
                            {
                                case '1':
                                    byte=1;
                                break;
                                case '2':
                                    byte=2;
                                break;
                                case '3':
                                    byte=3;
                                break;
                                case '4':
                                    byte=4;
                                break;
                            }
                            archAux.Valor+=byte;
                            itoa(archAux.Valor,cadAuxOp,16);
                            strupr(cadAuxOp);
                            longOperando=strlen(cadAuxOp);
                            n= 4 - longOperando;
                            if(n > 0)
                            {
                                k=0;
                                for(i=0; i < n; i++)
                                {
                                    archAux.CONTLOC[i]='0';
                                    k++;
                                }
                                j=0;
                                for(i=k; i<4 ; i++)
                                {
                                    archAux.CONTLOC[i]=cadAuxOp[j];
                                    j++;
                                }
                            }
                            else
                                strcpy(archAux.CONTLOC,cadAuxOp);
                        }
                    }
                }
            }
        }
    }
    if((MODODIRECCIONAMIENTO._IDX2 == 1) && (bandAuxInd == 1) && (bandAuxAcumInd == 0) && (bandErrorLong == 0))
    {
        band_IDX2=validaModoIndizadoIndirecto16(operando);
        if(band_IDX2 == 1)
        {
            printf("\n\n\tIndizado Indirecto de 16 bits, %c bytes",MODODIRECCIONAMIENTO.sumaBytes_IDX2);
            band_IDX2=1;
            banderaAux=1;
            archAux.CONTLOC[4]='\0';
            if(bandTemporal == 1)
            {
                fseek(fdTemp,0,2);
                fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
            }
            if(strcmp(etiqueta,"NULL") != 0)
            {
                if(bandTabsim == 1)
                {
                    fseek(fdTabsim,0,2);
                    fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                }
            }
            switch(MODODIRECCIONAMIENTO.sumaBytes_IDX2)
            {
                case '1':
                    byte=1;
                break;
                case '2':
                    byte=2;
                break;
                case '3':
                    byte=3;
                break;
                case '4':
                    byte=4;
                break;
            }
            archAux.Valor+=byte;
            itoa(archAux.Valor,cadAuxOp,16);
            strupr(cadAuxOp);
            longOperando=strlen(cadAuxOp);
            n= 4 - longOperando;
            if(n > 0)
            {
                k=0;
                for(i=0; i < n; i++)
                {
                    archAux.CONTLOC[i]='0';
                    k++;
                }
                j=0;
                for(i=k; i<4 ; i++)
                {
                    archAux.CONTLOC[i]=cadAuxOp[j];
                    j++;
                }
            }
            else
                strcpy(archAux.CONTLOC,cadAuxOp);
        }
        else
            band_IDX2=0;
    }
    if((MODODIRECCIONAMIENTO.DIDX == 1) && (bandAuxInd == 1) && (band_IDX2 == 0) && (bandAuxAcumInd == 1) && (bandErrorLong == 0))
    {
        bandDIDX=validaModoAcumuladorIndirecto(operando);
        if(bandDIDX == 1)
        {
            printf("\n\n\tIndizado de Acumulador Indirecto, %c bytes",MODODIRECCIONAMIENTO.sumaBytesDIDX);
            bandDIDX=1;
            banderaAux=1;
            archAux.CONTLOC[4]='\0';
            if(bandTemporal == 1)
            {
                fseek(fdTemp,0,2);
                fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
            }
            if(strcmp(etiqueta,"NULL") != 0)
            {
                if(bandTabsim == 1)
                {
                    fseek(fdTabsim,0,2);
                    fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                }
            }
            switch(MODODIRECCIONAMIENTO.sumaBytesDIDX)
            {
                case '1':
                    byte=1;
                break;
                case '2':
                    byte=2;
                break;
                case '3':
                    byte=3;
                break;
                case '4':
                    byte=4;
                break;
            }
            archAux.Valor+=byte;
            itoa(archAux.Valor,cadAuxOp,16);
            strupr(cadAuxOp);
            longOperando=strlen(cadAuxOp);
            n= 4 - longOperando;
            if(n > 0)
            {
                k=0;
                for(i=0; i < n; i++)
                {
                    archAux.CONTLOC[i]='0';
                    k++;
                }
                j=0;
                for(i=k; i<4 ; i++)
                {
                    archAux.CONTLOC[i]=cadAuxOp[j];
                    j++;
                }
            }
            else
                strcpy(archAux.CONTLOC,cadAuxOp);
        }
    }
    if((MODODIRECCIONAMIENTO.REL == 1) && (bandAuxRel == 1))
    {
        if(operando[0] != '\0')
        {
            for(k=0; k<strlen(operando); k++)
            {
                if(operando[k] == '\n')
                    operando[k]='\0';
            }
            if(validaLongEtiqueta(operando) == 1)
                contEtiqueta++;
            else
                printf("\n\tError: La longitud maxima de una etiqueta es de 8 caracteres.");
            if(validaIniEtiqueta(operando) == 1)
                contEtiqueta++;
            else
                printf("\n\tError: La etiqueta debe de iniciar con una letra.");
            if(validaCarEtiqueta(operando) == 1)
                contEtiqueta++;
            else
                printf("\n\tError: Los caracteres validos de una etiqueta son letras, digitos(0...9) y el guion bajo.");
        }
        if(contEtiqueta == 3)
            bandRelativo=1;
        if(bandRelativo == 1)
        {
            if(MODODIRECCIONAMIENTO.sumaBytesREL == '4')
                bandRelativo16=1;
            else
            {
                if(MODODIRECCIONAMIENTO.sumaBytesREL == '2')
                    bandRelativo8=1;
            }
        }
        if(bandRelativo8 == 1)
        {
            printf("\n\n\tRelativo de 8 bits,de %c bytes",MODODIRECCIONAMIENTO.sumaBytesREL);
            banderaAux=1;
            archAux.CONTLOC[4]='\0';
            if(bandTemporal == 1)
            {
                fseek(fdTemp,0,2);
                fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
            }
            if(strcmp(etiqueta,"NULL") != 0)
            {
                if(bandTabsim == 1)
                {
                    fseek(fdTabsim,0,2);
                    fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                }
            }
            switch(MODODIRECCIONAMIENTO.sumaBytesREL)
            {
                case '1':
                    byte=1;
                break;
                case '2':
                    byte=2;
                break;
                case '3':
                    byte=3;
                break;
                case '4':
                    byte=4;
                break;
            }
            archAux.Valor+=byte;
            itoa(archAux.Valor,cadAuxOp,16);
            strupr(cadAuxOp);
            longOperando=strlen(cadAuxOp);
            n= 4 - longOperando;
            if(n > 0)
            {
                k=0;
                for(i=0; i < n; i++)
                {
                    archAux.CONTLOC[i]='0';
                    k++;
                }
                j=0;
                for(i=k; i<4 ; i++)
                {
                    archAux.CONTLOC[i]=cadAuxOp[j];
                    j++;
                }
            }
            else
                strcpy(archAux.CONTLOC,cadAuxOp);
        }
        else
        {
            if(bandRelativo16 == 1)
            {
                printf("\n\n\tRelativo de 16 bits,de %c bytes",MODODIRECCIONAMIENTO.sumaBytesREL);
                banderaAux=1;
                archAux.CONTLOC[4]='\0';
                if(bandTemporal == 1)
                {
                    fseek(fdTemp,0,2);
                    fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                }
                if(strcmp(etiqueta,"NULL") != 0)
                {
                    if(bandTabsim == 1)
                    {
                        fseek(fdTabsim,0,2);
                        fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                    }
                }
                switch(MODODIRECCIONAMIENTO.sumaBytesREL)
                {
                    case '1':
                        byte=1;
                    break;
                    case '2':
                        byte=2;
                    break;
                    case '3':
                        byte=3;
                    break;
                    case '4':
                        byte=4;
                    break;
                }
                archAux.Valor+=byte;
                itoa(archAux.Valor,cadAuxOp,16);
                strupr(cadAuxOp);
                longOperando=strlen(cadAuxOp);
                n= 4 - longOperando;
                if(n > 0)
                {
                    k=0;
                    for(i=0; i < n; i++)
                    {
                        archAux.CONTLOC[i]='0';
                        k++;
                    }
                    j=0;
                    for(i=k; i<4 ; i++)
                    {
                        archAux.CONTLOC[i]=cadAuxOp[j];
                        j++;
                    }
                }
                else
                    strcpy(archAux.CONTLOC,cadAuxOp);
            }
        }
    }

	return banderaAux;
}

ARCH_AUX validaDirectivaORG(char etiqueta[10],char codop[10],char operando[10])
{
    int bandOrg=0;

    int bandEtiqueta=0;
    int bandera=0;
    int valOperando=0;
    int longOperando=0;
    int i=0;
    int j=0;
    int k=0;
    int n=0;
    int bandError=0;
    char cadAuxOp[4];
    ARCH_AUX archAux1;

    archAux1.DIR_INIC=0;
    for(i=0; i<4; i++)
        archAux1.CONTLOC[i]='\0';
    for(i=0; i<4; i++)
        cadAuxOp[i]='\0';

    if((strcmp(codop,"ORG") == 0) || (strcmp(codop,"Org") == 0) || (strcmp(codop,"org") == 0))
    {
        if(strcmp(etiqueta,"NULL") == 0)
            bandEtiqueta=1;
        if(bandEtiqueta == 1)
        {
            bandOrg=1;
            if(operando[0] == '$')
            {
                bandera=hexadecimal(operando);
                if(bandera == 1)
                {
                    valOperando=convierteHexadecimalDecimal(operando);
                    if((valOperando >= 0) && (valOperando <= 65535))
                    {
                        archAux1.DIR_INIC=valOperando;
                        itoa(archAux1.DIR_INIC,cadAuxOp,16);
                        strupr(cadAuxOp);
                        longOperando=strlen(cadAuxOp);
                        n= 4 - longOperando;
                        if(n > 0)
                        {
                            k=0;
                            for(i=0; i < n; i++)
                            {
                                archAux1.CONTLOC[i]='0';
                                k++;
                            }
                            j=0;
                            for(i=k; i<4; i++)
                            {
                                archAux1.CONTLOC[i]=cadAuxOp[j];
                                j++;
                            }
                        }
                        else
                            strcpy(archAux1.CONTLOC,cadAuxOp);
                        archAux1.bandera=1;
                    }
                    else
                        printf("\n\tError: Excede el Limite de la Directiva ORG, Rango Valido: 0 a 65535");
                }
                else
                    printf("\n\tError: Base Numerica Hexadecimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F");
            }
            else
            {
                if(operando[0] == '@')
                {
                    bandera=octal(operando);
                    if(bandera == 1)
                    {
                        valOperando=convierteOctalDecimal(operando);
                        if((valOperando >= 0) && (valOperando <= 65535))
                        {
                            archAux1.DIR_INIC=valOperando;
                            itoa(archAux1.DIR_INIC,cadAuxOp,16);
                            strupr(cadAuxOp);
                            longOperando=strlen(cadAuxOp);
                            n= 4 - longOperando;
                            if(n > 0)
                            {
                                k=0;
                                for(i=0; i < n; i++)
                                {
                                    archAux1.CONTLOC[i]='0';
                                    k++;
                                }
                                j=0;
                                for(i=k; i<4; i++)
                                {
                                    archAux1.CONTLOC[i]=cadAuxOp[j];
                                    j++;
                                }
                            }
                            else
                                strcpy(archAux1.CONTLOC,cadAuxOp);
                            archAux1.bandera=1;
                        }
                        else
                            printf("\n\tError: Excede el Limite de la Directiva ORG, Rango Valido: 0 a 65535");
                    }
                    else
                        printf("\n\tError: Base Numerica Octal Invalida,Caracteres validos 0,1,2,3,4,5,6,7");
                }
                else
                {
                    if(operando[0] == '%')
                    {
                        bandera=binario(operando);
                        if(bandera == 1)
                        {
                            valOperando=convierteBinarioDecimal(operando);
                            if((valOperando >= 0) && (valOperando <= 65535))
                            {
                                archAux1.DIR_INIC=valOperando;
                                itoa(archAux1.DIR_INIC,cadAuxOp,16);
                                strupr(cadAuxOp);
                                longOperando=strlen(cadAuxOp);
                                n= 4 - longOperando;
                                if(n > 0)
                                {
                                    k=0;
                                    for(i=0; i < n; i++)
                                    {
                                        archAux1.CONTLOC[i]='0';
                                        k++;
                                    }
                                    j=0;
                                    for(i=k; i<4; i++)
                                    {
                                        archAux1.CONTLOC[i]=cadAuxOp[j];
                                        j++;
                                    }
                                }
                                else
                                    strcpy(archAux1.CONTLOC,cadAuxOp);
                                archAux1.bandera=1;
                            }
                            else
                                printf("\n\tError: Excede el Limite de la Directiva ORG, Rango Valido: 0 a 65535");
                        }
                        else
                            printf("\n\tError: Base Numerica Binaria Invalida,Caracteres validos 0,1");
                    }
                    else
                    {
                        if((operando[0] >= 48) && (operando[0] <= 57))
                        {
                            bandera=decimal(operando);
                            if(bandera == 1)
                            {
                                valOperando=atoi(operando);
                                if((valOperando >= 0) && (valOperando <= 65535))
                                {
                                    archAux1.DIR_INIC=valOperando;
                                    itoa(archAux1.DIR_INIC,cadAuxOp,16);
                                    strupr(cadAuxOp);
                                    longOperando=strlen(cadAuxOp);
                                    n= 4 - longOperando;
                                    if(n > 0)
                                    {
                                        k=0;
                                        for(i=0; i < n; i++)
                                        {
                                            archAux1.CONTLOC[i]='0';
                                            k++;
                                        }
                                        j=0;
                                        for(i=k; i < 4; i++)
                                        {
                                            archAux1.CONTLOC[i]=cadAuxOp[j];
                                            j++;
                                        }
                                    }
                                    else
                                        strcpy(archAux1.CONTLOC,cadAuxOp);
                                    archAux1.bandera=1;
                                }
                                else
                                    printf("\n\tError: Excede el Limite de la Directiva ORG, Rango Valido: 0 a 65535");
                            }
                            else
                                printf("\n\tError: Base Numerica Decimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9");
                        }
                        else
                        {
                            if(operando[0] == '\0')
                            {
                                bandError=1;
                                printf("\n\tError: La Directiva ORG debe tener Operando");
                            }
                        }
                    }
                }
            }
        }
        else
        {
            printf("\n\tError: La Directiva ORG no Permite Etiquetas");
            bandOrg=1;
        }
    }
    return archAux1;
}

ARCH_AUX validaDirectivaEQU(char etiqueta[10],char codop[10],char operando[10])
{
    int bandEqu=0;
    int bandEtiqueta=0;
    int bandera=0;
    int valOperando=0;
    int longOperando=0;
    int i=0;
    int j=0;
    int k=0;
    int n=0;
    int bandError=0;
    int auxDireccion;
    char cadAuxOp[4];
    ARCH_AUX archAux1;


    for(i=0; i<5; i++)
        archAux1.DIR_EQU[i]='\0';
    for(i=0; i<5; i++)
        cadAuxOp[i]='\0';

    if(strcmp(etiqueta,"NULL") != 0)
        bandEtiqueta=1;
    if(bandEtiqueta == 1)
    {
        if(operando[0] == '$')
        {
            bandera=hexadecimal(operando);
            if(bandera == 1)
            {
                valOperando=convierteHexadecimalDecimal(operando);
                if((valOperando >= 0) && (valOperando <= 65535))
                {
                    auxDireccion=valOperando;
                    itoa(auxDireccion,cadAuxOp,16);
                    strupr(cadAuxOp);
                    longOperando=strlen(cadAuxOp);
                    n= 4 - longOperando;
                    if(n > 0)
                    {
                        k=0;
                        for(i=0; i < n; i++)
                        {
                            archAux1.DIR_EQU[i]='0';
                            k++;
                        }
                        j=0;
                        for(i=k; i<4; i++)
                        {
                            archAux1.DIR_EQU[i]=cadAuxOp[j];
                            j++;
                        }
                    }
                    else
                        strcpy(archAux1.DIR_EQU,cadAuxOp);
                    archAux1.bandera=1;
                }
                else
                    printf("\n\tError: Excede el Limite de la Directiva EQU, Rango Valido: 0 a 65535");
            }
            else
                printf("\n\tError: Base Numerica Hexadecimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F");
        }
        else
        {
            if(operando[0] == '@')
            {
                bandera=octal(operando);
                if(bandera == 1)
                {
                    valOperando=convierteOctalDecimal(operando);
                    if((valOperando >= 0) && (valOperando <= 65535))
                    {
                        auxDireccion=valOperando;
                        itoa(auxDireccion,cadAuxOp,16);
                        strupr(cadAuxOp);
                        longOperando=strlen(cadAuxOp);
                        n= 4 - longOperando;
                        if(n > 0)
                        {
                            k=0;
                            for(i=0; i < n; i++)
                            {
                                archAux1.DIR_EQU[i]='0';
                                k++;
                            }
                            j=0;
                            for(i=k; i<4; i++)
                            {
                                archAux1.DIR_EQU[i]=cadAuxOp[j];
                                j++;
                            }
                        }
                        else
                            strcpy(archAux1.CONTLOC,cadAuxOp);
                        archAux1.bandera=1;
                    }
                    else
                        printf("\n\tError: Excede el Limite de la Directiva ORG, Rango Valido: 0 a 65535");
                }
                else
                    printf("\n\tError: Base Numerica Octal Invalida,Caracteres validos 0,1,2,3,4,5,6,7");
            }
            else
            {
                if(operando[0] == '%')
                {
                    bandera=binario(operando);
                    if(bandera == 1)
                    {
                        valOperando=convierteBinarioDecimal(operando);
                        if((valOperando >= 0) && (valOperando <= 65535))
                        {
                            auxDireccion=valOperando;
                            itoa(auxDireccion,cadAuxOp,16);
                            strupr(cadAuxOp);
                            longOperando=strlen(cadAuxOp);
                            n= 4 - longOperando;
                            if(n > 0)
                            {
                                k=0;
                                for(i=0; i < n; i++)
                                {
                                    archAux1.DIR_EQU[i]='0';
                                    k++;
                                }
                                j=0;
                                for(i=k; i<4 ; i++)
                                {
                                    archAux1.DIR_EQU[i]=cadAuxOp[j];
                                    j++;
                                }
                            }
                            else
                                strcpy(archAux1.DIR_EQU,cadAuxOp);
                            archAux1.bandera=1;
                        }
                        else
                            printf("\n\tError: Excede el Limite de la Directiva EQU, Rango Valido: 0 a 65535");
                    }
                    else
                        printf("\n\tError: Base Numerica Binaria Invalida,Caracteres validos 0,1");
                }
                else
                {
                    if((operando[0] >= 48) && (operando[0] <= 57))
                    {
                        bandera=decimal(operando);
                        if(bandera == 1)
                        {
                            valOperando=atoi(operando);
                            if((valOperando >= 0) && (valOperando <= 65535))
                            {
                                auxDireccion=valOperando;
                                itoa(auxDireccion,cadAuxOp,16);
                                strupr(cadAuxOp);
                                longOperando=strlen(cadAuxOp);
                                n= 4 - longOperando;
                                if(n > 0)
                                {
                                    k=0;
                                    for(i=0; i < n; i++)
                                    {
                                        archAux1.DIR_EQU[i]='0';
                                        k++;
                                    }
                                    j=0;
                                    for(i=k; i<4 ; i++)
                                    {
                                        archAux1.DIR_EQU[i]=cadAuxOp[j];
                                        j++;
                                    }
                                }
                                else
                                    strcpy(archAux1.DIR_EQU,cadAuxOp);
                                archAux1.bandera=1;
                            }
                            else
                                printf("\n\tError: Excede el Limite de la Directiva EQU, Rango Valido: 0 a 65535");
                        }
                        else
                            printf("\n\tError: Base Numerica Decimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9");
                    }
                    else
                    {
                        if(operando[0] == '\0')
                        {
                            bandError=1;
                            printf("\n\tError: La Directiva EQU debe tener Operando");
                        }
                    }
                }
            }
        }
    }
    else
    {
        printf("\n\tError: La Directiva EQU Debe Contener Etiqueta");
        bandEqu=1;
    }
    return archAux1;
}


int validaDirectivaDC(char etiqueta[10],char codop[10],char operando[10],int bandDirectiva,int bandTemporal,FILE * fdTemp,int bandTabsim,FILE * fdTabsim)
{
    int n=0;
    int i=0;
    int j=0;
    int k=0;
    int bytes=0;
    int bandera=0;
    int bandError=0;
    int valOperando=0;
    int longOperando=0;
    int acumDirectiva=0;
    char cadAuxOp[5];

    if(bandDirectiva == 1)
    {
        if(operando[0] == '$')
        {
            bandera=hexadecimal(operando);
            if(bandera == 1)
            {
                valOperando=convierteHexadecimalDecimal(operando);
                if((valOperando >= 0) && (valOperando <= 65535))
                {
                    archAux.CONTLOC[4]='\0';
                    if(bandTemporal == 1)
                    {
                        fseek(fdTemp,0,2);
                        fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                        bandDirectiva=1;
                    }
                    if(strcmp(etiqueta,"NULL") != 0)
                    {
                        if(bandTabsim == 1)
                        {
                            fseek(fdTabsim,0,2);
                            fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                        }
                    }
                    bytes=2;
                    archAux.Valor+=bytes;
                    itoa(archAux.Valor,cadAuxOp,16);
                    strupr(cadAuxOp);
                    longOperando=strlen(cadAuxOp);
                    n= 4 - longOperando;
                    if(n > 0)
                    {
                        k=0;
                        for(i=0; i < n; i++)
                        {
                            archAux.CONTLOC[i]='0';
                            k++;
                        }
                        j=0;
                        for(i=k; i<4; i++)
                        {
                            archAux.CONTLOC[i]=cadAuxOp[j];
                            j++;
                        }
                    }
                    else
                        strcpy(archAux.CONTLOC,cadAuxOp);
                    acumDirectiva=1;
                }
                else
                    printf("\n\tError: Excede el Limite de la Directiva DW, Rango Valido: 0 a 65535");
            }
            else
                printf("\n\tError: Base Numerica Hexadecimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F");
        }
        else
        {
            if(operando[0] == '@')
            {
                bandera=octal(operando);
                if(bandera == 1)
                {
                    valOperando=convierteHexadecimalDecimal(operando);
                    if((valOperando >= 0) && (valOperando <= 65535))
                    {
                        archAux.CONTLOC[4]='\0';
                        if(bandTemporal == 1)
                        {
                            fseek(fdTemp,0,2);
                            fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                            bandDirectiva=1;
                        }
                        if(strcmp(etiqueta,"NULL") != 0)
                        {
                            if(bandTabsim == 1)
                            {
                                fseek(fdTabsim,0,2);
                                fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                            }
                        }
                        bytes=2;
                        archAux.Valor+=bytes;
                        itoa(archAux.Valor,cadAuxOp,16);
                        strupr(cadAuxOp);
                        longOperando=strlen(cadAuxOp);
                        n= 4 - longOperando;
                        if(n > 0)
                        {
                            k=0;
                            for(i=0; i < n; i++)
                            {
                                archAux.CONTLOC[i]='0';
                                k++;
                            }
                            j=0;
                            for(i=k; i<4 ; i++)
                            {
                                archAux.CONTLOC[i]=cadAuxOp[j];
                                j++;
                            }
                        }
                        else
                            strcpy(archAux.CONTLOC,cadAuxOp);
                        acumDirectiva=1;
                    }
                    else
                        printf("\n\tError: Excede el Limite de la Directiva DW, Rango Valido: 0 a 65535");
                }
                else
                    printf("\n\tError: Base Numerica Octal Invalida,Caracteres validos 0,1,2,3,4,5,6,7");
            }
            else
            {
                if(operando[0] == '%')
                {
                    bandera=binario(operando);
                    if(bandera == 1)
                    {
                        valOperando=convierteHexadecimalDecimal(operando);
                        if((valOperando >= 0) && (valOperando <= 65535))
                        {
                            archAux.CONTLOC[4]='\0';
                            if(bandTemporal == 1)
                            {
                                fseek(fdTemp,0,2);
                                fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                bandDirectiva=1;
                            }
                            if(strcmp(etiqueta,"NULL") != 0)
                            {
                                if(bandTabsim == 1)
                                {
                                    fseek(fdTabsim,0,2);
                                    fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                }
                            }
                            bytes=2;
                            archAux.Valor+=bytes;
                            itoa(archAux.Valor,cadAuxOp,16);
                            strupr(cadAuxOp);
                            longOperando=strlen(cadAuxOp);
                            n= 4 - longOperando;
                            if(n > 0)
                            {
                                k=0;
                                for(i=0; i < n; i++)
                                {
                                    archAux.CONTLOC[i]='0';
                                    k++;
                                }
                                j=0;
                                for(i=k; i<4 ; i++)
                                {
                                    archAux.CONTLOC[i]=cadAuxOp[j];
                                    j++;
                                }
                            }
                            else
                                strcpy(archAux.CONTLOC,cadAuxOp);
                            acumDirectiva=1;
                        }
                        else
                            printf("\n\tError: Excede el Limite de la Directiva DW, Rango Valido: 0 a 65535");
                    }
                    else
                        printf("\n\tError: Base Numerica Binaria Invalida,Caracteres validos 0,1");
                }
                else
                {
                    if((operando[0] >= 48) && (operando[0] <= 57))
                    {
                        bandera=decimal(operando);
                        if(bandera == 1)
                        {
                            valOperando=atoi(operando);
                            if((valOperando >= 0) && (valOperando <= 65535))
                            {
                                archAux.CONTLOC[4]='\0';
                                if(bandTemporal == 1)
                                {
                                    fseek(fdTemp,0,2);
                                    fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                    bandDirectiva=1;
                                }
                                if(strcmp(etiqueta,"NULL") != 0)
                                {
                                    if(bandTabsim == 1)
                                    {
                                        fseek(fdTabsim,0,2);
                                        fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                    }
                                }
                                bytes=2;
                                archAux.Valor+=bytes;
                                itoa(archAux.Valor,cadAuxOp,16);
                                strupr(cadAuxOp);
                                longOperando=strlen(cadAuxOp);
                                n= 4 - longOperando;
                                if(n > 0)
                                {
                                    k=0;
                                    for(i=0; i < n; i++)
                                    {
                                        archAux.CONTLOC[i]='0';
                                        k++;
                                    }
                                    j=0;
                                    for(i=k; i<4 ; i++)
                                    {
                                        archAux.CONTLOC[i]=cadAuxOp[j];
                                        j++;
                                    }
                                }
                                else
                                    strcpy(archAux.CONTLOC,cadAuxOp);
                                acumDirectiva=1;
                            }
                            else
                                printf("\n\tError: Excede el Limite de la Directiva DW, Rango Valido: 0 a 65535");
                        }
                        else
                            printf("\n\tError: Base Numerica Decimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9");
                    }
                    else
                    {
                        if(operando[0] == '\0')
                        {
                            bandError=1;
                            printf("\n\tError: La Directiva DW debe tener Operando");
                        }
                    }
                }
            }
        }
    }
    else
    {
        if(bandDirectiva == 2)
        {
            if(operando[0] == '$')
            {
                bandera=hexadecimal(operando);
                if(bandera == 1)
                {
                    valOperando=convierteHexadecimalDecimal(operando);
                    if((valOperando >= 0) && (valOperando <= 255))
                    {
                        archAux.CONTLOC[4]='\0';
                        if(bandTemporal == 1)
                        {
                            fseek(fdTemp,0,2);
                            fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                            bandDirectiva=1;
                        }
                        if(strcmp(etiqueta,"NULL") != 0)
                        {
                            if(bandTabsim == 1)
                            {
                                fseek(fdTabsim,0,2);
                                fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                            }
                        }
                        bytes=1;
                        archAux.Valor+=bytes;
                        itoa(archAux.Valor,cadAuxOp,16);
                        strupr(cadAuxOp);
                        longOperando=strlen(cadAuxOp);
                        n= 4 - longOperando;
                        if(n > 0)
                        {
                            k=0;
                            for(i=0; i < n; i++)
                            {
                                archAux.CONTLOC[i]='0';
                                k++;
                            }
                            j=0;
                            for(i=k; i<4 ; i++)
                            {
                                archAux.CONTLOC[i]=cadAuxOp[j];
                                j++;
                            }
                        }
                        else
                            strcpy(archAux.CONTLOC,cadAuxOp);
                        acumDirectiva=1;
                    }
                    else
                        printf("\n\tError: Excede el Limite de la Directiva DB, Rango Valido: 0 a 65535");
                }
                else
                    printf("\n\tError: Base Numerica Hexadecimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F");
            }
            else
            {
                if(operando[0] == '@')
                {
                    bandera=octal(operando);
                    if(bandera == 1)
                    {
                        valOperando=convierteHexadecimalDecimal(operando);
                        if((valOperando >= 0) && (valOperando <= 255))
                        {
                            archAux.CONTLOC[4]='\0';
                            if(bandTemporal == 1)
                            {
                                fseek(fdTemp,0,2);
                                fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                bandDirectiva=1;
                            }
                            if(strcmp(etiqueta,"NULL") != 0)
                            {
                                if(bandTabsim == 1)
                                {
                                    fseek(fdTabsim,0,2);
                                    fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                }
                            }
                            bytes=1;
                            archAux.Valor+=bytes;
                            itoa(archAux.Valor,cadAuxOp,16);
                            strupr(cadAuxOp);
                            longOperando=strlen(cadAuxOp);
                            n= 4 - longOperando;
                            if(n > 0)
                            {
                                k=0;
                                for(i=0; i < n; i++)
                                {
                                    archAux.CONTLOC[i]='0';
                                    k++;
                                }
                                j=0;
                                for(i=k; i<4 ; i++)
                                {
                                    archAux.CONTLOC[i]=cadAuxOp[j];
                                    j++;
                                }
                            }
                            else
                                strcpy(archAux.CONTLOC,cadAuxOp);
                            acumDirectiva=1;
                        }
                        else
                            printf("\n\tError: Excede el Limite de la Directiva DB, Rango Valido: 0 a 65535");
                    }
                    else
                        printf("\n\tError: Base Numerica Octal Invalida,Caracteres validos 0,1,2,3,4,5,6,7");
                }
                else
                {
                    if(operando[0] == '%')
                    {
                        bandera=binario(operando);
                        if(bandera == 1)
                        {
                            valOperando=convierteHexadecimalDecimal(operando);
                            if((valOperando >= 0) && (valOperando <= 255))
                            {
                                archAux.CONTLOC[4]='\0';
                                if(bandTemporal == 1)
                                {
                                    fseek(fdTemp,0,2);
                                    fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                    bandDirectiva=1;
                                }
                                if(strcmp(etiqueta,"NULL") != 0)
                                {
                                    if(bandTabsim == 1)
                                    {
                                        fseek(fdTabsim,0,2);
                                        fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                    }
                                }
                                bytes=1;
                                archAux.Valor+=bytes;
                                itoa(archAux.Valor,cadAuxOp,16);
                                strupr(cadAuxOp);
                                longOperando=strlen(cadAuxOp);
                                n= 4 - longOperando;
                                if(n > 0)
                                {
                                    k=0;
                                    for(i=0; i < n; i++)
                                    {
                                        archAux.CONTLOC[i]='0';
                                        k++;
                                    }
                                    j=0;
                                    for(i=k; i<4 ; i++)
                                    {
                                        archAux.CONTLOC[i]=cadAuxOp[j];
                                        j++;
                                    }
                                }
                                else
                                    strcpy(archAux.CONTLOC,cadAuxOp);
                                acumDirectiva=1;
                            }
                            else
                                printf("\n\tError: Excede el Limite de la Directiva DB, Rango Valido: 0 a 65535");
                        }
                        else
                            printf("\n\tError: Base Numerica Binaria Invalida,Caracteres validos 0,1");
                    }
                    else
                    {
                        if((operando[0] >= 48) && (operando[0] <= 57))
                        {
                            bandera=decimal(operando);
                            if(bandera == 1)
                            {
                                valOperando=atoi(operando);
                                if((valOperando >= 0) && (valOperando <= 255))
                                {
                                    archAux.CONTLOC[4]='\0';
                                    if(bandTemporal == 1)
                                    {
                                        fseek(fdTemp,0,2);
                                        fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                        bandDirectiva=1;
                                    }
                                    if(strcmp(etiqueta,"NULL") != 0)
                                    {
                                        if(bandTabsim == 1)
                                        {
                                            fseek(fdTabsim,0,2);
                                            fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                        }
                                    }
                                    bytes=1;
                                    archAux.Valor+=bytes;
                                    itoa(archAux.Valor,cadAuxOp,16);
                                    strupr(cadAuxOp);
                                    longOperando=strlen(cadAuxOp);
                                    n= 4 - longOperando;
                                    if(n > 0)
                                    {
                                        k=0;
                                        for(i=0; i < n; i++)
                                        {
                                            archAux.CONTLOC[i]='0';
                                            k++;
                                        }
                                        j=0;
                                        for(i=k; i<4 ; i++)
                                        {
                                            archAux.CONTLOC[i]=cadAuxOp[j];
                                            j++;
                                        }
                                    }
                                    else
                                        strcpy(archAux.CONTLOC,cadAuxOp);
                                    acumDirectiva=1;
                                }
                                else
                                    printf("\n\tError: Excede el Limite de la Directiva DB, Rango Valido: 0 a 65535");
                            }
                            else
                                printf("\n\tError: Base Numerica Decimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9");
                        }
                        else
                        {
                            if(operando[0] == '\0')
                            {
                                bandError=1;
                                printf("\n\tError: La Directiva DB debe tener Operando");
                            }
                        }
                    }
                }
            }
        }
        else
        {
            if(bandDirectiva == 3)
            {
                if(operando[0] == '$')
                {
                    bandera=hexadecimal(operando);
                    if(bandera == 1)
                    {
                        valOperando=convierteHexadecimalDecimal(operando);
                        if((valOperando >= 0) && (valOperando <= 65535))
                        {
                            archAux.CONTLOC[4]='\0';
                            if(bandTemporal == 1)
                            {
                                fseek(fdTemp,0,2);
                                fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                bandDirectiva=1;
                            }
                            if(strcmp(etiqueta,"NULL") != 0)
                            {
                                if(bandTabsim == 1)
                                {
                                    fseek(fdTabsim,0,2);
                                    fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                }
                            }
                            bytes=2;
                            archAux.Valor+=bytes;
                            itoa(archAux.Valor,cadAuxOp,16);
                            strupr(cadAuxOp);
                            longOperando=strlen(cadAuxOp);
                            n= 4 - longOperando;
                            if(n > 0)
                            {
                                k=0;
                                for(i=0; i < n; i++)
                                {
                                    archAux.CONTLOC[i]='0';
                                    k++;
                                }
                                j=0;
                                for(i=k; i<4 ; i++)
                                {
                                    archAux.CONTLOC[i]=cadAuxOp[j];
                                    j++;
                                }
                            }
                            else
                                strcpy(archAux.CONTLOC,cadAuxOp);
                            acumDirectiva=1;
                        }
                        else
                            printf("\n\tError: Excede el Limite de la Directiva DC.W, Rango Valido: 0 a 65535");
                    }
                    else
                        printf("\n\tError: Base Numerica Hexadecimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F");
                }
                else
                {
                    if(operando[0] == '@')
                    {
                        bandera=octal(operando);
                        if(bandera == 1)
                        {
                            valOperando=convierteHexadecimalDecimal(operando);
                            if((valOperando >= 0) && (valOperando <= 65535))
                            {
                                archAux.CONTLOC[4]='\0';
                                if(bandTemporal == 1)
                                {
                                    fseek(fdTemp,0,2);
                                    fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                    bandDirectiva=1;
                                }
                                if(strcmp(etiqueta,"NULL") != 0)
                                {
                                    if(bandTabsim == 1)
                                    {
                                        fseek(fdTabsim,0,2);
                                        fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                    }
                                }
                                bytes=2;
                                archAux.Valor+=bytes;
                                itoa(archAux.Valor,cadAuxOp,16);
                                strupr(cadAuxOp);
                                longOperando=strlen(cadAuxOp);
                                n= 4 - longOperando;
                                if(n > 0)
                                {
                                    k=0;
                                    for(i=0; i < n; i++)
                                    {
                                        archAux.CONTLOC[i]='0';
                                        k++;
                                    }
                                    j=0;
                                    for(i=k; i<4 ; i++)
                                    {
                                        archAux.CONTLOC[i]=cadAuxOp[j];
                                        j++;
                                    }
                                }
                                else
                                    strcpy(archAux.CONTLOC,cadAuxOp);
                                acumDirectiva=1;
                            }
                            else
                                printf("\n\tError: Excede el Limite de la Directiva DC.W, Rango Valido: 0 a 65535");
                        }
                        else
                            printf("\n\tError: Base Numerica Octal Invalida,Caracteres validos 0,1,2,3,4,5,6,7");
                    }
                    else
                    {
                        if(operando[0] == '%')
                        {
                            bandera=binario(operando);
                            if(bandera == 1)
                            {
                                valOperando=convierteHexadecimalDecimal(operando);
                                if((valOperando >= 0) && (valOperando <= 65535))
                                {
                                    archAux.CONTLOC[4]='\0';
                                    if(bandTemporal == 1)
                                    {
                                        fseek(fdTemp,0,2);
                                        fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                        bandDirectiva=1;
                                    }
                                    if(strcmp(etiqueta,"NULL") != 0)
                                    {
                                        if(bandTabsim == 1)
                                        {
                                            fseek(fdTabsim,0,2);
                                            fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                        }
                                    }
                                    bytes=2;
                                    archAux.Valor+=bytes;
                                    itoa(archAux.Valor,cadAuxOp,16);
                                    strupr(cadAuxOp);
                                    longOperando=strlen(cadAuxOp);
                                    n= 4 - longOperando;
                                    if(n > 0)
                                    {
                                        k=0;
                                        for(i=0; i < n; i++)
                                        {
                                            archAux.CONTLOC[i]='0';
                                            k++;
                                        }
                                        j=0;
                                        for(i=k; i<4 ; i++)
                                        {
                                            archAux.CONTLOC[i]=cadAuxOp[j];
                                            j++;
                                        }
                                    }
                                    else
                                        strcpy(archAux.CONTLOC,cadAuxOp);
                                    acumDirectiva=1;
                                }
                                else
                                    printf("\n\tError: Excede el Limite de la Directiva DC.W, Rango Valido: 0 a 65535");
                            }
                            else
                                printf("\n\tError: Base Numerica Binaria Invalida,Caracteres validos 0,1");
                        }
                        else
                        {
                            if((operando[0] >= 48) && (operando[0] <= 57))
                            {
                                bandera=decimal(operando);
                                if(bandera == 1)
                                {
                                    valOperando=atoi(operando);
                                    if((valOperando >= 0) && (valOperando <= 65535))
                                    {
                                        archAux.CONTLOC[4]='\0';
                                        if(bandTemporal == 1)
                                        {
                                            fseek(fdTemp,0,2);
                                            fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                            bandDirectiva=1;
                                        }
                                        if(strcmp(etiqueta,"NULL") != 0)
                                        {
                                            if(bandTabsim == 1)
                                            {
                                                fseek(fdTabsim,0,2);
                                                fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                            }
                                        }
                                        bytes=2;
                                        archAux.Valor+=bytes;
                                        itoa(archAux.Valor,cadAuxOp,16);
                                        strupr(cadAuxOp);
                                        longOperando=strlen(cadAuxOp);
                                        n= 4 - longOperando;
                                        if(n > 0)
                                        {
                                            k=0;
                                            for(i=0; i < n; i++)
                                            {
                                                archAux.CONTLOC[i]='0';
                                                k++;
                                            }
                                            j=0;
                                            for(i=k; i<4 ; i++)
                                            {
                                                archAux.CONTLOC[i]=cadAuxOp[j];
                                                j++;
                                            }
                                        }
                                        else
                                            strcpy(archAux.CONTLOC,cadAuxOp);
                                        acumDirectiva=1;
                                    }
                                    else
                                        printf("\n\tError: Excede el Limite de la Directiva DC.W, Rango Valido: 0 a 65535");
                                }
                                else
                                    printf("\n\tError: Base Numerica Decimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9");
                            }
                            else
                            {
                                if(operando[0] == '\0')
                                {
                                    bandError=1;
                                    printf("\n\tError: La Directiva DC.W debe tener Operando");
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                if(bandDirectiva == 4)
                {
                    if(operando[0] == '$')
                    {
                        bandera=hexadecimal(operando);
                        if(bandera == 1)
                        {
                            valOperando=convierteHexadecimalDecimal(operando);
                            if((valOperando >= 0) && (valOperando <= 255))
                            {
                                archAux.CONTLOC[4]='\0';
                                if(bandTemporal == 1)
                                {
                                    fseek(fdTemp,0,2);
                                    fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                    bandDirectiva=1;
                                }
                                if(strcmp(etiqueta,"NULL") != 0)
                                {
                                    if(bandTabsim == 1)
                                    {
                                        fseek(fdTabsim,0,2);
                                        fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                    }
                                }
                                bytes=1;
                                archAux.Valor+=bytes;
                                itoa(archAux.Valor,cadAuxOp,16);
                                strupr(cadAuxOp);
                                longOperando=strlen(cadAuxOp);
                                n= 4 - longOperando;
                                if(n > 0)
                                {
                                    k=0;
                                    for(i=0; i < n; i++)
                                    {
                                        archAux.CONTLOC[i]='0';
                                        k++;
                                    }
                                    j=0;
                                    for(i=k; i<4 ; i++)
                                    {
                                        archAux.CONTLOC[i]=cadAuxOp[j];
                                        j++;
                                    }
                                }
                                else
                                    strcpy(archAux.CONTLOC,cadAuxOp);
                                acumDirectiva=1;
                            }
                            else
                                printf("\n\tError: Excede el Limite de la Directiva DC.B, Rango Valido: 0 a 65535");
                        }
                        else
                            printf("\n\tError: Base Numerica Hexadecimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F");
                    }
                    else
                    {
                        if(operando[0] == '@')
                        {
                            bandera=octal(operando);
                            if(bandera == 1)
                            {
                                valOperando=convierteHexadecimalDecimal(operando);
                                if((valOperando >= 0) && (valOperando <= 255))
                                {
                                    archAux.CONTLOC[4]='\0';
                                    if(bandTemporal == 1)
                                    {
                                        fseek(fdTemp,0,2);
                                        fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                        bandDirectiva=1;
                                    }
                                    if(strcmp(etiqueta,"NULL") != 0)
                                    {
                                        if(bandTabsim == 1)
                                        {
                                            fseek(fdTabsim,0,2);
                                            fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                        }
                                    }
                                    bytes=1;
                                    archAux.Valor+=bytes;
                                    itoa(archAux.Valor,cadAuxOp,16);
                                    strupr(cadAuxOp);
                                    longOperando=strlen(cadAuxOp);
                                    n= 4 - longOperando;
                                    if(n > 0)
                                    {
                                        k=0;
                                        for(i=0; i < n; i++)
                                        {
                                            archAux.CONTLOC[i]='0';
                                            k++;
                                        }
                                        j=0;
                                        for(i=k; i<4 ; i++)
                                        {
                                            archAux.CONTLOC[i]=cadAuxOp[j];
                                            j++;
                                        }
                                    }
                                    else
                                        strcpy(archAux.CONTLOC,cadAuxOp);
                                    acumDirectiva=1;
                                }
                                else
                                    printf("\n\tError: Excede el Limite de la Directiva DC.B, Rango Valido: 0 a 65535");
                            }
                            else
                                printf("\n\tError: Base Numerica Octal Invalida,Caracteres validos 0,1,2,3,4,5,6,7");
                        }
                        else
                        {
                            if(operando[0] == '%')
                            {
                                bandera=binario(operando);
                                if(bandera == 1)
                                {
                                    valOperando=convierteHexadecimalDecimal(operando);
                                    if((valOperando >= 0) && (valOperando <= 255))
                                    {
                                        archAux.CONTLOC[4]='\0';
                                        if(bandTemporal == 1)
                                        {
                                            fseek(fdTemp,0,2);
                                            fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                            bandDirectiva=1;
                                        }
                                        if(strcmp(etiqueta,"NULL") != 0)
                                        {
                                            if(bandTabsim == 1)
                                            {
                                                fseek(fdTabsim,0,2);
                                                fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                            }
                                        }
                                        bytes=1;
                                        archAux.Valor+=bytes;
                                        itoa(archAux.Valor,cadAuxOp,16);
                                        strupr(cadAuxOp);
                                        longOperando=strlen(cadAuxOp);
                                        n= 4 - longOperando;
                                        if(n > 0)
                                        {
                                            k=0;
                                            for(i=0; i < n; i++)
                                            {
                                                archAux.CONTLOC[i]='0';
                                                k++;
                                            }
                                            j=0;
                                            for(i=k; i<4 ; i++)
                                            {
                                                archAux.CONTLOC[i]=cadAuxOp[j];
                                                j++;
                                            }
                                        }
                                        else
                                            strcpy(archAux.CONTLOC,cadAuxOp);
                                        acumDirectiva=1;
                                    }
                                    else
                                        printf("\n\tError: Excede el Limite de la Directiva DC.B, Rango Valido: 0 a 65535");
                                }
                                else
                                    printf("\n\tError: Base Numerica Binaria Invalida,Caracteres validos 0,1");
                            }
                            else
                            {
                                if((operando[0] >= 48) && (operando[0] <= 57))
                                {
                                    bandera=decimal(operando);
                                    if(bandera == 1)
                                    {
                                        valOperando=atoi(operando);
                                        if((valOperando >= 0) && (valOperando <= 255))
                                        {
                                            archAux.CONTLOC[4]='\0';
                                            if(bandTemporal == 1)
                                            {
                                                fseek(fdTemp,0,2);
                                                fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                                bandDirectiva=1;
                                            }
                                            if(strcmp(etiqueta,"NULL") != 0)
                                            {
                                                if(bandTabsim == 1)
                                                {
                                                    fseek(fdTabsim,0,2);
                                                    fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                                }
                                            }
                                            bytes=1;
                                            archAux.Valor+=bytes;
                                            itoa(archAux.Valor,cadAuxOp,16);
                                            strupr(cadAuxOp);
                                            longOperando=strlen(cadAuxOp);
                                            n= 4 - longOperando;
                                            if(n > 0)
                                            {
                                                k=0;
                                                for(i=0; i < n; i++)
                                                {
                                                    archAux.CONTLOC[i]='0';
                                                    k++;
                                                }
                                                j=0;
                                                for(i=k; i<4 ; i++)
                                                {
                                                    archAux.CONTLOC[i]=cadAuxOp[j];
                                                    j++;
                                                }
                                            }
                                            else
                                                strcpy(archAux.CONTLOC,cadAuxOp);
                                            acumDirectiva=1;
                                        }
                                        else
                                            printf("\n\tError: Excede el Limite de la Directiva DC.B, Rango Valido: 0 a 65535");
                                    }
                                    else
                                        printf("\n\tError: Base Numerica Decimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9");
                                }
                                else
                                {
                                    if(operando[0] == '\0')
                                    {
                                        bandError=1;
                                        printf("\n\tError: La Directiva DB debe tener Operando");
                                    }
                                }
                            }
                        }
                    }
                }
                else
                {
                    if(bandDirectiva == 5)
                    {
                        if(operando[0] == '$')
                        {
                            bandera=hexadecimal(operando);
                            if(bandera == 1)
                            {
                                valOperando=convierteHexadecimalDecimal(operando);
                                if((valOperando >= 0) && (valOperando <= 255))
                                {
                                    archAux.CONTLOC[4]='\0';
                                    if(bandTemporal == 1)
                                    {
                                        fseek(fdTemp,0,2);
                                        fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                        bandDirectiva=1;
                                    }
                                    if(strcmp(etiqueta,"NULL") != 0)
                                    {
                                        if(bandTabsim == 1)
                                        {
                                            fseek(fdTabsim,0,2);
                                            fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                        }
                                    }
                                    bytes=1;
                                    archAux.Valor+=bytes;
                                    itoa(archAux.Valor,cadAuxOp,16);
                                    strupr(cadAuxOp);
                                    longOperando=strlen(cadAuxOp);
                                    n= 4 - longOperando;
                                    if(n > 0)
                                    {
                                        k=0;
                                        for(i=0; i < n; i++)
                                        {
                                            archAux.CONTLOC[i]='0';
                                            k++;
                                        }
                                        j=0;
                                        for(i=k; i<4 ; i++)
                                        {
                                            archAux.CONTLOC[i]=cadAuxOp[j];
                                            j++;
                                        }
                                    }
                                    else
                                        strcpy(archAux.CONTLOC,cadAuxOp);
                                    acumDirectiva=1;
                                }
                                else
                                    printf("\n\tError: Excede el Limite de la Directiva FCB, Rango Valido: 0 a 65535");
                            }
                            else
                                printf("\n\tError: Base Numerica Hexadecimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F");
                        }
                        else
                        {
                            if(operando[0] == '@')
                            {
                                bandera=octal(operando);
                                if(bandera == 1)
                                {
                                    valOperando=convierteHexadecimalDecimal(operando);
                                    if((valOperando >= 0) && (valOperando <= 255))
                                    {
                                        archAux.CONTLOC[4]='\0';
                                        if(bandTemporal == 1)
                                        {
                                            fseek(fdTemp,0,2);
                                            fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                            bandDirectiva=1;
                                        }
                                        if(strcmp(etiqueta,"NULL") != 0)
                                        {
                                            if(bandTabsim == 1)
                                            {
                                                fseek(fdTabsim,0,2);
                                                fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                            }
                                        }
                                        bytes=1;
                                        archAux.Valor+=bytes;
                                        itoa(archAux.Valor,cadAuxOp,16);
                                        strupr(cadAuxOp);
                                        longOperando=strlen(cadAuxOp);
                                        n= 4 - longOperando;
                                        if(n > 0)
                                        {
                                            k=0;
                                            for(i=0; i < n; i++)
                                            {
                                                archAux.CONTLOC[i]='0';
                                                k++;
                                            }
                                            j=0;
                                            for(i=k; i<4 ; i++)
                                            {
                                                archAux.CONTLOC[i]=cadAuxOp[j];
                                                j++;
                                            }
                                        }
                                        else
                                            strcpy(archAux.CONTLOC,cadAuxOp);
                                        acumDirectiva=1;
                                    }
                                    else
                                        printf("\n\tError: Excede el Limite de la Directiva FCB, Rango Valido: 0 a 65535");
                                }
                                else
                                    printf("\n\tError: Base Numerica Octal Invalida,Caracteres validos 0,1,2,3,4,5,6,7");
                            }
                            else
                            {
                                if(operando[0] == '%')
                                {
                                    bandera=binario(operando);
                                    if(bandera == 1)
                                    {
                                        valOperando=convierteHexadecimalDecimal(operando);
                                        if((valOperando >= 0) && (valOperando <= 255))
                                        {
                                            archAux.CONTLOC[4]='\0';
                                            if(bandTemporal == 1)
                                            {
                                                fseek(fdTemp,0,2);
                                                fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                                bandDirectiva=1;
                                            }
                                            if(strcmp(etiqueta,"NULL") != 0)
                                            {
                                                if(bandTabsim == 1)
                                                {
                                                    fseek(fdTabsim,0,2);
                                                    fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                                }
                                            }
                                            bytes=1;
                                            archAux.Valor+=bytes;
                                            itoa(archAux.Valor,cadAuxOp,16);
                                            strupr(cadAuxOp);
                                            longOperando=strlen(cadAuxOp);
                                            n= 4 - longOperando;
                                            if(n > 0)
                                            {
                                                k=0;
                                                for(i=0; i < n; i++)
                                                {
                                                    archAux.CONTLOC[i]='0';
                                                    k++;
                                                }
                                                j=0;
                                                for(i=k; i<4 ; i++)
                                                {
                                                    archAux.CONTLOC[i]=cadAuxOp[j];
                                                    j++;
                                                }
                                            }
                                            else
                                                strcpy(archAux.CONTLOC,cadAuxOp);
                                            acumDirectiva=1;
                                        }
                                        else
                                            printf("\n\tError: Excede el Limite de la Directiva FCB, Rango Valido: 0 a 65535");
                                    }
                                    else
                                        printf("\n\tError: Base Numerica Binaria Invalida,Caracteres validos 0,1");
                                }
                                else
                                {
                                    if((operando[0] >= 48) && (operando[0] <= 57))
                                    {
                                        bandera=decimal(operando);
                                        if(bandera == 1)
                                        {
                                            valOperando=atoi(operando);
                                            if((valOperando >= 0) && (valOperando <= 255))
                                            {
                                                archAux.CONTLOC[4]='\0';
                                                if(bandTemporal == 1)
                                                {
                                                    fseek(fdTemp,0,2);
                                                    fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                                    bandDirectiva=1;
                                                }
                                                if(strcmp(etiqueta,"NULL") != 0)
                                                {
                                                    if(bandTabsim == 1)
                                                    {
                                                        fseek(fdTabsim,0,2);
                                                        fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                                    }
                                                }
                                                bytes=1;
                                                archAux.Valor+=bytes;
                                                itoa(archAux.Valor,cadAuxOp,16);
                                                strupr(cadAuxOp);
                                                longOperando=strlen(cadAuxOp);
                                                n= 4 - longOperando;
                                                if(n > 0)
                                                {
                                                    k=0;
                                                    for(i=0; i < n; i++)
                                                    {
                                                        archAux.CONTLOC[i]='0';
                                                        k++;
                                                    }
                                                    j=0;
                                                    for(i=k; i<4; i++)
                                                    {
                                                        archAux.CONTLOC[i]=cadAuxOp[j];
                                                        j++;
                                                    }
                                                }
                                                else
                                                    strcpy(archAux.CONTLOC,cadAuxOp);
                                                acumDirectiva=1;
                                            }
                                            else
                                                printf("\n\tError: Excede el Limite de la Directiva FCB, Rango Valido: 0 a 65535");
                                        }
                                        else
                                            printf("\n\tError: Base Numerica Decimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9");
                                    }
                                    else
                                    {
                                        if(operando[0] == '\0')
                                        {
                                            bandError=1;
                                            printf("\n\tError: La Directiva FCB debe tener Operando");
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        if(bandDirectiva == 6)
                        {
                            if(operando[0] == '$')
                            {
                                bandera=hexadecimal(operando);
                                if(bandera == 1)
                                {
                                    valOperando=convierteHexadecimalDecimal(operando);
                                    if((valOperando >= 0) && (valOperando <= 65535))
                                    {
                                        archAux.CONTLOC[4]='\0';
                                        if(bandTemporal == 1)
                                        {
                                            fseek(fdTemp,0,2);
                                            fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                            bandDirectiva=1;
                                        }
                                        if(strcmp(etiqueta,"NULL") != 0)
                                        {
                                            if(bandTabsim == 1)
                                            {
                                                fseek(fdTabsim,0,2);
                                                fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                            }
                                        }
                                        bytes=2;
                                        archAux.Valor+=bytes;
                                        itoa(archAux.Valor,cadAuxOp,16);
                                        strupr(cadAuxOp);
                                        longOperando=strlen(cadAuxOp);
                                        n= 4 - longOperando;
                                        if(n > 0)
                                        {
                                            k=0;
                                            for(i=0; i < n; i++)
                                            {
                                                archAux.CONTLOC[i]='0';
                                                k++;
                                            }
                                            j=0;
                                            for(i=k; i<4 ; i++)
                                            {
                                                archAux.CONTLOC[i]=cadAuxOp[j];
                                                j++;
                                            }
                                        }
                                        else
                                            strcpy(archAux.CONTLOC,cadAuxOp);
                                        acumDirectiva=1;
                                    }
                                    else
                                        printf("\n\tError: Excede el Limite de la Directiva FDB, Rango Valido: 0 a 65535");
                                }
                                else
                                    printf("\n\tError: Base Numerica Hexadecimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F");
                            }
                            else
                            {
                                if(operando[0] == '@')
                                {
                                    bandera=octal(operando);
                                    if(bandera == 1)
                                    {
                                        valOperando=convierteHexadecimalDecimal(operando);
                                        if((valOperando >= 0) && (valOperando <= 65535))
                                        {
                                            archAux.CONTLOC[4]='\0';
                                            if(bandTemporal == 1)
                                            {
                                                fseek(fdTemp,0,2);
                                                fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                                bandDirectiva=1;
                                            }
                                            if(strcmp(etiqueta,"NULL") != 0)
                                            {
                                                if(bandTabsim == 1)
                                                {
                                                    fseek(fdTabsim,0,2);
                                                    fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                                }
                                            }
                                            bytes=2;
                                            archAux.Valor+=bytes;
                                            itoa(archAux.Valor,cadAuxOp,16);
                                            strupr(cadAuxOp);
                                            longOperando=strlen(cadAuxOp);
                                            n= 4 - longOperando;
                                            if(n > 0)
                                            {
                                                k=0;
                                                for(i=0; i < n; i++)
                                                {
                                                    archAux.CONTLOC[i]='0';
                                                    k++;
                                                }
                                                j=0;
                                                for(i=k; i<4 ; i++)
                                                {
                                                    archAux.CONTLOC[i]=cadAuxOp[j];
                                                    j++;
                                                }
                                            }
                                            else
                                                strcpy(archAux.CONTLOC,cadAuxOp);
                                            acumDirectiva=1;
                                        }
                                        else
                                            printf("\n\tError: Excede el Limite de la Directiva FDB, Rango Valido: 0 a 65535");
                                    }
                                    else
                                        printf("\n\tError: Base Numerica Octal Invalida,Caracteres validos 0,1,2,3,4,5,6,7");
                                }
                                else
                                {
                                    if(operando[0] == '%')
                                    {
                                        bandera=binario(operando);
                                        if(bandera == 1)
                                        {
                                            valOperando=convierteHexadecimalDecimal(operando);
                                            if((valOperando >= 0) && (valOperando <= 65535))
                                            {
                                                archAux.CONTLOC[4]='\0';
                                                if(bandTemporal == 1)
                                                {
                                                    fseek(fdTemp,0,2);
                                                    fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                                    bandDirectiva=1;
                                                }
                                                if(strcmp(etiqueta,"NULL") != 0)
                                                {
                                                    if(bandTabsim == 1)
                                                    {
                                                        fseek(fdTabsim,0,2);
                                                        fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                                    }
                                                }
                                                bytes=2;
                                                archAux.Valor+=bytes;
                                                itoa(archAux.Valor,cadAuxOp,16);
                                                strupr(cadAuxOp);
                                                longOperando=strlen(cadAuxOp);
                                                n= 4 - longOperando;
                                                if(n > 0)
                                                {
                                                    k=0;
                                                    for(i=0; i < n; i++)
                                                    {
                                                        archAux.CONTLOC[i]='0';
                                                        k++;
                                                    }
                                                    j=0;
                                                    for(i=k; i<4 ; i++)
                                                    {
                                                        archAux.CONTLOC[i]=cadAuxOp[j];
                                                        j++;
                                                    }
                                                }
                                                else
                                                    strcpy(archAux.CONTLOC,cadAuxOp);
                                                acumDirectiva=1;
                                            }
                                            else
                                                printf("\n\tError: Excede el Limite de la Directiva FDB, Rango Valido: 0 a 65535");
                                        }
                                        else
                                            printf("\n\tError: Base Numerica Binaria Invalida,Caracteres validos 0,1");
                                    }
                                    else
                                    {
                                        if((operando[0] >= 48) && (operando[0] <= 57))
                                        {
                                            bandera=decimal(operando);
                                            if(bandera == 1)
                                            {
                                                valOperando=atoi(operando);
                                                if((valOperando >= 0) && (valOperando <= 65535))
                                                {
                                                    archAux.CONTLOC[4]='\0';
                                                    if(bandTemporal == 1)
                                                    {
                                                        fseek(fdTemp,0,2);
                                                        fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                                        bandDirectiva=1;
                                                    }
                                                    if(strcmp(etiqueta,"NULL") != 0)
                                                    {
                                                        if(bandTabsim == 1)
                                                        {
                                                            fseek(fdTabsim,0,2);
                                                            fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                                        }
                                                    }
                                                    bytes=2;
                                                    archAux.Valor+=bytes;
                                                    itoa(archAux.Valor,cadAuxOp,16);
                                                    strupr(cadAuxOp);
                                                    longOperando=strlen(cadAuxOp);
                                                    n= 4 - longOperando;
                                                    if(n > 0)
                                                    {
                                                        k=0;
                                                        for(i=0; i < n; i++)
                                                        {
                                                            archAux.CONTLOC[i]='0';
                                                            k++;
                                                        }
                                                        j=0;
                                                        for(i=k; i<4 ; i++)
                                                        {
                                                            archAux.CONTLOC[i]=cadAuxOp[j];
                                                            j++;
                                                        }
                                                    }
                                                    else
                                                        strcpy(archAux.CONTLOC,cadAuxOp);
                                                    acumDirectiva=1;
                                                }
                                                else
                                                    printf("\n\tError: Excede el Limite de la Directiva FDB, Rango Valido: 0 a 65535");
                                            }
                                            else
                                                printf("\n\tError: Base Numerica Decimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9");
                                        }
                                        else
                                        {
                                            if(operando[0] == '\0')
                                            {
                                                bandError=1;
                                                printf("\n\tError: La Directiva FDB debe tener Operando");
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            if(bandDirectiva == 7)
                            {
                                if((operando[0] == 34) && (operando[strlen(operando) - 1] == 34))
                                {
                                    archAux.CONTLOC[4]='\0';
                                    if(bandTemporal == 1)
                                    {
                                        fseek(fdTemp,0,2);
                                        fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                        bandDirectiva=1;
                                    }
                                    if(strcmp(etiqueta,"NULL") != 0)
                                    {
                                        if(bandTabsim == 1)
                                        {
                                            fseek(fdTabsim,0,2);
                                            fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                        }
                                    }
                                    bytes=strlen(operando) - 2;
                                    archAux.Valor+=bytes;
                                    itoa(archAux.Valor,cadAuxOp,16);
                                    strupr(cadAuxOp);
                                    longOperando=strlen(cadAuxOp);
                                    n= 4 - longOperando;
                                    if(n > 0)
                                    {
                                        k=0;
                                        for(i=0; i < n; i++)
                                        {
                                            archAux.CONTLOC[i]='0';
                                            k++;
                                        }
                                        j=0;
                                        for(i=k; i<4; i++)
                                        {
                                            archAux.CONTLOC[i]=cadAuxOp[j];
                                            j++;
                                        }
                                    }
                                    else
                                        strcpy(archAux.CONTLOC,cadAuxOp);
                                    acumDirectiva=1;
                                }
                                else
                                    printf("Error: \n\tLa Directiva FCC Necesita Comillas");
                            }
                            else
                            {
                                if(bandDirectiva == 8)
                                {
                                    if(operando[0] == '$')
                                    {
                                        bandera=hexadecimal(operando);
                                        if(bandera == 1)
                                        {
                                            valOperando=convierteHexadecimalDecimal(operando);
                                            if((valOperando >= 0) && (valOperando <= 65535))
                                            {
                                                archAux.CONTLOC[4]='\0';
                                                if(bandTemporal == 1)
                                                {
                                                    fseek(fdTemp,0,2);
                                                    fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                                    bandDirectiva=1;
                                                }
                                                if(strcmp(etiqueta,"NULL") != 0)
                                                {
                                                    if(bandTabsim == 1)
                                                    {
                                                        fseek(fdTabsim,0,2);
                                                        fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                                    }
                                                }
                                                bytes=valOperando*1;
                                                archAux.Valor+=bytes;
                                                itoa(archAux.Valor,cadAuxOp,16);
                                                strupr(cadAuxOp);
                                                longOperando=strlen(cadAuxOp);
                                                n= 4 - longOperando;
                                                if(n > 0)
                                                {
                                                    k=0;
                                                    for(i=0; i < n; i++)
                                                    {
                                                        archAux.CONTLOC[i]='0';
                                                        k++;
                                                    }
                                                    j=0;
                                                    for(i=k; i<4 ; i++)
                                                    {
                                                        archAux.CONTLOC[i]=cadAuxOp[j];
                                                        j++;
                                                    }
                                                }
                                                else
                                                    strcpy(archAux.CONTLOC,cadAuxOp);
                                                acumDirectiva=1;
                                            }
                                            else
                                                printf("\n\tError: Excede el Limite de la Directiva DS, Rango Valido: 0 a 65535");
                                        }
                                        else
                                            printf("\n\tError: Base Numerica Hexadecimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F");
                                    }
                                    else
                                    {
                                        if(operando[0] == '@')
                                        {
                                            bandera=octal(operando);
                                            if(bandera == 1)
                                            {
                                                valOperando=convierteHexadecimalDecimal(operando);
                                                if((valOperando >= 0) && (valOperando <= 65535))
                                                {
                                                    archAux.CONTLOC[4]='\0';
                                                    if(bandTemporal == 1)
                                                    {
                                                        fseek(fdTemp,0,2);
                                                        fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                                        bandDirectiva=1;
                                                    }
                                                    if(strcmp(etiqueta,"NULL") != 0)
                                                    {
                                                        if(bandTabsim == 1)
                                                        {
                                                            fseek(fdTabsim,0,2);
                                                            fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                                        }
                                                    }
                                                    bytes=valOperando*1;
                                                    archAux.Valor+=bytes;
                                                    itoa(archAux.Valor,cadAuxOp,16);
                                                    strupr(cadAuxOp);
                                                    longOperando=strlen(cadAuxOp);
                                                    n= 4 - longOperando;
                                                    if(n > 0)
                                                    {
                                                        k=0;
                                                        for(i=0; i < n; i++)
                                                        {
                                                            archAux.CONTLOC[i]='0';
                                                            k++;
                                                        }
                                                        j=0;
                                                        for(i=k; i<4 ; i++)
                                                        {
                                                            archAux.CONTLOC[i]=cadAuxOp[j];
                                                            j++;
                                                        }
                                                    }
                                                    else
                                                        strcpy(archAux.CONTLOC,cadAuxOp);
                                                    acumDirectiva=1;
                                                }
                                                else
                                                    printf("\n\tError: Excede el Limite de la Directiva DS, Rango Valido: 0 a 65535");
                                            }
                                            else
                                                printf("\n\tError: Base Numerica Octal Invalida,Caracteres validos 0,1,2,3,4,5,6,7");
                                        }
                                        else
                                        {
                                            if(operando[0] == '%')
                                            {
                                                bandera=binario(operando);
                                                if(bandera == 1)
                                                {
                                                    valOperando=convierteHexadecimalDecimal(operando);
                                                    if((valOperando >= 0) && (valOperando <= 65535))
                                                    {
                                                        archAux.CONTLOC[4]='\0';
                                                        if(bandTemporal == 1)
                                                        {
                                                            fseek(fdTemp,0,2);
                                                            fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                                            bandDirectiva=1;
                                                        }
                                                        if(strcmp(etiqueta,"NULL") != 0)
                                                        {
                                                            if(bandTabsim == 1)
                                                            {
                                                                fseek(fdTabsim,0,2);
                                                                fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                                            }
                                                        }
                                                        bytes=valOperando*1;
                                                        archAux.Valor+=bytes;
                                                        itoa(archAux.Valor,cadAuxOp,16);
                                                        strupr(cadAuxOp);
                                                        longOperando=strlen(cadAuxOp);
                                                        n= 4 - longOperando;
                                                        if(n > 0)
                                                        {
                                                            k=0;
                                                            for(i=0; i < n; i++)
                                                            {
                                                                archAux.CONTLOC[i]='0';
                                                                k++;
                                                            }
                                                            j=0;
                                                            for(i=k; i<4 ; i++)
                                                            {
                                                                archAux.CONTLOC[i]=cadAuxOp[j];
                                                                j++;
                                                            }
                                                        }
                                                        else
                                                            strcpy(archAux.CONTLOC,cadAuxOp);
                                                        acumDirectiva=1;
                                                    }
                                                    else
                                                        printf("\n\tError: Excede el Limite de la Directiva DS, Rango Valido: 0 a 65535");
                                                }
                                                else
                                                    printf("\n\tError: Base Numerica Binaria Invalida,Caracteres validos 0,1");
                                            }
                                            else
                                            {
                                                if((operando[0] >= 48) && (operando[0] <= 57))
                                                {
                                                    bandera=decimal(operando);
                                                    if(bandera == 1)
                                                    {
                                                        valOperando=atoi(operando);
                                                        if((valOperando >= 0) && (valOperando <= 65535))
                                                        {
                                                            archAux.CONTLOC[4]='\0';
                                                            if(bandTemporal == 1)
                                                            {
                                                                fseek(fdTemp,0,2);
                                                                fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                                                bandDirectiva=1;
                                                            }
                                                            if(strcmp(etiqueta,"NULL") != 0)
                                                            {
                                                                if(bandTabsim == 1)
                                                                {
                                                                    fseek(fdTabsim,0,2);
                                                                    fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                                                }
                                                            }
                                                            bytes=valOperando*1;
                                                            archAux.Valor+=bytes;
                                                            itoa(archAux.Valor,cadAuxOp,16);
                                                            strupr(cadAuxOp);
                                                            longOperando=strlen(cadAuxOp);
                                                            n= 4 - longOperando;
                                                            if(n > 0)
                                                            {
                                                                k=0;
                                                                for(i=0; i < n; i++)
                                                                {
                                                                    archAux.CONTLOC[i]='0';
                                                                    k++;
                                                                }
                                                                j=0;
                                                                for(i=k; i<4 ; i++)
                                                                {
                                                                    archAux.CONTLOC[i]=cadAuxOp[j];
                                                                    j++;
                                                                }
                                                            }
                                                            else
                                                                strcpy(archAux.CONTLOC,cadAuxOp);
                                                            acumDirectiva=1;
                                                        }
                                                        else
                                                            printf("\n\tError: Excede el Limite de la Directiva DS, Rango Valido: 0 a 65535");
                                                    }
                                                    else
                                                        printf("\n\tError: Base Numerica Decimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9");
                                                }
                                                else
                                                {
                                                    if(operando[0] == '\0')
                                                    {
                                                        bandError=1;
                                                        printf("\n\tError: La Directiva DS debe tener Operando");
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    if(bandDirectiva == 9)
                                    {
                                        if(operando[0] == '$')
                                        {
                                            bandera=hexadecimal(operando);
                                            if(bandera == 1)
                                            {
                                                valOperando=convierteHexadecimalDecimal(operando);
                                                if((valOperando >= 0) && (valOperando <= 65535))
                                                {
                                                    archAux.CONTLOC[4]='\0';
                                                    if(bandTemporal == 1)
                                                    {
                                                        fseek(fdTemp,0,2);
                                                        fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                                        bandDirectiva=1;
                                                    }
                                                    if(strcmp(etiqueta,"NULL") != 0)
                                                    {
                                                        if(bandTabsim == 1)
                                                        {
                                                            fseek(fdTabsim,0,2);
                                                            fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                                        }
                                                    }
                                                    bytes=valOperando*1;
                                                    archAux.Valor+=bytes;
                                                    itoa(archAux.Valor,cadAuxOp,16);
                                                    strupr(cadAuxOp);
                                                    longOperando=strlen(cadAuxOp);
                                                    n= 4 - longOperando;
                                                    if(n > 0)
                                                    {
                                                        k=0;
                                                        for(i=0; i < n; i++)
                                                        {
                                                            archAux.CONTLOC[i]='0';
                                                            k++;
                                                        }
                                                        j=0;
                                                        for(i=k; i<4 ; i++)
                                                        {
                                                            archAux.CONTLOC[i]=cadAuxOp[j];
                                                            j++;
                                                        }
                                                    }
                                                    else
                                                        strcpy(archAux.CONTLOC,cadAuxOp);
                                                    acumDirectiva=1;
                                                }
                                                else
                                                    printf("\n\tError: Excede el Limite de la Directiva DS.B, Rango Valido: 0 a 65535");
                                            }
                                            else
                                                printf("\n\tError: Base Numerica Hexadecimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F");
                                        }
                                        else
                                        {
                                            if(operando[0] == '@')
                                            {
                                                bandera=octal(operando);
                                                if(bandera == 1)
                                                {
                                                    valOperando=convierteHexadecimalDecimal(operando);
                                                    if((valOperando >= 0) && (valOperando <= 65535))
                                                    {
                                                        archAux.CONTLOC[4]='\0';
                                                        if(bandTemporal == 1)
                                                        {
                                                            fseek(fdTemp,0,2);
                                                            fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                                            bandDirectiva=1;
                                                        }
                                                        if(strcmp(etiqueta,"NULL") != 0)
                                                        {
                                                            if(bandTabsim == 1)
                                                            {
                                                                fseek(fdTabsim,0,2);
                                                                fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                                            }
                                                        }
                                                        bytes=valOperando*1;
                                                        archAux.Valor+=bytes;
                                                        itoa(archAux.Valor,cadAuxOp,16);
                                                        strupr(cadAuxOp);
                                                        longOperando=strlen(cadAuxOp);
                                                        n= 4 - longOperando;
                                                        if(n > 0)
                                                        {
                                                            k=0;
                                                            for(i=0; i < n; i++)
                                                            {
                                                                archAux.CONTLOC[i]='0';
                                                                k++;
                                                            }
                                                            j=0;
                                                            for(i=k; i<longOperando; i++)
                                                            {
                                                                archAux.CONTLOC[i]=cadAuxOp[j];
                                                                j++;
                                                            }
                                                        }
                                                        else
                                                            strcpy(archAux.CONTLOC,cadAuxOp);
                                                        acumDirectiva=1;
                                                    }
                                                    else
                                                        printf("\n\tError: Excede el Limite de la Directiva DS.B, Rango Valido: 0 a 65535");
                                                }
                                                else
                                                    printf("\n\tError: Base Numerica Octal Invalida,Caracteres validos 0,1,2,3,4,5,6,7");
                                            }
                                            else
                                            {
                                                if(operando[0] == '%')
                                                {
                                                    bandera=binario(operando);
                                                    if(bandera == 1)
                                                    {
                                                        valOperando=convierteHexadecimalDecimal(operando);
                                                        if((valOperando >= 0) && (valOperando <= 65535))
                                                        {
                                                            archAux.CONTLOC[4]='\0';
                                                            if(bandTemporal == 1)
                                                            {
                                                                fseek(fdTemp,0,2);
                                                                fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                                                bandDirectiva=1;
                                                            }
                                                            if(strcmp(etiqueta,"NULL") != 0)
                                                            {
                                                                if(bandTabsim == 1)
                                                                {
                                                                    fseek(fdTabsim,0,2);
                                                                    fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                                                }
                                                            }
                                                            bytes=valOperando*1;
                                                            archAux.Valor+=bytes;
                                                            itoa(archAux.Valor,cadAuxOp,16);
                                                            strupr(cadAuxOp);
                                                            longOperando=strlen(cadAuxOp);
                                                            n= 4 - longOperando;
                                                            if(n > 0)
                                                            {
                                                                k=0;
                                                                for(i=0; i < n; i++)
                                                                {
                                                                    archAux.CONTLOC[i]='0';
                                                                    k++;
                                                                }
                                                                j=0;
                                                                for(i=k; i<4 ; i++)
                                                                {
                                                                    archAux.CONTLOC[i]=cadAuxOp[j];
                                                                    j++;
                                                                }
                                                            }
                                                            else
                                                                strcpy(archAux.CONTLOC,cadAuxOp);
                                                            acumDirectiva=1;
                                                        }
                                                        else
                                                            printf("\n\tError: Excede el Limite de la Directiva DS.B, Rango Valido: 0 a 65535");
                                                    }
                                                    else
                                                        printf("\n\tError: Base Numerica Binaria Invalida,Caracteres validos 0,1");
                                                }
                                                else
                                                {
                                                    if((operando[0] >= 48) && (operando[0] <= 57))
                                                    {
                                                        bandera=decimal(operando);
                                                        if(bandera == 1)
                                                        {
                                                            valOperando=atoi(operando);
                                                            if((valOperando >= 0) && (valOperando <= 65535))
                                                            {
                                                                archAux.CONTLOC[4]='\0';
                                                                if(bandTemporal == 1)
                                                                {
                                                                    fseek(fdTemp,0,2);
                                                                    fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                                                    bandDirectiva=1;
                                                                }
                                                                if(strcmp(etiqueta,"NULL") != 0)
                                                                {
                                                                    if(bandTabsim == 1)
                                                                    {
                                                                        fseek(fdTabsim,0,2);
                                                                        fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                                                    }
                                                                }
                                                                bytes=valOperando*1;
                                                                archAux.Valor+=bytes;
                                                                itoa(archAux.Valor,cadAuxOp,16);
                                                                strupr(cadAuxOp);
                                                                longOperando=strlen(cadAuxOp);
                                                                n= 4 - longOperando;
                                                                if(n > 0)
                                                                {
                                                                    k=0;
                                                                    for(i=0; i < n; i++)
                                                                    {
                                                                        archAux.CONTLOC[i]='0';
                                                                        k++;
                                                                    }
                                                                    j=0;
                                                                    for(i=k; i<4; i++)
                                                                    {
                                                                        archAux.CONTLOC[i]=cadAuxOp[j];
                                                                        j++;
                                                                    }
                                                                }
                                                                else
                                                                    strcpy(archAux.CONTLOC,cadAuxOp);
                                                                acumDirectiva=1;
                                                            }
                                                            else
                                                                printf("\n\tError: Excede el Limite de la Directiva DS.B, Rango Valido: 0 a 65535");
                                                        }
                                                        else
                                                            printf("\n\tError: Base Numerica Decimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9");
                                                    }
                                                    else
                                                    {
                                                        if(operando[0] == '\0')
                                                        {
                                                            bandError=1;
                                                            printf("\n\tError: La Directiva DS.B debe tener Operando");
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {
                                        if(bandDirectiva == 10)
                                        {
                                            if(operando[0] == '$')
                                            {
                                                bandera=hexadecimal(operando);
                                                if(bandera == 1)
                                                {
                                                    valOperando=convierteHexadecimalDecimal(operando);
                                                    if((valOperando >= 0) && (valOperando <= 65535))
                                                    {
                                                        archAux.CONTLOC[4]='\0';
                                                        if(bandTemporal == 1)
                                                        {
                                                            fseek(fdTemp,0,2);
                                                            fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                                            bandDirectiva=1;
                                                        }
                                                        if(strcmp(etiqueta,"NULL") != 0)
                                                        {
                                                            if(bandTabsim == 1)
                                                            {
                                                                fseek(fdTabsim,0,2);
                                                                fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                                            }
                                                        }
                                                        bytes=valOperando*2;
                                                        archAux.Valor+=bytes;
                                                        itoa(archAux.Valor,cadAuxOp,16);
                                                        strupr(cadAuxOp);
                                                        longOperando=strlen(cadAuxOp);
                                                        n= 4 - longOperando;
                                                        if(n > 0)
                                                        {
                                                            k=0;
                                                            for(i=0; i < n; i++)
                                                            {
                                                                archAux.CONTLOC[i]='0';
                                                                k++;
                                                            }
                                                            j=0;
                                                            for(i=k; i<4 ; i++)
                                                            {
                                                                archAux.CONTLOC[i]=cadAuxOp[j];
                                                                j++;
                                                            }
                                                        }
                                                        else
                                                            strcpy(archAux.CONTLOC,cadAuxOp);
                                                        acumDirectiva=1;
                                                    }
                                                    else
                                                        printf("\n\tError: Excede el Limite de la Directiva DS.W, Rango Valido: 0 a 65535");
                                                }
                                                else
                                                    printf("\n\tError: Base Numerica Hexadecimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F");
                                            }
                                            else
                                            {
                                                if(operando[0] == '@')
                                                {
                                                    bandera=octal(operando);
                                                    if(bandera == 1)
                                                    {
                                                        valOperando=convierteHexadecimalDecimal(operando);
                                                        if((valOperando >= 0) && (valOperando <= 65535))
                                                        {
                                                            archAux.CONTLOC[4]='\0';
                                                            if(bandTemporal == 1)
                                                            {
                                                                fseek(fdTemp,0,2);
                                                                fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                                                bandDirectiva=1;
                                                            }
                                                            if(strcmp(etiqueta,"NULL") != 0)
                                                            {
                                                                if(bandTabsim == 1)
                                                                {
                                                                    fseek(fdTabsim,0,2);
                                                                    fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                                                }
                                                            }
                                                            bytes=valOperando*2;
                                                            archAux.Valor+=bytes;
                                                            itoa(archAux.Valor,cadAuxOp,16);
                                                            strupr(cadAuxOp);
                                                            longOperando=strlen(cadAuxOp);
                                                            n= 4 - longOperando;
                                                            if(n > 0)
                                                            {
                                                                k=0;
                                                                for(i=0; i < n; i++)
                                                                {
                                                                    archAux.CONTLOC[i]='0';
                                                                    k++;
                                                                }
                                                                j=0;
                                                                for(i=k; i<4 ; i++)
                                                                {
                                                                    archAux.CONTLOC[i]=cadAuxOp[j];
                                                                    j++;
                                                                }
                                                            }
                                                            else
                                                                strcpy(archAux.CONTLOC,cadAuxOp);
                                                            acumDirectiva=1;
                                                        }
                                                        else
                                                            printf("\n\tError: Excede el Limite de la Directiva DS.W, Rango Valido: 0 a 65535");
                                                    }
                                                    else
                                                        printf("\n\tError: Base Numerica Octal Invalida,Caracteres validos 0,1,2,3,4,5,6,7");
                                                }
                                                else
                                                {
                                                    if(operando[0] == '%')
                                                    {
                                                        bandera=binario(operando);
                                                        if(bandera == 1)
                                                        {
                                                            valOperando=convierteHexadecimalDecimal(operando);
                                                            if((valOperando >= 0) && (valOperando <= 65535))
                                                            {
                                                                archAux.CONTLOC[4]='\0';
                                                                if(bandTemporal == 1)
                                                                {
                                                                    fseek(fdTemp,0,2);
                                                                    fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                                                    bandDirectiva=1;
                                                                }
                                                                if(strcmp(etiqueta,"NULL") != 0)
                                                                {
                                                                    if(bandTabsim == 1)
                                                                    {
                                                                        fseek(fdTabsim,0,2);
                                                                        fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                                                    }
                                                                }
                                                                bytes=valOperando*2;
                                                                archAux.Valor+=bytes;
                                                                itoa(archAux.Valor,cadAuxOp,16);
                                                                strupr(cadAuxOp);
                                                                longOperando=strlen(cadAuxOp);
                                                                n= 4 - longOperando;
                                                                if(n > 0)
                                                                {
                                                                    k=0;
                                                                    for(i=0; i < n; i++)
                                                                    {
                                                                        archAux.CONTLOC[i]='0';
                                                                        k++;
                                                                    }
                                                                    j=0;
                                                                    for(i=k; i<4 ; i++)
                                                                    {
                                                                        archAux.CONTLOC[i]=cadAuxOp[j];
                                                                        j++;
                                                                    }
                                                                }
                                                                else
                                                                    strcpy(archAux.CONTLOC,cadAuxOp);
                                                                acumDirectiva=1;
                                                            }
                                                            else
                                                                printf("\n\tError: Excede el Limite de la Directiva DS.W, Rango Valido: 0 a 65535");
                                                        }
                                                        else
                                                            printf("\n\tError: Base Numerica Binaria Invalida,Caracteres validos 0,1");
                                                    }
                                                    else
                                                    {
                                                        if((operando[0] >= 48) && (operando[0] <= 57))
                                                        {
                                                            bandera=decimal(operando);
                                                            if(bandera == 1)
                                                            {
                                                                valOperando=atoi(operando);
                                                                if((valOperando >= 0) && (valOperando <= 65535))
                                                                {
                                                                    archAux.CONTLOC[4]='\0';
                                                                    if(bandTemporal == 1)
                                                                    {
                                                                        fseek(fdTemp,0,2);
                                                                        fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                                                        bandDirectiva=1;
                                                                    }
                                                                    if(strcmp(etiqueta,"NULL") != 0)
                                                                    {
                                                                        if(bandTabsim == 1)
                                                                        {
                                                                            fseek(fdTabsim,0,2);
                                                                            fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                                                        }
                                                                    }
                                                                    bytes=valOperando*2;
                                                                    archAux.Valor+=bytes;
                                                                    itoa(archAux.Valor,cadAuxOp,16);
                                                                    strupr(cadAuxOp);
                                                                    longOperando=strlen(cadAuxOp);
                                                                    n= 4 - longOperando;
                                                                    if(n > 0)
                                                                    {
                                                                        k=0;
                                                                        for(i=0; i < n; i++)
                                                                        {
                                                                            archAux.CONTLOC[i]='0';
                                                                            k++;
                                                                        }
                                                                        j=0;
                                                                        for(i=k; i<4 ; i++)
                                                                        {
                                                                            archAux.CONTLOC[i]=cadAuxOp[j];
                                                                            j++;
                                                                        }
                                                                    }
                                                                    else
                                                                        strcpy(archAux.CONTLOC,cadAuxOp);
                                                                    acumDirectiva=1;
                                                                }
                                                                else
                                                                    printf("\n\tError: Excede el Limite de la Directiva DS.W, Rango Valido: 0 a 65535");
                                                            }
                                                            else
                                                                printf("\n\tError: Base Numerica Decimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9");
                                                        }
                                                        else
                                                        {
                                                            if(operando[0] == '\0')
                                                            {
                                                                bandError=1;
                                                                printf("\n\tError: La Directiva DS.W debe tener Operando");
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        else
                                        {
                                            if(bandDirectiva == 11)
                                            {
                                                if(operando[0] == '$')
                                                {
                                                    bandera=hexadecimal(operando);
                                                    if(bandera == 1)
                                                    {
                                                        valOperando=convierteHexadecimalDecimal(operando);
                                                        if((valOperando >= 0) && (valOperando <= 65535))
                                                        {
                                                            archAux.CONTLOC[4]='\0';
                                                            if(bandTemporal == 1)
                                                            {
                                                                fseek(fdTemp,0,2);
                                                                fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                                                bandDirectiva=1;
                                                            }
                                                            if(strcmp(etiqueta,"NULL") != 0)
                                                            {
                                                                if(bandTabsim == 1)
                                                                {
                                                                    fseek(fdTabsim,0,2);
                                                                    fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                                                }
                                                            }
                                                            bytes=valOperando*1;
                                                            archAux.Valor+=bytes;
                                                            itoa(archAux.Valor,cadAuxOp,16);
                                                            strupr(cadAuxOp);
                                                            longOperando=strlen(cadAuxOp);
                                                            n= 4 - longOperando;
                                                            if(n > 0)
                                                            {
                                                                k=0;
                                                                for(i=0; i < n; i++)
                                                                {
                                                                    archAux.CONTLOC[i]='0';
                                                                    k++;
                                                                }
                                                                j=0;
                                                                for(i=k; i<4 ; i++)
                                                                {
                                                                    archAux.CONTLOC[i]=cadAuxOp[j];
                                                                    j++;
                                                                }
                                                            }
                                                            else
                                                                strcpy(archAux.CONTLOC,cadAuxOp);
                                                            acumDirectiva=1;
                                                        }
                                                        else
                                                            printf("\n\tError: Excede el Limite de la Directiva RMB, Rango Valido: 0 a 65535");
                                                    }
                                                    else
                                                        printf("\n\tError: Base Numerica Hexadecimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F");
                                                }
                                                else
                                                {
                                                    if(operando[0] == '@')
                                                    {
                                                        bandera=octal(operando);
                                                        if(bandera == 1)
                                                        {
                                                            valOperando=convierteHexadecimalDecimal(operando);
                                                            if((valOperando >= 0) && (valOperando <= 65535))
                                                            {
                                                                archAux.CONTLOC[4]='\0';
                                                                if(bandTemporal == 1)
                                                                {
                                                                    fseek(fdTemp,0,2);
                                                                    fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                                                    bandDirectiva=1;
                                                                }
                                                                if(strcmp(etiqueta,"NULL") != 0)
                                                                {
                                                                    if(bandTabsim == 1)
                                                                    {
                                                                        fseek(fdTabsim,0,2);
                                                                        fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                                                    }
                                                                }
                                                                bytes=valOperando*1;
                                                                archAux.Valor+=bytes;
                                                                itoa(archAux.Valor,cadAuxOp,16);
                                                                strupr(cadAuxOp);
                                                                longOperando=strlen(cadAuxOp);
                                                                n= 4 - longOperando;
                                                                if(n > 0)
                                                                {
                                                                    k=0;
                                                                    for(i=0; i < n; i++)
                                                                    {
                                                                        archAux.CONTLOC[i]='0';
                                                                        k++;
                                                                    }
                                                                    j=0;
                                                                    for(i=k; i<4; i++)
                                                                    {
                                                                        archAux.CONTLOC[i]=cadAuxOp[j];
                                                                        j++;
                                                                    }
                                                                }
                                                                else
                                                                    strcpy(archAux.CONTLOC,cadAuxOp);
                                                                acumDirectiva=1;
                                                            }
                                                            else
                                                                printf("\n\tError: Excede el Limite de la Directiva RMB, Rango Valido: 0 a 65535");
                                                        }
                                                        else
                                                            printf("\n\tError: Base Numerica Octal Invalida,Caracteres validos 0,1,2,3,4,5,6,7");
                                                    }
                                                    else
                                                    {
                                                        if(operando[0] == '%')
                                                        {
                                                            bandera=binario(operando);
                                                            if(bandera == 1)
                                                            {
                                                                valOperando=convierteHexadecimalDecimal(operando);
                                                                if((valOperando >= 0) && (valOperando <= 65535))
                                                                {
                                                                    archAux.CONTLOC[4]='\0';
                                                                    if(bandTemporal == 1)
                                                                    {
                                                                        fseek(fdTemp,0,2);
                                                                        fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                                                        bandDirectiva=1;
                                                                    }
                                                                    if(strcmp(etiqueta,"NULL") != 0)
                                                                    {
                                                                        if(bandTabsim == 1)
                                                                        {
                                                                            fseek(fdTabsim,0,2);
                                                                            fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                                                        }
                                                                    }
                                                                    bytes=valOperando*1;
                                                                    archAux.Valor+=bytes;
                                                                    itoa(archAux.Valor,cadAuxOp,16);
                                                                    strupr(cadAuxOp);
                                                                    longOperando=strlen(cadAuxOp);
                                                                    n= 4 - longOperando;
                                                                    if(n > 0)
                                                                    {
                                                                        k=0;
                                                                        for(i=0; i < n; i++)
                                                                        {
                                                                            archAux.CONTLOC[i]='0';
                                                                            k++;
                                                                        }
                                                                        j=0;
                                                                        for(i=k; i<4; i++)
                                                                        {
                                                                            archAux.CONTLOC[i]=cadAuxOp[j];
                                                                            j++;
                                                                        }
                                                                    }
                                                                    else
                                                                        strcpy(archAux.CONTLOC,cadAuxOp);
                                                                    acumDirectiva=1;
                                                                }
                                                                else
                                                                    printf("\n\tError: Excede el Limite de la Directiva RMB, Rango Valido: 0 a 65535");
                                                            }
                                                            else
                                                                printf("\n\tError: Base Numerica Binaria Invalida,Caracteres validos 0,1");
                                                        }
                                                        else
                                                        {
                                                            if((operando[0] >= 48) && (operando[0] <= 57))
                                                            {
                                                                bandera=decimal(operando);
                                                                if(bandera == 1)
                                                                {
                                                                    valOperando=atoi(operando);
                                                                    if((valOperando >= 0) && (valOperando <= 65535))
                                                                    {
                                                                        archAux.CONTLOC[4]='\0';
                                                                        if(bandTemporal == 1)
                                                                        {
                                                                            fseek(fdTemp,0,2);
                                                                            fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                                                            bandDirectiva=1;
                                                                        }
                                                                        if(strcmp(etiqueta,"NULL") != 0)
                                                                        {
                                                                            if(bandTabsim == 1)
                                                                            {
                                                                                fseek(fdTabsim,0,2);
                                                                                fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                                                            }
                                                                        }
                                                                        bytes=valOperando*1;
                                                                        archAux.Valor+=bytes;
                                                                        itoa(archAux.Valor,cadAuxOp,16);
                                                                        strupr(cadAuxOp);
                                                                        longOperando=strlen(cadAuxOp);
                                                                        n= 4 - longOperando;
                                                                        if(n > 0)
                                                                        {
                                                                            k=0;
                                                                            for(i=0; i < n; i++)
                                                                            {
                                                                                archAux.CONTLOC[i]='0';
                                                                                k++;
                                                                            }
                                                                            j=0;
                                                                            for(i=k; i<4 ; i++)
                                                                            {
                                                                                archAux.CONTLOC[i]=cadAuxOp[j];
                                                                                j++;
                                                                            }
                                                                        }
                                                                        else
                                                                            strcpy(archAux.CONTLOC,cadAuxOp);
                                                                        acumDirectiva=1;
                                                                    }
                                                                    else
                                                                        printf("\n\tError: Excede el Limite de la Directiva RMB, Rango Valido: 0 a 65535");
                                                                }
                                                                else
                                                                    printf("\n\tError: Base Numerica Decimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9");
                                                            }
                                                            else
                                                            {
                                                                if(operando[0] == '\0')
                                                                {
                                                                    bandError=1;
                                                                    printf("\n\tError: La Directiva RMB debe tener Operando");
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                if(bandDirectiva == 12)
                                                {
                                                    if(operando[0] == '$')
                                                    {
                                                        bandera=hexadecimal(operando);
                                                        if(bandera == 1)
                                                        {
                                                            valOperando=convierteHexadecimalDecimal(operando);
                                                            if((valOperando >= 0) && (valOperando <= 65535))
                                                            {
                                                                archAux.CONTLOC[4]='\0';
                                                                if(bandTemporal == 1)
                                                                {
                                                                    fseek(fdTemp,0,2);
                                                                    fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                                                    bandDirectiva=1;
                                                                }
                                                                if(strcmp(etiqueta,"NULL") != 0)
                                                                {
                                                                    if(bandTabsim == 1)
                                                                    {
                                                                        fseek(fdTabsim,0,2);
                                                                        fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                                                    }
                                                                }
                                                                bytes=valOperando*2;
                                                                archAux.Valor+=bytes;
                                                                itoa(archAux.Valor,cadAuxOp,16);
                                                                strupr(cadAuxOp);
                                                                longOperando=strlen(cadAuxOp);
                                                                n= 4 - longOperando;
                                                                if(n > 0)
                                                                {
                                                                    k=0;
                                                                    for(i=0; i < n; i++)
                                                                    {
                                                                        archAux.CONTLOC[i]='0';
                                                                        k++;
                                                                    }
                                                                    j=0;
                                                                    for(i=k; i<4 ; i++)
                                                                    {
                                                                        archAux.CONTLOC[i]=cadAuxOp[j];
                                                                        j++;
                                                                    }
                                                                }
                                                                else
                                                                    strcpy(archAux.CONTLOC,cadAuxOp);
                                                                acumDirectiva=1;
                                                            }
                                                            else
                                                                printf("\n\tError: Excede el Limite de la Directiva RMW, Rango Valido: 0 a 65535");
                                                        }
                                                        else
                                                            printf("\n\tError: Base Numerica Hexadecimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F");
                                                    }
                                                    else
                                                    {
                                                        if(operando[0] == '@')
                                                        {
                                                            bandera=octal(operando);
                                                            if(bandera == 1)
                                                            {
                                                                valOperando=convierteHexadecimalDecimal(operando);
                                                                if((valOperando >= 0) && (valOperando <= 65535))
                                                                {
                                                                    archAux.CONTLOC[4]='\0';
                                                                    if(bandTemporal == 1)
                                                                    {
                                                                        fseek(fdTemp,0,2);
                                                                        fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                                                        bandDirectiva=1;
                                                                    }
                                                                    if(strcmp(etiqueta,"NULL") != 0)
                                                                    {
                                                                        if(bandTabsim == 1)
                                                                        {
                                                                            fseek(fdTabsim,0,2);
                                                                            fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                                                        }
                                                                    }
                                                                    bytes=valOperando*2;
                                                                    archAux.Valor+=bytes;
                                                                    itoa(archAux.Valor,cadAuxOp,16);
                                                                    strupr(cadAuxOp);
                                                                    longOperando=strlen(cadAuxOp);
                                                                    n= 4 - longOperando;
                                                                    if(n > 0)
                                                                    {
                                                                        k=0;
                                                                        for(i=0; i < n; i++)
                                                                        {
                                                                            archAux.CONTLOC[i]='0';
                                                                            k++;
                                                                        }
                                                                        j=0;
                                                                        for(i=k; i<4 ; i++)
                                                                        {
                                                                            archAux.CONTLOC[i]=cadAuxOp[j];
                                                                            j++;
                                                                        }
                                                                    }
                                                                    else
                                                                        strcpy(archAux.CONTLOC,cadAuxOp);
                                                                    acumDirectiva=1;
                                                                }
                                                                else
                                                                    printf("\n\tError: Excede el Limite de la Directiva RMW, Rango Valido: 0 a 65535");
                                                            }
                                                            else
                                                                printf("\n\tError: Base Numerica Octal Invalida,Caracteres validos 0,1,2,3,4,5,6,7");
                                                        }
                                                        else
                                                        {
                                                            if(operando[0] == '%')
                                                            {
                                                                bandera=binario(operando);
                                                                if(bandera == 1)
                                                                {
                                                                    valOperando=convierteHexadecimalDecimal(operando);
                                                                    if((valOperando >= 0) && (valOperando <= 65535))
                                                                    {
                                                                        archAux.CONTLOC[4]='\0';
                                                                        if(bandTemporal == 1)
                                                                        {
                                                                            fseek(fdTemp,0,2);
                                                                            fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                                                            bandDirectiva=1;
                                                                        }
                                                                        if(strcmp(etiqueta,"NULL") != 0)
                                                                        {
                                                                            if(bandTabsim == 1)
                                                                            {
                                                                                fseek(fdTabsim,0,2);
                                                                                fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                                                            }
                                                                        }
                                                                        bytes=valOperando*2;
                                                                        archAux.Valor+=bytes;
                                                                        itoa(archAux.Valor,cadAuxOp,16);
                                                                        strupr(cadAuxOp);
                                                                        longOperando=strlen(cadAuxOp);
                                                                        n= 4 - longOperando;
                                                                        if(n > 0)
                                                                        {
                                                                            k=0;
                                                                            for(i=0; i < n; i++)
                                                                            {
                                                                                archAux.CONTLOC[i]='0';
                                                                                k++;
                                                                            }
                                                                            j=0;
                                                                            for(i=k; i<4 ; i++)
                                                                            {
                                                                                archAux.CONTLOC[i]=cadAuxOp[j];
                                                                                j++;
                                                                            }
                                                                        }
                                                                        else
                                                                            strcpy(archAux.CONTLOC,cadAuxOp);
                                                                        acumDirectiva=1;
                                                                    }
                                                                    else
                                                                        printf("\n\tError: Excede el Limite de la Directiva RMW, Rango Valido: 0 a 65535");
                                                                }
                                                                else
                                                                    printf("\n\tError: Base Numerica Binaria Invalida,Caracteres validos 0,1");
                                                            }
                                                            else
                                                            {
                                                                if((operando[0] >= 48) && (operando[0] <= 57))
                                                                {
                                                                    bandera=decimal(operando);
                                                                    if(bandera == 1)
                                                                    {
                                                                        valOperando=atoi(operando);
                                                                        if((valOperando >= 0) && (valOperando <= 65535))
                                                                        {
                                                                            archAux.CONTLOC[4]='\0';
                                                                            if(bandTemporal == 1)
                                                                            {
                                                                                fseek(fdTemp,0,2);
                                                                                fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                                                                                bandDirectiva=1;
                                                                            }
                                                                            if(strcmp(etiqueta,"NULL") != 0)
                                                                            {
                                                                                if(bandTabsim == 1)
                                                                                {
                                                                                    fseek(fdTabsim,0,2);
                                                                                    fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.CONTLOC);
                                                                                }
                                                                            }
                                                                            bytes=valOperando*2;
                                                                            archAux.Valor+=bytes;
                                                                            itoa(archAux.Valor,cadAuxOp,16);
                                                                            strupr(cadAuxOp);
                                                                            longOperando=strlen(cadAuxOp);
                                                                            n= 4 - longOperando;
                                                                            if(n > 0)
                                                                            {
                                                                                k=0;
                                                                                for(i=0; i < n; i++)
                                                                                {
                                                                                    archAux.CONTLOC[i]='0';
                                                                                    k++;
                                                                                }
                                                                                j=0;
                                                                                for(i=k; i<4; i++)
                                                                                {
                                                                                    archAux.CONTLOC[i]=cadAuxOp[j];
                                                                                    j++;
                                                                                }
                                                                            }
                                                                            else
                                                                                strcpy(archAux.CONTLOC,cadAuxOp);
                                                                            acumDirectiva=1;
                                                                        }
                                                                        else
                                                                            printf("\n\tError: Excede el Limite de la Directiva RMW, Rango Valido: 0 a 65535");
                                                                    }
                                                                    else
                                                                        printf("\n\tError: Base Numerica Decimal Invalida,Caracteres validos 0,1,2,3,4,5,6,7,8,9");
                                                                }
                                                                else
                                                                {
                                                                    if(operando[0] == '\0')
                                                                    {
                                                                        bandError=1;
                                                                        printf("\n\tError: La Directiva RMW debe tener Operando");
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return acumDirectiva;
}


int validaDirectiva(char etiqueta[10],char codop[10],char operando[10],int bandTemporal,FILE * fdTemp,int bandTabsim,FILE * fdTabsim)
{
    ARCH_AUX archAux1;
    int acumDirectiva=0;

    if((strcmp(codop,"ORG") == 0) || (strcmp(codop,"Org") == 0) || (strcmp(codop,"org") == 0))
    {
        archAux1=validaDirectivaORG(etiqueta,codop,operando);
        if((archAux1.bandera == 1) && (ORG == 0))
        {
            archAux.DIR_INIC=archAux1.DIR_INIC;
            archAux.Valor=archAux.DIR_INIC;
            strcpy(archAux.CONTLOC,archAux1.CONTLOC);
            acumDirectiva=1;
            archAux.CONTLOC[4]='\0';
            if(bandTemporal == 1)
            {
                fseek(fdTemp,0,2);
                fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.CONTLOC,etiqueta,codop,operando);
                ORG=1;
            }
        }
        else
        {
            if(ORG == 1)
                printf("\n\tError: Solo es Valida una Directiva ORG");
        }
    }
    else
    {
        if((strcmp(codop,"DW") == 0) || (strcmp(codop,"Dw") == 0) || (strcmp(codop,"dw") == 0))
        {
            acumDirectiva=validaDirectivaDC(etiqueta,codop,operando,1,bandTemporal,fdTemp,bandTabsim,fdTabsim);
        }
        else
        {
            if((strcmp(codop,"DB") == 0) || (strcmp(codop,"Db") == 0) || (strcmp(codop,"db") == 0))
            {
                acumDirectiva=validaDirectivaDC(etiqueta,codop,operando,2,bandTemporal,fdTemp,bandTabsim,fdTabsim);
            }
            else
            {
                if((strcmp(codop,"DC.W") == 0) || (strcmp(codop,"Dc.w") == 0) || (strcmp(codop,"dc.w") == 0))
                {
                    acumDirectiva=validaDirectivaDC(etiqueta,codop,operando,3,bandTemporal,fdTemp,bandTabsim,fdTabsim);
                }
                else
                {
                    if((strcmp(codop,"DC.B") == 0) || (strcmp(codop,"Dc.b") == 0) || (strcmp(codop,"dc.b") == 0))
                    {
                        acumDirectiva=validaDirectivaDC(etiqueta,codop,operando,4,bandTemporal,fdTemp,bandTabsim,fdTabsim);
                    }
                    else
                    {
                        if((strcmp(codop,"FCB") == 0) || (strcmp(codop,"Fcb") == 0) || (strcmp(codop,"fcb") == 0))
                        {
                            acumDirectiva=validaDirectivaDC(etiqueta,codop,operando,5,bandTemporal,fdTemp,bandTabsim,fdTabsim);
                        }
                        else
                        {
                            if((strcmp(codop,"FDB") == 0) || (strcmp(codop,"Fdb") == 0) || (strcmp(codop,"fdb") == 0))
                            {
                                acumDirectiva=validaDirectivaDC(etiqueta,codop,operando,6,bandTemporal,fdTemp,bandTabsim,fdTabsim);
                            }
                            else
                            {
                                if((strcmp(codop,"FCC") == 0) || (strcmp(codop,"Fcc") == 0) || (strcmp(codop,"fcc") == 0))
                                {
                                    acumDirectiva=validaDirectivaDC(etiqueta,codop,operando,7,bandTemporal,fdTemp,bandTabsim,fdTabsim);
                                }
                                else
                                {
                                    if((strcmp(codop,"DS") == 0) || (strcmp(codop,"Ds") == 0) || (strcmp(codop,"ds") == 0))
                                    {
                                        acumDirectiva=validaDirectivaDC(etiqueta,codop,operando,8,bandTemporal,fdTemp,bandTabsim,fdTabsim);
                                    }
                                    else
                                    {
                                        if((strcmp(codop,"DS.B") == 0) || (strcmp(codop,"Ds.b") == 0) || (strcmp(codop,"ds.b") == 0))
                                        {
                                            acumDirectiva=validaDirectivaDC(etiqueta,codop,operando,9,bandTemporal,fdTemp,bandTabsim,fdTabsim);
                                        }
                                        else
                                        {
                                            if((strcmp(codop,"DS.W") == 0) || (strcmp(codop,"Ds.w") == 0) || (strcmp(codop,"ds.w") == 0))
                                            {
                                                acumDirectiva=validaDirectivaDC(etiqueta,codop,operando,10,bandTemporal,fdTemp,bandTabsim,fdTabsim);
                                            }
                                            else
                                            {
                                                if((strcmp(codop,"RMB") == 0) || (strcmp(codop,"Rmb") == 0) || (strcmp(codop,"rmb") == 0))
                                                {
                                                    acumDirectiva=validaDirectivaDC(etiqueta,codop,operando,11,bandTemporal,fdTemp,bandTabsim,fdTabsim);
                                                }
                                                else
                                                {
                                                    if((strcmp(codop,"RMW") == 0) || (strcmp(codop,"Rmw") == 0) || (strcmp(codop,"rmw") == 0))
                                                    {
                                                        acumDirectiva=validaDirectivaDC(etiqueta,codop,operando,12,bandTemporal,fdTemp,bandTabsim,fdTabsim);
                                                    }
                                                    else
                                                    {
                                                        if((strcmp(codop,"EQU") == 0) || (strcmp(codop,"Equ") == 0) || (strcmp(codop,"equ") == 0))
                                                        {
                                                            archAux1=validaDirectivaEQU(etiqueta,codop,operando);
                                                            strcpy(archAux.DIR_EQU,archAux1.DIR_EQU);
                                                            archAux.DIR_EQU[4]='\0';
                                                            if(bandTemporal == 1)
                                                            {
                                                                fseek(fdTemp,0,2);
                                                                fprintf(fdTemp,"%s\t%s\t%s\t%s\n",archAux.DIR_EQU,etiqueta,codop,operando);
                                                                acumDirectiva=1;
                                                            }
                                                            if(strcmp(etiqueta,"NULL") != 0)
                                                            {
                                                                if(bandTabsim == 1)
                                                                {
                                                                    fseek(fdTabsim,0,2);
                                                                    fprintf(fdTabsim,"%s\t%s\n",etiqueta,archAux.DIR_EQU);
                                                                }
                                                            }

                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return acumDirectiva;
}

COD_MAQ RecuperaCodigoMaquina(FILE * fdTabOp,char codop[12],char operando[10])
{
    TAB_OP TABOP;
    COD_MAQ COD_MAQUINA;

	int i=0;
	int j=0;
	int cont=0;
	int aux=0;
	int band=0;

	int banderaAux=0;
	int bandModoDirExt=0;
	int bandModoImm=0;
	int bandAuxModoDir=0;
	int bandAuxModoExt=0;
	int bandAuxModoIDX=0;
	int bandIDX=0;
	int bandIDX1=0;
	int bandIDX2=0;
	int band_IDX2=0;
	int bandDIDX=0;
	int bandAuxInd=0;
	int bandAuxAcumInd=0;
	int bandAuxRel=0;
	int contAuxInd=0;
	int bandErrorLong=0;
	int bandErrorLong1=0;
	int pre=0;
	int post=0;
	int bandIndexados=0;

	char cadena[50];
	char caracter;

	int bndInh=0;
	int bndImm=0;
	int bndDir=0;
	int bndExt=0;
	int bndIdx=0;
	int bndIdx1=0;
	int bndIdx2=0;
	int bnd_Idx2=0;

    fseek(fdTabOp,0,0);
	while((fgets(cadena,50,fdTabOp)) && (banderaAux == 0))
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
		    if(strcmp(TABOP.direccionamiento,"INH") == 0)
		    {
		        COD_MAQUINA.INH=1;
                strcpy(COD_MAQUINA.codmaqINH,TABOP.codMaq);
		    }
            else
            {
                if(strcmp(TABOP.direccionamiento,"IMM") == 0)
                {
                    COD_MAQUINA.IMM=1;
                    strcpy(COD_MAQUINA.codmaqIMM,TABOP.codMaq);
                    COD_MAQUINA.bytesCalcularIMM=TABOP.bytes_por_calcular;
                }
                else
                {
                    if(strcmp(TABOP.direccionamiento,"DIR") == 0)
                    {
                        COD_MAQUINA.DIR=1;
                        strcpy(COD_MAQUINA.codmaqDIR,TABOP.codMaq);
                    }
                    else
                    {
                        if(strcmp(TABOP.direccionamiento,"EXT") == 0)
                        {
                            COD_MAQUINA.EXT=1;
                            strcpy(COD_MAQUINA.codmaqEXT,TABOP.codMaq);
                        }
                        else
                        {
                            if(strcmp(TABOP.direccionamiento,"IDX") == 0)
                                {
                                    COD_MAQUINA.IDX=1;
                                    strcpy(COD_MAQUINA.codmaqIDX,TABOP.codMaq);
                                }
                                else
                                {
                                    if(strcmp(TABOP.direccionamiento,"IDX1") == 0)
                                    {
                                        COD_MAQUINA.IDX1=1;
                                        strcpy(COD_MAQUINA.codmaqIDX1,TABOP.codMaq);
                                    }
                                    else
                                    {
                                        if(strcmp(TABOP.direccionamiento,"IDX2") == 0)
                                        {
                                            COD_MAQUINA.IDX2=1;
                                            strcpy(COD_MAQUINA.codmaqIDX2,TABOP.codMaq);
                                        }
                                        else
                                        {
                                            if(strcmp(TABOP.direccionamiento,"[IDX2]") == 0)
                                            {
                                                COD_MAQUINA._IDX2 =1;
                                                strcpy(COD_MAQUINA.codmaq_IDX2,TABOP.codMaq);
                                            }
                                            else
                                            {
                                                if(strcmp(TABOP.direccionamiento,"[D,IDX]") == 0)
                                                {
                                                    COD_MAQUINA.DIDX=1;
                                                    strcpy(COD_MAQUINA.codmaqDIDX,TABOP.codMaq);
                                                }
                                            }
                                        }
                                    }
                                }
                        }
                    }
                }
            }
		}
	}

	aux=0;
	aux=strlen(operando);
	for(i=0; i<aux; i++)
	{
	    if(operando[i] == ',')
            bandIndexados=1;
	}
    if(bandIndexados == 1)
    {
        if(strlen(operando) < 2)
            bandIndexados=2;
    }
	for(i=0; i<aux; i++)
	{
	    if(operando[i] == '[')
            contAuxInd++;
        if(operando[i] == ']')
            contAuxInd+=2;
	}
	if(contAuxInd == 3)
	{
	    if(aux > 2)
            bandAuxInd=1;
        else
            bandErrorLong=1;
	}
	if(aux < 2)
        bandErrorLong1=1;
	if(bandAuxInd == 1)
	{
	    if(operando[1] > 65)
            bandAuxAcumInd=1;
	}
	if(operando[0] >= 65)
        bandAuxRel=1;

    if(COD_MAQUINA.INH == 1)
    {
        if(strcmp(operando,"NULL") == 0)
        {
            COD_MAQUINA.bandera=1;
            bndInh=1;
        }
    }
	if((COD_MAQUINA.IMM == 1) && (bndInh == 0) && (bandIndexados == 0) && (bandAuxInd == 0))
    {
        if(operando[0] == '#')
        {
            if(strlen(operando) >= 2)
                bandModoImm=1;
            if(bandModoImm == 1)
            {
                if(COD_MAQUINA.bytesCalcularIMM == '1')
                    band=1;
                else
                {
                    if(COD_MAQUINA.bytesCalcularIMM == '2')
                        band=2;
                }
                bandModoImm=validaModoInmediato(operando,band);
                if(bandModoImm == 1)
                {
                    COD_MAQUINA.bandera=2;
                    bndImm=1;
                }
                else
                {
                    if(bandModoImm == 2)
                    {
                        COD_MAQUINA.bandera=3;
                        bndImm=1;
                    }
                }
            }

        }
    }
    if(((COD_MAQUINA.DIR == 1) && ((bndImm == 0) && (bndInh == 0))) && (COD_MAQUINA.EXT == 1) && (bandIndexados == 0) && (bandAuxInd == 0))
    {
        if(COD_MAQUINA.DIR == 1)
            bandAuxModoDir=1;
        if(COD_MAQUINA.EXT == 1)
            bandAuxModoExt=1;
        bandModoDirExt=validaModoDirectoExtendido(operando,bandAuxModoDir,bandAuxModoExt);
        if(bandModoDirExt == 1)
        {
            COD_MAQUINA.bandera=4;
            bndDir=1;
        }
        else
        {
            if(bandModoDirExt == 2)
            {
                COD_MAQUINA.bandera=5;
                bndExt=1;
            }
        }
    }

    if((((COD_MAQUINA.IDX == 1) || (COD_MAQUINA.IDX1 == 1) || (COD_MAQUINA.IDX2 == 1))  && ((bndDir == 0) && (bndExt == 0) && (bndInh == 0) && (bndImm == 0))) && (bandIndexados == 1) && (bandAuxInd == 0) && (bandErrorLong == 0))
    {
        if(COD_MAQUINA.IDX == 1)
            bandIDX=1;
        if(COD_MAQUINA.IDX1 == 1)
            bandIDX1=1;
        if((COD_MAQUINA.IDX2 == 1) == 1)
            bandIDX2=1;

        bandAuxModoIDX=validaModoIDX(operando,bandIDX,bandIDX1,bandIDX2);

        if(bandAuxModoIDX == 1)
        {
            COD_MAQUINA.bandera=6; //Ind 5 bits
                bndIdx=1;
        }
        else
        {
            if(bandAuxModoIDX == 4)
            {
                COD_MAQUINA.bandera=7; //Ind 9 bits
                bndIdx1=1;
            }
            else
            {
                if(bandAuxModoIDX == 5)
                {
                    COD_MAQUINA.bandera=8; //Ind 16 bits
                    bndIdx2=1;
                }
                else
                {
                    if(bandAuxModoIDX == 2)
                    {
                        if(operando[strlen(operando) - 1] == '+')
                            post+=2;
                        else
                        {
                            if(operando[strlen(operando) - 1] == '-')
                                post++;
                        }
                        for(i=0; i<strlen(operando); i++)
                        {
                            if((operando[i] == '+') && (operando[strlen(operando) - 1] != '+'))
                                pre+=2;
                            else
                            {
                                if((operando[i] == '-') && (operando[strlen(operando) - 1] != '-'))
                                    pre++;
                            }
                        }
                        if(post == 1)
                        {
                            COD_MAQUINA.bandera=9; //Ind auto post dec
                            bndIdx=1;
                        }
                        else
                        {
                            if(post == 2)
                            {
                                COD_MAQUINA.bandera=10; //Ind auto post inc
                                bndIdx=1;
                            }
                            else
                            {
                                if(pre == 2)
                                {
                                    COD_MAQUINA.bandera=11; //Ind auto pre inc
                                    bndIdx=1;
                                }
                                else
                                {
                                    if(pre == 1)
                                    {
                                        COD_MAQUINA.bandera=12; //Ind auto pre dec
                                        bndIdx=1;
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        if(bandAuxModoIDX == 3)
                        {
                            COD_MAQUINA.bandera=13; //Ind acum
                            bndIdx=1;
                        }
                    }
                }
            }
        }
    }

    if((COD_MAQUINA._IDX2 == 1) && (bandAuxInd == 1) && (bandAuxAcumInd == 0) && (bandErrorLong == 0))
    {
        band_IDX2=validaModoIndizadoIndirecto16(operando);
        if(band_IDX2 == 1)
        {
            COD_MAQUINA.bandera=14; //Ind ind 16 bits
            bnd_Idx2=1;
        }
    }

    if((COD_MAQUINA.DIDX == 1) && (bandAuxInd == 1) && (bnd_Idx2 == 0) && (bandAuxAcumInd == 1) && (bandErrorLong == 0))
    {
        bandDIDX=validaModoAcumuladorIndirecto(operando);
        if(bandDIDX == 1)
        {
            COD_MAQUINA.bandera=15; //Ind acum ind
            bnd_Idx2=1;
        }
    }

	return COD_MAQUINA;
}

ValXB RecuperaXB(char sentencia[5],char sentencia1[10])
{
    FILE *fdXb;
    ValXB XB;
    int i=0;
    int j=0;
    int cont=0;
    int aux=0;
    int aux1=0;
    char sintaxis[8];
    char valor[3];
    char indicador[12];
    char cadena[30];
    char caracter;
    int bandera=0;

     for(i=0; i<30; i++)
        cadena[i]='\0';

    fdXb=fopen("XB.txt","r");
    if(fdXb != NULL)
    {
        fseek(fdXb,0,0);
        while((fgets(cadena,30,fdXb)) && (bandera == 0))
        {
            for(i=0; i<8; i++)
                sintaxis[i]='\0';
            for(i=0; i<3; i++)
                valor[i]='\0';
            for(i=0; i<12; i++)
                indicador[i]='\0';

            for(i=0; i<strlen(cadena); i++)
            {
                caracter=cadena[i];
                if((caracter != '\t') && (caracter != '\n'))
                {
                    switch(cont)
                    {
                        case 0:
                            sintaxis[j]=caracter;
                            j++;
                        break;
                        case 1:
                            valor[j]=caracter;
                            j++;
                        break;
                        case 2:
                            indicador[j]=caracter;
                            j++;
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
            cont=0;
            j=0;
            aux=strcmp(sentencia,sintaxis);
            aux1=strcmp(sentencia1,indicador);
            if((aux == 0) && (aux1 == 0))
            {
                strcpy(XB.xb,valor);
                bandera=1;
            }
        }
    }
    fclose(fdXb);
    return XB;
}

int main()
{
    FILE *fd;
    FILE *fdTabOp;
    FILE *fdTemp;
    FILE *fdTabsim;

    COD_MAQ CODIGO_MAQUINA;
    ValXB XB;

    int bandTemporal=0;
    int bandTabsim=0;
    int i=0;
    int j=0;
    int k=0;
    int m=0;
    int n=0;
    int cont=1;
    int contop=1;
    int contEtiqueta=0;
    int contCodop=0; //contadores
    int bEnd=0;
    int band=0;
    int valorDecimal=0;
    int bandComentario=0;
    int x=0;
    int aux=0;
    int bandOpe=0;
    int bandcont=0; //banderas
    int bandOperando=0;
    int bandAuxOperando=0;
    int banderaAux=0;
    int bandAuxOp=0;
    int bandDirectiva=0;
    int longitud=0;
    int total=0;
    int banderaAuxiliar=0;
    int bandSigno=0;
    int bandComa=0;
    int band_signo=0;
    int numeroAux=0;
    char registro[3];
    char operandoAuxiliar[10];
    char cadComplemento[20];
    char op[8];
    char car;
    char cadenaAuxiliar[10];
    char cadenaTemporal[40];
    char etiquetaTemp[10];
    char valorTemp[5];
    char operandoTemp[10];
    char codopTemp[10];
    char etiqueta[15];
    char codop[12];
    char operando[40];
    char caracter;
    char cadena[50];
    char cadAuxiliar[40];
    char cad_numero[10];
    char cadAux[10];
    char cadAux1[10];

    for(i=0; i<15; i++)
        etiqueta[i]='\0';
    for(i=0; i<12; i++)
        codop[i]='\0';
    for(i=0; i<40; i++)
        operando[i]='\0';
    archAux.DIR_INIC=0;
    for(i=0; i<4; i++)
        archAux.CONTLOC[i]='\0';
    for(i=0; i<40; i++)
        cadAuxiliar[i]='\0';
    for(i=0; i<40; i++)
        cadenaTemporal[i]='\0';
    for(i=0; i<5; i++)
        valorTemp[i]='\0';
    for(i=0; i<10; i++)
        codopTemp[i]='\0';
    for(i=0; i<10; i++)
        operandoTemp[i]='\0';
    for(i=0; i<10; i++)
        etiquetaTemp[i]='\0';
    for(i=0; i<8; i++)
        op[i]='\0';
    for(i=0; i<10; i++)
        cadenaAuxiliar[i]='\0';
    for(i=0; i<10; i++)
        cadAux[i]='\0';
    for(i=0; i<10; i++)
        cadAux1[i]='\0';
    for(i=0; i<10; i++)
        operandoAuxiliar[i]='\0';
    for(i=0; i<10; i++)
        cad_numero[i]='\0';
    for(i=0; i<3; i++)
        registro[i]='\0';

    fd=fopen("PRACT6.txt","r");
    if(fd != NULL)
    {
        fdTemp=fopen("P2tmp.txt","w+");
        if(fdTemp != NULL)
            bandTemporal=1;

        fdTabsim=fopen("TABSIM.txt","w+");
        if(fdTabsim != NULL)
            bandTabsim=1;

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
						{
							bEnd=1;
							archAux.CONTLOC[4]='\0';
                            if(bandTemporal == 1)
                            {
                                fseek(fdTemp,0,2);
                                fprintf(fdTemp,"%s\t%s\t%s\tNULL\n",archAux.CONTLOC,etiqueta,codop);
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
                if(existeCodOp(fdTabOp,codop) == 0)
                {
                    if(validaDirectiva(etiqueta,codop,operando,bandTemporal,fdTemp,bandTabsim,fdTabsim) == 1)
                        bandDirectiva=1;
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
                    bandAuxOp=Recupera(fdTabOp,codop,operando,etiqueta,bandTemporal,fdTemp,bandTabsim,fdTabsim);
                    if(bandAuxOp == 1)
                        bandDirectiva=1;
                }
                else
                {
                	bandAuxOperando=0;
                    strcpy(operando,"NULL");
                    printf("\nOPERANDO: %s\n",operando);
                    bandAuxOp=Recupera(fdTabOp,codop,operando,etiqueta,bandTemporal,fdTemp,bandTabsim,fdTabsim);
                    if(bandAuxOp == 1)
                    {
                        archAux.CONTLOC[4]='\0';
                        bandDirectiva=1;

                    }
                }
                if((bandOperando == 0) && (bandAuxOperando == 1))
                {
                	if((bEnd == 0) && (banderaAux == 0) && (bandDirectiva == 0))
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
        cont=0;
        if(bandTemporal == 1)
        {
            fseek(fdTemp,0,0);
            printf("\n\n\tCONTLOC\tETI\tCODOP\tOPERANDO\tCODIGO MAQUINA\n");
            while(fgets(cadenaTemporal,30,fdTemp))
            {
                for(i=0; i<5; i++)
                    valorTemp[i]='\0';
                for(i=0; i<10; i++)
                    codopTemp[i]='\0';
                for(i=0; i<10; i++)
                    operandoTemp[i]='\0';
                for(i=0; i<10; i++)
                    etiquetaTemp[i]='\0';
                for(i=0; i<8; i++)
                    op[i]='\0';
                for(i=0; i<10; i++)
                    cadenaAuxiliar[i]='\0';
                for(i=0; i<10; i++)
                    cadAux[i]='\0';
                for(i=0; i<10; i++)
                    cadAux1[i]='\0';
                for(i=0; i<10; i++)
                    operandoAuxiliar[i]='\0';
                for(i=0; i<10; i++)
                    cad_numero[i]='\0';
                for(i=0; i<3; i++)
                    registro[i]='\0';
                bandComa=0;
                bandSigno=0;
                band_signo=0;
                for(i=0; i<strlen(cadenaTemporal); i++)
                {
                    caracter=cadenaTemporal[i];
                    if((caracter != '\t') && (caracter != '\n'))
                    {
                        switch(cont)
                        {
                            case 0:
                                valorTemp[j]=caracter;
                                j++;
                            break;
                            case 1:
                                etiquetaTemp[j]=caracter;
                                j++;
                            break;
                            case 2:
                                codopTemp[j]=caracter;
                                j++;
                            break;
                            case 3:
                                operandoTemp[j]=caracter;
                                j++;
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
                cont=0;
                j=0;
                if(existeCodOp(fdTabOp,codopTemp) == 1)
                {
                    CODIGO_MAQUINA=RecuperaCodigoMaquina(fdTabOp,codopTemp,operandoTemp);
                    if(CODIGO_MAQUINA.bandera == 1)
                    {
                        printf("\n\n\t%s\t%s\t%s\t%s\t\t%s\n",valorTemp,etiquetaTemp,codopTemp,operandoTemp,CODIGO_MAQUINA.codmaqINH);
                    }
                    if((CODIGO_MAQUINA.bandera == 2) || (CODIGO_MAQUINA.bandera == 3))
                    {
                        strcpy(cadenaAuxiliar,operandoTemp);
                        for(n=0; n<10; n++)
                            operandoTemp[n]='\0';
                        m=0;
                        for(n=0; n < strlen(cadenaAuxiliar); n++)
                        {
                            if(cadenaAuxiliar[n] == '#')
                                banderaAuxiliar=1;
                            if((banderaAuxiliar == 1) && (cadenaAuxiliar[n] != '#') && (cadenaAuxiliar[n] != '\t'))
                            {
                                operandoTemp[m]=cadenaAuxiliar[n];
                                m++;
                            }
                        }
                        if(CODIGO_MAQUINA.bandera == 2)
                        {
                            if(operandoTemp[0] == '$')
                            {
                                m=0;
                                for(n=0; n<strlen(operandoTemp); n++)
                                {
                                    car=operandoTemp[n];
                                    if(car != '$')
                                    {
                                        op[m]=car;
                                        m++;
                                    }
                                }
                                if(strlen(op) == 2)
                                    strcat(CODIGO_MAQUINA.codmaqIMM,op);
                                else
                                {
                                    aux=0;
                                    longitud=strlen(op);
                                    total=2-longitud;
                                    for(i=0; i<total; i++)
                                    {
                                        cadenaAuxiliar[i]='0';
                                        aux++;
                                    }
                                    x=0;
                                    for(i=aux; i<2; i++)
                                    {
                                        cadenaAuxiliar[i]=op[x];
                                        x++;
                                    }
                                    strcat(CODIGO_MAQUINA.codmaqIMM,cadenaAuxiliar);
                                }
                            }
                            else
                            {
                                if(operandoTemp[0] == '@')
                                {
                                    m=0;
                                    for(n=0; n<strlen(operandoTemp); n++)
                                    {
                                        car=operandoTemp[n];
                                        if(car != '@')
                                        {
                                            op[m]=car;
                                            m++;
                                        }
                                    }
                                    valorDecimal=convierteOctalDecimal(op);
                                    itoa(valorDecimal,op,16);
                                    strupr(op);
                                    if(strlen(op) == 2)
                                        strcat(CODIGO_MAQUINA.codmaqIMM,op);
                                    else
                                    {
                                        aux=0;
                                        longitud=strlen(op);
                                        total=2-longitud;
                                        for(i=0; i<total; i++)
                                        {
                                            cadenaAuxiliar[i]='0';
                                            aux++;
                                        }
                                        x=0;
                                        for(i=aux; i<2; i++)
                                        {
                                            cadenaAuxiliar[i]=op[x];
                                            x++;
                                        }
                                        strcat(CODIGO_MAQUINA.codmaqIMM,cadenaAuxiliar);
                                    }
                                }
                                else
                                {
                                    if(operandoTemp[0] == '%')
                                    {
                                        m=0;
                                        for(n=0; n<strlen(operandoTemp); n++)
                                        {
                                            car=operandoTemp[n];
                                            if(car != '%')
                                            {
                                                op[m]=car;
                                                m++;
                                            }
                                        }
                                        valorDecimal=convierteBinarioDecimal(op);
                                        itoa(valorDecimal,op,16);
                                        strupr(op);
                                        if(strlen(op) == 2)
                                            strcat(CODIGO_MAQUINA.codmaqIMM,op);
                                        else
                                        {
                                            aux=0;
                                            longitud=strlen(op);
                                            total=2-longitud;
                                            for(i=0; i<total; i++)
                                            {
                                                cadenaAuxiliar[i]='0';
                                                aux++;
                                            }
                                            x=0;
                                            for(i=aux; i<2; i++)
                                            {
                                                cadenaAuxiliar[i]=op[x];
                                                x++;
                                            }
                                            strcat(CODIGO_MAQUINA.codmaqIMM,cadenaAuxiliar);
                                        }
                                    }
                                    else
                                    {
                                        if((operandoTemp[0] >= 48) && (operandoTemp[0] <= 57))
                                        {
                                            valorDecimal=atoi(operandoTemp);
                                            itoa(valorDecimal,op,16);
                                            strupr(op);
                                            if(strlen(op) == 2)
                                                strcat(CODIGO_MAQUINA.codmaqIMM,op);
                                            else
                                            {
                                                aux=0;
                                                longitud=strlen(op);
                                                total=2-longitud;
                                                for(i=0; i<total; i++)
                                                for(i=0; i<strlen(op); i++)
                                                {
                                                    cadenaAuxiliar[i]='0';
                                                    aux++;
                                                }
                                                x=0;
                                                for(i=aux; i<2; i++)
                                                {
                                                    cadenaAuxiliar[i]=op[x];
                                                    x++;
                                                }
                                                strcat(CODIGO_MAQUINA.codmaqIMM,cadenaAuxiliar);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            if(CODIGO_MAQUINA.bandera == 3)
                            {
                                if(operandoTemp[0] == '$')
                                {
                                    m=0;
                                    for(n=0; n<strlen(operandoTemp); n++)
                                    {
                                        car=operandoTemp[n];
                                        if(car != '$')
                                        {
                                            op[m]=car;
                                            m++;
                                        }
                                    }
                                    if(strlen(op) == 4)
                                        strcat(CODIGO_MAQUINA.codmaqIMM,op);
                                    else
                                    {
                                        aux=0;
                                        longitud=strlen(op);
                                        total=4-longitud;
                                        for(i=0; i<total; i++)
                                        {
                                            cadenaAuxiliar[i]='0';
                                            aux++;
                                        }
                                        x=0;
                                        for(i=aux; i<4; i++)
                                        {
                                            cadenaAuxiliar[i]=op[x];
                                            x++;
                                        }
                                        strcat(CODIGO_MAQUINA.codmaqIMM,cadenaAuxiliar);
                                    }
                                }
                                else
                                {
                                    if(operandoTemp[0] == '@')
                                    {
                                        m=0;
                                        for(n=0; n<strlen(operandoTemp); n++)
                                        {
                                            car=operandoTemp[n];
                                            if(car != '@')
                                            {
                                                op[m]=car;
                                                m++;
                                            }
                                        }
                                        valorDecimal=convierteOctalDecimal(op);
                                        itoa(valorDecimal,op,16);
                                        strupr(op);
                                        if(strlen(op) == 4)
                                            strcat(CODIGO_MAQUINA.codmaqIMM,op);
                                        else
                                        {
                                            aux=0;
                                            longitud=strlen(op);
                                            total=4-longitud;
                                            for(i=0; i<total; i++)
                                            {
                                                cadenaAuxiliar[i]='0';
                                                aux++;
                                            }
                                            x=0;
                                            for(i=aux; i<4; i++)
                                            {
                                                cadenaAuxiliar[i]=op[x];
                                                x++;
                                            }
                                            strcat(CODIGO_MAQUINA.codmaqIMM,cadenaAuxiliar);
                                        }
                                    }
                                    else
                                    {
                                        if(operandoTemp[0] == '%')
                                        {
                                            m=0;
                                            for(n=0; n<strlen(operandoTemp); n++)
                                            {
                                                car=operandoTemp[n];
                                                if(car != '%')
                                                {
                                                    op[m]=car;
                                                    m++;
                                                }
                                            }
                                            valorDecimal=convierteBinarioDecimal(op);
                                            itoa(valorDecimal,op,16);
                                            strupr(op);
                                            if(strlen(op) == 4)
                                                strcat(CODIGO_MAQUINA.codmaqIMM,op);
                                            else
                                            {
                                                aux=0;
                                                longitud=strlen(op);
                                                total=4-longitud;
                                                for(i=0; i<total; i++)
                                                {
                                                    cadenaAuxiliar[i]='0';
                                                    aux++;
                                                }
                                                x=0;
                                                for(i=aux; i<4; i++)
                                                {
                                                    cadenaAuxiliar[i]=op[x];
                                                    x++;
                                                }
                                                strcat(CODIGO_MAQUINA.codmaqIMM,cadenaAuxiliar);
                                            }
                                        }
                                        else
                                        {
                                            if((operandoTemp[0] >= 48) && (operandoTemp[0] <= 57))
                                            {
                                                valorDecimal=atoi(operandoTemp);
                                                itoa(valorDecimal,op,16);
                                                strupr(op);
                                                if(strlen(op) == 4)
                                                    strcat(CODIGO_MAQUINA.codmaqIMM,op);
                                                else
                                                {
                                                    aux=0;
                                                    longitud=strlen(op);
                                                    total=4-longitud;
                                                    for(i=0; i<total; i++)
                                                    {
                                                        cadenaAuxiliar[i]='0';
                                                        aux++;
                                                    }
                                                    x=0;
                                                    for(i=aux; i<4; i++)
                                                    {
                                                        cadenaAuxiliar[i]=op[x];
                                                        x++;
                                                    }
                                                    strcat(CODIGO_MAQUINA.codmaqIMM,cadenaAuxiliar);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        printf("\n\n\t%s\t%s\t%s\t%s\t\t%s\n",valorTemp,etiquetaTemp,codopTemp,operandoTemp,CODIGO_MAQUINA.codmaqIMM);
                    }
                    if(CODIGO_MAQUINA.bandera == 4)
                    {
                        if(operandoTemp[0] == '$')
                        {
                            m=0;
                            for(n=0; n<strlen(operandoTemp); n++)
                            {
                                car=operandoTemp[n];
                                if(car != '$')
                                {
                                    op[m]=car;
                                    m++;
                                }
                            }
                            if(strlen(op) == 2)
                                strcat(CODIGO_MAQUINA.codmaqDIR,op);
                            else
                            {
                                aux=0;
                                longitud=strlen(op);
                                total=2-longitud;
                                for(i=0; i<total; i++)
                                {
                                    cadenaAuxiliar[i]='0';
                                    aux++;
                                }
                                x=0;
                                for(i=aux; i<2; i++)
                                {
                                    cadenaAuxiliar[i]=op[x];
                                    x++;
                                }
                                strcat(CODIGO_MAQUINA.codmaqDIR,cadenaAuxiliar);
                            }
                        }
                        else
                        {
                            if(operandoTemp[0] == '@')
                            {
                                m=0;
                                for(n=0; n<strlen(operandoTemp); n++)
                                {
                                    car=operandoTemp[n];
                                    if(car != '@')
                                    {
                                        op[m]=car;
                                        m++;
                                    }
                                }
                                valorDecimal=convierteOctalDecimal(op);
                                itoa(valorDecimal,op,16);
                                strupr(op);
                                if(strlen(op) == 2)
                                    strcat(CODIGO_MAQUINA.codmaqDIR,op);
                                else
                                {
                                    aux=0;
                                    longitud=strlen(op);
                                    total=2-longitud;
                                    for(i=0; i<total; i++)
                                    {
                                        cadenaAuxiliar[i]='0';
                                        aux++;
                                    }
                                    x=0;
                                    for(i=aux; i<2; i++)
                                    {
                                        cadenaAuxiliar[i]=op[x];
                                        x++;
                                    }
                                    strcat(CODIGO_MAQUINA.codmaqDIR,cadenaAuxiliar);
                                }
                            }
                            else
                            {
                                if(operandoTemp[0] == '%')
                                {
                                    m=0;
                                    for(n=0; n<strlen(operandoTemp); n++)
                                    {
                                        car=operandoTemp[n];
                                        if(car != '%')
                                        {
                                            op[m]=car;
                                            m++;
                                        }
                                    }
                                    valorDecimal=convierteBinarioDecimal(op);
                                    itoa(valorDecimal,op,16);
                                    strupr(op);
                                    if(strlen(op) == 2)
                                        strcat(CODIGO_MAQUINA.codmaqDIR,op);
                                    else
                                    {
                                        aux=0;
                                        longitud=strlen(op);
                                        total=2-longitud;
                                        for(i=0; i<total; i++)
                                        {
                                            cadenaAuxiliar[i]='0';
                                            aux++;
                                        }
                                        x=0;
                                        for(i=aux; i<2; i++)
                                        {
                                            cadenaAuxiliar[i]=op[x];
                                            x++;
                                        }
                                        strcat(CODIGO_MAQUINA.codmaqDIR,cadenaAuxiliar);
                                    }
                                }
                                else
                                {
                                    if((operandoTemp[0] >= 48) && (operandoTemp[0] <= 57))
                                    {
                                        valorDecimal=atoi(operandoTemp);
                                        itoa(valorDecimal,op,16);
                                        strupr(op);
                                        if(strlen(op) == 2)
                                            strcat(CODIGO_MAQUINA.codmaqDIR,op);
                                        else
                                        {
                                            aux=0;
                                            longitud=strlen(op);
                                            total=2-longitud;
                                            for(i=0; i<total; i++)
                                            for(i=0; i<strlen(op); i++)
                                            {
                                                cadenaAuxiliar[i]='0';
                                                aux++;
                                            }
                                            x=0;
                                            for(i=aux; i<2; i++)
                                            {
                                                cadenaAuxiliar[i]=op[x];
                                                x++;
                                            }
                                            strcat(CODIGO_MAQUINA.codmaqDIR,cadenaAuxiliar);
                                        }
                                    }
                                }
                            }
                        }
                        printf("\n\n\t%s\t%s\t%s\t%s\t\t%s\n",valorTemp,etiquetaTemp,codopTemp,operandoTemp,CODIGO_MAQUINA.codmaqDIR);
                    }
                    if(CODIGO_MAQUINA.bandera == 5)
                    {
                        if(operandoTemp[0] == '$')
                        {
                            m=0;
                            for(n=0; n<strlen(operandoTemp); n++)
                            {
                                car=operandoTemp[n];
                                if(car != '$')
                                {
                                    op[m]=car;
                                    m++;
                                }
                            }
                            if(strlen(op) == 4)
                                strcat(CODIGO_MAQUINA.codmaqEXT,op);
                            else
                            {
                                aux=0;
                                longitud=strlen(op);
                                total=4-longitud;
                                for(i=0; i<total; i++)
                                {
                                    cadenaAuxiliar[i]='0';
                                    aux++;
                                }
                                x=0;
                                for(i=aux; i<4; i++)
                                {
                                    cadenaAuxiliar[i]=op[x];
                                    x++;
                                }
                                strcat(CODIGO_MAQUINA.codmaqEXT,cadenaAuxiliar);
                            }
                        }
                        else
                        {
                            if(operandoTemp[0] == '@')
                            {
                                m=0;
                                for(n=0; n<strlen(operandoTemp); n++)
                                {
                                    car=operandoTemp[n];
                                    if(car != '@')
                                    {
                                        op[m]=car;
                                        m++;
                                    }
                                }
                                valorDecimal=convierteOctalDecimal(op);
                                itoa(valorDecimal,op,16);
                                strupr(op);
                                if(strlen(op) == 4)
                                    strcat(CODIGO_MAQUINA.codmaqEXT,op);
                                else
                                {
                                    aux=0;
                                    longitud=strlen(op);
                                    total=4-longitud;
                                    for(i=0; i<total; i++)
                                    {
                                        cadenaAuxiliar[i]='0';
                                        aux++;
                                    }
                                    x=0;
                                    for(i=aux; i<4; i++)
                                    {
                                        cadenaAuxiliar[i]=op[x];
                                        x++;
                                    }
                                    strcat(CODIGO_MAQUINA.codmaqEXT,cadenaAuxiliar);
                                }
                            }
                            else
                            {
                                if(operandoTemp[0] == '%')
                                {
                                    m=0;
                                    for(n=0; n<strlen(operandoTemp); n++)
                                    {
                                        car=operandoTemp[n];
                                        if(car != '%')
                                        {
                                            op[m]=car;
                                            m++;
                                        }
                                    }
                                    valorDecimal=convierteBinarioDecimal(op);
                                    itoa(valorDecimal,op,16);
                                    strupr(op);
                                    if(strlen(op) == 4)
                                        strcat(CODIGO_MAQUINA.codmaqEXT,op);
                                    else
                                    {
                                        aux=0;
                                        longitud=strlen(op);
                                        total=4-longitud;
                                        for(i=0; i<total; i++)
                                        {
                                            cadenaAuxiliar[i]='0';
                                            aux++;
                                        }
                                        x=0;
                                        for(i=aux; i<4; i++)
                                        {
                                            cadenaAuxiliar[i]=op[x];
                                            x++;
                                        }
                                        strcat(CODIGO_MAQUINA.codmaqEXT,cadenaAuxiliar);
                                    }
                                }
                                else
                                {
                                    if((operandoTemp[0] >= 48) && (operandoTemp[0] <= 57))
                                    {
                                        valorDecimal=atoi(operandoTemp);
                                        itoa(valorDecimal,op,16);
                                        strupr(op);
                                        if(strlen(op) == 4)
                                            strcat(CODIGO_MAQUINA.codmaqEXT,op);
                                        else
                                        {
                                            aux=0;
                                            longitud=strlen(op);
                                            total=4-longitud;
                                            for(i=0; i<total; i++)
                                            {
                                                cadenaAuxiliar[i]='0';
                                                aux++;
                                            }
                                            x=0;
                                            for(i=aux; i<4; i++)
                                            {
                                                cadenaAuxiliar[i]=op[x];
                                                x++;
                                            }
                                            strcat(CODIGO_MAQUINA.codmaqEXT,cadenaAuxiliar);
                                        }
                                    }
                                }
                            }
                        }
                        printf("\n\n\t%s\t%s\t%s\t%s\t\t%s\n",valorTemp,etiquetaTemp,codopTemp,operandoTemp,CODIGO_MAQUINA.codmaqEXT);
                    }
                    else
                    {
                        if(CODIGO_MAQUINA.bandera == 6)
                        {
                            XB=RecuperaXB(operandoTemp,"5BCONST");
                            strcat(CODIGO_MAQUINA.codmaqIDX,XB.xb);
                            printf("\n\n\t%s\t%s\t%s\t%s\t\t%s\n",valorTemp,etiquetaTemp,codopTemp,operandoTemp,CODIGO_MAQUINA.codmaqIDX);
                        }
                        else
                        {
                            if(CODIGO_MAQUINA.bandera == 7)
                            {
                                strcpy(cadAux,operandoTemp);
                                n=0;
                                m=0;
                                if(cadAux[0] == '-')
                                    bandSigno=1;
                                for(i=0; i<strlen(cadAux); i++)
                                {
                                    if(cadAux[i] == ',')
                                    {
                                        bandComa=1;
                                    }
                                    if(bandComa == 0)
                                    {
                                        cad_numero[n]=cadAux[i];
                                        n++;
                                    }
                                    else
                                    {
                                        if(cadAux[i] != ',')
                                        {
                                            registro[m]=cadAux[i];
                                            m++;
                                        }
                                    }
                                }
                                n=0;
                                for(i=0; i<10; i++)
                                    cadAux[i]='\0';
                                for(i=0; i<strlen(cad_numero); i++)
                                {
                                    if(cad_numero[i] == '-')
                                        band_signo=1;
                                    else
                                    {
                                        cadAux[n]=cad_numero[i];
                                        n++;
                                    }
                                }
                                numeroAux=atoi(cadAux);
                                if(bandSigno == 0)
                                {
                                    operandoAuxiliar[0]= 'N';
                                    operandoAuxiliar[1]= ',';
                                    n=2;
                                    for(i=0; i<3; i++)
                                    {
                                        operandoAuxiliar[n]=registro[i];
                                        n++;
                                    }
                                }
                                else
                                {
                                    if(bandSigno == 1)
                                    {
                                        operandoAuxiliar[0]= '-';
                                        operandoAuxiliar[1]= 'N';
                                        operandoAuxiliar[2]= ',';
                                        n=3;
                                        for(i=0; i<4; i++)
                                        {
                                            operandoAuxiliar[n]=registro[i];
                                            n++;
                                        }
                                        valorDecimal=numeroAux;

                                        itoa((~valorDecimal)+1,cadComplemento,16);
                                        op[0]=cadComplemento[strlen(cadComplemento)-2];
                                        op[1]=cadComplemento[strlen(cadComplemento)-1];
                                        strupr(op);
                                    }
                                }
                                XB=RecuperaXB(operandoAuxiliar,"9BCONST");
                                strcat(CODIGO_MAQUINA.codmaqIDX1,XB.xb);

                                if(bandSigno == 0)
                                {
                                    valorDecimal=numeroAux;
                                    itoa(valorDecimal,op,16);
                                    strupr(op);
                                }

                                if(strlen(op) == 2)
                                    strcat(CODIGO_MAQUINA.codmaqIDX1,op);
                                else
                                {
                                    aux=0;
                                    longitud=strlen(op);
                                    total=2-longitud;
                                    for(i=0; i<total; i++)
                                    {
                                        cadenaAuxiliar[i]='0';
                                        aux++;
                                    }
                                    x=0;
                                    for(i=aux; i<2; i++)
                                    {
                                        cadenaAuxiliar[i]=op[x];
                                        x++;
                                    }
                                    strcat(CODIGO_MAQUINA.codmaqIDX1,cadenaAuxiliar);
                                }
                                printf("\n\n\t%s\t%s\t%s\t%s\t\t%s\n",valorTemp,etiquetaTemp,codopTemp,operandoTemp,CODIGO_MAQUINA.codmaqIDX1);
                            }
                            else
                            {
                                if(CODIGO_MAQUINA.bandera == 8)
                                {
                                    strcpy(cadAux,operandoTemp);
                                    n=0;
                                    m=0;
                                    for(i=0; i<strlen(cadAux); i++)
                                    {
                                        if(cadAux[i] == ',')
                                        {
                                            bandComa=1;
                                        }
                                        if(bandComa == 0)
                                        {
                                            cad_numero[n]=cadAux[i];
                                            n++;
                                        }
                                        else
                                        {
                                            if(cadAux[i] != ',')
                                            {
                                                registro[m]=cadAux[i];
                                                m++;
                                            }
                                        }
                                    }
                                    numeroAux=atoi(cadAux);
                                    operandoAuxiliar[0]= 'N';
                                    operandoAuxiliar[1]= ',';
                                    strcat(operandoAuxiliar,registro);
                                    XB=RecuperaXB(operandoAuxiliar,"16BCONST");
                                    strcat(CODIGO_MAQUINA.codmaqIDX2,XB.xb);

                                    valorDecimal=numeroAux;
                                    itoa(valorDecimal,op,16);
                                    strupr(op);
                                    if(strlen(op) == 4)
                                        strcat(CODIGO_MAQUINA.codmaqIDX2,op);
                                    else
                                    {
                                        aux=0;
                                        longitud=strlen(op);
                                        total=4-longitud;
                                        for(i=0; i<total; i++)
                                        {
                                            cadenaAuxiliar[i]='0';
                                            aux++;
                                        }
                                        x=0;
                                        for(i=aux; i<4; i++)
                                        {
                                            cadenaAuxiliar[i]=op[x];
                                            x++;
                                        }
                                        strcat(CODIGO_MAQUINA.codmaqIDX2,cadenaAuxiliar);
                                    }
                                    printf("\n\n\t%s\t%s\t%s\t%s\t\t%s\n",valorTemp,etiquetaTemp,codopTemp,operandoTemp,CODIGO_MAQUINA.codmaqIDX2);
                                }
                                else
                                {
                                    if(CODIGO_MAQUINA.bandera == 9)
                                    {
                                        XB=RecuperaXB(operandoTemp,"POST-DEC");
                                        strcat(CODIGO_MAQUINA.codmaqIDX,XB.xb);
                                        printf("\n\n\t%s\t%s\t%s\t%s\t\t%s\n",valorTemp,etiquetaTemp,codopTemp,operandoTemp,CODIGO_MAQUINA.codmaqIDX);
                                    }
                                    else
                                    {
                                        if(CODIGO_MAQUINA.bandera == 10)
                                        {
                                            XB=RecuperaXB(operandoTemp,"POST-INC");
                                            strcat(CODIGO_MAQUINA.codmaqIDX,XB.xb);
                                            printf("\n\n\t%s\t%s\t%s\t%s\t\t%s\n",valorTemp,etiquetaTemp,codopTemp,operandoTemp,CODIGO_MAQUINA.codmaqIDX);
                                        }
                                        else
                                        {
                                            if(CODIGO_MAQUINA.bandera == 11)
                                            {
                                                XB=RecuperaXB(operandoTemp,"PRE-INC");
                                                strcat(CODIGO_MAQUINA.codmaqIDX,XB.xb);
                                                printf("\n\n\t%s\t%s\t%s\t%s\t\t%s\n",valorTemp,etiquetaTemp,codopTemp,operandoTemp,CODIGO_MAQUINA.codmaqIDX);
                                            }
                                            else
                                            {
                                                if(CODIGO_MAQUINA.bandera == 12)
                                                {
                                                    XB=RecuperaXB(operandoTemp,"PRE-DEC");
                                                    strcat(CODIGO_MAQUINA.codmaqIDX,XB.xb);
                                                    printf("\n\n\t%s\t%s\t%s\t%s\t\t%s\n",valorTemp,etiquetaTemp,codopTemp,operandoTemp,CODIGO_MAQUINA.codmaqIDX);
                                                }
                                                else
                                                {
                                                    if(CODIGO_MAQUINA.bandera == 13)
                                                    {
                                                        if((operandoTemp[0] == 'A') || (operandoTemp[0] == 'a'))
                                                        {
                                                            XB=RecuperaXB(operandoTemp,"AOFFSET");
                                                            strcat(CODIGO_MAQUINA.codmaqIDX,XB.xb);
                                                            printf("\n\n\t%s\t%s\t%s\t%s\t\t%s\n",valorTemp,etiquetaTemp,codopTemp,operandoTemp,CODIGO_MAQUINA.codmaqIDX);
                                                        }
                                                        else
                                                        {
                                                            if((operandoTemp[0] == 'B') || (operandoTemp[0] == 'b'))
                                                            {
                                                                XB=RecuperaXB(operandoTemp,"BOFFSET");
                                                                strcat(CODIGO_MAQUINA.codmaqIDX,XB.xb);
                                                                printf("\n\n\t%s\t%s\t%s\t%s\t\t%s\n",valorTemp,etiquetaTemp,codopTemp,operandoTemp,CODIGO_MAQUINA.codmaqIDX);
                                                            }
                                                            else
                                                            {
                                                                if((operandoTemp[0] == 'D') || (operandoTemp[0] == 'd'))
                                                                {
                                                                    XB=RecuperaXB(operandoTemp,"DOFFSET");
                                                                    strcat(CODIGO_MAQUINA.codmaqIDX,XB.xb);
                                                                    printf("\n\n\t%s\t%s\t%s\t%s\t\t%s\n",valorTemp,etiquetaTemp,codopTemp,operandoTemp,CODIGO_MAQUINA.codmaqIDX);
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                else
                    printf("\n\n\t%s\t%s\t%s\t%s\t\tNo Encontrado\n",valorTemp,etiquetaTemp,codopTemp,operandoTemp);
            }
        }
    }
    else
        perror("");
    fclose(fd);
    fclose(fdTabOp);
    getch();
    return 0;
}
