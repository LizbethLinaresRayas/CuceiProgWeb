#include <stdio.h>
#include <stdlib.h>
#include <String.h>

int main()
{

    int i=0;
    int j=0;
    int k=0;
    int l=0;
    int numero=0;
    int numAux=0;
    char cadenaAux[4];
    char cadenaTotal[6];
    int numeroTotal=0;
    char cadena[10];
    char caracter;
    int longitud=0;
    strcpy(cadena,"1010");

    for(i=0; i<6; i++)
        cadenaTotal[i]='\0';
    for(i=0; i<4; i++)
        cadenaAux[i]='\0';
    for(i=0; i<10; i++)
        cadena[i]='\0';


    longitud=strlen(cadena);
    j=3;
    for(i=longitud-1; i>=0; i--)
    {
        cadenaAux[j]=cadena[i];
        j--;
        if(j < 0)
        {
            for(k=0; k<4; k++)
            {
                if(cadenaAux[k] == '1')
                    numAux=1;
                else
                {
                    if(cadenaAux[k] == '0')
                        numAux=0;
                }
                if(k == 0)
                {
                    numero=numAux*8;
                    numeroTotal+=numero;
                }
                else
                {
                    if(k == 1)
                    {
                        numero=numAux*4;
                        numeroTotal+=numero;
                    }
                    else
                    {
                        if(k == 2)
                        {
                            numero=numAux*2;
                            numeroTotal+=numero;
                        }
                        else
                        {
                            if(k == 3)
                            {
                                numero=numAux*1;
                                numeroTotal+=numero;
                            }
                        }
                    }
                }
            }
            switch(numeroTotal)
            {
                case 1:
                    caracter='1';
                break;
                case 2:
                    caracter='2';
                break;
                case 3:
                    caracter='3';
                break;
                case 4:
                    caracter='4';
                break;
                case 5:
                    caracter='5';
                break;
                case 6:
                    caracter='6';
                break;
                case 7:
                    caracter='7';
                break;
                case 8:
                    caracter='8';
                break;
                case 9:
                    caracter='9';
                break;
                case 10:
                    caracter='A';
                break;
                case 11:
                    caracter='B';
                break;
                case 12:
                    caracter='C';
                break;
                case 13:
                    caracter='D';
                break;
                case 14:
                    caracter='E';
                break;
                case 15:
                    caracter='F';
                break;
            }


            cadenaTotal[l]=caracter;
            l++;
            j=0;
        }
    }
    printf("Numero: %s",cadenaTotal);
    return 0;
}
