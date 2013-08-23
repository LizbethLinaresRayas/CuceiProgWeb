#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <math.h>

typedef struct{
    char nomProgramador[20];
    char operacion[15];
    int TME;
    int numPrograma;
}PROCESO;

typedef struct{
    PROCESO P1;
    PROCESO P2;
    PROCESO P3;
    PROCESO P4;
    int contProceso;
}LOTE;

typedef struct{
    int numProg;
    char nomProg[20];
    char operacion[10];
    int resultado;
    int bnd;
}PROCESOTERMINADO;

typedef struct nodoProceso{
    PROCESO Proceso;
    struct nodoProceso * sig;
}nodoProceso;

typedef struct nodoLote{
    LOTE Lote;
    struct nodoLote * sig;
}nodoLote;

typedef struct nodoProcesoTerminado{
    PROCESOTERMINADO ProcesoTerminado;
    struct nodoProcesoTerminado * sig;
}nodoProcesoTerminado;

typedef struct nodoProceso NodoProceso;
typedef struct nodoLote NodoLote;
typedef struct nodoProcesoTerminado NodoProcesoTerminado;

typedef struct{
    NodoProceso *frente;
    NodoProceso *final;
}COLAPROCESO;

typedef struct{
    NodoLote *frente;
    NodoLote *final;
}COLALOTE;

typedef struct{
    NodoProcesoTerminado *frente;
    NodoProcesoTerminado *final;
}COLAPROCESOTERMINADO;

int gotoxy(short x, short y){

    COORD coord;
    HANDLE h_stdout;

    coord.X = x;
    coord.Y = y;

    if((h_stdout = GetStdHandle(STD_OUTPUT_HANDLE)) == INVALID_HANDLE_VALUE)
       return 0;

    if(SetConsoleCursorPosition(h_stdout, coord) == 0)
       return 0;

    return 1;
}

void inicializar(COLAPROCESO *C)
{
    NodoProceso *aux;
    aux = (NodoProceso*)malloc(sizeof(NodoProceso));
    aux->sig=NULL;
    C->final=aux;
    C->frente=aux;
}

void inicializarLote(COLALOTE *CL)
{
    NodoLote *aux;
    aux = (NodoLote*)malloc(sizeof(NodoLote));
    aux->sig=NULL;
    CL->final=aux;
    CL->frente=aux;
}

void inicializarProcesoTerminado(COLAPROCESOTERMINADO *CPT)
{
    NodoProcesoTerminado *aux;
    aux = (NodoProcesoTerminado*)malloc(sizeof(nodoProcesoTerminado));
    aux->sig=NULL;
    CPT->final=aux;
    CPT->frente=aux;
}

int vacia(COLAPROCESO *C)
{
    return (C->frente==C->final);
}

int vaciaLote(COLALOTE *CL)
{
    return (CL->frente == CL->final);
}

int vaciaProcesoTerminado(COLAPROCESOTERMINADO *CPT)
{
    return (CPT->frente == CPT->final);
}

void insertar(COLAPROCESO *C,PROCESO proceso)
{
    NodoProceso *aux;
    aux=(NodoProceso*)malloc(sizeof(NodoProceso));
    aux->Proceso=proceso;
    aux->sig=NULL;
    C->final->sig=aux;
    C->final=aux;
}

void insertaProcesoTerminado(COLAPROCESOTERMINADO *CPT,PROCESOTERMINADO procesoTerminado)
{
    NodoProcesoTerminado *aux;
    aux=(NodoProcesoTerminado*)malloc(sizeof(NodoProcesoTerminado));
    aux->ProcesoTerminado=procesoTerminado;
    aux->sig=NULL;
    CPT->final->sig=aux;
    CPT->final=aux;
}

void mostrarProcesoTerminado(COLAPROCESOTERMINADO *CPT,int numLote)
{
    int auxgoto=0;

    if(vaciaProcesoTerminado(CPT))
            puts("COLA VACIA...");
    else
    {
        NodoProcesoTerminado *aux;
        aux=CPT->frente->sig;
        while(aux != NULL)
        {
            gotoxy(89,12+auxgoto);printf("Num. Programa: %d ",aux->ProcesoTerminado.numProg);
            gotoxy(86,13+auxgoto);printf("Nom. Programador: %s ",aux->ProcesoTerminado.nomProg);
            gotoxy(93,14+auxgoto);printf("Operacion: %s",aux->ProcesoTerminado.operacion);
            gotoxy(93,15+auxgoto);printf("Resultado: %d",aux->ProcesoTerminado.resultado);
            gotoxy(94,16+auxgoto); printf("No. Lote: %d",numLote);
            aux=aux->sig;
            auxgoto+=6;
         }
    }
}

int totProceso(COLAPROCESO *C)
{
    int contProceso=0;

    NodoProceso *aux;
    aux=C->frente->sig;
    while(aux != NULL)
    {
        contProceso++;
        aux=aux->sig;
    }
    return contProceso;
}

void cargaLote(COLAPROCESO *C,COLALOTE *CL)
{
    int contProceso=0;
    int auxProceso=1;
    int contLote=0;
    int numLotes=0;
    int auxCociente=0;
    int auxMod=0;
    int auxiliar=0;
    int totalProceso=0;

    LOTE lote;

    lote.contProceso=0;
    NodoLote *aux1;
    NodoProceso *aux;

    contProceso=totProceso(C);

    if(contProceso <= 4)
    {
        aux=C->frente->sig;
        while((aux != NULL) && (contProceso > 0))
        {
            switch(auxProceso)
            {
                case 1:
                    strcpy(lote.P1.nomProgramador,aux->Proceso.nomProgramador);
                    strcpy(lote.P1.operacion,aux->Proceso.operacion);
                    lote.P1.TME=aux->Proceso.TME;
                    lote.P1.numPrograma=aux->Proceso.numPrograma;
                    lote.contProceso=1;
                break;
                case 2:
                    strcpy(lote.P2.nomProgramador,aux->Proceso.nomProgramador);
                    strcpy(lote.P2.operacion,aux->Proceso.operacion);
                    lote.P2.TME=aux->Proceso.TME;
                    lote.P2.numPrograma=aux->Proceso.numPrograma;
                    lote.contProceso=2;
                break;
                case 3:
                    strcpy(lote.P3.nomProgramador,aux->Proceso.nomProgramador);
                    strcpy(lote.P3.operacion,aux->Proceso.operacion);
                    lote.P3.TME=aux->Proceso.TME;
                    lote.P3.numPrograma=aux->Proceso.numPrograma;
                    lote.contProceso=3;
                break;
                case 4:
                    strcpy(lote.P4.nomProgramador,aux->Proceso.nomProgramador);
                    strcpy(lote.P4.operacion,aux->Proceso.operacion);
                    lote.P4.TME=aux->Proceso.TME;
                    lote.P4.numPrograma=aux->Proceso.numPrograma;
                    lote.contProceso=4;
                break;
            }
            auxProceso++;
            aux=aux->sig;
            contProceso--;
        }
        aux1=(NodoLote*)malloc(sizeof(NodoLote));
        aux1->Lote=lote;
        aux1->sig=NULL;
        CL->final->sig=aux1;
        CL->final=aux1;
    }
    else
    {
        auxiliar=contProceso;
        auxCociente=contProceso / 4;
        auxMod=contProceso % 4;
        if(auxMod == 0)
            numLotes=auxCociente;
        else
            numLotes=auxCociente+1;
        aux=C->frente->sig;
        while((aux != NULL) && (contProceso > 0))
        {
            switch(auxProceso)
            {
                case 1:
                    strcpy(lote.P1.nomProgramador,aux->Proceso.nomProgramador);
                    strcpy(lote.P1.operacion,aux->Proceso.operacion);
                    lote.P1.TME=aux->Proceso.TME;
                    lote.P1.numPrograma=aux->Proceso.numPrograma;
                    lote.contProceso=1;
                break;
                case 2:
                    strcpy(lote.P2.nomProgramador,aux->Proceso.nomProgramador);
                    strcpy(lote.P2.operacion,aux->Proceso.operacion);
                    lote.P2.TME=aux->Proceso.TME;
                    lote.P2.numPrograma=aux->Proceso.numPrograma;
                    lote.contProceso=2;
                break;
                case 3:
                    strcpy(lote.P3.nomProgramador,aux->Proceso.nomProgramador);
                    strcpy(lote.P3.operacion,aux->Proceso.operacion);
                    lote.P3.TME=aux->Proceso.TME;
                    lote.P3.numPrograma=aux->Proceso.numPrograma;
                    lote.contProceso=3;
                break;
                case 4:
                    strcpy(lote.P4.nomProgramador,aux->Proceso.nomProgramador);
                    strcpy(lote.P4.operacion,aux->Proceso.operacion);
                    lote.P4.TME=aux->Proceso.TME;
                    lote.P4.numPrograma=aux->Proceso.numPrograma;
                    lote.contProceso=4;
                break;
            }
            auxProceso++;
            aux=aux->sig;
            contProceso--;
            totalProceso++;
            if((lote.contProceso == 4) || (auxiliar == totalProceso))
            {
                aux1=(NodoLote*)malloc(sizeof(NodoLote));
                aux1->Lote=lote;
                aux1->sig=NULL;
                CL->final->sig=aux1;
                CL->final=aux1;
                contLote++;
                auxProceso=1;
            }
        }
    }
}

void delay(int x)
{
    int i;
    for(i=0; i<=x*1000000; i++);
}

void barra(){
    int i;

    //system("COLOR f2");
    //printf("color(f color fondo --- 2 color letra)\n");
    gotoxy(45,27);printf("Procesando... ");
    for(i=60; i<80; i++)
    {
        delay(50);
        gotoxy(i,27);printf("%c",219);
    }
    //gotoxy(i,23);system("pause");
}

int suma(int num1,int num2)
{
    return num1+num2;
}

int resta(int num1,int num2)
{
    return num1-num2;
}

int division(int num1,int num2)
{
    if(num2 == 0)
        return -1;
    else
        return num1/num2;
}

int multiplicacion(int num1,int num2)
{
    return num1*num2;
}

int modulo(int num1,int num2)
{
    return num1%num2;
}

int potencia(int num1,int num2)
{
    return pow(num1,num2);
}

void Proceso(COLALOTE *CL,int cantProceso)
{
    int contLote=0;
    char operacion[10];
    int numLotesPendientes=0;
    int auxCociente=0;
    int auxMod=0;
    int numLotes=0;
    int i=0;
    int j=0;
    int k=0;
    int m=0;
    int contAux=1;
    int auxProceso=1;
    int contOperador=0;
    int num=0;
    int num1=0;
    char caracter;
    int bndFin=0;
    int relojGlobal=0;
    int resultado=0;
    int auxgoto=0;
    int bnd1=0;

    char operando1[4];
    char operando2[4];
    char operador1;
    char nombreProgramador[15];

    COLAPROCESOTERMINADO CPT;
    PROCESOTERMINADO procesoTerminado;
    PROCESO proceso;

    inicializarProcesoTerminado(&CPT);

    if(!vaciaLote(CL))
    {
        contLote++;//Lotes Generados
        auxCociente=cantProceso / 4;
        auxMod=cantProceso % 4;
        if(auxMod == 0)  //total de lotes
            numLotes=auxCociente;
        else
            numLotes=auxCociente+1;

        numLotesPendientes=numLotes-1; // lotes pendientes
        if(numLotesPendientes < 0)   //si resulta negativo se asigna 0
            numLotesPendientes=0;

        NodoLote *aux;    //primer nodo
        aux=CL->frente->sig;
        system("cls");
        while(aux != NULL)
        {
            while((auxProceso <= cantProceso) && (bndFin == 0))
            {
                switch(auxProceso)//la variable operacion toma valor
                {
                    case 1:
                        strcpy(operacion,aux->Lote.P1.operacion);
                    break;
                    case 2:
                        strcpy(operacion,aux->Lote.P2.operacion);
                    break;
                    case 3:
                        strcpy(operacion,aux->Lote.P3.operacion);
                    break;
                    case 4:
                        strcpy(operacion,aux->Lote.P4.operacion);
                    break;
                }
                //Se resuelve operacion
                caracter='\0';
                contAux=1;//Asigna el valor al operando que corresponda
                contOperador=0;//Determina el numero del operador
                j=0;
                for(i=0; i<strlen(operacion); i++) // separa operandos y operadores
                {
                    caracter=operacion[i];
                    if((caracter >= 48) && (caracter <= 57))
                    {
                        switch(contAux)
                        {
                             case 1:
                                operando1[j]=caracter;
                                j++;
                            break;
                            case 2:
                                operando2[j]=caracter;
                                j++;
                            break;
                        }
                    }
                    else
                    {
                        if(contOperador == 0)
                        {
                            operador1=caracter;
                            contOperador++;
                            j=0;
                            contAux++;
                        }
                    }
                }
                if(contOperador == 1)
                {
                    num=atoi(operando1);
                    num1=atoi(operando2);
                    switch(operador1)
                    {
                        case '+':
                            resultado=suma(num,num1);                    break;
                        case '*':
                            resultado=multiplicacion(num,num1);
                        break;
                        case '-':
                            resultado=resta(num,num1);
                        break;
                        case '/':
                            resultado=division(num,num1);
                        break;
                        case '%':
                            resultado=modulo(num,num1);
                        break;
                        case '^':
                            resultado=potencia(num,num1);
                        break;
                    }
                }
                system("cls");
                auxgoto=0;
                gotoxy(10,6);printf("Numero de lotes pendientes: %d",numLotesPendientes);
                //procesos terminados
                if((procesoTerminado.bnd == 1) && (bnd1 == 0))
                {
                    gotoxy(89,12);printf("                                 ");
                    gotoxy(94,10);printf("Proceso Terminado");
                    insertaProcesoTerminado(&CPT,procesoTerminado);
                    mostrarProcesoTerminado(&CPT,contLote);
                }
                else
                {
                    gotoxy(94,10);printf("Proceso Terminado");
                    gotoxy(89,12);printf("No hay Procesos Terminados.");
                }
                if(numLotes > 1)
                {
                    if(auxProceso >= 4)
                        bnd1=1;
                }

                //Procesos en ejecucion
                gotoxy(57,10);printf("Proceso en Ejecucion");

                switch(auxProceso)
                {
                    case 1:
                        proceso=aux->Lote.P1;
                        strcpy(aux->Lote.P1.nomProgramador,"NULO");
                    break;
                    case 2:
                        proceso=aux->Lote.P2;
                        strcpy(aux->Lote.P2.nomProgramador,"NULO");
                    break;
                    case 3:
                        proceso=aux->Lote.P3;
                        strcpy(aux->Lote.P3.nomProgramador,"NULO");
                    break;
                    case 4:
                        proceso=aux->Lote.P4;
                        strcpy(aux->Lote.P4.nomProgramador,"NULO");
                    break;
                }
                strcpy(nombreProgramador,proceso.nomProgramador);
                strcpy(proceso.nomProgramador,"NULO");

                //Lotes en ejecucion
                gotoxy(14,10);printf("Lote en Ejecucion");
                gotoxy(7,12); printf("No. Lote en Ejec: %d",contLote);

                switch(aux->Lote.contProceso)
                {
                    case 1:
                        if((strcmp(aux->Lote.P1.nomProgramador,"NULO")) != 0)
                        {
                            gotoxy(5,14+auxgoto); printf("Nombre Programador: %s",aux->Lote.P1.nomProgramador);
                            gotoxy(20,16+auxgoto);printf("TME: %d",aux->Lote.P1.TME);
                            auxgoto+=4;
                        }
                    break;
                    case 2:
                        if(aux->Lote.contProceso == 2)
                        {
                            if((strcmp(aux->Lote.P1.nomProgramador,"NULO")) != 0)
                            {
                                gotoxy(5,14+auxgoto);printf("Nombre Programador: %s",aux->Lote.P1.nomProgramador);
                                gotoxy(20,16+auxgoto);printf("TME: %d",aux->Lote.P1.TME);
                                auxgoto+=4;
                            }
                            if((strcmp(aux->Lote.P2.nomProgramador,"NULO")) != 0)
                            {
                                gotoxy(5,14+auxgoto);printf("Nombre Programador: %s",aux->Lote.P2.nomProgramador);
                                gotoxy(20,16+auxgoto);printf("TME: %d",aux->Lote.P2.TME);
                                auxgoto+=4;
                            }
                        }
                    break;
                    case 3:
                        if((strcmp(aux->Lote.P1.nomProgramador,"NULO")) != 0)
                        {
                            gotoxy(5,14+auxgoto);printf("Nombre Programador: %s",aux->Lote.P1.nomProgramador);
                            gotoxy(20,16+auxgoto);printf("TME: %d",aux->Lote.P1.TME);
                            auxgoto+=4;
                        }
                        if((strcmp(aux->Lote.P2.nomProgramador,"NULO")) != 0)
                        {
                            gotoxy(5,14+auxgoto);printf("Nombre Programador: %s",aux->Lote.P2.nomProgramador);
                            gotoxy(20,16+auxgoto);printf("TME: %d",aux->Lote.P2.TME);
                            auxgoto+=4;
                        }
                        if((strcmp(aux->Lote.P3.nomProgramador,"NULO")) != 0)
                        {
                            gotoxy(5,14+auxgoto);printf("Nombre Programador: %s",aux->Lote.P3.nomProgramador);
                            gotoxy(20,16+auxgoto);printf("TME: %d",aux->Lote.P3.TME);
                            auxgoto+=4;
                        }
                    break;
                    case 4:
                        if((strcmp(aux->Lote.P1.nomProgramador,"NULO")) != 0)
                        {
                            gotoxy(5,14+auxgoto);printf("Nombre Programador: %s",aux->Lote.P1.nomProgramador);
                            gotoxy(20,16+auxgoto);printf("TME: %d",aux->Lote.P1.TME);
                            auxgoto+=4;
                        }
                        if((strcmp(aux->Lote.P2.nomProgramador,"NULO")) != 0)
                        {
                            gotoxy(5,14+auxgoto);printf("Nombre Programador: %s",aux->Lote.P2.nomProgramador);
                            gotoxy(20,16+auxgoto);printf("TME: %d",aux->Lote.P2.TME);
                            auxgoto+=4;
                        }
                        if((strcmp(aux->Lote.P3.nomProgramador,"NULO")) != 0)
                        {
                            gotoxy(5,14+auxgoto);printf("Nombre Programador: %s",aux->Lote.P3.nomProgramador);
                            gotoxy(20,16+auxgoto);printf("TME: %d",aux->Lote.P3.TME);
                            auxgoto+=4;
                        }
                        if((strcmp(aux->Lote.P4.nomProgramador,"NULO")) != 0)
                        {
                            gotoxy(5,14+auxgoto);printf("Nombre Programador: %s",aux->Lote.P4.nomProgramador);
                            gotoxy(20,16+auxgoto);printf("TME: %d",aux->Lote.P4.TME);
                        }
                    break;
                }

                gotoxy(49,12);printf("Nom. Programador: %s",nombreProgramador);
                gotoxy(56,14);printf("Operacion: %s",proceso.operacion);
                gotoxy(62,16);printf("TME: %d",proceso.TME);
                gotoxy(52,18);printf("Num. Programa: %d",proceso.numPrograma);
                gotoxy(62,20);printf("TTE: ");
                gotoxy(62,22);printf("TRE: ");
                m=proceso.TME;
                for(k=0; k<proceso.TME; k++)
                {
                    delay(800);
                    gotoxy(62,20);printf("TTE: %d",k);
                    gotoxy(62,22);printf("TRE: %d",m);
                    m--;
                }
                barra();
                delay(300);
                gotoxy(62,20);printf("TTE: %d",k);
                gotoxy(62,22);printf("TRE: %d",m);
                delay(100);
                gotoxy(45,27);printf(" Terminado... ");
                procesoTerminado.numProg=proceso.numPrograma;
                strcpy(procesoTerminado.nomProg,nombreProgramador);
                strcpy(procesoTerminado.operacion,proceso.operacion);
                procesoTerminado.resultado=resultado;
                procesoTerminado.bnd=1;
                relojGlobal+=proceso.TME;

                if((aux->Lote.contProceso == 1) && (bnd1 == 0))
                {
                    gotoxy(89,12);printf("                                 ");
                    gotoxy(94,10);printf("Proceso Terminado");
                    insertaProcesoTerminado(&CPT,procesoTerminado);
                    mostrarProcesoTerminado(&CPT,contLote);
                    gotoxy(57,10);printf("Proceso en Ejecucion");
                    gotoxy(49,12);printf("Nom. Programador:        ");
                    gotoxy(56,14);printf("Operacion:            ");
                    gotoxy(62,16);printf("TME:              ");
                    gotoxy(52,18);printf("Num. Programa:     ");
                    gotoxy(62,20);printf("TTE:         ");
                    gotoxy(62,22);printf("TRE:       ");
                    gotoxy(35,27);printf("                                                                    ");
                    gotoxy(49,26);printf("No Hay proceso en Ejecucion.");
                    bndFin=1;
                }
                if((auxProceso == cantProceso) && (bnd1 == 0))
                {
                    if(bndFin == 0)
                    {
                        gotoxy(89,12);printf("                                 ");
                        gotoxy(94,10);printf("Proceso Terminado");
                        insertaProcesoTerminado(&CPT,procesoTerminado);
                        mostrarProcesoTerminado(&CPT,contLote);
                        bnd1=1;
                    }
                    gotoxy(57,10);printf("Proceso en Ejecucion");
                    gotoxy(49,12);printf("Nom. Programador:        ");
                    gotoxy(56,14);printf("Operacion:            ");
                    gotoxy(62,16);printf("TME:              ");
                    gotoxy(52,18);printf("Num. Programa:     ");
                    gotoxy(62,20);printf("TTE:         ");
                    gotoxy(62,22);printf("TRE:       ");
                    gotoxy(35,27);printf("                                                                    ");
                    gotoxy(49,26);printf("No Hay proceso en Ejecucion.");
                }
                gotoxy(63,34);printf("Contador Global: %d",relojGlobal);
                auxProceso++; //Se incrementa en cada proceso
                delay(80);
            }
            aux=aux->sig;
            auxProceso=1;
            numLotesPendientes--;
            contLote++;
            bnd1=0;
         }
    }
}

int validaOperacion(char operacion[10])
{
    int i=0;
    int j=0;
    char caracter;
    char operador;
    int bnd=1;
    char operando1[10];
    char operando2[10];
    int contAux=1;
    int contOperador=0;
    int num=0;
    int num1=0;

    for(i=0; i<10; i++)
        operando1[i]='\0';
    for(i=0; i<10; i++)
        operando2[i]='\0';

    for(i=0; i<strlen(operacion); i++) // separa operandos y operadores
    {
        caracter=operacion[i];
        if((caracter >= 48) && (caracter <= 57))
        {
            if(contAux == 1)
            {
                operando1[j]=caracter;
                j++;
            }
            else
            {
                if(contAux == 2)
                {
                    operando2[j]=caracter;
                    j++;
                }
            }
        }
        else
        {
            operador=caracter;
            if((operador == '+') || (operador == '-') || (operador == '/') || (operador == '*') || (operador == '%') || (operador == '^'))
            {
                contOperador++;
                j=0;
                contAux++;
            }
        }
    }
    if(contOperador == 1)
    {
        num=atoi(operando1);
        num1=atoi(operando2);
        switch(operador)
        {
            case '/':
                if(num1 == 0)
                    bnd=0;
            break;
            case '%':
                if(num1 == 0)
                    bnd=0;
            break;
        }
    }
    return bnd;
}

int main()
{
    int cantProceso=0;
    int contProceso=0;
    int bnd=0;
    int bnd1=0;
    int bnd2=1;
    int Arreglo[10];
    int i=0;
    int j=0;

    PROCESO proceso;
    COLAPROCESO C;
    COLALOTE CL;

    inicializar(&C);
    inicializarLote(&CL);
    system("cls");

    gotoxy(14,6);printf("Cantidad de Procesos: ");
    scanf("%d",&cantProceso);

    while(contProceso < cantProceso)
    {
        system("cls");
        gotoxy(35,4);printf("Proceso No.%d",contProceso+1);
        gotoxy(33,8);printf("Ingresa los siguientes datos:");
        gotoxy(10,10);printf("Nombre de Programador:");
        fflush(stdin);
        gotoxy(33,10);gets(proceso.nomProgramador);
        gotoxy(22,12);printf("Operacion:                ");
        fflush( stdin);
        gotoxy(33,12);gets(proceso.operacion);
        bnd2=validaOperacion(proceso.operacion);
        while(bnd2 == 0)
        {
            gotoxy(23,20);printf("Operacion Invalida.");
            gotoxy(22,12);printf("Operacion:                ");
            fflush(stdin);
            gotoxy(33,12);gets(proceso.operacion);
            bnd2=validaOperacion(proceso.operacion);
            gotoxy(23,20);printf("                               ");
        }
        gotoxy(9,14);printf("Tiempo Maximo Estimado:");
        fflush(stdin);
        gotoxy(33,14);scanf("%d",&proceso.TME);
        if(proceso.TME > 0)
            bnd1=1;
        while(bnd1 == 0)
        {
            gotoxy(23,20);printf("El TME tiene que ser mayor a 0.");
            gotoxy(9,14);printf("Tiempo Maximo Estimado:      ");
            fflush(stdin);
            gotoxy(33,14);scanf("%d",&proceso.TME);
            if(proceso.TME > 0)
                bnd1=1;
        }
        gotoxy(23,20);printf("                               ");
        gotoxy(13,16);printf("Numero de Programa:");
        fflush(stdin);
        gotoxy(33,16);scanf("%d",&proceso.numPrograma);
        for(j=0; j<10; j++)
        {
            if(bnd == 0)
            {
                if(Arreglo[j] == proceso.numPrograma)
                    bnd=1;
            }
        }
        if(bnd == 1)
        {
            while(bnd == 1)
            {
                gotoxy(23,20);printf("ID Existente...Intente de Nuevo");
                bnd=0;
                gotoxy(13,16);printf("Numero de Programa:  ");
                fflush(stdin);
                gotoxy(33,16);scanf("%d",&proceso.numPrograma);
                for(j=0; j<10; j++)
                {
                    if(Arreglo[j] == proceso.numPrograma)
                        bnd=1;
                }
                getch();
            }
            if(bnd == 0)
            {
                insertar(&C,proceso);
                contProceso++;
                Arreglo[i]=proceso.numPrograma;
                i++;
                gotoxy(23,20);printf(" ...Proceso No.%d Almacenado... ",contProceso);
                getch();
            }
        }
        else
        {
            insertar(&C,proceso);
            contProceso++;
            Arreglo[i]=proceso.numPrograma;
            i++;
            gotoxy(28,20);printf("...Proceso No.%d Almacenado...",contProceso);
            getch();
        }
        bnd=0;
        bnd1=0;
        bnd2=1;
    }
    cargaLote(&C,&CL);
    Proceso(&CL,cantProceso);
    getch();
    return 0;
}
