#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define capMarco 30

typedef struct{
    int pagina;
    int capPagina;
    int marco;
}Pag;

typedef struct{
    int memProceso;
    Pag paginas[capMarco];
    int cantPaginas;
    char operacion[15];
    int resultado;
    int numPrograma;
    int tRestQuantum;
    int TiempoRest;
    int status;
    int bndBloqueado;
    int contTiempoEspera;
    int bndNuevo;
    int bndTerminado;
    int tiempInt;
    int TME;
    int tejecucion;
    int tLlegada;
    int tRespuesta;
    int tServicio;
    int tEspera;
    int tFinalizacion;
    int tRetorno;
    int bndtermino;
}PROCESO;

typedef struct{
    int memProceso;
    Pag paginas[capMarco];
    int cantPaginas;
    int numProg;
    char nomProg[20];
    char operacion[10];
    int resultado;
    int bnd;
    int TME;
    int TiempoRest;
    int auxTiempo;
    int tejecucion;
    int tLlegada;
    int tRespuesta;
    int tServicio;
    int tEspera;
    int tFinalizacion;
    int tRetorno;
    int bndtermino;
}PROCESOTERMINADO;

typedef struct{
    int numPrograma;
    int tLlegada;
    int tFinalizacion;
    int tServicio;
    int tEspera;
    int tRetorno;
    int tRespuesta;
    int bndtermino;
}TIEMPOS;

typedef struct nodoProceso{
    PROCESO Proceso;
    struct nodoProceso * sig;
}nodoProceso;

typedef struct nodoProcesoTerminado{
    PROCESOTERMINADO ProcesoTerminado;
    struct nodoProcesoTerminado * sig;
}nodoProcesoTerminado;

typedef struct nodoTiempos{
    TIEMPOS Tiempos;
    struct nodoTiempos * sig;
}nodoTiempos;

typedef struct nodoProceso NodoProceso;
typedef struct nodoProcesoTerminado NodoProcesoTerminado;
typedef struct nodoTiempos NodoTiempos;

typedef struct{
    NodoProceso *frente;
    NodoProceso *final;
    int contProceso;
}COLAPROCESO;

typedef struct{
    NodoProcesoTerminado *frente;
    NodoProcesoTerminado *final;
}COLAPROCESOTERMINADO;

typedef struct{
    NodoTiempos *frente;
    NodoTiempos *final;
}COLATIEMPOS;

typedef struct
{
    int noMarco;
    int memDisponible;
    int numPagina;
    int tamPagina;
    int bndDisp;
    int marcoIdProceso;

}Marco;

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

void inicializar(COLAPROCESO *C)
{
    NodoProceso *aux;
    aux = (NodoProceso*)malloc(sizeof(NodoProceso));
    aux->sig=NULL;
    C->final=aux;
    C->frente=aux;
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
    return (C->frente == C->final);
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

void mostrarProcesoTerminado(COLAPROCESOTERMINADO *CPT)
{
    int auxgoto=0;

    if(!vaciaProcesoTerminado(CPT))
    {
        NodoProcesoTerminado *aux;
        aux=CPT->frente->sig;
        while(aux != NULL)
        {
            gotoxy(114,13+auxgoto);printf("Num. Programa: %d ",aux->ProcesoTerminado.numProg);
            gotoxy(118,15+auxgoto);printf("Operacion: %s",aux->ProcesoTerminado.operacion);
            if(aux->ProcesoTerminado.resultado == 0)
            {
                gotoxy(118,17+auxgoto);printf("Resultado: Error Ejecucion");
            }
            else
            {
                gotoxy(118,17+auxgoto);printf("Resultado: %d",aux->ProcesoTerminado.resultado);
            }
            aux=aux->sig;
            auxgoto+=8;
         }
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

PROCESO creaProceso(int numPrograma)
{
    PROCESO proceso;
    int i=0;
    int num1=0;
    int num2=0;
    char numero1[4];
    char numero2[4];
    int opAleatorio=0;
    int memoria;

    num1=0;
    num2=0;
    for(i=0; i<12; i++)
        proceso.operacion[i]='\0';
    for(i=0; i<3; i++)
        numero1[i]='\0';
    for(i=0; i<3; i++)
        numero2[i]='\0';
    for(i=0; i<12; i++)
        proceso.operacion[i]='\0';

    proceso.numPrograma=numPrograma;
    num1=1+rand()%101;
    itoa(num1,numero1,10);
    num2=1+rand()%101;
    itoa(num2,numero2,10);
    opAleatorio=rand()%5;
    proceso.tiempInt=6;
    memoria=1+rand()%60;
    proceso.memProceso=memoria;
    proceso.cantPaginas=0;

    for(i=0; i<capMarco; i++)
    {
        proceso.paginas[i].pagina = 0;
        proceso.paginas[i].capPagina=0;
    }

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
    proceso.TME=1+rand()%30;
    proceso.TiempoRest=proceso.TME;
    proceso.tRestQuantum=proceso.TME;
    return proceso;
}

void encabezado()
{
    gotoxy(50,3);printf("----- PRACTICA NO.7 -----");
    gotoxy(1,7);printf("No.Prog.");
    gotoxy(12,7);printf("Estado");
    gotoxy(23,7);printf("Operacion");
    gotoxy(37,7);printf("Result.");
    gotoxy(49,7);printf("T.Llegada");
    gotoxy(63,7);printf("T.Finaliz.");
    gotoxy(76,7);printf("T.Retorno");
    gotoxy(88,7);printf("T.Espera");
    gotoxy(99,7);printf("T.Serv.");
    gotoxy(109,7);printf("T.Restante");
    gotoxy(122,7);printf("T.Resp.");
}

int mostrarTiemposProcesosTerminados(COLAPROCESOTERMINADO *CPT)
{
    int gotobcp=0;
    NodoProcesoTerminado *auxCPT;

    if(!vaciaProcesoTerminado(CPT))
    {
        auxCPT=CPT->frente->sig;
        while(auxCPT != NULL)
        {
            gotoxy(3,10+gotobcp);printf("%d",auxCPT->ProcesoTerminado.numProg);
            gotoxy(11,10+gotobcp);printf("Terminado");
            gotoxy(25,10+gotobcp);printf("%s",auxCPT->ProcesoTerminado.operacion);
            if(auxCPT->ProcesoTerminado.resultado == 0)
            {
                gotoxy(38,10+gotobcp);printf("Error");
            }
            else
            {
                gotoxy(38,10+gotobcp);printf("%d",auxCPT->ProcesoTerminado.resultado);
            }
            gotoxy(52,10+gotobcp);printf("%d",auxCPT->ProcesoTerminado.tLlegada);
            gotoxy(66,10+gotobcp);printf("%d",auxCPT->ProcesoTerminado.tFinalizacion);
            gotoxy(79,10+gotobcp);printf("%d",auxCPT->ProcesoTerminado.tRetorno);
            gotoxy(91,10+gotobcp);printf("%d",auxCPT->ProcesoTerminado.tEspera);
            gotoxy(102,10+gotobcp);printf("%d",auxCPT->ProcesoTerminado.tServicio);
            gotoxy(112,10+gotobcp);printf("NULO");
            gotoxy(124,10+gotobcp);printf("%d",auxCPT->ProcesoTerminado.tRespuesta);
            auxCPT=auxCPT->sig;
            gotobcp+=2;
        }
    }
    return gotobcp;
}

void encabezadoProcesoNoEjecucion()
{
    gotoxy(82,10);printf("Proceso en Ejecucion");
    gotoxy(82,13);printf("Num. Programa:     ");
    gotoxy(86,15);printf("Operacion:            ");
    gotoxy(92,17);printf("TME:              ");
    gotoxy(80,19);printf("Tiempo restante:             ");
    gotoxy(92,21);printf("TTE:         ");
    gotoxy(92,23);printf("TRE:       ");
    gotoxy(84,27);printf("                                                                    ");
    gotoxy(84,27);printf("No Hay proceso en Ejecucion.");
}

void inicializaMarcos(Marco Marcos[])
{
    int i=0;

    for(i=0; i<capMarco ; i++)
    {
        Marcos[i].noMarco = i;
        Marcos[i].memDisponible = 4;
        Marcos[i].numPagina = 0;
        Marcos[i].tamPagina = 0;
        Marcos[i].bndDisp = 1;
    }
    //1 Disponible
    //0 Ocupado
    Marcos[0].noMarco = 0;
    Marcos[0].bndDisp = 0;
    Marcos[0].memDisponible = 0;
    Marcos[0].tamPagina = 4;
    Marcos[1].noMarco = 1;
    Marcos[1].bndDisp = 0;
    Marcos[1].memDisponible = 0;
    Marcos[1].tamPagina = 4;
}

int marcosDisponibles(Marco Marcos[])
{
    int i;
    int marco=0;

    for(i=2; i<capMarco; i++)
    {
        if(Marcos[i].bndDisp == 1)
            marco++;
    }
    return marco;
}

int calculaPaginas(int cantMemoria)
{
    int noPag=0;
    int mod=0;

    mod=cantMemoria % 4;
    if(mod > 0)
        noPag = (cantMemoria / 4) + 1;
    else
        noPag = cantMemoria / 4;

    return noPag;
}

int recuperaPagDisp(Marco Marcos[])
{
    int i=2;
    int encontrado=0;
    int marco=0;

    while(encontrado == 0)
    {
        if(Marcos[i].bndDisp == 1)
        {
            marco=i;
            encontrado=1;
        }
        i++;
    }
    return marco;
}

int retornaPosliberaMarco(Marco Marcos[],int numPagina,int numProceso)
{
    int i=2;
    int encontrado=0;
    int posicion=0;

    while(encontrado == 0)
    {
        if((Marcos[i].numPagina == numPagina) && (Marcos[i].marcoIdProceso == numProceso))
        {
            posicion=i;
            encontrado=1;
        }
        i++;
    }
    return posicion;
}

Marco liberaMarco(Marco Marcos[],int numPagina)
{
    int i=2;
    int encontrado=0;
    Marco marcoRetornar;

    while(encontrado == 0)
    {
        if(Marcos[i].numPagina == numPagina)
        {
            Marcos[i].numPagina = 0;
            Marcos[i].memDisponible = 4;
            Marcos[i].tamPagina = 0;
            Marcos[i].bndDisp = 1;
            Marcos[i].marcoIdProceso = 0;
            encontrado=1;
        }
        i++;
    }
    return marcoRetornar;
}

void muestraMemoria(Marco Marcos[])
{
    int i=0;
    int j=0;
    int auxgoto=0;

    gotoxy(1,9);printf("No. Esp");

    for(i=0; i< 15; i++)
    {
        gotoxy(2,11+auxgoto);printf("%d",i);
        auxgoto += 2;
    }

    auxgoto=0;
    for(i=0; i< 15; i++)
    {
        if(Marcos[i].bndDisp == 0)
        {
            for(j=0; j < Marcos[i].tamPagina; j++)
            {
                gotoxy(4+j,11+auxgoto);printf("%c%c",219,219);
            }
        }
        auxgoto += 2;
    }
    gotoxy(12,9);printf("No. Esp");
    auxgoto=0;
    for(i=15; i< capMarco; i++)
    {
        gotoxy(12,11+auxgoto);printf("%d",i);
        auxgoto += 2;
    }

    auxgoto=0;
    for(i=15; i< capMarco; i++)
    {
        if(Marcos[i].bndDisp == 0)
        {
            for(j=0; j < Marcos[i].tamPagina; j++)
            {
                gotoxy(15+j,11+auxgoto);printf("%c%c",219,219);
            }
        }
        auxgoto += 2;
    }
}

void limpiaPantallaMemoria(Marco Marcos[])
{
    int i=0;
    int auxgoto=0;

    for(i=0; i< 15; i++)
    {
        gotoxy(1,11+auxgoto);printf("                        ");
        auxgoto += 2;
    }
}

void Proceso(COLAPROCESO *NUEVOS,int cantidadProcesos,COLAPROCESO *LISTOS,COLAPROCESO *CPN,COLAPROCESOTERMINADO *CPT,int quantum)
{
    int bndEspacio=0;
    int numMarco=0;
    int numPag=0;
    int memoria=0;
    int posicion=0;
    int cantMarcosDisp = 0;
    int bndIntReloj=0;
    int reloj=1;
    int relojGlobal=0;
    int auxTiempo=0;
    int contAux=0;
    int contMemoria=0;
    int contProceso=0;
    int cantProceso=0;
    int gotobcp=0;
    int axgoto=0;
    int axxgoto=0;
    int auxiliar=0;
    int numPrograma=0;
    int ax=0;
    int i=0;
    int j=0;
    int k=0;
    int m=0;
    int bndAuxiliar=0;
    int contOperador=0;
    int contLote=0;
    int numLotesPendientes=0;
    int auxProceso=1;
    int num=0;
    int num1=0;
    int resultado=0;
    int auxgoto=0;
    int aux_goto=0;
    int bndAuxProceso=0;
    int bndErrorProceso=0;
    int contProcesosEjec=0;
    int bndEncendido=0;
    int bndProcesoBloqueado=0;
    int nuevos=0;
    int bndNuevos=0;
    int contCPN=0;
    int contCPNAux=0;
    char operacion[10];
    char operando1[5];
    char operando2[5];
    char operador1;
    char caracter;
    char carac;
    int numProMostrar=0;
    int tamanoMostrar=0;

    PROCESO proceso;
    PROCESO procesoCreado;
    PROCESO procesoNuevo;
    PROCESOTERMINADO procesoTerminado;

    NodoProceso *auxNuevos;
    NodoProceso *auxListos;
    NodoProceso *aux;
    NodoProceso *auxiliarI;
    NodoProceso *auxCPN;

    numPrograma=NUEVOS->contProceso;
    cantProceso=cantidadProcesos;
    Marco Marcos[capMarco];

    inicializaMarcos(Marcos);

    nuevos=cantProceso;
    /**Cola Nuevos a Cola Listos estimación de memoria**/
    auxNuevos=NUEVOS->frente->sig;//Primer Proceso
    cantMarcosDisp=marcosDisponibles(Marcos);
    memoria=auxNuevos->Proceso.memProceso;
    if((memoria) <= (cantMarcosDisp * 4))
    {
        bndEspacio=1;
        numPag = calculaPaginas(auxNuevos->Proceso.memProceso);
        for(i=0; i< numPag; i++)
        {
            numMarco=recuperaPagDisp(Marcos);
            auxNuevos->Proceso.paginas[i].pagina=i;
            auxNuevos->Proceso.paginas[i].marco=numMarco;
            Marcos[numMarco].marcoIdProceso=auxNuevos->Proceso.numPrograma;
            Marcos[numMarco].noMarco=numMarco;
            Marcos[numMarco].numPagina=i;
            if(memoria >= 4)
            {
                memoria -= 4;
                Marcos[numMarco].tamPagina=4;
                auxNuevos->Proceso.paginas[i].capPagina=4;
            }
            else
            {
                Marcos[numMarco].tamPagina=memoria;
                auxNuevos->Proceso.paginas[i].capPagina=memoria;
                memoria=0;
            }
            Marcos[numMarco].bndDisp=0;
            auxNuevos->Proceso.cantPaginas++;
        }
    }
    else
    {
        /**Toma datos del proceso por entrar**/
        numProMostrar=auxNuevos->Proceso.numPrograma;
        tamanoMostrar=auxNuevos->Proceso.memProceso;
    }
    while((auxNuevos != NULL) && (bndEspacio == 1))
    {
        bndEspacio=0;
        procesoNuevo=auxNuevos->Proceso;
        procesoNuevo.status=0;//nuevo
        procesoNuevo.bndBloqueado=0;
        procesoNuevo.contTiempoEspera=0;
        procesoNuevo.bndNuevo=0;
        procesoNuevo.tejecucion=0;
        procesoNuevo.tLlegada=relojGlobal;
        //procesoNuevo.tRespuesta=relojGlobal;
        procesoNuevo.tServicio=procesoNuevo.TME;
        insertar(LISTOS,procesoNuevo);
        contMemoria++;
        auxNuevos->Proceso.bndTerminado=1;
        auxNuevos=auxNuevos->sig;
        nuevos--;

        cantMarcosDisp=marcosDisponibles(Marcos);
        if(auxNuevos != NULL)
        {
            memoria=auxNuevos->Proceso.memProceso;
            if((memoria) <= (cantMarcosDisp * 4))
            {
                bndEspacio=1;
                numPag = calculaPaginas(auxNuevos->Proceso.memProceso);
                for(i=0; i< numPag; i++)
                {
                    numMarco=recuperaPagDisp(Marcos);
                    auxNuevos->Proceso.paginas[i].pagina=i;
                    auxNuevos->Proceso.paginas[i].marco=numMarco;
                    Marcos[numMarco].marcoIdProceso=auxNuevos->Proceso.numPrograma;
                    Marcos[numMarco].noMarco=numMarco;
                    Marcos[numMarco].numPagina=i;
                    if(memoria >= 4)
                    {
                        memoria -= 4;
                        Marcos[numMarco].tamPagina=4;
                        auxNuevos->Proceso.paginas[i].capPagina=4;
                    }
                    else
                    {
                        Marcos[numMarco].tamPagina=memoria;
                        auxNuevos->Proceso.paginas[i].capPagina=memoria;
                        memoria=0;
                    }
                    Marcos[numMarco].bndDisp=0;
                    auxNuevos->Proceso.cantPaginas++;
                }
            }
            else
            {
                //Mostrar Proceso por entrar
                numProMostrar=auxNuevos->Proceso.numPrograma;
                tamanoMostrar=auxNuevos->Proceso.memProceso;
            }
        }
    }

    /**Se toma el proceso de la cola de nuevos**/
    aux=LISTOS->frente->sig;
    while(aux != NULL)
    {
        strcpy(operacion,aux->Proceso.operacion);

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
        gotoxy(50,3);printf("----- PRACTICA NO.7 -----");
        if(nuevos < 0)
            nuevos=0;
        gotoxy(3,3);printf("Nuevos: %d",nuevos); //Cantidad de Listos
        gotoxy(2,5);printf("Quantum: %d",quantum); //Valor del Quantum
        if(nuevos > 0)
        {
            gotoxy(17,3);printf("Num. Proceso por Entrar: %d",numProMostrar);
            gotoxy(17,5);printf("Tam. Proceso por Entrar: %d",tamanoMostrar);
        }
        limpiaPantallaMemoria(Marcos);
        muestraMemoria(Marcos);
        gotoxy(42,10);printf("Listos");
        gotoxy(60,10);printf("Bloqueados");
        auxListos=aux->sig;
        auxgoto=0;
        aux_goto=0;
        while(auxListos != NULL)
        {
            /**Mostrar cola de listos**/
            if(auxListos->Proceso.status == 0)
            {
                gotoxy(37,13+auxgoto); printf("Num. Programa: %d",auxListos->Proceso.numPrograma);
                gotoxy(46,15+auxgoto);printf("TME: %d",auxListos->Proceso.TME);
                gotoxy(34,17+auxgoto);printf("Tiempo Restante: %d",auxListos->Proceso.TiempoRest);
                gotoxy(43,19+auxgoto);printf("Tamano: %d",auxListos->Proceso.memProceso);
                auxgoto+=10;
                auxListos=auxListos->sig;
            }
            /**Mostrar cola de bloqueados**/
            else
            {
                if(auxListos->Proceso.status == 1)
                {
                    gotoxy(57,13+aux_goto);printf("Num. Programa: %d",auxListos->Proceso.numPrograma);
                    gotoxy(67,15+aux_goto);printf("TTB: %d",auxListos->Proceso.contTiempoEspera);
                    aux_goto+=6;
                    auxListos=auxListos->sig;
                }
            }
        }

        /**Procesos terminados**/
        if((procesoTerminado.bnd == 1) && (bndAuxProceso == 0))
        {
            gotoxy(109,14);printf("                                 ");
            gotoxy(113,10);printf("Procesos Terminados");
            insertaProcesoTerminado(CPT,procesoTerminado);
            mostrarProcesoTerminado(CPT);
            contProcesosEjec++;
            bndAuxProceso=1;
        }
        else
        {
            if((bndProcesoBloqueado == 1) || (bndAuxProceso == 1))
            {
                gotoxy(109,14);printf("                                 ");
                gotoxy(113,10);printf("Procesos Terminados");
                mostrarProcesoTerminado(CPT);
            }
            else
            {
                gotoxy(113,10);printf("Procesos Terminados");
                gotoxy(108,14);printf("No hay Procesos Terminados.");
            }
        }

        /**Proceso en ejecución**/
        proceso=aux->Proceso;
        if(proceso.bndNuevo == 0)
        {
            proceso.tRespuesta=relojGlobal-contProceso;
            proceso.bndNuevo=1;
        }
        gotoxy(82,10);printf("Proceso en Ejecucion");
        gotoxy(82,13);printf("Num. Programa: %d",proceso.numPrograma);
        gotoxy(86,15);printf("Operacion: %s",proceso.operacion);
        gotoxy(92,17);printf("TME: %d",proceso.TME);
        gotoxy(80,19);printf("Tiempo Restante: %d",proceso.TiempoRest);
        gotoxy(92,21);printf("TTE: ");
        gotoxy(92,23);printf("TRE: ");
        gotoxy(92,25);printf("TTQ: ");
        gotoxy(85,34);printf("Reloj Global: %d",relojGlobal);

        if(proceso.bndBloqueado == 0)
        {
            if(proceso.tRestQuantum >= quantum)
            {
                auxiliar=quantum;
                m=proceso.TiempoRest;
                if(m < 0)//modificar
                    m=0;
                k=0;
                auxTiempo=proceso.TME-proceso.tejecucion;
            }
            else
            {
                auxiliar=proceso.TiempoRest;
                m=proceso.TiempoRest;
                if(m < 0)//modificar
                    m=0;
                k=0;
                auxTiempo=proceso.TME-proceso.tejecucion;
                bndIntReloj=0;
            }
        }
        else
        {
            if(proceso.bndBloqueado == 1)
            {
                if(proceso.TiempoRest >= quantum)
                {
                    auxiliar=quantum;
                    m=proceso.TiempoRest;
                    if(m < 0)//modificar
                        m=0;
                    k=0;
                    auxTiempo=proceso.TME-proceso.tejecucion;
                }
                else
                {
                    auxiliar=proceso.TiempoRest;
                    m=proceso.TiempoRest;
                    if(m < 0)//modificar
                        m=0;
                    k=0;
                    auxTiempo=proceso.TME-proceso.tejecucion;
                    bndIntReloj=0;
                }

            }
        }
        while((reloj <= auxiliar) && (k <= auxTiempo) && (bndErrorProceso == 0) && (bndProcesoBloqueado == 0))
        {
            if(kbhit())
                caracter=getch();
            gotoxy(92,21);printf("TTE:    ");
            gotoxy(92,23);printf("TRE:    ");
            gotoxy(92,25);printf("TTQ:    ");
            gotoxy(92,21);printf("TTE: %d",k);
            gotoxy(92,23);printf("TRE: %d",m);
            gotoxy(92,25);printf("TTQ: %d",reloj);
            delay(300);
            if(caracter == 'W')
            {
                gotoxy(82,27);printf("Se ha producido un error");
                delay(150);
                bndErrorProceso=1;
            }
            else
            {
                if(caracter == 'P')
                {
                    while(carac != 'C')
                    {
                        gotoxy(82,27);printf("Pausa...Presiona la Tecla 'C' para Continuar");
                        kbhit();
                        carac=getch();
                    }
                    if(carac == 'C')
                    {
                        gotoxy(82,27);printf("                                              ");
                        gotoxy(82,27);printf(".......Listo para continuar.......");
                        delay(200);
                        gotoxy(82,27);printf("                                  ");
                    }
                    gotoxy(82,34);printf("                                 ");
                }
                else
                {
                    if(caracter == 'I')
                    {
                        gotoxy(80,27);printf("El proceso ha sido Interrumpido");
                        delay(100);
                        proceso.status=1;//bloqueado
                        proceso.bndBloqueado=1;
                        proceso.contTiempoEspera=0;
                        insertar(LISTOS,proceso);
                        bndProcesoBloqueado=1;
                    }
                    else
                    {
                        if(caracter == 'N')
                        {
                            numPrograma=NUEVOS->contProceso;
                            procesoCreado=creaProceso(NUEVOS->contProceso);
                            NUEVOS->contProceso++;
                            procesoCreado.status=0;

                            /**Verifica si hay marcos disponibles**/
                            cantMarcosDisp=marcosDisponibles(Marcos);
                            memoria=procesoCreado.memProceso;
                            if(((memoria) <= (cantMarcosDisp * 4)) && (nuevos <= 0))
                            {
                                bndEspacio=1;
                                numPag = calculaPaginas(procesoCreado.memProceso);
                                for(i=0; i< numPag; i++)
                                {
                                    numMarco=recuperaPagDisp(Marcos);
                                    procesoCreado.paginas[i].pagina=i;
                                    procesoCreado.paginas[i].marco=numMarco;
                                    Marcos[numMarco].marcoIdProceso=procesoCreado.numPrograma;
                                    Marcos[numMarco].noMarco=numMarco;
                                    Marcos[numMarco].numPagina=i;
                                    if(memoria >= 4)
                                    {
                                        memoria -= 4;
                                        Marcos[numMarco].tamPagina=4;
                                        procesoCreado.paginas[i].capPagina=4;
                                    }
                                    else
                                    {
                                        Marcos[numMarco].tamPagina=memoria;
                                        procesoCreado.paginas[i].capPagina=memoria;
                                        memoria=0;
                                    }
                                    Marcos[numMarco].bndDisp=0;
                                    procesoCreado.cantPaginas++;
                                }
                            }
                            /**Si hay espacio en memoria y no hay procesos en cola de nuevos**/
                            if((bndEspacio == 1) && (nuevos <= 0))
                            {
                                bndEspacio=0;
                                procesoCreado.contTiempoEspera=0;
                                procesoCreado.bndNuevo=0;
                                procesoCreado.tejecucion=0;
                                procesoCreado.tLlegada=relojGlobal;
                                procesoCreado.tRespuesta=0;
                                procesoCreado.tServicio=procesoNuevo.TME;
                                insertar(LISTOS,procesoCreado);
                                cantProceso++;
                                contMemoria++;
                                gotoxy(82,27);printf("...Se creo un Proceso Nuevo...");
                                delay(250);
                                gotoxy(82,27);printf("                                      ");
                                gotoxy(50,3);printf("----- PRACTICA NO.7 -----");
                                gotoxy(42,10);printf("Listos");
                                axxgoto=0;
                                auxiliarI=aux->sig;
                                while(auxiliarI != NULL)
                                {
                                    if(auxiliarI->Proceso.status == 0)
                                    {
                                        gotoxy(37,13+axxgoto); printf("Num. Programa: %d",auxiliarI->Proceso.numPrograma);
                                        gotoxy(46,15+axxgoto);printf("TME: %d",auxiliarI->Proceso.TME);
                                        gotoxy(34,17+axxgoto);printf("Tiempo Restante: %d",auxiliarI->Proceso.TiempoRest);
                                        gotoxy(43,19+axxgoto);printf("Tamano: %d",auxiliarI->Proceso.memProceso);
                                        delay(200);
                                        axxgoto+=10;
                                    }
                                    auxiliarI=auxiliarI->sig;
                                }
                            }
                            else
                            {
                                bndNuevos=1;
                                numPrograma=NUEVOS->contProceso;
                                procesoCreado.bndTerminado=0;
                                insertar(CPN,procesoCreado);
                                contCPN++;
                                if(nuevos == 0)
                                {
                                    //Mostrar Proceso por entrar
                                    numProMostrar=procesoCreado.numPrograma;
                                    tamanoMostrar=procesoCreado.memProceso;
                                }
                                nuevos++;
                                numPrograma++;
                                cantProceso++;
                                gotoxy(3,3);printf("Nuevos: %d",nuevos); //Cantidad de Listos
                                gotoxy(2,5);printf("Quantum: %d",quantum); //Valor del Quantum
                                gotoxy(67,27);printf("...Se creo un Proceso Nuevo...");
                                delay(200);
                                gotoxy(67,27);printf("                                      ");
                            }
                            limpiaPantallaMemoria(Marcos);
                            muestraMemoria(Marcos);
                            //Mostrar Proceso por entrar
                            if(nuevos > 0)
                            {
                                gotoxy(17,3);printf("Num. Proceso por Entrar: %d",numProMostrar);
                                gotoxy(17,5);printf("Tam. Proceso por Entrar: %d",tamanoMostrar);
                            }
                        }
                        else
                        {
                            if(caracter == 'T')
                            {
                                while(carac != 'C')
                                {
                                    system("cls");
                                    encabezado();

                                    //Proceso Terminado
                                    gotobcp=mostrarTiemposProcesosTerminados(CPT);

                                    //Procesos Listos y Bloqueados
                                    auxiliarI=aux;
                                    int bndListo=1;
                                    while(auxiliarI != NULL)
                                    {
                                        auxiliarI->Proceso.tEspera=(-1)*(auxiliarI->Proceso.tLlegada-relojGlobal);
                                        gotoxy(3,10+gotobcp);printf("%d",auxiliarI->Proceso.numPrograma);
                                        if(auxiliarI->Proceso.status == 0)
                                        {
                                            if(bndListo == 1)
                                            {
                                                gotoxy(11,10+gotobcp);printf("EJECUCION");
                                                bndListo=0;
                                            }
                                            else
                                            {
                                                gotoxy(11,10+gotobcp);printf("LISTOS");
                                            }
                                        }
                                        if(auxiliarI->Proceso.status == 1)
                                        {
                                            gotoxy(11,10+gotobcp);printf("BLOQUEADO");
                                        }
                                        gotoxy(25,10+gotobcp);printf("%s",auxiliarI->Proceso.operacion);
                                        gotoxy(38,10+gotobcp);printf("NULO");
                                        gotoxy(52,10+gotobcp);printf("%d",auxiliarI->Proceso.tLlegada);
                                        gotoxy(66,10+gotobcp);printf("NULO");
                                        gotoxy(79,10+gotobcp);printf("NULO");
                                        gotoxy(91,10+gotobcp);printf("%d",auxiliarI->Proceso.tEspera);
                                        gotoxy(102,10+gotobcp);printf("%d",auxiliarI->Proceso.tServicio);
                                        if(auxiliarI->Proceso.status == 0)
                                        {
                                            gotoxy(112,10+gotobcp);printf("NULO");
                                        }
                                        if(auxiliarI->Proceso.status == 1)
                                        {
                                            gotoxy(112,10+gotobcp);printf("%d",auxiliarI->Proceso.tiempInt - auxiliarI->Proceso.contTiempoEspera);
                                        }
                                        gotoxy(124,10+gotobcp);printf("%d",auxiliarI->Proceso.tRespuesta);
                                        auxiliarI=auxiliarI->sig;
                                        gotobcp+=2;
                                    }
                                    //Procesos Nuevos
                                    auxiliarI=auxNuevos;
                                    while(auxiliarI != NULL)
                                    {
                                        gotoxy(3,10+gotobcp);printf("%d",auxiliarI->Proceso.numPrograma);
                                        gotoxy(11,10+gotobcp);printf("NUEVOS");
                                        gotoxy(25,10+gotobcp);printf("%s",auxiliarI->Proceso.operacion);
                                        gotoxy(38,10+gotobcp);printf("NULO");
                                        gotoxy(52,10+gotobcp);printf("NULO");
                                        gotoxy(66,10+gotobcp);printf("NULO");
                                        gotoxy(79,10+gotobcp);printf("NULO");
                                        gotoxy(91,10+gotobcp);printf("NULO");
                                        gotoxy(102,10+gotobcp);printf("NULO");
                                        gotoxy(112,10+gotobcp);printf("NULO");
                                        gotoxy(124,10+gotobcp);printf("NULO");
                                        auxiliarI=auxiliarI->sig;
                                        gotobcp+=2;
                                    }
                                    if(bndAuxiliar != 0)
                                    {
                                        auxiliarI=auxCPN;
                                        while(auxiliarI != NULL)
                                        {
                                            gotoxy(3,10+gotobcp);printf("%d",auxiliarI->Proceso.numPrograma);
                                            gotoxy(11,10+gotobcp);printf("NUEVOS");
                                            gotoxy(25,10+gotobcp);printf("%s",auxiliarI->Proceso.operacion);
                                            gotoxy(38,10+gotobcp);printf("NULO");
                                            gotoxy(52,10+gotobcp);printf("NULO");
                                            gotoxy(66,10+gotobcp);printf("NULO");
                                            gotoxy(79,10+gotobcp);printf("NULO");
                                            gotoxy(91,10+gotobcp);printf("NULO");
                                            gotoxy(102,10+gotobcp);printf("NULO");
                                            gotoxy(112,10+gotobcp);printf("NULO");
                                            gotoxy(124,10+gotobcp);printf("NULO");
                                            auxiliarI=auxiliarI->sig;
                                            gotobcp+=2;
                                        }
                                    }
                                    gotoxy(60,38);printf("Pausa...Presiona la Tecla 'C' para Continuar");
                                    kbhit();
                                    carac=getch();
                                }
                                //Limpia Pantalla de BCP
                                system("cls");
                                gotoxy(50,3);printf("----- PRACTICA NO.7 -----");
                                gotoxy(3,3);printf("Nuevos: %d",nuevos); //Cantidad de Listos
                                gotoxy(2,5);printf("Quantum: %d",quantum); //Valor del Quantum
                                if(nuevos > 0)
                                {
                                    gotoxy(17,3);printf("Num. Proceso por Entrar: %d",numProMostrar);
                                    gotoxy(17,5);printf("Tam. Proceso por Entrar: %d",tamanoMostrar);
                                }
                                limpiaPantallaMemoria(Marcos);
                                muestraMemoria(Marcos);
                                gotoxy(42,10);printf("Listos");
                                gotoxy(60,10);printf("Bloqueados");
                                gotoxy(57,13);   printf("                ");
                                gotoxy(67,15);   printf("                ");
                                gotoxy(57,13+6); printf("                ");
                                gotoxy(67,15+6); printf("                ");
                                gotoxy(57,13+12);printf("                ");
                                gotoxy(67,15+12);printf("                ");
                                gotoxy(57,13+18);printf("                ");
                                gotoxy(67,15+18);printf("                ");
                                axgoto=0;
                                axxgoto=0;
                                auxiliarI=aux->sig;
                                while(auxiliarI != NULL)
                                {
                                    if(auxiliarI->Proceso.status == 0)
                                    {
                                        gotoxy(37,13+axxgoto); printf("Num. Programa: %d",auxiliarI->Proceso.numPrograma);
                                        gotoxy(46,15+axxgoto);printf("TME: %d",auxiliarI->Proceso.TME);
                                        gotoxy(34,17+axxgoto);printf("Tiempo Restante: %d",auxiliarI->Proceso.TiempoRest);
                                        gotoxy(43,19+axxgoto);printf("Tamano: %d",auxiliarI->Proceso.memProceso);
                                        axxgoto+=10;
                                    }
                                    if(auxiliarI->Proceso.status == 1)
                                    {
                                        auxiliarI->Proceso.contTiempoEspera++;
                                        gotoxy(57,13+axgoto);printf("Num. Programa: %d",auxiliarI->Proceso.numPrograma);
                                        gotoxy(67,15+axgoto);printf("TTB: %d",auxiliarI->Proceso.contTiempoEspera);
                                        axgoto+=6;
                                        if(auxiliarI->Proceso.contTiempoEspera >= auxiliarI->Proceso.tiempInt)
                                        {
                                            auxiliarI->Proceso.status=0;
                                            auxiliarI->Proceso.contTiempoEspera=0;
                                            auxiliarI->Proceso.TiempoRest=auxiliarI->Proceso.TME-auxiliarI->Proceso.tejecucion;
                                        }
                                    }
                                    auxiliarI=auxiliarI->sig;
                                }
                                gotoxy(82,10);printf("Proceso en Ejecucion");
                                gotoxy(82,13);printf("Num. Programa: %d",proceso.numPrograma);
                                gotoxy(86,15);printf("Operacion: %s",proceso.operacion);
                                gotoxy(92,17);printf("TME: %d",proceso.TME);
                                gotoxy(80,19);printf("Tiempo Restante: %d",proceso.TiempoRest);
                                gotoxy(92,21);printf("TTE:    ");
                                gotoxy(92,23);printf("TRE:    ");
                                gotoxy(92,25);printf("TTQ:    ");
                                gotoxy(92,21);printf("TTE: %d",k);
                                gotoxy(92,23);printf("TRE: %d",m);
                                gotoxy(92,25);printf("TTQ: %d",reloj);
                                gotoxy(113,10);printf("Procesos Terminados");
                                if(vaciaProcesoTerminado(CPT))
                                {
                                    gotoxy(120,14);printf("No hay Procesos Terminados.");
                                }
                                else
                                {
                                    mostrarProcesoTerminado(CPT);
                                }
                                gotoxy(85,34);printf("Reloj Global: %d",relojGlobal);
                            }
                            else
                            {
                                if(caracter == 'A')
                                {
                                    while(carac != 'C')
                                    {
                                        system("cls");
                                        /**Mostrar tablas de procesos**/
                                        gotoxy(50,2);printf("----- PRACTICA NO.7 -----");
                                        gotoxy(54,4);printf("TABLAS DE PROCESOS");
                                        // gotoxy(1,7);printf("No.Prog.");
                                        auxListos=aux;
                                        auxgoto=0;
                                        aux_goto=0;
                                        while(auxListos != NULL)
                                        {
                                            if((auxListos->Proceso.status == 0) || (auxListos->Proceso.status == 1))
                                            {
                                                gotoxy(3 +auxgoto,7); printf("Num. Programa: %d",auxListos->Proceso.numPrograma);
                                                gotoxy(5 +auxgoto,9);printf("Pag.");
                                                gotoxy(10+auxgoto,9);printf("Marco");
                                                aux_goto=0;
                                                for(i=0; i < auxListos->Proceso.cantPaginas; i++)
                                                {
                                                    gotoxy(6 +auxgoto,11+aux_goto);printf("%d",auxListos->Proceso.paginas[i].pagina);
                                                    gotoxy(12+auxgoto,11+aux_goto);printf("%d",auxListos->Proceso.paginas[i].marco);
                                                    aux_goto += 2;//vertical
                                                }
                                                auxListos=auxListos->sig;
                                                auxgoto+=20;//Horizontal
                                            }
                                        }
                                        auxgoto=0;
                                        gotoxy(118,9); printf("No. Marco Disp.");
                                        for(i=2; i < capMarco; i++)
                                        {
                                            if(Marcos[i].bndDisp == 1)
                                            {
                                                gotoxy(124,11+auxgoto);printf("%d",Marcos[i].noMarco);
                                                auxgoto+=2;
                                            }
                                        }
                                        gotoxy(50,34);printf("Pausa...Presiona la Tecla 'C' para Continuar");
                                        kbhit();
                                        carac=getch();
                                    }
                                    //Limpia Pantalla de Tablas de  procesos
                                    system("cls");
                                    gotoxy(50,3);printf("----- PRACTICA NO.7 -----");
                                    gotoxy(3,3);printf("Nuevos: %d",nuevos); //Cantidad de Listos
                                    gotoxy(2,5);printf("Quantum: %d",quantum); //Valor del Quantum
                                    limpiaPantallaMemoria(Marcos);
                                    muestraMemoria(Marcos);
                                    gotoxy(42,10);printf("Listos");
                                    gotoxy(60,10);printf("Bloqueados");
                                    if(nuevos > 0)
                                    {
                                        gotoxy(17,3);printf("Num. Proceso por Entrar: %d",numProMostrar);
                                        gotoxy(17,5);printf("Tam. Proceso por Entrar: %d",tamanoMostrar);
                                    }
                                    gotoxy(57,13);   printf("                ");
                                    gotoxy(67,15);   printf("                ");
                                    gotoxy(57,13+6); printf("                ");
                                    gotoxy(67,15+6); printf("                ");
                                    gotoxy(57,13+12);printf("                ");
                                    gotoxy(67,15+12);printf("                ");
                                    gotoxy(57,13+18);printf("                ");
                                    gotoxy(67,15+18);printf("                ");
                                    axgoto=0;
                                    axxgoto=0;
                                    auxiliarI=aux->sig;
                                    while(auxiliarI != NULL)
                                    {
                                        if(auxiliarI->Proceso.status == 0)
                                        {
                                            gotoxy(37,13+axxgoto); printf("Num. Programa: %d",auxiliarI->Proceso.numPrograma);
                                            gotoxy(46,15+axxgoto);printf("TME: %d",auxiliarI->Proceso.TME);
                                            gotoxy(34,17+axxgoto);printf("Tiempo Restante: %d",auxiliarI->Proceso.TiempoRest);
                                            gotoxy(43,19+axxgoto);printf("Tamano: %d",auxiliarI->Proceso.memProceso);
                                            axxgoto+=10;
                                        }
                                        if(auxiliarI->Proceso.status == 1)
                                        {
                                            auxiliarI->Proceso.contTiempoEspera++;
                                            gotoxy(57,13+axgoto);printf("Num. Programa: %d",auxiliarI->Proceso.numPrograma);
                                            gotoxy(67,15+axgoto);printf("TTB: %d",auxiliarI->Proceso.contTiempoEspera);
                                            axgoto+=6;
                                            if(auxiliarI->Proceso.contTiempoEspera >= auxiliarI->Proceso.tiempInt)
                                            {
                                                auxiliarI->Proceso.status=0;
                                                auxiliarI->Proceso.contTiempoEspera=0;
                                                auxiliarI->Proceso.TiempoRest=auxiliarI->Proceso.TME-auxiliarI->Proceso.tejecucion;
                                            }
                                        }
                                        auxiliarI=auxiliarI->sig;
                                    }
                                    gotoxy(82,10);printf("Proceso en Ejecucion");
                                    gotoxy(82,13);printf("Num. Programa: %d",proceso.numPrograma);
                                    gotoxy(86,15);printf("Operacion: %s",proceso.operacion);
                                    gotoxy(92,17);printf("TME: %d",proceso.TME);
                                    gotoxy(80,19);printf("Tiempo Restante: %d",proceso.TiempoRest);
                                    gotoxy(92,21);printf("TTE:    ");
                                    gotoxy(92,23);printf("TRE:    ");
                                    gotoxy(92,25);printf("TTQ:    ");
                                    gotoxy(92,21);printf("TTE: %d",k);
                                    gotoxy(92,23);printf("TRE: %d",m);
                                    gotoxy(92,25);printf("TTQ: %d",reloj);
                                    gotoxy(113,10);printf("Procesos Terminados");
                                    if(vaciaProcesoTerminado(CPT))
                                    {
                                        gotoxy(120,14);printf("No hay Procesos Terminados.");
                                    }
                                    else
                                    {
                                        mostrarProcesoTerminado(CPT);
                                    }
                                    gotoxy(85,34);printf("Reloj Global: %d",relojGlobal);
                                }
                                else
                                    gotoxy(72,27);printf("                           ");
                            }
                        }
                    }
                }
                m--;
                k++;
                reloj++;
                proceso.tRestQuantum--;
                proceso.TiempoRest--;
                proceso.tejecucion++;
                relojGlobal++;
                gotoxy(85,34);printf("Reloj Global: %d",relojGlobal);
                axgoto=0;
                axxgoto=0;
                gotoxy(57,13);   printf("                ");
                gotoxy(67,15);   printf("                ");
                gotoxy(57,13+6); printf("                ");
                gotoxy(67,15+6); printf("                ");
                gotoxy(57,13+12);printf("                ");
                gotoxy(67,15+12);printf("                ");
                gotoxy(57,13+18);printf("                ");
                gotoxy(67,15+18);printf("                ");

                auxiliarI=aux->sig;
                while(auxiliarI != NULL)
                {
                    if(auxiliarI->Proceso.status == 0)
                    {
                        gotoxy(37,13+axxgoto); printf("Num. Programa: %d",auxiliarI->Proceso.numPrograma);
                        gotoxy(46,15+axxgoto);printf("TME: %d",auxiliarI->Proceso.TME);
                        gotoxy(34,17+axxgoto);printf("Tiempo Restante: %d",auxiliarI->Proceso.TiempoRest);
                        gotoxy(43,19+axxgoto);printf("Tamano: %d",auxiliarI->Proceso.memProceso);
                        axxgoto+=10;
                    }
                    if(auxiliarI->Proceso.status == 1)
                    {
                        auxiliarI->Proceso.contTiempoEspera++;
                        gotoxy(57,13+axgoto);printf("Num. Programa: %d",auxiliarI->Proceso.numPrograma);
                        gotoxy(67,15+axgoto);printf("TTB: %d",auxiliarI->Proceso.contTiempoEspera);
                        axgoto+=6;
                        if(auxiliarI->Proceso.contTiempoEspera >= auxiliarI->Proceso.tiempInt)
                        {
                            auxiliarI->Proceso.status=0;
                            auxiliarI->Proceso.contTiempoEspera=0;
                            auxiliarI->Proceso.TiempoRest=auxiliarI->Proceso.TME-auxiliarI->Proceso.tejecucion;
                        }
                    }
                    auxiliarI=auxiliarI->sig;
                }
            }
            caracter='\0';
            carac='\0';
        }
        if((reloj >= quantum) && (bndProcesoBloqueado == 0))
        {
            reloj=1;
            insertar(LISTOS,proceso);
            bndIntReloj=1;
        }
        else
        {
            if((proceso.TiempoRest == 0) || (bndProcesoBloqueado == 1))
            {
                reloj=1;
                bndIntReloj=0;
            }
        }

        //Si se interrumpe el último proceso
        if(((contProceso+1) == cantProceso) && (bndProcesoBloqueado == 1))
        {
            system("cls");
            gotoxy(50,3);printf("----- PRACTICA NO.7 -----");
            gotoxy(3,3);printf("Nuevos: %d",nuevos); //Cantidad de Listos
            gotoxy(2,5);printf("Quantum: %d",quantum); //Valor del Quantum
            limpiaPantallaMemoria(Marcos);
            muestraMemoria(Marcos);
            gotoxy(42,10);printf("Listos");
            gotoxy(60,10);printf("Bloqueados");
            gotoxy(113,10);printf("Procesos Terminados");
            //Mostrar Proceso por entrar
            if(nuevos > 0)
            {
                gotoxy(17,3);printf("Num. Proceso por Entrar: %d",numProMostrar);
                gotoxy(17,5);printf("Tam. Proceso por Entrar: %d",tamanoMostrar);
            }
            auxgoto=0;
            aux_goto=0;
            if(nuevos < 0)
                nuevos=0;
            encabezadoProcesoNoEjecucion();
            gotoxy(69,27);printf("...En Espera de Proceso...");
            mostrarProcesoTerminado(CPT);
            ax=0;
            while(ax != 2)
            {
                if(ax == 1)
                {
                    ax=2;
                    gotoxy(37,13);printf("                      ");
                    gotoxy(46,15);printf("                    ");
                }
                proceso.tejecucion++;
                relojGlobal++;
                gotoxy(85,34);printf("Reloj Global: %d",relojGlobal);

                gotoxy(44,15);printf("                    ");
                axgoto=0;
                axxgoto=0;
                gotoxy(57,13);   printf("                ");
                gotoxy(67,15);   printf("                ");
                gotoxy(57,13+6); printf("                ");
                gotoxy(67,15+6); printf("                ");
                gotoxy(57,13+12);printf("                ");
                gotoxy(67,15+12);printf("                ");
                gotoxy(57,13+18);printf("                ");
                gotoxy(67,15+18);printf("                ");
                auxiliarI=aux->sig;
                while(auxiliarI != NULL)
                {
                    if(auxiliarI->Proceso.status == 0)
                    {
                        gotoxy(37,13+axxgoto);printf("Num. Programa: %d",auxiliarI->Proceso.numPrograma);
                        gotoxy(46,15+axxgoto);printf("TME: %d",auxiliarI->Proceso.TME);
                        gotoxy(34,17+axxgoto);printf("Tiempo Restante: %d",auxiliarI->Proceso.TiempoRest);
                        gotoxy(43,19+axxgoto);printf("Tamano: %d",auxiliarI->Proceso.memProceso);
                        delay(200);
                        axxgoto+=10;
                    }
                    if(auxiliarI->Proceso.status == 1)
                    {
                        auxiliarI->Proceso.contTiempoEspera++;
                        gotoxy(57,13+axgoto);printf("Num. Programa: %d",auxiliarI->Proceso.numPrograma);
                        gotoxy(67,15+axgoto);printf("TTB: %d",auxiliarI->Proceso.contTiempoEspera);
                        delay(200);
                        axgoto+=6;

                        if(auxiliarI->Proceso.contTiempoEspera >= auxiliarI->Proceso.tiempInt)
                        {
                            auxiliarI->Proceso.status=0;
                            auxiliarI->Proceso.contTiempoEspera=0;
                            auxiliarI->Proceso.TiempoRest=auxiliarI->Proceso.TME-auxiliarI->Proceso.tejecucion;
                            ax=1;
                        }
                    }
                    auxiliarI=auxiliarI->sig;
                }
            }
        }

        //Si no hay error en el proceso o ha sido bloqueado
        if((bndErrorProceso == 0) && (bndProcesoBloqueado == 0) && (bndIntReloj == 0))
        {
            gotoxy(92,21);printf("TTE: %d",k);
            gotoxy(92,23);printf("TRE: %d",m);
            gotoxy(92,25);printf("TTQ: %d",reloj);
            gotoxy(85,27);printf("......Terminado......");
            delay(300);
            procesoTerminado.numProg=proceso.numPrograma;
            procesoTerminado.TME=proceso.TME;
            //Calcula tiempos
            proceso.bndtermino=1; //Termino correctamente
            procesoTerminado.memProceso=proceso.memProceso;
            procesoTerminado.cantPaginas=proceso.cantPaginas;

            for(i=0; i<procesoTerminado.cantPaginas; i++)
                procesoTerminado.paginas[i]=proceso.paginas[i];

            for(i=0; i<procesoTerminado.cantPaginas; i++)
            {
                posicion = retornaPosliberaMarco(Marcos,procesoTerminado.paginas[i].pagina,procesoTerminado.numProg);
                if((posicion >=2) && (posicion <= 29))
                {
                    Marcos[posicion].numPagina = 0;
                    Marcos[posicion].memDisponible = 4;
                    Marcos[posicion].tamPagina = 0;
                    Marcos[posicion].bndDisp = 1;
                    Marcos[posicion].marcoIdProceso = 0;
                }
            }
            limpiaPantallaMemoria(Marcos);
            muestraMemoria(Marcos);
            delay(100);
            strcpy(procesoTerminado.operacion,proceso.operacion);
            if(bndEncendido == 0)
                procesoTerminado.resultado=resultado;
            else
                procesoTerminado.resultado=proceso.resultado;
            procesoTerminado.bnd=1;
            bndAuxProceso=0;
            contProceso++;
            contMemoria--;
            proceso.tFinalizacion=relojGlobal-contProceso;
            proceso.tRetorno=proceso.tFinalizacion-proceso.tLlegada;
            proceso.tServicio=proceso.tServicio;//calcula tiempos
            proceso.tEspera=relojGlobal-proceso.tServicio;
            //se copian en proceso terminado
            procesoTerminado.tejecucion=proceso.tejecucion;
            procesoTerminado.tEspera=proceso.tEspera;
            procesoTerminado.tFinalizacion=proceso.tFinalizacion;
            procesoTerminado.TiempoRest=proceso.TiempoRest;
            procesoTerminado.tLlegada=proceso.tLlegada;
            procesoTerminado.tRespuesta=proceso.tRespuesta;
            procesoTerminado.tServicio=proceso.tServicio;
            procesoTerminado.tRetorno=proceso.tRetorno;
        }
        else
        {
            if(bndErrorProceso == 1)
            {
                gotoxy(92,21);printf("TTE: %d",k);
                gotoxy(92,23);printf("TRE: %d",m);
                gotoxy(92,25);printf("TTQ: %d",reloj);
                gotoxy(82,27);printf("......Terminado......    ");
                delay(300);
                procesoTerminado.numProg=proceso.numPrograma;
                procesoTerminado.auxTiempo=proceso.tejecucion;
                proceso.tLlegada=proceso.tLlegada;//calcula tiempos
                proceso.tRespuesta=proceso.tRespuesta;//calcula tiempos
                proceso.tServicio=proceso.tejecucion;
                proceso.bndtermino=0; //Termino con error

                procesoTerminado.memProceso=proceso.memProceso;
                procesoTerminado.cantPaginas=proceso.cantPaginas;

                for(i=0; i<procesoTerminado.cantPaginas; i++)
                    procesoTerminado.paginas[i]=proceso.paginas[i];

                for(i=0; i<procesoTerminado.cantPaginas; i++)
                {
                    posicion = retornaPosliberaMarco(Marcos,procesoTerminado.paginas[i].pagina,procesoTerminado.numProg);
                    if((posicion >=2) && (posicion <= 29))
                    {
                        Marcos[posicion].numPagina = 0;
                        Marcos[posicion].memDisponible = 4;
                        Marcos[posicion].tamPagina = 0;
                        Marcos[posicion].bndDisp = 1;
                        Marcos[posicion].marcoIdProceso = 0;
                    }
                }
                limpiaPantallaMemoria(Marcos);
                muestraMemoria(Marcos);
                delay(100);

                strcpy(procesoTerminado.operacion,proceso.operacion);
                procesoTerminado.resultado=0;
                procesoTerminado.bnd=1;
                bndAuxProceso=0;
                contProceso++;
                contMemoria--;
                //calcula tiempos
                proceso.numPrograma=procesoTerminado.numProg;
                proceso.tFinalizacion=relojGlobal-contProceso;
                proceso.tRetorno=proceso.tFinalizacion-proceso.tLlegada;
                proceso.tEspera=relojGlobal-proceso.tServicio;
                //copia en proceso terminado
                procesoTerminado.tejecucion=proceso.tejecucion;
                procesoTerminado.tEspera=proceso.tEspera;
                procesoTerminado.tFinalizacion=proceso.tFinalizacion;
                procesoTerminado.TiempoRest=proceso.TiempoRest;
                procesoTerminado.tLlegada=proceso.tLlegada;
                procesoTerminado.tRespuesta=proceso.tRespuesta;
                procesoTerminado.tServicio=proceso.tServicio;
                procesoTerminado.tRetorno=proceso.tRetorno;
            }
        }

        if(bndIntReloj == 1)
        {
            gotoxy(85,27);printf("......Quantum Terminado......");
            delay(300);
            gotoxy(84,27);printf("                                     ");
        }

        //último proceso
        if(contProceso == cantProceso)
        {
            gotoxy(97,14);printf("                                 ");
            gotoxy(113,10);printf("Procesos Terminados");
            insertaProcesoTerminado(CPT,procesoTerminado);
            mostrarProcesoTerminado(CPT);
            contProcesosEjec++;
            bndAuxProceso=1;
            encabezadoProcesoNoEjecucion();
        }
        if((bndAuxiliar == 0) && (bndNuevos == 1))
        {
            auxCPN=CPN->frente->sig;
            bndAuxiliar=1;
        }
        else
        {
            if((bndAuxiliar == 2) && (nuevos > 0))
            {
                auxCPN=CPN->frente->sig;
                for(i=0; i < contCPNAux; i++)
                {
                    auxCPN=auxCPN->sig;
                }
                bndAuxiliar=1;
            }
        }
        //Si hay espacio en memoria
        if(auxNuevos != NULL)
        {
            cantMarcosDisp=marcosDisponibles(Marcos);
            memoria=auxNuevos->Proceso.memProceso;
            if((memoria) <= (cantMarcosDisp * 4))
            {
                bndEspacio=1;
                numPag = calculaPaginas(auxNuevos->Proceso.memProceso);
                for(i=0; i< numPag; i++)
                {
                    numMarco=recuperaPagDisp(Marcos);
                    auxNuevos->Proceso.paginas[i].pagina=i;
                    auxNuevos->Proceso.paginas[i].marco=numMarco;
                    Marcos[numMarco].marcoIdProceso=auxNuevos->Proceso.numPrograma;
                    Marcos[numMarco].noMarco=numMarco;
                    Marcos[numMarco].numPagina=i;
                    if(memoria >= 4)
                    {
                        memoria -= 4;
                        Marcos[numMarco].tamPagina=4;
                        auxNuevos->Proceso.paginas[i].capPagina=4;
                    }
                    else
                    {
                        Marcos[numMarco].tamPagina=memoria;
                        auxNuevos->Proceso.paginas[i].capPagina=memoria;
                        memoria=0;
                    }
                    Marcos[numMarco].bndDisp=0;
                    auxNuevos->Proceso.cantPaginas++;
                }
            }
            else
            {
                //Mostrar Proceso por entrar
                numProMostrar=auxNuevos->Proceso.numPrograma;
                tamanoMostrar=auxNuevos->Proceso.memProceso;
            }
        }
        if((bndEspacio == 1) && (auxNuevos != NULL))
        {
            bndEspacio=0;
            procesoNuevo=auxNuevos->Proceso;
            proceso.contTiempoEspera=0;
            procesoNuevo.bndBloqueado=0;
            procesoNuevo.tejecucion=0;
            procesoNuevo.bndNuevo=0;
            procesoNuevo.status=0;
            procesoNuevo.tLlegada=(relojGlobal-contProceso);
            procesoNuevo.tServicio=procesoNuevo.TME;
            procesoNuevo.tRespuesta=0;
            insertar(LISTOS,procesoNuevo);
            auxNuevos->Proceso.bndTerminado=1;
            auxNuevos=auxNuevos->sig;
            contMemoria++;
            nuevos--;
            gotoxy(3,3);printf("Nuevos: %d",nuevos); //Cantidad de Listos
            gotoxy(2,5);printf("Quantum: %d",quantum); //Valor del Quantum
        }
        else
        {
            if((auxNuevos == NULL) && (bndNuevos == 1))
            {
                cantMarcosDisp=marcosDisponibles(Marcos);
                if(auxCPN != NULL)
                {
                    memoria=auxCPN->Proceso.memProceso;
                    if((memoria) <= (cantMarcosDisp * 4))
                    {
                        bndEspacio=1;
                        numPag = calculaPaginas(auxCPN->Proceso.memProceso);
                        for(i=0; i< numPag; i++)
                        {
                            numMarco=recuperaPagDisp(Marcos);
                            auxCPN->Proceso.paginas[i].pagina=i;
                            auxCPN->Proceso.paginas[i].marco=numMarco;
                            Marcos[numMarco].marcoIdProceso=auxCPN->Proceso.numPrograma;
                            Marcos[numMarco].noMarco=numMarco;
                            Marcos[numMarco].numPagina=i;
                            if(memoria >= 4)
                            {
                                memoria -= 4;
                                Marcos[numMarco].tamPagina=4;
                                auxCPN->Proceso.paginas[i].capPagina=4;
                            }
                            else
                            {
                                Marcos[numMarco].tamPagina=memoria;
                                auxCPN->Proceso.paginas[i].capPagina=memoria;
                                memoria=0;
                            }
                            Marcos[numMarco].bndDisp=0;
                            auxCPN->Proceso.cantPaginas++;
                        }
                    }
                    else
                    {
                        numProMostrar=auxCPN->Proceso.numPrograma;
                        tamanoMostrar=auxCPN->Proceso.memProceso;
                    }
                }
            }
            if((bndEspacio == 1) && (auxNuevos == NULL) && (bndNuevos == 1))
            {
                while((auxCPN != NULL) && (bndEspacio == 1))
                {
                    bndEspacio=0;
                    procesoNuevo=auxCPN->Proceso;
                    contCPNAux++;
                    procesoNuevo.status=0;//nuevo
                    procesoNuevo.bndBloqueado=0;
                    procesoNuevo.contTiempoEspera=0;
                    procesoNuevo.bndNuevo=0;
                    procesoNuevo.tejecucion=0;
                    procesoNuevo.tLlegada=relojGlobal;
                    procesoNuevo.tRespuesta=0;
                    procesoNuevo.tServicio=procesoNuevo.TME;
                    insertar(LISTOS,procesoNuevo);
                    contMemoria++;
                    auxCPN=auxCPN->sig;
                    if(auxCPN == NULL)
                        bndAuxiliar=2;
                    nuevos--;

                    cantMarcosDisp=marcosDisponibles(Marcos);
                    if(auxCPN != NULL)
                    {
                        memoria=auxCPN->Proceso.memProceso;
                        if((memoria) <= (cantMarcosDisp * 4))
                        {
                            bndEspacio=1;
                            numPag = calculaPaginas(auxCPN->Proceso.memProceso);
                            for(i=0; i< numPag; i++)
                            {
                                numMarco=recuperaPagDisp(Marcos);
                                auxCPN->Proceso.paginas[i].pagina=i;
                                auxCPN->Proceso.paginas[i].marco=numMarco;
                                Marcos[numMarco].marcoIdProceso=auxCPN->Proceso.numPrograma;
                                Marcos[numMarco].noMarco=numMarco;
                                Marcos[numMarco].numPagina=i;
                                if(memoria >= 4)
                                {
                                    memoria -= 4;
                                    Marcos[numMarco].tamPagina=4;
                                    auxCPN->Proceso.paginas[i].capPagina=4;
                                }
                                else
                                {
                                    Marcos[numMarco].tamPagina=memoria;
                                    auxCPN->Proceso.paginas[i].capPagina=memoria;
                                    memoria=0;
                                }
                                Marcos[numMarco].bndDisp=0;
                                auxCPN->Proceso.cantPaginas++;
                            }
                        }
                        else
                        {
                            //Mostrar Proceso por entrar
                            numProMostrar=auxCPN->Proceso.numPrograma;
                            tamanoMostrar=auxCPN->Proceso.memProceso;
                        }
                    }
                    gotoxy(5,6);printf("Nuevos: %d",nuevos); //Cantidad de Listos
                }
            }
        }
        aux=aux->sig;
        auxProceso=1;
        numLotesPendientes--;
        contLote++;
        bndProcesoBloqueado=0;
        bndErrorProceso=0;
    }
    delay(400);

    //muestra Tabla BCP's
    system("cls");
    encabezado();
    gotobcp=mostrarTiemposProcesosTerminados(CPT);
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
    int contProceso=0;
    int cantidadProcesos=0;
    int numPrograma=1;
    int quantum=0;


    PROCESO proceso;
    COLAPROCESO NUEVOS;
    COLAPROCESO LISTOS;
    COLAPROCESO CPN;
    COLAPROCESOTERMINADO CPT;

    inicializar(&NUEVOS);
    inicializar(&LISTOS);
    inicializar(&CPN);
    inicializarProcesoTerminado(&CPT);

    NUEVOS.contProceso=1;

    system("cls");
    gotoxy(50,3);printf("----- PRACTICA NO.7 -----");
    gotoxy(14,6);printf("Cantidad de Procesos: ");
    scanf("%d",&cantidadProcesos);
    gotoxy(14,9);printf("Tamaño del Quantum: ");
    scanf("%d",&quantum);

    while(contProceso < cantidadProcesos)
    {
        system("cls");
        proceso=creaProceso(NUEVOS.contProceso);
        insertar(&NUEVOS,proceso);
        NUEVOS.contProceso++;
        contProceso++;
        numPrograma++;
    }
    Proceso(&NUEVOS,cantidadProcesos,&LISTOS,&CPN,&CPT,quantum);
    getch();
    return 0;
}
