#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct{
    int bndStatus;
    char operacion[15];
    int resultado;
    int TME;
    int numPrograma;
    int TiempoRest;

}PROCESO;

typedef struct{
    PROCESO P1;
    PROCESO P2;
    PROCESO P3;
    PROCESO P4;
    int contProceso;
}LOTE;

typedef struct{
    PROCESO P1;
    PROCESO P2;
    PROCESO P3;
    PROCESO P4;
    PROCESO P5;
    PROCESO P6;
    PROCESO P7;
    PROCESO P8;
    PROCESO P9;
    PROCESO P10;
    PROCESO P11;
    PROCESO P12;
    int contProceso;
}LOTE_ESPERA;

typedef struct{
    int numProg;
    char nomProg[20];
    char operacion[10];
    int resultado;
    int bnd;
    int TME;
    int TiempoRest;
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

    if(!vaciaProcesoTerminado(CPT))
    {
        NodoProcesoTerminado *aux;
        aux=CPT->frente->sig;
        while(aux != NULL)
        {
            gotoxy(89,13+auxgoto);printf("Num. Programa: %d ",aux->ProcesoTerminado.numProg);
            gotoxy(93,15+auxgoto);printf("Operacion: %s",aux->ProcesoTerminado.operacion);
            if(aux->ProcesoTerminado.resultado == 0)
            {
                gotoxy(93,17+auxgoto);printf("Resultado: Error Ejecucion");
            }
            else
            {
                gotoxy(93,17+auxgoto);printf("Resultado: %d",aux->ProcesoTerminado.resultado);
            }
            gotoxy(94,19+auxgoto); printf("No. Lote: %d",numLote);
            aux=aux->sig;
            auxgoto+=10;
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
                    lote.P1.bndStatus=aux->Proceso.bndStatus;
                    strcpy(lote.P1.operacion,aux->Proceso.operacion);
                    lote.P1.TME=aux->Proceso.TME;
                    lote.P1.TiempoRest=aux->Proceso.TiempoRest;
                    lote.P1.numPrograma=aux->Proceso.numPrograma;
                    lote.contProceso=1;
                break;
                case 2:
                    lote.P2.bndStatus=aux->Proceso.bndStatus;
                    strcpy(lote.P2.operacion,aux->Proceso.operacion);
                    lote.P2.TME=aux->Proceso.TME;
                    lote.P2.TiempoRest=aux->Proceso.TiempoRest;
                    lote.P2.numPrograma=aux->Proceso.numPrograma;
                    lote.contProceso=2;
                break;
                case 3:
                    lote.P3.bndStatus=aux->Proceso.bndStatus;
                    strcpy(lote.P3.operacion,aux->Proceso.operacion);
                    lote.P3.TME=aux->Proceso.TME;
                    lote.P3.TiempoRest=aux->Proceso.TiempoRest;
                    lote.P3.numPrograma=aux->Proceso.numPrograma;
                    lote.contProceso=3;
                break;
                case 4:
                    lote.P4.bndStatus=aux->Proceso.bndStatus;
                    strcpy(lote.P4.operacion,aux->Proceso.operacion);
                    lote.P4.TME=aux->Proceso.TME;
                    lote.P4.TiempoRest=aux->Proceso.TiempoRest;
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
                    lote.P1.bndStatus=aux->Proceso.bndStatus;
                    strcpy(lote.P1.operacion,aux->Proceso.operacion);
                    lote.P1.TME=aux->Proceso.TME;
                    lote.P1.TiempoRest=aux->Proceso.TiempoRest;
                    lote.P1.numPrograma=aux->Proceso.numPrograma;
                    lote.contProceso=1;
                break;
                case 2:
                    lote.P2.bndStatus=aux->Proceso.bndStatus;
                    strcpy(lote.P2.operacion,aux->Proceso.operacion);
                    lote.P2.TME=aux->Proceso.TME;
                    lote.P2.TiempoRest=aux->Proceso.TiempoRest;
                    lote.P2.numPrograma=aux->Proceso.numPrograma;
                    lote.contProceso=2;
                break;
                case 3:
                    lote.P3.bndStatus=aux->Proceso.bndStatus;
                    strcpy(lote.P3.operacion,aux->Proceso.operacion);
                    lote.P3.TME=aux->Proceso.TME;
                    lote.P3.TiempoRest=aux->Proceso.TiempoRest;
                    lote.P3.numPrograma=aux->Proceso.numPrograma;
                    lote.contProceso=3;
                break;
                case 4:
                    lote.P4.bndStatus=aux->Proceso.bndStatus;
                    strcpy(lote.P4.operacion,aux->Proceso.operacion);
                    lote.P4.TME=aux->Proceso.TME;
                    lote.P4.TiempoRest=aux->Proceso.TiempoRest;
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

    gotoxy(45,27);printf("Procesando... ");
    for(i=60; i<80; i++)
    {
        delay(50);
        gotoxy(i,27);printf("%c",219);
    }
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
    char carac;
    int bndFin=0;
    int relojGlobal=0;
    int resultado=0;
    int auxgoto=0;
    int bnd1=0;
    int bndErrorProceso=0;
    int bndProcesoInt=0;
    int bndAux=0;
    int bndInterrumpidos=0;
    int contInterrumpidos=0;
    int contProcesosEjec=0;
    int bndEncendido=0;
    int bandLote=0;
    int auxLote=0;
    int auxProceso1=1;
    int bandAuxiliar=0;

    char operando1[4];
    char operando2[4];
    char operador1;

    COLAPROCESOTERMINADO CPT;
    PROCESOTERMINADO procesoTerminado;
    PROCESO proceso;
    PROCESOTERMINADO procesoInt;
    LOTE_ESPERA LoteProcesoEspera;

    procesoTerminado.bnd=0;
    LoteProcesoEspera.contProceso=0;

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

        auxLote=numLotes;
        numLotesPendientes=numLotes-1; // lotes pendientes
        if(numLotesPendientes < 0)   //si resulta negativo se asigna 0
            numLotesPendientes=0;

        NodoLote *aux;    //primer nodo
        aux=CL->frente->sig;
        system("cls");
        while((aux != NULL) || ((LoteProcesoEspera.contProceso >= 1) && (contInterrumpidos > 0)))
        {
            while((((auxProceso <= aux->Lote.contProceso) && (bndFin == 0)) || ((LoteProcesoEspera.contProceso >= 1) && (contInterrumpidos > 0))) && (bandLote == 0))
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
                if(bndAux == 1)
                {
                    bndAux=0;
                    bndInterrumpidos=1;
                }

                if((LoteProcesoEspera.contProceso >= 1) && (bndEncendido == 1))
                {
                    switch(auxProceso)//la variable operacion toma valor
                    {
                        case 1:
                            strcpy(operacion,LoteProcesoEspera.P1.operacion);
                        break;
                        case 2:
                            strcpy(operacion,LoteProcesoEspera.P2.operacion);
                        break;
                        case 3:
                            strcpy(operacion,LoteProcesoEspera.P3.operacion);
                        break;
                        case 4:
                            strcpy(operacion,LoteProcesoEspera.P4.operacion);
                        break;
                        case 5:
                            strcpy(operacion,LoteProcesoEspera.P5.operacion);
                        break;
                        case 6:
                            strcpy(operacion,LoteProcesoEspera.P6.operacion);
                        break;
                        case 7:
                            strcpy(operacion,LoteProcesoEspera.P7.operacion);
                        break;
                        case 8:
                            strcpy(operacion,LoteProcesoEspera.P8.operacion);
                        break;
                        case 9:
                            strcpy(operacion,LoteProcesoEspera.P9.operacion);
                        break;
                        case 10:
                            strcpy(operacion,LoteProcesoEspera.P10.operacion);
                        break;
                        case 11:
                            strcpy(operacion,LoteProcesoEspera.P11.operacion);
                        break;
                        case 12:
                            strcpy(operacion,LoteProcesoEspera.P12.operacion);
                        break;
                    }
                }
                //Se resuelve operacion
                for(i=0; i<3; i++)
                    operando1[i]='\0';
                for(i=0; i<3; i++)
                    operando2[i]='\0';
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
                resultado=0;
                if(contOperador == 1)
                {
                    num=atoi(operando1);
                    num1=atoi(operando2);
                    switch(operador1)
                    {
                        case '+':
                            resultado=suma(num,num1);
                        break;
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
                    contProcesosEjec++;
                }
                else
                {
                    if(((bndInterrumpidos == 1) && (bndEncendido == 0)) || (bndInterrumpidos == 1))
                    {
                        gotoxy(89,12);printf("                                 ");
                        gotoxy(94,10);printf("Proceso Terminado");
                        mostrarProcesoTerminado(&CPT,contLote);
                    }
                    else
                    {
                        if(procesoTerminado.bnd == 2)
                        {
                            gotoxy(89,12);printf("                                 ");
                            gotoxy(94,10);printf("Proceso Terminado");
                            mostrarProcesoTerminado(&CPT,contLote);
                        }
                        else
                        {
                            gotoxy(94,10);printf("Proceso Terminado");
                            gotoxy(89,12);printf("No hay Procesos Terminados.");
                        }
                    }
                }

                //Procesos en ejecucion
                gotoxy(57,10);printf("Proceso en Ejecucion");
                if(bndInterrumpidos == 0)
                {
                    switch(auxProceso)
                    {
                        case 1:
                            proceso=aux->Lote.P1;
                            aux->Lote.P1.bndStatus=0;
                        break;
                        case 2:
                            proceso=aux->Lote.P2;
                            aux->Lote.P2.bndStatus=0;
                        break;
                        case 3:
                            proceso=aux->Lote.P3;
                            aux->Lote.P3.bndStatus=0;
                        break;
                        case 4:
                            proceso=aux->Lote.P4;
                            aux->Lote.P4.bndStatus=0;
                        break;
                    }
                }
                //prueba
                if(contProcesosEjec >= 4)
                {
                    if((((LoteProcesoEspera.contProceso >= 1) && (LoteProcesoEspera.contProceso >= (aux->Lote.contProceso - (contProcesosEjec-(4*(auxLote-1)))))) || (bndInterrumpidos == 1)) && (bandAuxiliar == 0))
                    {
                        auxProceso1=1;
                        bandAuxiliar=1;
                    }
                }
                else
                {
                    if((((LoteProcesoEspera.contProceso >= 1) && (LoteProcesoEspera.contProceso >= (aux->Lote.contProceso - contProcesosEjec))) || (bndInterrumpidos == 1)) && (bandAuxiliar == 0))
                    {
                        auxProceso1=1;
                        bandAuxiliar=1;
                    }
                }
                if(bandAuxiliar == 1)
                {
                    switch(auxProceso1)
                    {
                        case 1:
                            proceso=LoteProcesoEspera.P1;
                            LoteProcesoEspera.P1.bndStatus=0;
                            bndEncendido=1;
                        break;
                        case 2:
                            proceso=LoteProcesoEspera.P2;
                            LoteProcesoEspera.P2.bndStatus=0;
                            bndEncendido=1;
                        break;
                        case 3:
                            proceso=LoteProcesoEspera.P3;
                            LoteProcesoEspera.P3.bndStatus=0;
                            bndEncendido=1;
                        break;
                        case 4:
                            proceso=LoteProcesoEspera.P4;
                            LoteProcesoEspera.P4.bndStatus=0;
                            bndEncendido=1;
                        break;
                        case 5:
                            proceso=LoteProcesoEspera.P5;
                            LoteProcesoEspera.P5.bndStatus=0;
                            bndEncendido=1;
                        break;
                        case 6:
                            proceso=LoteProcesoEspera.P6;
                            LoteProcesoEspera.P6.bndStatus=0;
                            bndEncendido=1;
                        break;
                        case 7:
                            proceso=LoteProcesoEspera.P7;
                            LoteProcesoEspera.P7.bndStatus=0;
                            bndEncendido=1;
                        break;
                        case 8:
                            proceso=LoteProcesoEspera.P8;
                            LoteProcesoEspera.P8.bndStatus=0;
                            bndEncendido=1;
                        break;
                        case 9:
                            proceso=LoteProcesoEspera.P9;
                            LoteProcesoEspera.P9.bndStatus=0;
                            bndEncendido=1;
                        break;
                        case 10:
                            proceso=LoteProcesoEspera.P10;
                            LoteProcesoEspera.P10.bndStatus=0;
                            bndEncendido=1;
                        break;
                        case 11:
                            proceso=LoteProcesoEspera.P11;
                            LoteProcesoEspera.P11.bndStatus=0;
                            bndEncendido=1;
                        break;
                        case 12:
                            proceso=LoteProcesoEspera.P12;
                            LoteProcesoEspera.P12.bndStatus=0;
                            bndEncendido=1;
                        break;
                    }
                }
                proceso.bndStatus=0;

                //Lotes en ejecucion
                gotoxy(14,10);printf("Lote en Ejecucion");
                gotoxy(7,12); printf("No. Lote en Ejec: %d",contLote);

                switch(aux->Lote.contProceso)
                {
                    case 1:
                        if(aux->Lote.P1.bndStatus != 0)
                        {
                            gotoxy(10,15+auxgoto); printf("Num. Programa: %d",aux->Lote.P1.numPrograma);
                            gotoxy(20,17+auxgoto);printf("TME: %d",aux->Lote.P1.TME);
                            gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",aux->Lote.P1.TiempoRest);
                            auxgoto+=8;
                        }
                    break;
                    case 2:
                        if(aux->Lote.contProceso == 2)
                        {
                            if(aux->Lote.P1.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",aux->Lote.P1.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",aux->Lote.P1.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",aux->Lote.P1.TiempoRest);
                                auxgoto+=8;
                            }
                            if(aux->Lote.P2.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",aux->Lote.P2.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",aux->Lote.P2.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",aux->Lote.P2.TiempoRest);
                                auxgoto+=8;
                            }
                        }
                    break;
                    case 3:
                        if(aux->Lote.P1.bndStatus != 0)
                        {
                            gotoxy(10,15+auxgoto);printf("Num. Programa: %d",aux->Lote.P1.numPrograma);
                            gotoxy(20,17+auxgoto);printf("TME: %d",aux->Lote.P1.TME);
                            gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",aux->Lote.P1.TiempoRest);
                            auxgoto+=8;
                        }
                        if(aux->Lote.P2.bndStatus != 0)
                        {
                            gotoxy(10,15+auxgoto);printf("Num. Programa: %d",aux->Lote.P2.numPrograma);
                            gotoxy(20,17+auxgoto);printf("TME: %d",aux->Lote.P2.TME);
                            gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",aux->Lote.P2.TiempoRest);
                            auxgoto+=8;
                        }
                        if(aux->Lote.P3.bndStatus != 0)
                        {
                            gotoxy(10,15+auxgoto);printf("Num. Programa: %d",aux->Lote.P3.numPrograma);
                            gotoxy(20,17+auxgoto);printf("TME: %d",aux->Lote.P3.TME);
                            gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",aux->Lote.P3.TiempoRest);
                            auxgoto+=8;
                        }
                    break;
                    case 4:
                        if(aux->Lote.P1.bndStatus != 0)
                        {
                            gotoxy(10,15+auxgoto);printf("Num. Programa: %d",aux->Lote.P1.numPrograma);
                            gotoxy(20,17+auxgoto);printf("TME: %d",aux->Lote.P1.TME);
                            gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",aux->Lote.P1.TiempoRest);
                            auxgoto+=8;
                        }
                        if(aux->Lote.P2.bndStatus != 0)
                        {
                            gotoxy(10,15+auxgoto);printf("Num. Programa: %d",aux->Lote.P2.numPrograma);
                            gotoxy(20,17+auxgoto);printf("TME: %d",aux->Lote.P2.TME);
                            gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",aux->Lote.P2.TiempoRest);
                            auxgoto+=8;
                        }
                        if(aux->Lote.P3.bndStatus != 0)
                        {
                            gotoxy(10,15+auxgoto);printf("Num. Programa: %d",aux->Lote.P3.numPrograma);
                            gotoxy(20,17+auxgoto);printf("TME: %d",aux->Lote.P3.TME);
                            gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",aux->Lote.P3.TiempoRest);
                            auxgoto+=8;
                        }
                        if(aux->Lote.P4.bndStatus != 0)
                        {
                            gotoxy(10,15+auxgoto);printf("Num. Programa: %d",aux->Lote.P4.numPrograma);
                            gotoxy(20,17+auxgoto);printf("TME: %d",aux->Lote.P4.TME);
                            gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",aux->Lote.P4.TiempoRest);
                            auxgoto+=8;
                        }
                    break;
                }
                if(LoteProcesoEspera.contProceso > 0)
                {
                    switch(LoteProcesoEspera.contProceso)
                    {
                        case 1:
                            if(LoteProcesoEspera.P1.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto); printf("Num. Programa: %d",LoteProcesoEspera.P1.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P1.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P1.TiempoRest);
                                auxgoto+=8;
                            }
                        break;
                        case 2:
                            if(LoteProcesoEspera.contProceso == 2)
                            {
                                if(LoteProcesoEspera.P1.bndStatus != 0)
                                {
                                    gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P1.numPrograma);
                                    gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P1.TME);
                                    gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P1.TiempoRest);
                                    auxgoto+=8;
                                }
                                if(LoteProcesoEspera.P2.bndStatus != 0)
                                {
                                    gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P2.numPrograma);
                                    gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P2.TME);
                                    gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P2.TiempoRest);
                                    auxgoto+=8;
                                }
                            }
                        break;
                        case 3:
                            if(LoteProcesoEspera.P1.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P1.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P1.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P1.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P2.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P2.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P2.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P2.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P3.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P3.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P3.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P3.TiempoRest);
                                auxgoto+=8;
                            }
                        break;
                        case 4:
                            if(LoteProcesoEspera.P1.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P1.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P1.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P1.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P2.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P2.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P2.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P2.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P3.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P3.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P3.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P3.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P4.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P4.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P4.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P4.TiempoRest);
                                auxgoto+=8;
                            }
                        break;
                        case 5:
                            if(LoteProcesoEspera.P1.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P1.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P1.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P1.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P2.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P2.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P2.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P2.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P3.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P3.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P3.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P3.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P4.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P4.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P4.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P4.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P5.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P5.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P5.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P5.TiempoRest);
                                auxgoto+=8;
                            }
                        break;
                        case 6:
                            if(LoteProcesoEspera.P1.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P1.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P1.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P1.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P2.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P2.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P2.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P2.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P3.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P3.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P3.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P3.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P4.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P4.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P4.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P4.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P5.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P5.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P5.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P5.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P6.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P6.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P6.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P6.TiempoRest);
                                auxgoto+=8;
                            }
                        break;
                        case 7:
                            if(LoteProcesoEspera.P1.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P1.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P1.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P1.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P2.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P2.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P2.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P2.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P3.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P3.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P3.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P3.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P4.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P4.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P4.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P4.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P5.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P5.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P5.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P5.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P6.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P6.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P6.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P6.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P7.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P7.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P7.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P7.TiempoRest);
                                auxgoto+=8;
                            }
                        break;
                        case 8:
                            if(LoteProcesoEspera.P1.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P1.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P1.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P1.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P2.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P2.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P2.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P2.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P3.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P3.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P3.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P3.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P4.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P4.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P4.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P4.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P5.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P5.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P5.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P5.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P6.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P6.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P6.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P6.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P7.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P7.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P7.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P7.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P8.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P8.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P8.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P8.TiempoRest);
                                auxgoto+=8;
                            }
                        break;
                        case 9:
                            if(LoteProcesoEspera.P1.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P1.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P1.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P1.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P2.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P2.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P2.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P2.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P3.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P3.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P3.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P3.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P4.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P4.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P4.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P4.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P5.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P5.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P5.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P5.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P6.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P6.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P6.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P6.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P7.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P7.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P7.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P7.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P8.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P8.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P8.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P8.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P9.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P9.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P9.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P9.TiempoRest);
                                auxgoto+=8;
                            }
                        break;
                        case 10:
                            if(LoteProcesoEspera.P1.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P1.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P1.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P1.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P2.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P2.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P2.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P2.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P3.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P3.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P3.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P3.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P4.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P4.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P4.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P4.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P5.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P5.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P5.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P5.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P6.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P6.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P6.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P6.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P7.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P7.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P7.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P7.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P8.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P8.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P8.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P8.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P9.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P9.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P9.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P9.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P10.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P10.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P10.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P10.TiempoRest);
                                auxgoto+=8;
                            }
                        break;
                        case 11:
                            if(LoteProcesoEspera.P1.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P1.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P1.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P1.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P2.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P2.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P2.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P2.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P3.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P3.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P3.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P3.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P4.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P4.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P4.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P4.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P5.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P5.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P5.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P5.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P6.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P6.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P6.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P6.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P7.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P7.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P7.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P7.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P8.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P8.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P8.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P8.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P9.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P9.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P9.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P9.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P10.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P10.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P10.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P10.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P11.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P11.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P11.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P11.TiempoRest);
                                auxgoto+=8;
                            }
                        break;
                        case 12:
                            if(LoteProcesoEspera.P1.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P1.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P1.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P1.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P2.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P2.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P2.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P2.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P3.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P3.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P3.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P3.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P4.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P4.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P4.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P4.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P5.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P5.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P5.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P5.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P6.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P6.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P6.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P6.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P7.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P7.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P7.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P7.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P8.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P8.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P8.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P8.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P9.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P9.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P9.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P9.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P10.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P10.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P10.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P10.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P11.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P11.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P11.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P11.TiempoRest);
                                auxgoto+=8;
                            }
                            if(LoteProcesoEspera.P12.bndStatus != 0)
                            {
                                gotoxy(10,15+auxgoto);printf("Num. Programa: %d",LoteProcesoEspera.P12.numPrograma);
                                gotoxy(20,17+auxgoto);printf("TME: %d",LoteProcesoEspera.P12.TME);
                                gotoxy(8,19+auxgoto);printf("Tiempo Restante: %d",LoteProcesoEspera.P12.TiempoRest);
                                auxgoto+=8;
                            }
                        break;
                    }
                }
                gotoxy(52,13);printf("Num. Programa: %d",proceso.numPrograma);
                gotoxy(56,15);printf("Operacion: %s",proceso.operacion);
                gotoxy(62,17);printf("TME: %d",proceso.TME);
                gotoxy(50,19);printf("Tiempo Restante: %d",proceso.TiempoRest);
                gotoxy(62,21);printf("TTE: ");
                gotoxy(62,23);printf("TRE: ");
                if(bndEncendido == 0)
                {
                    m=proceso.TME;
                    k=0;
                    while((k < proceso.TME) && (bndErrorProceso == 0) && (bndProcesoInt == 0))
                    {
                        if(kbhit())
                            caracter=getch();
                        delay(300);
                        gotoxy(62,21);printf("TTE: %d",k);
                        gotoxy(62,23);printf("TRE: %d",m);
                        if(caracter == 'W')
                        {
                            gotoxy(50,34);printf("Se ha producido un error");
                            bndErrorProceso=1;
                        }
                        else
                        {
                            if(caracter == 'P')
                            {
                                while(carac != 'C')
                                {
                                    gotoxy(50,34);printf("Pausa...Presiona la Tecla 'C' para Continuar");
                                    kbhit();
                                    carac=getch();
                                }
                                if(carac == 'C')
                                {
                                    gotoxy(50,34);printf("                                              ");
                                    gotoxy(50,34);printf(".......Listo para continuar.......");
                                }
                                gotoxy(50,34);printf("                                 ");
                            }
                            else
                            {
                                if(caracter == 'I')
                                {
                                    gotoxy(50,34);printf("El proceso ha sido Interrumpido");
                                    procesoInt.numProg=proceso.numPrograma;
                                    strcpy(procesoInt.operacion,proceso.operacion);
                                    procesoInt.resultado=resultado;
                                    procesoInt.TME=proceso.TME;
                                    procesoInt.TiempoRest=proceso.TME-k;
                                    bndProcesoInt=1;
                                    contInterrumpidos++;
                                }
                                else
                                    gotoxy(50,34);printf("                           ");
                            }
                            m--;
                            k++;
                        }
                    }
                }
                else
                {
                    m=proceso.TiempoRest;
                    k=0;
                    while((k < proceso.TiempoRest) && (bndErrorProceso == 0) && (bndProcesoInt == 0))
                    {
                        if(kbhit())
                            caracter=getch();
                        delay(300);
                        gotoxy(62,21);printf("TTE: %d",k);
                        gotoxy(62,23);printf("TRE: %d",m);
                        if(caracter == 'W')
                        {
                            gotoxy(50,34);printf("Se ha producido un error");
                            bndErrorProceso=1;
                        }
                        else
                        {
                            if(caracter == 'P')
                            {
                                while(carac != 'C')
                                {
                                    gotoxy(50,34);printf("Pausa...Presiona la Tecla 'C' para Continuar");
                                    kbhit();
                                    carac=getch();
                                }
                                if(carac == 'C')
                                {
                                    gotoxy(50,34);printf("                                              ");
                                    gotoxy(50,34);printf(".......Listo para continuar.......");
                                }
                                gotoxy(50,34);printf("                                 ");
                            }
                            else
                            {
                                if(caracter == 'I')
                                {
                                    gotoxy(50,34);printf("El proceso ha sido Interrumpido");
                                    procesoInt.numProg=proceso.numPrograma;
                                    strcpy(procesoInt.operacion,proceso.operacion);
                                    procesoInt.resultado=proceso.resultado;
                                    procesoInt.TME=proceso.TME;
                                    procesoInt.TiempoRest=proceso.TME-k;
                                    bndProcesoInt=1;
                                    contInterrumpidos++;
                                }
                                else
                                    gotoxy(50,34);printf("                           ");
                            }
                            m--;
                            k++;
                        }
                    }
                }
                if((bndErrorProceso == 0) && (bndProcesoInt == 0))
                {
                    barra();
                    delay(500);
                    gotoxy(62,21);printf("TTE: %d",k);
                    gotoxy(62,23);printf("TRE: %d",m);
                    delay(100);
                    gotoxy(45,27);printf(" Terminado... ");
                    procesoTerminado.numProg=proceso.numPrograma;
                    strcpy(procesoTerminado.operacion,proceso.operacion);
                    if(bndEncendido == 0)
                        procesoTerminado.resultado=resultado;
                    else
                        procesoTerminado.resultado=proceso.resultado;
                    procesoTerminado.bnd=1;
                    relojGlobal+=proceso.TME;
                }
                else
                {
                    if(bndErrorProceso == 1)
                    {
                        gotoxy(62,21);printf("TTE: %d",k);
                        gotoxy(62,23);printf("TRE: %d",m);
                        gotoxy(45,27);printf(" Terminado... ");
                        delay(300);
                        procesoTerminado.numProg=proceso.numPrograma;
                        strcpy(procesoTerminado.operacion,proceso.operacion);
                        procesoTerminado.resultado=0;
                        procesoTerminado.bnd=1;
                        relojGlobal+=proceso.TME;
                    }
                    if(bndProcesoInt == 1)
                    {
                        switch(LoteProcesoEspera.contProceso)
                        {
                            case 0:
                                LoteProcesoEspera.P1.numPrograma=procesoInt.numProg;
                                strcpy(LoteProcesoEspera.P1.operacion,procesoInt.operacion);
                                LoteProcesoEspera.P1.resultado=procesoInt.resultado;
                                LoteProcesoEspera.P1.bndStatus=1;
                                LoteProcesoEspera.P1.TME=proceso.TME;
                                LoteProcesoEspera.P1.TiempoRest=LoteProcesoEspera.P1.TME-(k-1);
                                LoteProcesoEspera.contProceso++;
                            break;
                            case 1:
                                LoteProcesoEspera.P2.numPrograma=procesoInt.numProg;
                                strcpy(LoteProcesoEspera.P2.operacion,procesoInt.operacion);
                                LoteProcesoEspera.P2.resultado=procesoInt.resultado;
                                LoteProcesoEspera.P2.bndStatus=1;
                                LoteProcesoEspera.P2.TME=proceso.TME;
                                LoteProcesoEspera.P2.TiempoRest=LoteProcesoEspera.P2.TME-(k-1);
                                LoteProcesoEspera.contProceso++;
                            break;
                            case 2:
                                LoteProcesoEspera.P3.numPrograma=procesoInt.numProg;
                                strcpy(LoteProcesoEspera.P3.operacion,procesoInt.operacion);
                                LoteProcesoEspera.P3.resultado=procesoInt.resultado;
                                LoteProcesoEspera.P3.bndStatus=1;
                                LoteProcesoEspera.P3.TME=proceso.TME;
                                LoteProcesoEspera.P3.TiempoRest=LoteProcesoEspera.P3.TME-(k-1);
                                LoteProcesoEspera.contProceso++;
                            break;
                            case 3:
                                LoteProcesoEspera.P4.numPrograma=procesoInt.numProg;
                                strcpy(LoteProcesoEspera.P4.operacion,procesoInt.operacion);
                                LoteProcesoEspera.P4.resultado=procesoInt.resultado;
                                LoteProcesoEspera.P4.bndStatus=1;
                                LoteProcesoEspera.P4.TME=proceso.TME;
                                LoteProcesoEspera.P4.TiempoRest=LoteProcesoEspera.P4.TME-(k-1);
                                LoteProcesoEspera.contProceso++;
                            break;
                            case 4:
                                LoteProcesoEspera.P5.numPrograma=procesoInt.numProg;
                                strcpy(LoteProcesoEspera.P5.operacion,procesoInt.operacion);
                                LoteProcesoEspera.P5.resultado=procesoInt.resultado;
                                LoteProcesoEspera.P5.bndStatus=1;
                                LoteProcesoEspera.P5.TME=proceso.TME;
                                LoteProcesoEspera.P5.TiempoRest=LoteProcesoEspera.P5.TME-(k-1);
                                LoteProcesoEspera.contProceso++;
                            break;
                            case 5:
                                LoteProcesoEspera.P6.numPrograma=procesoInt.numProg;
                                strcpy(LoteProcesoEspera.P6.operacion,procesoInt.operacion);
                                LoteProcesoEspera.P6.resultado=procesoInt.resultado;
                                LoteProcesoEspera.P6.bndStatus=1;
                                LoteProcesoEspera.P6.TME=proceso.TME;
                                LoteProcesoEspera.P6.TiempoRest=LoteProcesoEspera.P6.TME-(k-1);
                                LoteProcesoEspera.contProceso++;
                            break;
                            case 6:
                                LoteProcesoEspera.P7.numPrograma=procesoInt.numProg;
                                strcpy(LoteProcesoEspera.P7.operacion,procesoInt.operacion);
                                LoteProcesoEspera.P7.resultado=procesoInt.resultado;
                                LoteProcesoEspera.P7.bndStatus=1;
                                LoteProcesoEspera.P7.TME=proceso.TME;
                                LoteProcesoEspera.P7.TiempoRest=LoteProcesoEspera.P7.TME-(k-1);
                                LoteProcesoEspera.contProceso++;
                            break;
                            case 7:
                                LoteProcesoEspera.P8.numPrograma=procesoInt.numProg;
                                strcpy(LoteProcesoEspera.P8.operacion,procesoInt.operacion);
                                LoteProcesoEspera.P8.resultado=procesoInt.resultado;
                                LoteProcesoEspera.P8.bndStatus=1;
                                LoteProcesoEspera.P8.TME=proceso.TME;
                                LoteProcesoEspera.P8.TiempoRest=LoteProcesoEspera.P8.TME-(k-1);
                                LoteProcesoEspera.contProceso++;
                            break;
                            case 8:
                                LoteProcesoEspera.P9.numPrograma=procesoInt.numProg;
                                strcpy(LoteProcesoEspera.P9.operacion,procesoInt.operacion);
                                LoteProcesoEspera.P9.resultado=procesoInt.resultado;
                                LoteProcesoEspera.P9.bndStatus=1;
                                LoteProcesoEspera.P9.TME=proceso.TME;
                                LoteProcesoEspera.P9.TiempoRest=LoteProcesoEspera.P9.TME-(k-1);
                                LoteProcesoEspera.contProceso++;
                            break;
                            case 9:
                                LoteProcesoEspera.P10.numPrograma=procesoInt.numProg;
                                strcpy(LoteProcesoEspera.P10.operacion,procesoInt.operacion);
                                LoteProcesoEspera.P10.resultado=procesoInt.resultado;
                                LoteProcesoEspera.P10.bndStatus=1;
                                LoteProcesoEspera.P10.TME=proceso.TME;
                                LoteProcesoEspera.P10.TiempoRest=LoteProcesoEspera.P10.TME-(k-1);
                                LoteProcesoEspera.contProceso++;
                            break;
                            case 10:
                                LoteProcesoEspera.P11.numPrograma=procesoInt.numProg;
                                strcpy(LoteProcesoEspera.P11.operacion,procesoInt.operacion);
                                LoteProcesoEspera.P11.resultado=procesoInt.resultado;
                                LoteProcesoEspera.P11.bndStatus=1;
                                LoteProcesoEspera.P11.TME=proceso.TME;
                                LoteProcesoEspera.P11.TiempoRest=LoteProcesoEspera.P11.TME-(k-1);
                                LoteProcesoEspera.contProceso++;
                            break;
                            case 11:
                                LoteProcesoEspera.P12.numPrograma=procesoInt.numProg;
                                strcpy(LoteProcesoEspera.P12.operacion,procesoInt.operacion);
                                LoteProcesoEspera.P12.resultado=procesoInt.resultado;
                                LoteProcesoEspera.P12.bndStatus=1;
                                LoteProcesoEspera.P12.TME=proceso.TME;
                                LoteProcesoEspera.P12.TiempoRest=LoteProcesoEspera.P12.TME-(k-1);
                                LoteProcesoEspera.contProceso++;
                            break;
                        }
                        procesoTerminado.bnd=2;
                    }
                }
                if((aux->Lote.contProceso == 1) && (bnd1 == 0))
                {
                    gotoxy(89,12);printf("                                 ");
                    gotoxy(94,10);printf("Proceso Terminado");
                    insertaProcesoTerminado(&CPT,procesoTerminado);
                    mostrarProcesoTerminado(&CPT,contLote);
                    gotoxy(57,10);printf("Proceso en Ejecucion");
                    gotoxy(52,13);printf("Num. Programa:     ");
                    gotoxy(56,15);printf("Operacion:            ");
                    gotoxy(62,17);printf("TME:              ");
                    gotoxy(50,19);printf("Tiempo restante:             ");
                    gotoxy(62,21);printf("TTE:         ");
                    gotoxy(62,23);printf("TRE:       ");
                    gotoxy(35,27);printf("                                                                    ");
                    gotoxy(49,26);printf("No Hay proceso en Ejecucion.");
                    bndFin=1;
                    contProcesosEjec++;
                }
                if((auxProceso == cantProceso) && (bnd1 == 0) && (bndEncendido == 0))
                {
                    if(bndFin == 0)
                    {
                        gotoxy(89,12);printf("                                 ");
                        gotoxy(94,10);printf("Proceso Terminado");
                        insertaProcesoTerminado(&CPT,procesoTerminado);
                        mostrarProcesoTerminado(&CPT,contLote);
                        contProcesosEjec++;
                        bnd1=1;
                    }
                    gotoxy(57,10);printf("Proceso en Ejecucion");
                    gotoxy(52,13);printf("Num. Programa:     ");
                    gotoxy(56,15);printf("Operacion:            ");
                    gotoxy(62,17);printf("TME:              ");
                    gotoxy(50,19);printf("Tiempo Restante:         ");
                    gotoxy(62,21);printf("TTE:         ");
                    gotoxy(62,23);printf("TRE:       ");
                    gotoxy(35,27);printf("                                                                    ");
                    gotoxy(49,26);printf("No Hay proceso en Ejecucion.");
                }
                if((contProcesosEjec+1) == cantProceso)
                {
                    if(bndFin == 0)
                    {
                        gotoxy(89,12);printf("                                 ");
                        gotoxy(94,10);printf("Proceso Terminado");
                        insertaProcesoTerminado(&CPT,procesoTerminado);
                        mostrarProcesoTerminado(&CPT,contLote);
                        contProcesosEjec++;
                        bnd1=1;
                    }
                    gotoxy(57,10);printf("Proceso en Ejecucion");
                    gotoxy(52,13);printf("Num. Programa:     ");
                    gotoxy(56,15);printf("Operacion:            ");
                    gotoxy(62,17);printf("TME:              ");
                    gotoxy(50,19);printf("Tiempo Restante:         ");
                    gotoxy(62,21);printf("TTE:         ");
                    gotoxy(62,23);printf("TRE:       ");
                    gotoxy(35,27);printf("                                                                    ");
                    gotoxy(49,26);printf("No Hay proceso en Ejecucion.");
                }
                if((bndInterrumpidos == 1) && (bndEncendido == 1))
                {
                    if(bndFin == 0)
                    {
                        gotoxy(89,12);printf("                                 ");
                        gotoxy(94,10);printf("Proceso Terminado");
                        insertaProcesoTerminado(&CPT,procesoTerminado);
                        mostrarProcesoTerminado(&CPT,contLote);
                        contProcesosEjec++;
                        bnd1=1;
                        contInterrumpidos--;
                    }
                    gotoxy(57,10);printf("Proceso en Ejecucion");
                    gotoxy(52,13);printf("Num. Programa:     ");
                    gotoxy(56,15);printf("Operacion:            ");
                    gotoxy(62,17);printf("TME:              ");
                    gotoxy(50,19);printf("Tiempo Restante:          ");
                    gotoxy(62,21);printf("TTE:         ");
                    gotoxy(62,23);printf("TRE:       ");
                    gotoxy(35,27);printf("                                                                    ");
                    gotoxy(49,26);printf("No Hay proceso en Ejecucion.");
                }
                gotoxy(63,34);printf("Contador Global: %d",relojGlobal);
                auxProceso++; //Se incrementa en cada proceso
                delay(80);
                if(bndEncendido == 1)
                    auxProceso1++;
                bndErrorProceso=0;
                bndProcesoInt=0;
                if(auxProceso1>cantProceso)
                    bndAux=1;
                if(cantProceso == contProcesosEjec)
                    bandLote=1;
                if(auxLote > 1)
                {
                    if(contInterrumpidos > 0)
                    {
                        if(contProcesosEjec == 3)
                            bandLote=1;
                    }
                }
            }
            aux=aux->sig;
            auxProceso=1;
            numLotesPendientes--;
            contLote++;
            bnd1=0;
            bndAux=0;
            bandAuxiliar=0;
            bndEncendido=0;
            bndInterrumpidos=0;
            contInterrumpidos=0;
            auxProceso1=1;
            bandLote=0;
            LoteProcesoEspera.contProceso=0;
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
    int i=0;
    int num1=0;
    int num2=0;
    char numero1[4];
    char numero2[4];
    int opAleatorio=0;

    PROCESO proceso;
    COLAPROCESO C;
    COLALOTE CL;

    inicializar(&C);
    inicializarLote(&CL);
    system("cls");

    gotoxy(14,6);printf("Cantidad de Procesos: ");
    scanf("%d",&cantProceso);

    proceso.numPrograma=1;

    while(contProceso < cantProceso)
    {
        system("cls");
        for(i=0; i<12; i++)
            proceso.operacion[i]='\0';
        num1=1+rand()%101;
        itoa(num1,numero1,10);
        num2=1+rand()%101;
        itoa(num2,numero2,10);
        opAleatorio=rand()%5;
        switch(opAleatorio)
        {
            case 0:
                strcat(proceso.operacion,numero1);
                strcat(proceso.operacion,"+");
                strcat(proceso.operacion,numero2);
            break;
            case 1:
                strcat(proceso.operacion,numero1);
                strcat(proceso.operacion,"-");
                strcat(proceso.operacion,numero2);
            break;
            case 2:
                strcat(proceso.operacion,numero1);
                strcat(proceso.operacion,"/");
                strcat(proceso.operacion,numero2);
            break;
            case 3:
                strcat(proceso.operacion,numero1);
                strcat(proceso.operacion,"*");
                strcat(proceso.operacion,numero2);
            break;
            case 4:
                strcat(proceso.operacion,numero1);
                strcat(proceso.operacion,"%");
                strcat(proceso.operacion,numero2);
            break;
            case 5:
                strcat(proceso.operacion,numero1);
                strcat(proceso.operacion,"^");
                strcat(proceso.operacion,numero2);
            break;
        }
        proceso.bndStatus=1;
        proceso.TME=1+rand()%10;
        proceso.TiempoRest=0;
        insertar(&C,proceso);
        proceso.numPrograma++;
        num1=0;
        num2=0;
        for(i=0; i<3; i++)
            numero1[i]='\0';
        for(i=0; i<3; i++)
            numero2[i]='\0';
        for(i=0; i<12; i++)
            proceso.operacion[i]='\0';
        contProceso++;
    }
    cargaLote(&C,&CL);
    Proceso(&CL,cantProceso);
    getch();
    return 0;
}
