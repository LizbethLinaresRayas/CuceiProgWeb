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

            aux=pow(16,j);
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
        if((band == 1) && (operando[i] != '#') && (operando[i] != '-'))
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

int Recupera(FILE * fdTabOp,char codop[12],char operando[10])
{
    TAB_OP TABOP;
    MOD_DIRECCIONAMIENTO MODODIRECCIONAMIENTO;
	int i=0;
	int j=0;
	int k=0;
	int cont=0;
	int aux=0;
	int banderaAux=0;
	char cadena[50];
	char caracter;
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
                }
                else
                {
                    if(bandModoImm == 2)
                    {
                        printf("\n\n\tInmediato de 16 bits, de %c bytes ",MODODIRECCIONAMIENTO.sumaBytesIMM);
                        banderaAux=1;
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
        }
        else
        {
            if(bandModoDirExt == 2)
            {
                printf("\n\n\tExtendido, de %c bytes",MODODIRECCIONAMIENTO.sumaBytesEXT);
                bandModoExt=1;
                banderaAux=1;
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
        }
        else
        {
            if(bandAuxModoIDX == 4)
            {
                printf("\n\n\tIndizado de 9 bits, %c bytes",MODODIRECCIONAMIENTO.sumaBytesIDX1);
                bandAuxModoIDX1=1;
                banderaAux=1;
            }
            else
            {
                if(bandAuxModoIDX == 5)
                {
                    printf("\n\n\tIndizado de 16 bits, %c bytes",MODODIRECCIONAMIENTO.sumaBytesIDX2);
                    bandAuxModoIDX2=1;
                    banderaAux=1;
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
                        }
                        else
                        {
                            if(post == 2)
                            {
                                printf("\n\n\tIndizado de Auto Post Imncremento, %c bytes",MODODIRECCIONAMIENTO.sumaBytesIDX);
                                bandAuxModoIDXPre=1;
                                banderaAux=1;
                            }
                            else
                            {
                                if(pre == 2)
                                {
                                    printf("\n\n\tIndizado de Auto Pre Incremento, %c bytes",MODODIRECCIONAMIENTO.sumaBytesIDX);
                                    bandAuxModoIDXPre=1;
                                    banderaAux=1;
                                }
                                else
                                {
                                    if(pre == 1)
                                    {
                                        printf("\n\n\tIndizado de Auto Pre Decremento, %c bytes",MODODIRECCIONAMIENTO.sumaBytesIDX);
                                        bandAuxModoIDXPre=1;
                                        banderaAux=1;
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
            printf("\n\n\tRelativo de 8 bits,de %c bytes",MODODIRECCIONAMIENTO.sumaBytesREL);
        else
        {
            if(bandRelativo16 == 1)
                printf("\n\n\tRelativo de 16 bits,de %c bytes",MODODIRECCIONAMIENTO.sumaBytesREL);
        }
    }

	return banderaAux;
}

int main()
{
    FILE *fd;
    FILE *fdTabOp;
    int i=0,j=0,k=0;
    int cont=1;
    int contop=1;
    int contEtiqueta=0;
    int contCodop=0; //contadores
    int bEnd=0;
    int band=0;
    int bandComentario=0;
    int bandOpe=0;
    int bandcont=0; //banderas
    int bandOperando=0;
    int bandAuxOperando=0;
    int banderaAux=0;
    int bandAuxOp=0;
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
                    bandAuxOp=Recupera(fdTabOp,codop,operando);
                }
                else
                {
                	bandAuxOperando=0;
                    strcpy(operando,"NULL");
                    printf("\nOPERANDO: %s\n",operando);
                    bandAuxOp=Recupera(fdTabOp,codop,operando);
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
    fclose(fd);
    fclose(fdTabOp);
    return 0;
    getch();
}
