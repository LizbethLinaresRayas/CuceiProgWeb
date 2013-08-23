/*Adriana Lizbeth Linares Rayas Lic. Informatica
Cod. 210596378 Secc. D-15*/
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#define Max 100

typedef enum{
    domingo,
    lunes,
    martes,
    miercoles,
    jueves,
    viernes,
    sabado
}Wday;

typedef enum{
    verdadero,
    falso
}booleano;



typedef struct{
    int dia;
    int mes;
    int year;
    Wday dia_sem;
    int hora;
    int min;
    int sec;
}Fecha;

typedef struct{
    unsigned int idVideo;
    char TituloPelicula[30];
    Fecha fecha;
    char Director[30];
    char ActorPrinc[30];
    int cantExistencia;
    float precioLista;
    float precioVenta;
    char fechaPublic[9];
}Pelicula;

typedef struct{
    unsigned id_video;
    int cantidad;
    float precioUni;
}detVideo;

typedef struct{
    int idVenta;
    unsigned int idVendedor;
    Fecha fechaVenta;
    char nomCliente[30];
    int totArticulos;
    float subtotal;
    float iva;
    float total;
    detVideo detalleVideo[20];
}Venta;

typedef struct{
    unsigned int idEmpleado;
    char nomEmpleado[30];
    char puesto[15];
    float sueldo;
    int hrsTrab;
    char password[15];
    char usuario[15];
}Empleado;

Fecha capturaFecha(){
    Fecha fecha;
    time_t segundos;
    struct tm *fecha_sistem;
    segundos = time(NULL);
    fecha_sistem = localtime(&segundos);
    system("Cls");
    fecha.dia = fecha_sistem->tm_mday;
    fecha.mes = ++ fecha_sistem->tm_mon;
    fecha.year = 1900 + fecha_sistem->tm_year;
    fecha.dia_sem = fecha_sistem->tm_wday;
    fecha.hora = fecha_sistem->tm_hour;
    fecha.min = fecha_sistem->tm_min;
    fecha.sec = fecha_sistem->tm_sec;
    return fecha;
}

int gotoxy(short x, short y)
{
   COORD coord;
   HANDLE h_stdout;

   coord.X = x;
   coord.Y = y;

   if ((h_stdout = GetStdHandle(STD_OUTPUT_HANDLE)) == INVALID_HANDLE_VALUE)
      return 0;

   if (SetConsoleCursorPosition(h_stdout, coord) == 0)
      return 0;

   return 1;
}

void CapturaVideo(Pelicula P[Max],int *cont){
    int x,cant,i;
    char nombre[30];

    if(*cont == 0)
        P[*cont].idVideo = rand()%999999;
    else
        P[*cont].idVideo = P[*(cont)-1].idVideo + 1;
    P[*cont].fecha=capturaFecha();
    printf("\nFecha: %d/%d/%d  Hora: %d:%d:%d",P[*cont].fecha.dia,P[*cont].fecha.mes,P[*cont].fecha.year,
         P[*cont].fecha.hora,P[*cont].fecha.min,P[*cont].fecha.sec);
    printf("\n\n\t\tID Video: %d",P[*cont].idVideo);
    printf("\n\n\t\tIngresa los Siguientes Datos:\n");
    printf("\n\n\t\tNombre de Pelicula: ");
    fflush(stdin);
    gets(P[*cont].TituloPelicula);
    strupr(P[*cont].TituloPelicula);
    printf("\n\n\t\tNombre Director: ");
    fflush(stdin);
    gets(P[*cont].Director);
    strupr(P[*cont].Director);
    printf("\n\n\t\tNombre Actor Principal: ");
    fflush(stdin);
    gets(P[*cont].ActorPrinc);
    strupr(P[*cont].ActorPrinc);
    printf("\n\n\t\tFecha Publicacion dd/mm/aa: ");
    scanf("%s",&P[*cont].fechaPublic);
    printf("\n\n\t\tCantidad en Existencia: ");
    scanf("%d",&P[*cont].cantExistencia);
    printf("\n\n\t\tPrecio Lista: ");
    scanf("%f",&P[*cont].precioLista);
    printf("\n\n\t\tPrecio al Publico: ");
    scanf("%f",&P[*cont].precioVenta);
    printf("\n\n\t-->Datos Capturados\n");
    (*cont)++;
    getch();
}

void MostrarVideo(Pelicula P[Max],int i){
    int fila=8;

    if(P[i].idVideo != 0){
        gotoxy(4,6);printf("ID");
        gotoxy(4,(fila+i));printf("%u",P[i].idVideo);
        gotoxy(13,5);printf("Titulo");
        gotoxy(12,6);printf("Pelicula");
        gotoxy(12,(fila+i));printf("%s",P[i].TituloPelicula);
        gotoxy(26,6);printf("Director");
        gotoxy(26,(fila+i));printf("%s",P[i].Director);
        gotoxy(42,5);printf("Actor");
        gotoxy(41,6);printf("Principal");
        gotoxy(41,(fila+i));printf("%s",P[i].ActorPrinc);
        gotoxy(53,6);printf("Exist.");
        gotoxy(54,(fila+i));printf("%d",P[i].cantExistencia);
        gotoxy(62,5);printf("Precio");
        gotoxy(62,6);printf("Lista");
        gotoxy(62,(fila+i));printf("%.2f",P[i].precioLista);
        gotoxy(71,5);printf("Precio");
        gotoxy(71,6);printf("Venta");
        gotoxy(71,(fila+i));printf("%.2f",P[i].precioVenta);
        gotoxy(79,5);printf("Fecha");
        gotoxy(79,6);printf("Public.");
        gotoxy(79,(fila+i));printf("%s\n",P[i].fechaPublic);
    }
}

void ConsulExistencia(Pelicula P[Max],int i,unsigned int id){

    if(id==P[i].idVideo){
        system("cls");
        gotoxy(5,6);printf("Nombre");
        gotoxy(5,8);printf("%s",P[i].TituloPelicula);
        gotoxy(18,6);printf("Cant. Existencia");
        gotoxy(19,8);printf("%d\n",P[i].cantExistencia);
    }
    else
        printf("\n\n\t-->Video No Encontrado\n");
    getch();
}

void modifVideo(Pelicula P[Max],int i,int cant){
    P[i].cantExistencia=cant;
    printf("\n\n\t-->Cambios Realizados\n");
}


int BuscarVideo(Pelicula P[Max],int *cont,char titulo[30]){
    int i,p;

    for(i=0;i < (*cont-1) ;i++){
        if(P[i].idVideo != 0){
            p=strcmpi(P[i].TituloPelicula,titulo);
            if(p == 0)
                return i;
            else
                return -1;
        }
    }
}

void passwd(char passwd[15],char usu[15]){
    int i,c;
    printf("\n\n\t\tNombre de Usuario: ");
    fflush(stdin);
    gets(usu);
    printf("\n\n\t\tContraseña: ");
    i=0;
    while((c=_getch())!=13){
        if(c==8){
            passwd[i]='\0';
            i--;
            printf("\b\b");
        }
        else
        {
            printf("*");
            passwd[i]=c;
            i++;
        }
    }
    passwd[i]='\0';
}

void CapturaEmpleado(Empleado E[Max],int *cont){
    int num;

    num=rand()%99999999;
    E[*cont].idEmpleado=num+123;
    printf("\n\n\t\tClave Empleado: %d",E[*cont].idEmpleado);
    printf("\n\n\t\tIngresa los Siguientes Datos:\n");
    printf("\n\n\t\tNombre: ");
    fflush(stdin);
    gets(E[*cont].nomEmpleado);
    strupr(E[*cont].nomEmpleado);
    printf("\n\n\t\tPuesto: ");
    fflush(stdin);
    gets(E[*cont].puesto);
    strupr(E[*cont].puesto);
    printf("\n\n\t\tSueldo: ");
    scanf("%f",&E[*cont].sueldo);
    printf("\n\n\t\tHoras Trabajadas a la Semana: ");
    scanf("%d",&E[*cont].hrsTrab);
    printf("\n\n\t\tContraseña: ");
    passwd(E[*cont].password,E[*cont].usuario);
    printf("\n\n\t-->Datos Guardados\n");
    (*cont)++;
    getch();
}

void mostrarEmp(Empleado E[Max],int i){
    int fila=8;

    gotoxy(6,5);printf("ID");
    gotoxy(4,6);printf("Empleado");
    gotoxy(5,(fila+i));printf("%d",E[i].idEmpleado);
    gotoxy(18,6);printf("Nombre");
    gotoxy(14,(fila+i));printf("%s",E[i].nomEmpleado);
    gotoxy(30,6);printf("Puesto");
    gotoxy(30,(fila+i));printf("%s",E[i].puesto);
    gotoxy(43,6);printf("Sueldo");
    gotoxy(43,(fila+i));printf("%.2f",E[i].sueldo);
    gotoxy(53,5);printf("Horas Trabajadas");
    gotoxy(54,6);printf("por Semana");
    gotoxy(56,(fila+i));printf("%d\n",E[i].hrsTrab);
}

int buscarEmpleado(Empleado E[Max],int cont,unsigned int id){
    int i;

    for(i=0;i<cont;i++)
        if(E[i].idEmpleado == id )
            return i;
    return -1;
}

int existeEmpleado(Empleado E[Max],int cont,unsigned int id){
    int i;

    for(i=0;i<cont;i++)
        if(E[i].idEmpleado == id)
            return i;
    return -1;
}

int existepssw(Empleado E[Max],int cont,char passwd[15],char usu[15],int id){
    int i,p,u;

    for(i=0;i<cont;i++){
        if(E[i].idEmpleado == id){
            p=strcmpi(E[i].password,passwd);
            u=strcmpi(E[i].usuario,usu);
            if((p == 0) && (u == 0))
                return i;
            else
                return -1;
        }
    }
}

int existePelicula(Pelicula P[Max],int cont,unsigned int id){
    int i;

    for(i=0;i<cont;i++)
        if(P[i].idVideo == id)
           return i;
    return -1;
}

void EliminarVideo(Pelicula P[Max],int *cont,int i,char titulo[30],char titulo1[30]){
    unsigned int id;
    int x,x1;
    char op;

    x=strcmp(P[i].TituloPelicula,titulo);
    x1=strcmp(P[i].Director,titulo1);
    if((x == 0) && (x1 == 0)){
        printf("\n\n\t\tDatos Correctos");
        system("cls");
        MostrarVideo(P,i);
        printf("\n\n\t\tIngresa el Id del Video a Eliminar: ");
        scanf("%u",&id);
        if(P[i].idVideo == id){
            if(P[i].cantExistencia<2){
                printf("\n\n\t-->Esta Seguro que Decea Eliminar este Video\n\n\tS. SI\n\n\tN. NO -> ");
                scanf("%s",&op);
                if((op == 's') || (op == 'S')){
                    P[i].idVideo=0;
                    printf("\n\n\t-->Video Eliminado\n");
                    (*cont)--;
                }
                else
                    printf("\n\n\t-->No se Realizo Ninguna Modificacion");
            }
            else
                printf("\n\n\t-->La Existencia Excede el limite\n");
        }
        else
            printf("\n\n\t-->No Existe\n");
    }
    else
        printf("\n\n\t-->No Existe\n");
    getch();
}

void inicializaVenta(Venta v[Max]){
    int i;

    for(i=0;i<Max;i++)
        v[i].subtotal = 0;
}

void mostrarVenta(Venta venta[Max],int cont,Empleado E[Max],int contEmp, Pelicula vid[Max],int contVideo){
    int fila,columna,i;
    fila=8; columna=10;

        gotoxy(28,1);printf(" N O T A   D E   V E N T A ");
        gotoxy(70,3);printf("No. 0000%d",venta[cont].idVenta);
        gotoxy(40,3);printf("\n\n\tFECHA: %d/%d/%d HORA: %d:%d:%d",venta[cont].fechaVenta.dia,venta[cont].fechaVenta.mes,venta[cont].fechaVenta.year,
             venta[cont].fechaVenta.hora,venta[cont].fechaVenta.min,venta[cont].fechaVenta.sec);
        gotoxy(2,4);puts(venta[cont].nomCliente);
        gotoxy(1,5);printf("ID_EMPLEADO: %u\tNOMBRE:  %s",venta[cont].idVendedor,E[buscarEmpleado(E,contEmp,venta[cont].idVendedor)].nomEmpleado);
        gotoxy(10,6);printf("**********     PRODUCTOS     **********");
        gotoxy(1,fila-1);printf("|");
        gotoxy(2,fila-1);printf("CLAVE");
        gotoxy(17,fila-1);printf("|");
        gotoxy(18,fila-1);printf("DESCRIPCION");
        gotoxy(44,fila-1);printf("|");
        gotoxy(45,fila-1);printf("CANTIDAD");
        gotoxy(59,fila-1);printf("|");
        gotoxy(60,fila-1);printf("PRECIO UNITARIO");
        gotoxy(78,fila-1);printf("|");
        for(i=0;i<venta[cont].totArticulos;i++){
            gotoxy(1,fila+i);printf("|");
            gotoxy(2,fila+i);printf("%u",venta[cont].detalleVideo[i].id_video);
            gotoxy(17,fila+i);printf("|");
            gotoxy(18,fila+i);puts(vid[existePelicula(vid,contVideo,venta[cont].detalleVideo[i].id_video)].TituloPelicula);
            gotoxy(44,fila+i);printf("|");
            gotoxy(45,fila+i);printf("%d",venta[cont].detalleVideo[i].cantidad);
            gotoxy(59,fila+i);printf("|");
            gotoxy(60,fila+i);printf("%.2f",venta[cont].detalleVideo[i].precioUni);
            gotoxy(78,fila+i);printf("|");
        }
        gotoxy(60,fila+i+2);printf("SUBTOTAL: %.2f",venta[cont].subtotal);
        gotoxy(60,fila+i+3);printf("IVA: %.2f",venta[cont].iva);
        gotoxy(60,fila+i+4);printf("TOTAL: %.2f\n",venta[cont].total);
}

void CapturaVenta(Venta venta[Max],int *cont,Empleado E[Max],int contEmp,Pelicula vid[Max],int contVideo){
    unsigned int id_emp,id_video;
    booleano bandd=falso, validar=falso;
    int x,x1,i=0,xr;
    int fila =8;
    static int y = 0;

    venta[*cont].totArticulos=0;
    venta[*cont].idVenta = ++y;
    venta[*cont].fechaVenta = capturaFecha();
    do{
        printf("\n\n\t\tId del empleado: ");
        scanf("%u",&id_emp);
        x1=existeEmpleado(E,contEmp,id_emp);
        if(x1 != -1){
            venta[*cont].idVendedor=id_emp;
            bandd=verdadero;
        }
        else{
            printf("\n\n\t-->El id del empleado no existe \n");
            xr++;
        }
    }while((bandd == falso) && (xr<4));
    bandd=verdadero;
    printf("\n\n\t\tNombre del cliente: ");
    fflush(stdin);
    gets(venta[*cont].nomCliente);
    strupr(venta[*cont].nomCliente);
    do{
        printf("\n\n\t\tId del video: ");
        scanf("%d",&id_video);
        x=existePelicula(vid,contVideo,id_video);
        if(x >= 0){
            venta[*cont].detalleVideo[i].id_video=id_video;
            do{
                printf("\n\n\t\tCantidad: ");
                scanf("%d",&venta[*cont].detalleVideo[i].cantidad);
                if(venta[*cont].detalleVideo[i].cantidad > vid[x].cantExistencia){
                    printf("-->La Cantidad de Venta sobre pasa las");
                    printf("EXISTENCIAS EN INVENTARIO: %d \n\t\tCapture nuevamente la Cantidad",vid[x].cantExistencia);
                    validar = verdadero;
                }
                else{
                    vid[x].cantExistencia -= venta[*cont].detalleVideo[i].cantidad;
                    venta[*cont].totArticulos ++;
                    validar = verdadero;
                }

            }while(validar);
            venta[*cont].detalleVideo[i].precioUni=vid[x].precioVenta;

            venta[*cont].subtotal+=venta[*cont].detalleVideo[i].precioUni * venta[*cont].detalleVideo[i].cantidad;
            venta[*cont].iva=venta[*cont].subtotal*0.16;
            venta[*cont].total=venta[*cont].subtotal+venta[*cont].iva;
            i++;
            printf("\n\n\t-->Agregar otro Video a la Venta? 1. SI 0. NO: -> ");
            scanf("%d",&bandd);

        }
        else
            printf("\n\n\t-->Esa pelicula no se encuentra en el inventario");
    }while(bandd);
    system("cls");
    mostrarVenta(venta,*cont,E,contEmp,vid,contVideo);
    (*cont) ++;
    getch();
}

BuscarVenta(Venta venta[Max],int cont,int d,int m,int a){
    int i,x;

    for(i=0;i<cont;i++)
        if((venta[i].fechaVenta.dia == d) && (venta[i].fechaVenta.mes == m) && (venta[i].fechaVenta.year == a))
            return i;
    return -1;
}

void corteCaja(Venta venta[Max],int cont,int d,int m,int a){
    int i;
    float tot=0;

    for(i=0;i<cont;i++){
        if(venta[i].idVenta != 0){
            if((venta[i].fechaVenta.dia == d) && (venta[i].fechaVenta.mes == m) && (venta[i].fechaVenta.year == a))
                tot+=venta[i].total;
        }
    }
    printf("\n\n\t\tTotal de Ventas: %.2f",tot);
}

void EliminarVenta(Pelicula P[Max],int *contVid,Venta venta[Max],int *cont,int id){
    int  i,cant,x,t;
    unsigned int idV;

    for(i=0;i<*cont;i++){
        if(venta[i].idVenta != 0){
            if(venta[i].idVenta == id){
                venta[i].idVenta=0;
                cant=venta[i].detalleVideo[i].cantidad;
                idV=venta[i].detalleVideo[i].id_video;
                x=existePelicula(P,cont,idV);
                if(x != -1)
                    P[i].cantExistencia+=cant;
                printf("\n\n\t-->Venta Eliminada");
            }
            else
                printf("\n\n\t-->La Venta No Existe");
        }
        else
            printf("\n\n\t-->La Venta No Existe");
    }
}


int main()
{
    system("COLOR f9");
    int opc,opVid,opcion,i,nvaCant,x,band=0,bandera=0,bandd=0,b=0;
    int contVideo,contVenta,contEmp,dd,mm,aa;
    char nombre[30],dir[30],psw[15],usu[15];
    unsigned int id;
    Pelicula Peli[Max];
    Venta Vent[Max];
    Empleado emp[Max];

    contVideo=0;
    contVenta=0;
    contEmp=0;

    do{
        system("cls");
        printf("\n\n\t\t<< MENU >>");
        printf("\n\n\t\t1. Ventas");
        printf("\n\n\t\t2. Pelicula");
        printf("\n\n\t\t3. Empleados");
        printf("\n\n\t\t4. Salir");
        printf("\n\n\t-->Elige una Opcion: ");
        scanf("%d",&opc);
        switch(opc){
            case 1:
                do{
                    system("cls");
                    printf("\n\n\t\tMENU VENTAS");
                    printf("\n\n\t\t1. Captura");
                    printf("\n\n\t\t2. Consulta Venta");
                    printf("\n\n\t\t3. Corte de caja");
                    printf("\n\n\t\t4. Eliminar Venta");
                    printf("\n\n\t\t5. Regresar");
                    printf("\n\n\t-->Elige una Opcion: ");
                    scanf("%d",&x);
                    switch(x){
                        case 1:
                            system("cls");
                            if((bandera == 1) && (b == 1)){
                                bandd=1;
                                printf("\n\n\t\t<< Captura de Venta >>");
                                CapturaVenta(Vent,&contVenta,emp,contEmp,Peli,contVideo);
                            }
                            else
                                printf("\n\n\t-->No existen Videos y empleados capturados");
                            getch();
                        break;
                        case 2:
                            system("cls");
                            if(bandd == 1){
                                printf("\n\n\t\t<< Consulta Venta >>");
                                printf("\n\n\t\tIngresa Fecha de la Venta a Consultar\n\n\t\tDia dd: ");
                                scanf("%d",&dd);
                                printf("\n\n\t\tMes mm: ");
                                scanf("%d",&mm);
                                printf("\n\n\t\tAño aaaa: ");
                                scanf("%d",&aa);
                                for(i=0;i<contVenta;i++){
                                    if(Vent[i].idVenta != 0){
                                        x=BuscarVenta(Vent,contVenta,dd,mm,aa);
                                        if(x != -1){
                                            system("cls");
                                            for(i=0;i<contVenta;i++)
                                                mostrarVenta(Vent,i,emp,contEmp,Peli,contVideo);
                                        }
                                        else
                                            printf("\n\n\t-->La Venta no Existe");
                                    }
                                    else
                                        printf("\n\n\t-->La Venta no Existe");
                                }
                            }
                            else
                                printf("\n\n\t-->No hay Ventas Capturadas");
                            getch();
                        break;
                        case 3:
                            system("cls");
                            if(bandd == 1){
                                printf("\n\n\t\t<< Corte de Caja por Dia >>");
                                printf("\n\n\t\tIngresa Fecha\n\n\t\tDia dd: ");
                                scanf("%d",&dd);
                                printf("\n\n\t\tMes mm: ");
                                scanf("%d",&mm);
                                printf("\n\n\t\tAño aaaa: ");
                                scanf("%d",&aa);
                                corteCaja(Vent,contVenta,dd,mm,aa);
                            }
                            else
                                printf("\n\n\t-->No hay Ventas Capturadas");
                            getch();
                        break;
                        case 4:
                            system("cls");
                            if(bandd == 1){
                                printf("\n\n\t\t<< Elimar Venta >>");
                                printf("\n\n\t\tIngresa el Id del Empleado: ");
                                scanf("%d",&id);
                                passwd(psw,usu);
                                x=existepssw(emp,contEmp,psw,usu,id);
                                if(x != -1){
                                    system("cls");
                                    printf("\n\n\t\tIngresa el Id de la Venta a Eliminar: ");
                                    scanf("%d",&id);
                                    EliminarVenta(Peli,&contVideo,Vent,&contVenta,id);
                                }
                                else
                                    printf("\n\n\t-->Incorrecto");
                            }
                            else
                                printf("\n\n\t-->No hay Ventas Capturadas");
                            getch();
                        break;
                        case 5:
                            printf("\n\n\t-->Regresar Menu Principal");
                        break;
                        default:
                            printf("\n\n\t-->Opcion Incorrecta");
                    }
                }while(x!=5);
                getch();
            break;
            case 2:
                do{
                    system("cls");
                    printf("\n\n\t\t << MENU VIDEO >>");
                    printf("\n\n\t\t1. Captura");
                    printf("\n\n\t\t2. Consulta Existencias");
                    printf("\n\n\t\t3. Busqueda");
                    printf("\n\n\t\t4. Eliminar");
                    printf("\n\n\t\t5. Inventario");
                    printf("\n\n\t\t6. Regresar");
                    printf("\n\n\t-->Elige una Opcion: ");
                    scanf("%d",&opVid);
                    switch(opVid){
                        case 1:
                            do{
                                band=1;
                                system("cls");
                                printf("\n\n\t\t<< Captura de Video >>");
                                printf("\n\n\t\t1. Nuevo");
                                printf("\n\n\t\t2. Existente");
                                printf("\n\n\t\t3. Regresar");
                                printf("\n\n\t-->Elige una Opcion: ");
                                scanf("%d",&opcion);
                                switch(opcion){
                                    case 1:
                                        bandera=1;
                                        system("cls");
                                        printf("\n\n\t\t<< Captura Nuevo Video >>");
                                        CapturaVideo(Peli,&contVideo);

                                    break;
                                    case 2:
                                        system("cls");
                                        if(bandera==1){
                                            printf("\n\n\t\t<< Modificar Video >>");
                                            printf("\n\n\t\tIngresa el nombre de la Pelicula: ");
                                            fflush(stdin);
                                            gets(nombre);
                                            strupr(nombre);
                                            for(i=0;i<contVideo;i++){
                                                x=BuscarVideo(Peli,&contVideo,nombre);
                                                if(x != -1){
                                                    printf("\n\n\t\tIngresa la Nueva Cantidad: ");
                                                    scanf("%d",&nvaCant);
                                                    modifVideo(Peli,i,nvaCant);
                                                    system("cls");
                                                    MostrarVideo(Peli,i);
                                                }
                                                else
                                                    printf("Datos Incorrectos");
                                            }
                                        }
                                        else
                                            printf("\n\n\t-->No hay Videos Capturados");
                                        getch();
                                    break;
                                    case 3:
                                        printf("\n\n\t-->Regresar Menu Video");
                                    break;
                                    default:
                                        printf("\n\n\t-->Opcion Incorrecta");
                                }
                            }while(opcion!=3);
                        break;
                        case 2:
                            system("cls");
                            if(band==1){
                                printf("\n\n\t\t<< Consulta de Existencias >>");
                                printf("\n\n\tIngresa ID del Video: ");
                                scanf("%u",&id);
                                for(i=0;i<contVideo;i++)
                                    ConsulExistencia(Peli,i,id);
                            }
                            else
                                printf("\n\n\t-->No hay Datos Capturados");
                            getch();
                        break;
                        case 3:
                            system("cls");
                            if(band==1){
                                printf("\n\n\t\t<< Busqueda Video >>");
                                printf("\n\n\t\tIngresa el Titulo de la Pelicula: ");
                                fflush(stdin);
                                gets(nombre);
                                strupr(nombre);
                                for(i=0;i<contVideo;i++){
                                    x=BuscarVideo(Peli,&contVideo,nombre);
                                    if(x != -1){
                                        MostrarVideo(Peli,i);
                                    }
                                    else
                                        printf("\n\n\t-->El video No Existe");
                                }
                            }
                            else
                                printf("\n\n\t-->No hay Datos Capturados");
                            getch();
                        break;
                        case 4:
                            system("cls");
                            if(band==1){
                                printf("\n\n\t\t<< Eliminar Video >>");
                                printf("\n\n\t\tIngresa el Titulo de la Pelicula: ");
                                fflush(stdin);
                                gets(nombre);
                                strupr(nombre);
                                printf("\n\n\t\tIngresa Nombre del Director: ");
                                fflush(stdin);
                                gets(dir);
                                strupr(dir);
                                for(i=0;i<contVideo;i++){
                                    EliminarVideo(Peli,&contVideo,i,nombre,dir);
                                }
                            }
                            else
                                printf("\n\n\t-->No hay Datos Capturados");
                            getch();
                        break;
                        case 5:
                            system("cls");
                            if(band==1){
                                printf("\n\n\t\t\t\tInventario");
                                for(i=0;i<contVideo;i++)
                                        MostrarVideo(Peli,i);
                            }
                            else
                                printf("\n\n\t-->No hay Datos Capturados");
                            getch();
                        break;
                        case 6:
                            printf("\n\n\t-->Regresar Menu Principal");
                            getch();
                        break;
                        default:
                            printf("\n\n\t-->Opcion Incorrecta");
                    }
                }while(opVid!=6);
            break;
            case 3:
                do{
                    system("cls");
                    printf("\n\n\t\t<< MENU EMPLEADOS >>");
                    printf("\n\n\t\t1. Captura de Empleados");
                    printf("\n\n\t\t2. Mostrar");
                    printf("\n\n\t\t3. Regresar");
                    printf("\n\n\t-->Elige una Opcion: ");
                    scanf("%d",&x);
                    switch(x){
                        case 1:
                            b=1;
                            system("cls");
                            printf("\n\n\t\t<< Captura Empleado >>");
                            CapturaEmpleado(emp,&contEmp);
                        break;
                        case 2:
                            system("cls");
                            if(b == 1){
                                printf("\n\n\t\t<< Mostrar Empleado >>");
                                for(i=0;i<contEmp;i++)
                                    mostrarEmp(emp,i);
                            }
                            else
                                printf("\n\n\t-->No hay Empleados Capturados");
                            getch();
                        break;
                        case 3:
                            printf("\n\n-->Regresar Menu Empleado");
                        break;
                        default:
                            printf("\n\n\t-->Opcion Incorrecta");
                    }
                }while(x!=3);
                getch();
            break;
            case 4:
                system("cls");
                printf("\n\n\t\tGracias por tu Visita");
            break;
            default:
                printf("\n\n\t-->Opcion Incorrecta");
        }
    }while(opc!=4);
    getch();
}
