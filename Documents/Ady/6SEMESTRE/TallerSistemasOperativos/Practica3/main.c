#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct{
    char operacion[15];
    int resultado;
    int TME;
    int numPrograma;
    int TiempoRest;
    int status;
    int bndBloqueado;
    int tEspera;
    int contTiempoEspera;
    int tLlegada;
    int tRespuesta;
    int tServicio;
    int bndNuevo;
    int tejecucion;
}PROCESO;

typedef struct{
    int numProg;
    char nomProg[20];
    char operacion[10];
    int resultado;
    int bnd;
    int TME;
    int TiempoRest;
    int auxTiempo;
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

void inicializarTiempos(COLATIEMPOS *T)
{
    NodoTiempos *aux;
    aux = (NodoTiempos*)malloc(sizeof(NodoTiempos));
    aux->sig=NULL;
    T->final=aux;
    T->frente=aux;
}

int vacia(COLAPROCESO *C)
{
    return (C->frente == C->final);
}

int vaciaProcesoTerminado(COLAPROCESOTERMINADO *CPT)
{
    return (CPT->frente == CPT->final);
}

int vaciaTiempos(COLATIEMPOS *T)
{
    return (T->frente == T->final);
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

void insertaTiempos(COLATIEMPOS *CT,TIEMPOS tiempos)
{
    NodoTiempos *aux;
    aux=(NodoTiempos*)malloc(sizeof(NodoTiempos));
    aux->Tiempos=tiempos;
    aux->sig=NULL;
    CT->final->sig=aux;
    CT->final=aux;
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
            gotoxy(102,13+auxgoto);printf("Num. Programa: %d ",aux->ProcesoTerminado.numProg);
            gotoxy(106,15+auxgoto);printf("Operacion: %s",aux->ProcesoTerminado.operacion);
            if(aux->ProcesoTerminado.resultado == 0)
            {
                gotoxy(106,17+auxgoto);printf("Resultado: Error Ejecucion");
            }
            else
            {
                gotoxy(106,17+auxgoto);printf("Resultado: %d",aux->ProcesoTerminado.resultado);
            }
            aux=aux->sig;
            auxgoto+=8;
         }
    }
}

void mostrarTiempos(COLATIEMPOS *CT)
{
    int auxgoto=0;

    gotoxy(10,7);printf("No. Programa");
    gotoxy(25,7);printf("T.Llegada");
    gotoxy(39,7);printf("T.Finalizacion");
    gotoxy(56,7);printf("T.Servicio");
    gotoxy(71,7);printf("T.Espera");
    gotoxy(86,7);printf("T.Retorno");
    gotoxy(101,7);printf("T.Respuesta");
    gotoxy(115,7);printf("Terminado");

    if(!vaciaTiempos(CT))
    {
        NodoTiempos *aux;
        aux=CT->frente->sig;
        while(aux != NULL)
        {
            gotoxy(14,10+auxgoto);printf("%d",aux->Tiempos.numPrograma);
            gotoxy(28,10+auxgoto);printf("%d",aux->Tiempos.tLlegada);
            gotoxy(43,10+auxgoto);printf("%d",aux->Tiempos.tFinalizacion);
            gotoxy(59,10+auxgoto);printf("%d",aux->Tiempos.tServicio);
            gotoxy(73,10+auxgoto);printf("%d",aux->Tiempos.tEspera);
            gotoxy(89,10+auxgoto);printf("%d",aux->Tiempos.tRetorno);
            gotoxy(105,10+auxgoto);printf("%d",aux->Tiempos.tRespuesta);
            if(aux->Tiempos.bndtermino == 1)
            {
                gotoxy(117,10+auxgoto);printf("Correcto");
            }
            else
            {
                gotoxy(117,10+auxgoto);printf("Error");
            }
            aux=aux->sig;
            auxgoto+=2;
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

PROCESO RecuperaNuevo(COLAPROCESO *NUEVOS,NodoProceso *auxNuevos)
{
    NodoProceso *auxiliar;
    PROCESO proceso;

    auxiliar=auxNuevos;
    proceso=auxiliar->Proceso;
    proceso.status=0;//nuevo
    return proceso;
}

void Proceso(COLAPROCESO *NUEVOS,int cantProceso,COLAPROCESO *LISTOS)
{
    int relojGlobal=0;
    int contAux=0;
    int contMemoria=0;
    int contProceso=0;
    int axgoto=0;
    int axxgoto=0;
    int auxiliar=0;
    int ax=0;
    int i=0;
    int j=0;
    int k=0;
    int m=0;
    int contOperador=0;

    PROCESO proceso;
    char operacion[10];
    char operando1[5];
    char operando2[5];
    char operador1;
    char caracter;
    int contLote=0;
    int numLotesPendientes=0;
    int auxProceso=1;
    int num=0;
    int num1=0;
    char carac;
    int resultado=0;
    int auxgoto=0;
    int aux_goto=0;
    int bndAuxProceso=0;
    int bndErrorProceso=0;
    int contProcesosEjec=0;
    int bndEncendido=0;
    int bndProcesoBloqueado=0;
    int nuevos=0;

    PROCESO procesoNuevo;
    TIEMPOS tiempos;
    PROCESOTERMINADO procesoTerminado;

    COLAPROCESOTERMINADO CPT;
    COLATIEMPOS TIEMPOS;

    NodoProceso *auxNuevos;
    NodoProceso *auxListos;
    NodoProceso *aux;
    NodoProceso *auxiliarI;

    inicializarProcesoTerminado(&CPT);
    inicializarTiempos(&TIEMPOS);

    NUEVOS->contProceso=cantProceso;

    nuevos=cantProceso;
    //Cola Nuevos a Cola Listos
    auxNuevos=NUEVOS->frente->sig;
    while((auxNuevos != NULL) && (contMemoria < 4))
    {
        procesoNuevo=auxNuevos->Proceso;
        procesoNuevo.status=0;//nuevo
        procesoNuevo.bndBloqueado=0;
        procesoNuevo.contTiempoEspera=0;
        procesoNuevo.bndNuevo=0;
        procesoNuevo.tejecucion=0;
        procesoNuevo.tLlegada=relojGlobal;
        procesoNuevo.tRespuesta=relojGlobal;
        procesoNuevo.tServicio=procesoNuevo.TME;
        insertar(LISTOS,procesoNuevo);
        contMemoria++;
        auxNuevos=auxNuevos->sig;
        nuevos--;
    }

    //Cola Nuevos
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
        gotoxy(50,3);printf("----- PRACTICA NO.3 -----");
        gotoxy(5,6);printf("Nuevos: %d",nuevos); //Cantidad de Listos
        gotoxy(10,10);printf("Listos");
        gotoxy(37,10);printf("Bloqueados");
        if(nuevos < 0)
            nuevos=0;
        auxListos=aux->sig;
        auxgoto=0;
        aux_goto=0;
        while(auxListos != NULL)
        {
            if(auxListos->Proceso.status == 0)
            {
                gotoxy( 4,13+auxgoto); printf("Num. Programa: %d",auxListos->Proceso.numPrograma);
                gotoxy(14,15+auxgoto);printf("TME: %d",auxListos->Proceso.TME);
                gotoxy( 2,17+auxgoto);printf("Tiempo Restante: %d",auxListos->Proceso.TiempoRest);
                auxgoto+=8;
                auxListos=auxListos->sig;
            }
            else
            {
                if(auxListos->Proceso.status == 1)
                {
                    gotoxy(34,13+aux_goto);printf("Num. Programa: %d",auxListos->Proceso.numPrograma);
                    gotoxy(44,15+aux_goto);printf("TTB: %d",auxListos->Proceso.contTiempoEspera);
                    aux_goto+=6;
                    auxListos=auxListos->sig;
                }
            }
        }

        //procesos terminados
        if((procesoTerminado.bnd == 1) && (bndAuxProceso == 0))
        {
            gotoxy(99,14);printf("                                 ");
            gotoxy(103,10);printf("Procesos Terminados");
            insertaProcesoTerminado(&CPT,procesoTerminado);
            mostrarProcesoTerminado(&CPT,contLote);
            contProcesosEjec++;
            bndAuxProceso=1;
        }
        else
        {
            if((bndProcesoBloqueado == 1) || (bndAuxProceso == 1))
            {
                gotoxy(99,14);printf("                                 ");
                gotoxy(103,10);printf("Procesos Terminados");
                mostrarProcesoTerminado(&CPT,contLote);
            }
            else
            {
                gotoxy(103,10);printf("Procesos Terminados");
                gotoxy(98,14);printf("No hay Procesos Terminados.");
            }
        }

        //Procesos en ejecucion
        proceso=aux->Proceso;
        if(proceso.bndNuevo == 0)
        {
            proceso.tRespuesta=(relojGlobal-contProceso) - proceso.tLlegada;
            proceso.bndNuevo=1;
        }
        gotoxy(67,10);printf("Proceso en Ejecucion");
        gotoxy(67,13);printf("Num. Programa: %d",proceso.numPrograma);
        gotoxy(71,15);printf("Operacion: %s",proceso.operacion);
        gotoxy(77,17);printf("TME: %d",proceso.TME);
        gotoxy(65,19);printf("Tiempo Restante: %d",proceso.TiempoRest);
        gotoxy(77,21);printf("TTE: ");
        gotoxy(77,23);printf("TRE: ");
        gotoxy(70,34);printf("Reloj Global: %d",relojGlobal);

        if(proceso.bndBloqueado == 0)
        {
            m=proceso.TME;
            k=0;
            auxiliar=proceso.TME;
        }
        else
        {
            if(proceso.bndBloqueado == 1)
            {
                m=proceso.TiempoRest;
                if(m < 0)//modificar
                    m=0;
                k=0;
                auxiliar=proceso.TME-proceso.tejecucion;
            }
        }
        while((k <= auxiliar) && (bndErrorProceso == 0) && (bndProcesoBloqueado == 0))
        {
            if(kbhit())
                caracter=getch();
            delay(200);
            gotoxy(77,21);printf("TTE:    ");
            gotoxy(77,23);printf("TRE:    ");
            gotoxy(77,21);printf("TTE: %d",k);
            gotoxy(77,23);printf("TRE: %d",m);
            if(caracter == 'W')
            {
                gotoxy(67,27);printf("Se ha producido un error");
                delay(150);
                bndErrorProceso=1;
            }
            else
            {
                if(caracter == 'P')
                {
                    while(carac != 'C')
                    {
                        gotoxy(67,27);printf("Pausa...Presiona la Tecla 'C' para Continuar");
                        kbhit();
                        carac=getch();
                    }
                    if(carac == 'C')
                    {
                        gotoxy(67,27);printf("                                              ");
                        gotoxy(67,27);printf(".......Listo para continuar.......");
                        delay(200);
                        gotoxy(67,27);printf("                                  ");
                    }
                    gotoxy(67,34);printf("                                 ");
                }
                else
                {
                    if(caracter == 'I')
                    {
                        gotoxy(65,27);printf("El proceso ha sido Interrumpido");
                        delay(100);
                        proceso.status=1;//bloqueado
                        proceso.bndBloqueado=1;
                        proceso.contTiempoEspera=0;
                        insertar(LISTOS,proceso);
                        bndProcesoBloqueado=1;
                    }
                    else
                        gotoxy(67,27);printf("                           ");
                }
                m--;
                k++;
                proceso.tejecucion++;
                relojGlobal++;
                gotoxy(70,34);printf("Reloj Global: %d",relojGlobal);
                axgoto=0;
                axxgoto=0;
                gotoxy(34,13);printf("                      ");
                gotoxy(44,15);printf("                    ");
                gotoxy(34,13+6);printf("                      ");
                gotoxy(44,15+6);printf("                    ");
                gotoxy(34,13+12);printf("                      ");
                gotoxy(44,15+12);printf("                    ");
                gotoxy(34,13+18);printf("                      ");
                gotoxy(44,15+18);printf("                    ");

                auxiliarI=aux->sig;
                while(auxiliarI != NULL)
                {
                    if(auxiliarI->Proceso.status == 0)
                    {
                        gotoxy( 4,13+axxgoto); printf("Num. Programa: %d",auxiliarI->Proceso.numPrograma);
                        gotoxy(14,15+axxgoto);printf("TME: %d",auxiliarI->Proceso.TME);
                        gotoxy( 2,17+axxgoto);printf("Tiempo Restante: %d",auxiliarI->Proceso.TiempoRest);
                        axxgoto+=8;
                    }
                    if(auxiliarI->Proceso.status == 1)
                    {
                        auxiliarI->Proceso.contTiempoEspera++;
                        gotoxy(34,13+axgoto);printf("Num. Programa: %d",auxiliarI->Proceso.numPrograma);
                        gotoxy(44,15+axgoto);printf("TTB: %d",auxiliarI->Proceso.contTiempoEspera);
                        axgoto+=6;
                        if(auxiliarI->Proceso.contTiempoEspera >= 6)
                        {
                            auxiliarI->Proceso.status=0;
                            auxiliarI->Proceso.contTiempoEspera=0;
                            auxiliarI->Proceso.TiempoRest=auxiliarI->Proceso.TME-auxiliarI->Proceso.tejecucion;
                        }
                    }
                    auxiliarI=auxiliarI->sig;
                }
            }
        }

        //Si se interrumpe el último proceso
        if(((contProceso+1) == cantProceso) && (bndProcesoBloqueado == 1))
        {
            system("cls");
            gotoxy(50,3);printf("----- PRACTICA NO.3 -----");
            gotoxy(5,6);printf("Nuevos: %d",nuevos); //Cantidad de Listos
            gotoxy(10,10);printf("Listos");
            gotoxy(37,10);printf("Bloqueados");
            gotoxy(103,10);printf("Procesos Terminados");
            auxgoto=0;
            aux_goto=0;
            if(nuevos < 0)
                nuevos=0;
            gotoxy(67,10);printf("Proceso en Ejecucion");
            gotoxy(67,13);printf("Num. Programa:     ");
            gotoxy(71,15);printf("Operacion:            ");
            gotoxy(77,17);printf("TME:              ");
            gotoxy(65,19);printf("Tiempo restante:             ");
            gotoxy(77,21);printf("TTE:         ");
            gotoxy(77,23);printf("TRE:       ");
            gotoxy(69,27);printf("                                                                    ");
            gotoxy(69,27);printf("...En Espera de Proceso...");
            mostrarProcesoTerminado(&CPT,contLote);
            ax=0;
            while(ax != 2)
            {
                if(ax == 1)
                {
                    ax=2;
                    gotoxy(34,13);printf("                      ");
                    gotoxy(44,15);printf("                    ");
                }
                proceso.tejecucion++;
                relojGlobal++;
                gotoxy(70,34);printf("Reloj Global: %d",relojGlobal);

                gotoxy(44,15);printf("                    ");
                axgoto=0;
                axxgoto=0;
                auxiliarI=aux->sig;
                while(auxiliarI != NULL)
                {
                    if(auxiliarI->Proceso.status == 0)
                    {
                        gotoxy( 4,13+axxgoto); printf("Num. Programa: %d",auxiliarI->Proceso.numPrograma);
                        gotoxy(14,15+axxgoto);printf("TME: %d",auxiliarI->Proceso.TME);
                        gotoxy( 2,17+axxgoto);printf("Tiempo Restante: %d",auxiliarI->Proceso.TiempoRest);
                        delay(200);
                        axxgoto+=8;
                    }
                    if(auxiliarI->Proceso.status == 1)
                    {
                        auxiliarI->Proceso.contTiempoEspera++;
                        gotoxy(34,13+axgoto);printf("Num. Programa: %d",auxiliarI->Proceso.numPrograma);
                        gotoxy(44,15+axgoto);printf("TTB: %d",auxiliarI->Proceso.contTiempoEspera);
                        delay(200);
                        axgoto+=6;

                        if(auxiliarI->Proceso.contTiempoEspera >= 6)
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
        if((bndErrorProceso == 0) && (bndProcesoBloqueado == 0))
        {
            gotoxy(70,27);printf("......Terminado......");
            delay(200);
            procesoTerminado.numProg=proceso.numPrograma;
            tiempos.tLlegada=proceso.tLlegada;//calcula tiempos
            tiempos.tRespuesta=proceso.tRespuesta;//calcula tiempos
            tiempos.bndtermino=1; //Termino correctamente
            strcpy(procesoTerminado.operacion,proceso.operacion);
            if(bndEncendido == 0)
                procesoTerminado.resultado=resultado;
            else
                procesoTerminado.resultado=proceso.resultado;
            procesoTerminado.bnd=1;
            bndAuxProceso=0;
            contProceso++;
            contMemoria--;
            nuevos--;

            //calcula tiempos
            tiempos.numPrograma=procesoTerminado.numProg;
            tiempos.tFinalizacion=relojGlobal-contProceso;
            tiempos.tRetorno=tiempos.tFinalizacion-tiempos.tLlegada;
            tiempos.tServicio=proceso.tServicio;//calcula tiempos
            tiempos.tEspera=tiempos.tRetorno-tiempos.tServicio;
            insertaTiempos(&TIEMPOS,tiempos);
        }
        else
        {
            if(bndErrorProceso == 1)
            {
                gotoxy(77,21);printf("TTE: %d",k);
                gotoxy(77,23);printf("TRE: %d",m);
                gotoxy(67,27);printf("......Terminado......    ");
                delay(200);
                procesoTerminado.numProg=proceso.numPrograma;
                procesoTerminado.auxTiempo=proceso.tejecucion;
                tiempos.tLlegada=proceso.tLlegada;//calcula tiempos
                tiempos.tRespuesta=proceso.tRespuesta;//calcula tiempos
                tiempos.tServicio=proceso.tejecucion;
                tiempos.bndtermino=0; //Termino con error
                strcpy(procesoTerminado.operacion,proceso.operacion);
                procesoTerminado.resultado=0;
                procesoTerminado.bnd=1;
                bndAuxProceso=0;
                contProceso++;
                contMemoria--;
                nuevos--;
                //calcula tiempos
                tiempos.numPrograma=procesoTerminado.numProg;
                tiempos.tFinalizacion=relojGlobal-contProceso;
                tiempos.tRetorno=tiempos.tFinalizacion-tiempos.tLlegada;
                tiempos.tEspera=tiempos.tRetorno-procesoTerminado.auxTiempo;
                insertaTiempos(&TIEMPOS,tiempos);
            }
        }

        //último proceso
        if(contProceso == cantProceso)
        {
            gotoxy(97,14);printf("                                 ");
            gotoxy(103,10);printf("Procesos Terminados");
            insertaProcesoTerminado(&CPT,procesoTerminado);
            mostrarProcesoTerminado(&CPT,contLote);
            contProcesosEjec++;
            bndAuxProceso=1;
            gotoxy(67,10);printf("Proceso en Ejecucion");
            gotoxy(67,13);printf("Num. Programa:     ");
            gotoxy(71,15);printf("Operacion:            ");
            gotoxy(77,17);printf("TME:              ");
            gotoxy(65,19);printf("Tiempo restante:             ");
            gotoxy(77,21);printf("TTE:         ");
            gotoxy(77,23);printf("TRE:       ");
            gotoxy(69,27);printf("                                                                    ");
            gotoxy(69,27);printf("No Hay proceso en Ejecucion.");
        }
        //Si hay espacio en memoria
        if((contMemoria < 4) && (auxNuevos != NULL))
        {
            procesoNuevo=RecuperaNuevo(NUEVOS,auxNuevos);
            proceso.contTiempoEspera=0;
            procesoNuevo.bndBloqueado=0;
            procesoNuevo.tejecucion=0;
            procesoNuevo.bndNuevo=0;
            procesoNuevo.status=0;
            procesoNuevo.tLlegada=(relojGlobal-contProceso);
            procesoNuevo.tServicio=procesoNuevo.TME;
            procesoNuevo.tRespuesta=relojGlobal;
            insertar(LISTOS,procesoNuevo);
            auxNuevos=auxNuevos->sig;
            contMemoria++;
        }
        aux=aux->sig;
        auxProceso=1;
        numLotesPendientes--;
        contLote++;
        bndProcesoBloqueado=0;
        bndErrorProceso=0;
    }
    delay(400);
    system("cls");
    gotoxy(50,3);printf("----- PRACTICA NO.3 -----");
    mostrarTiempos(&TIEMPOS);

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
    COLAPROCESO NUEVOS;
    COLAPROCESO LISTOS;

    inicializar(&NUEVOS);
    inicializar(&LISTOS);

    system("cls");
    gotoxy(50,3);printf("----- PRACTICA NO.3 -----");
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
        proceso.TME=1+rand()%30;
        proceso.TiempoRest=proceso.TME;
        insertar(&NUEVOS,proceso);
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
    Proceso(&NUEVOS,cantProceso,&LISTOS);
    getch();
    return 0;
}
