#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#define Max 100
#define x 15

typedef struct{
        char Nombre[15];
        char ApellidoP[15];
        char ApellidoM[15];
        unsigned long telefono[4];
        char CURP[17];
    }personal;

    typedef struct{
        char calle[10];
        int num;
        char col[10];
        char cd[10];
        unsigned int cp;
    }dom;

    typedef struct{
        char dep[10];
        char area[10];
        char puesto[10];
        int contrato;
        float sueldohr;
    }laboral;

    typedef struct{
        int dia;
        int mes;
        int ano;
    }ingreso;

    typedef struct{
        personal Nom;
        dom Domicilio;
        laboral Lab;
        ingreso Ingreso;
        unsigned int IdEmpleado;
    }Emp;

void Captura(Emp Empleado[],int num){
    int i,j,n=3,op;
    for(i=1;i<=num;i++){
        printf("\n\t-->Empleado No.%d",i);
        printf("\n\n\t\t<< Datos Empleado>>\n");
        printf("\n\n\t\tId Empleado: %u",Empleado[i].IdEmpleado);
        printf("\n\n\t\tApellido Paterno: ");
        scanf("%s",&Empleado[i].Nom.ApellidoP);
        strupr(Empleado[i].Nom.ApellidoP);
        printf("\n\n\t\tApellido Materno: ");
        scanf("%s",&Empleado[i].Nom.ApellidoM);
        strupr(Empleado[i].Nom.ApellidoM);
        printf("\n\n\t\tNombre: ");
        scanf("%s",&Empleado[i].Nom.Nombre);
        strupr(Empleado[i].Nom.Nombre);
        printf("\n\n\t\tCURP: ");
        scanf("%s",&Empleado[i].Nom.CURP);
        strupr(Empleado[i].Nom.CURP);
        for(j=1;j<=n;j++){
            if(j==1){
                printf("\n\n\t\tTelefono de Emergencia: ");
                scanf("%u",&Empleado[i].Nom.telefono[j]);
            }
            else{
                if(j==2){
                    printf("\n\n\t\tCelular: ");
                    scanf("%u",&Empleado[i].Nom.telefono[j]);
                }
                else{
                    if(j==3){
                        printf("\n\n\t\tTelefono fijo: ");
                        scanf("%u",&Empleado[i].Nom.telefono[j]);
                    }
                }
            }
        }
        printf("\n\n\t\t->Domicilio: ");
        printf("\n\n\t\tCalle: ");
        scanf("%s",&Empleado[i].Domicilio.calle);
        strupr(Empleado[i].Domicilio.calle);
        printf("\n\n\t\tNumero: ");
        scanf("%d",&Empleado[i].Domicilio.num);
        printf("\n\n\t\tColonia: ");
        scanf("%s",&Empleado[i].Domicilio.col);
        strupr(Empleado[i].Domicilio.col);
        printf("\n\n\t\tCiudad: ");
        scanf("%s",&Empleado[i].Domicilio.cd);
        strupr(Empleado[i].Domicilio.cd);
        printf("\n\n\t\tCodigo Postal: ");
        scanf("%d",&Empleado[i].Domicilio.cp);
        printf("\n\n\t\t->Datos Laborales: ");
        printf("\n\n\t\tDepartamento: ");
        scanf("%s",&Empleado[i].Lab.dep);
        strupr(Empleado[i].Lab.dep);
        printf("\n\n\t\tArea: ");
        scanf("%s",&Empleado[i].Lab.area);
        strupr(Empleado[i].Lab.area);
        printf("\n\n\t\tPuesto: ");
        scanf("%s",&Empleado[i].Lab.puesto);
        strupr(Empleado[i].Lab.puesto);
        do{
            printf("\n\n\t\t->Tipo de Contrato: \n");
            printf("\n\n\t\t1. Tiempo completo\n\n\t\t2. Medio Tiempo");
            printf("\n\n\t\t-->Elige una Opcion: ");
            scanf("%d",&op);
            switch(op){
                case 1:
                    Empleado[i].Lab.contrato=8;
                break;
                case 2:
                    Empleado[i].Lab.contrato=4;
                break;
                default:
                    printf("\n\n\t-->Opcion Inocrrecta");
            }
        }while(op!=1 && op!=2);
        printf("\n\n\t\tSueldo por Hora: ");
        scanf("%f",&Empleado[i].Lab.sueldohr);
        printf("\n\n\t\t->Fecha de ingreso: ");
        printf("\n\n\t\tDia dd: ");
        scanf("%d",&Empleado[i].Ingreso.dia);
        printf("\n\n\t\tMes mm: ");
        scanf("%d",&Empleado[i].Ingreso.mes);
        printf("\n\n\t\tAno aaaa: ");
        scanf("%d",&Empleado[i].Ingreso.ano);
        printf("\n\t-->Datos Capturados\n\n");
    }
}

void Eliminar(Emp Empleado[],int num){
    int i,a,n;
    char nombre[15],apellido[15];
    printf("\n\n\t-->Ingresa:");
    printf("\n\n\t\tApellido Paterno: ");
    scanf("%s",&apellido);
    strupr(apellido);
    printf("\n\n\t\tNombre: ");
    scanf("%s",&nombre);
    strupr(nombre);
    for(i=1;i<=num;i++){
        if(Empleado[i].IdEmpleado!=0){
            a=strcmpi(apellido,Empleado[i].Nom.ApellidoP);
            n=strcmpi(nombre,Empleado[i].Nom.Nombre);
            if((a==0) && (n==0)){
                Empleado[i].IdEmpleado=0;
                printf("\n\n\t-->Elemento Eliminado\n\n");
            }
            else
                printf("\n\n\t->Empleado no Encontrado\n\n");
        }
    }
}

void Mostrar(Emp Empleado[],int num){
    int i,j,n=4;
    for(i=1;i<=num;i++){
        if(Empleado[i].IdEmpleado!=0){
            printf("\n\n\t\t<< Datos Empleado>>");
            printf("\n\n\t\tId Empleado: %u",Empleado[i].IdEmpleado);
            printf("\n\n\t\t->Datos Personales: ");
            printf("\n\n\t\tApellido Paterno: %s",Empleado[i].Nom.ApellidoP);
            printf("\n\n\t\tApellido Materno: %s",Empleado[i].Nom.ApellidoM);
            printf("\n\n\t\tNombre: %s",Empleado[i].Nom.Nombre);
            printf("\n\n\t\tCURP: %s",Empleado[i].Nom.CURP);
            for(j=1;j<=n;j++){
                if(j==1)
                    printf("\n\n\t\tTelefono de Emergencia: %u",Empleado[i].Nom.telefono[j]);
                else{
                    if(j==2)
                        printf("\n\n\t\tCelular: %u",Empleado[i].Nom.telefono[j]);
                    else
                        if(j==3)
                            printf("\n\n\t\tTelefono fijo: %u",Empleado[i].Nom.telefono[j]);
                }
            }
            printf("\n\n\t\t->Domicilio: ");
            printf("\n\n\t\tCalle: %s No.%d",Empleado[i].Domicilio.calle,Empleado[i].Domicilio.num);
            printf("\n\n\t\tColonia: %s",Empleado[i].Domicilio.col);
            printf("\n\n\t\tCiudad: %s",Empleado[i].Domicilio.cd);
            printf("\n\n\t\tCod. Postal: %u",Empleado[i].Domicilio.cp);
            printf("\n\n\t\t->Laborales: ");
            printf("\n\n\t\tDepartamento: %s",Empleado[i].Lab.dep);
            printf("\n\n\t\tArea: %s",Empleado[i].Lab.area);
            printf("\n\n\t\tPuesto: %s",Empleado[i].Lab.puesto);
            if(Empleado[i].Lab.contrato==8)
                printf("\n\n\t\tTipo de Contrato: Tiempo Completo 8 HRS");
            else
                printf("\n\n\t\tTipo de Contrato: Medio Tiempo 4 HRS");
            printf("\n\n\t\tSueldo por Hora: $%.2f",Empleado[i].Lab.sueldohr);
            printf("\n\n\t\tFecha de Ingreso: %d/%d/%d\n\n",Empleado[i].Ingreso.dia,Empleado[i].Ingreso.mes,Empleado[i].Ingreso.ano);
        }
    }
}


void Consulta(Emp Empleado[],int num){
    int i,j,n,a,dd,mm,aa,ID;
    char nombre[15],apellido[15];
    printf("\n\n\tIngresa:");
    printf("\n\n\t\tDia dd: ");
    scanf("%d",&dd);
    printf("\n\n\t\tMes mm: ");
    scanf("%d",&mm);
    printf("\n\n\t\tAno aaaa: ");
    scanf("%d",&aa);
    for(i=1;i<=num;i++){
        if(Empleado[i].IdEmpleado!=0){
            if(dd==Empleado[i].Ingreso.dia && mm==Empleado[i].Ingreso.mes && aa==Empleado[i].Ingreso.ano){
                printf("\n\n\t\t<< Datos Empleado >>");
                printf("\n\n\t\tId Empleado: %u",Empleado[i].IdEmpleado);
                printf("\n\n\t\tApellido Paterno: %s",Empleado[i].Nom.ApellidoP);
                printf("\n\n\t\tApellido Materno: %s\n\n",Empleado[i].Nom.ApellidoM);
                printf("\n\n\t\tNombre: %s",Empleado[i].Nom.Nombre);
            }
            else
                printf("\n\n\t->Empleado no Encontrado\n\n");
            printf("\n\n\t\t>> Ver Detalles de la Lista << ");
            printf("\n\n\t-->Ingresa el Apellido Paterno del Empleado: ");
            scanf("%s",&apellido);
            strupr(apellido);
            printf("\n\n\t-->Ingresa el Nombre del Empleado: ");
            scanf("%s",&nombre);
            strupr(nombre);
            n=strcmpi(nombre,Empleado[i].Nom.Nombre);
            a=strcmpi(apellido,Empleado[i].Nom.ApellidoP);
            if(n==0 && a==0){
                printf("\n\n\t\t<< Datos Empleado>>");
                printf("\n\n\t\tId Empleado: %u",Empleado[i].IdEmpleado);
                printf("\n\n\t\t->Datos Personales: ");
                printf("\n\n\t\tApellido Paterno: %s",Empleado[i].Nom.ApellidoP);
                printf("\n\n\t\tApellido Materno: %s",Empleado[i].Nom.ApellidoM);
                printf("\n\n\t\tNombre: %s",Empleado[i].Nom.Nombre);
                printf("\n\n\t\tCURP: %s",Empleado[i].Nom.CURP);
                for(j=1;j<=n;j++){
                    if(j==1)
                        printf("\n\n\t\tTelefono de Emergencia: %u",Empleado[i].Nom.telefono[j]);
                    else{
                        if(j==2)
                            printf("\n\n\t\tCelular: %u",Empleado[i].Nom.telefono[j]);
                        else
                            printf("\n\n\t\tTelefono fijo: %u",Empleado[i].Nom.telefono[j]);
                    }
                }
                printf("\n\n\t\t->Domicilio: ");
                printf("\n\n\t\tCalle: %s No.%d",Empleado[i].Domicilio.calle,Empleado[i].Domicilio.num);
                printf("\n\n\t\tColonia: %s",Empleado[i].Domicilio.col);
                printf("\n\n\t\tCiudad: %s",Empleado[i].Domicilio.cd);
                printf("\n\n\t\tC.P.: %u",Empleado[i].Domicilio.cp);
                printf("\n\n\t\t->Laborales: ");
                printf("\n\n\t\tDepartamento: %s",Empleado[i].Lab.dep);
                printf("\n\n\t\tArea: %s",Empleado[i].Lab.area);
                printf("\n\n\t\tPuesto: %s",Empleado[i].Lab.puesto);
                if(Empleado[i].Lab.contrato==8)
                    printf("\n\n\t\tTipo de Contrato: Tiempo Completo 8 HRS");
                else
                    printf("\n\n\t\tTipo de Contrato: Medio Tiempo 4 HRS");
                printf("\n\n\t\tSueldo por Hora: $%.2f",Empleado[i].Lab.sueldohr);
                printf("\n\n\t\tFecha de Ingreso: %d/%d/%d\n\n",Empleado[i].Ingreso.dia,Empleado[i].Ingreso.mes,Empleado[i].Ingreso.ano);
            }
        }
        else
            printf("\n\n\t->Empleado no Encontrado\n\n");
    }
}



void SueldoMensual(Emp Empleado[],int num){
    char nombre[15],apellido[15];
    int i,a,n;
    float sueldoMen;
    printf("\n\t\tIngresa Apellido Paterno del Empleado: ");
    scanf("%s",&apellido);
    strupr(apellido);
    printf("\n\n\t\tIngresa Nombre del Empleado: ");
    scanf("%s",&nombre);
    strupr(nombre);
    for(i=1;i<=num;i++){
	    if(Empleado[i].IdEmpleado!=0){
            n=strcmpi(nombre,Empleado[i].Nom.Nombre);
            a=strcmpi(apellido,Empleado[i].Nom.ApellidoP);
            if(n==0 && a==0){
                sueldoMen=Empleado[i].Lab.contrato*Empleado[i].Lab.sueldohr*30;
                printf("\n\n\t\tApellido Paterno: %s",Empleado[i].Nom.ApellidoP);
                printf("\n\n\t\tApellido Materno: %s",Empleado[i].Nom.ApellidoM);
                printf("\n\n\t\tNombre: %s",Empleado[i].Nom.Nombre);
                printf("\n\n\t\tSalario Mensual: $%.2f\n\n",sueldoMen);
            }
	    }
	    else
            printf("\n\t->Empleado no Encontrado\n\n");
    }
}

void IDEmp(Emp Empleado[],int num){
    int i;
    unsigned int id;
    for(i=1;i<=num;i++){
        id=rand()% (100000000-10000000+i) + 10000000;
        if(id!=Empleado[i].IdEmpleado)
            Empleado[i].IdEmpleado=id;
    }
}

void passwd(char password[],char usuario[]){
    int i,c;
    printf("\n\n\t\tIngresa Nombre de Usuario: ");
    scanf("%s",&usuario);
    printf("\n\n\t\tIngresa Contrasena: ");
    i=0;
    while((c=_getch())!=13){
        if(c==8){
            password[i]='\0';
            i--;
            printf("\b\b");
        }
        else
        {
            printf("*");
            password[i]=c;
            i++;
        }
    }
    password[i]='\0';
}


main()
{
    Emp E[Max];
    int opc,num,band,bandd,opcion,u,c,j,b;
    char password[x],password1[x];
    char usuario[x],usuario1[x];
    do{
        printf("\n\n\t\t<< MENU >>");
        printf("\n\n\t\t1. Capturar ");
        printf("\n\n\t\t2. Eliminar");
        printf("\n\n\t\t3. Mostrar");
        printf("\n\n\t\t4. Consulta");
        printf("\n\n\t\t5. Sueldo Mensual");
        printf("\n\n\t\t6. Password");
        printf("\n\n\t\t7. Salir");
        printf("\n\n\t-->Elige una Opcion: ");
        scanf("%d",&opc);
        switch(opc){
            case 1:
                band=1;
                printf("\n\t\t << Captura de Datos >>\n");
                printf("\n\t-->No. de Empleados a Capturar: ");
                scanf("%d",&num);
                IDEmp(E,num);
                Captura(E,num);
            break;
            case 2:
                if(band==1){
                    if(bandd==1){
                        b=1;
                        j=1;
                        while(j<=3 && b==1){
                            b=0;
                            passwd(password1,usuario1);
                            u=strcmpi(password,password1);
                            c=strcmpi(usuario,usuario1);
                            if(u==0 && c==0){
                                printf("\n\n\t\t << Eliminar Datos >>\n");
                                Eliminar(E,num);
                            }
                            else
                                printf("\n\n\t-->Datos Incorrectos");
                            j++;
                            }
                            if(j=3)
                                printf("\n\n\t-->Se Agotaron los Intentos");
                    }
                    else
                        printf("\n\n\t-->Es Necesario un Usuario Registrado");
                }
                else
                    printf("\n\n\t-->No hay Datos Capturados");
            break;
            case 3:
                if(band==1){
                    printf("\n\t\t << Mostrar Datos >>\n");
                    Mostrar(E,num);
                }
                else
                    printf("\n\n\t-->No hay Datos Capturados");
            break;
            case 4:
                if(band==1){
                    printf("\n\t\t << Consulta de Datos >>\n");
                    Consulta(E,num);
                }
                else
                    printf("\n\n\t-->No hay Datos Capturados");
            break;
            case 5:
                if(band==1){
                    printf("\n\t\t << Calcular Sueldo Mensual >>\n");
                    SueldoMensual(E,num);
                }
                else
                    printf("\n\n\t-->No hay Datos Capturados");
            break;
            case 6:
                do{
                    printf("\n\n\t\t<< Menu Password >>");
                    printf("\n\n\t\t1. Crear Password");
                    printf("\n\n\t\t2. Modificar Password");
                    printf("\n\n\t\t3. Salir");
                    printf("\n\n\t-->Elige una Opcion: ");
                    scanf("%d",&opcion);
                    switch(opcion){
                        case 1:
                            bandd=1;
                            printf("\n\n\t\t<< Crear Usuario >>");
                            passwd(password,usuario);
                            printf("\n\n\t-->Datos Guardados");
                        break;
                        case 2:
                            if(bandd==1){
                                printf("\n\n\t\t<< Modificar Usuario >>");
                                printf("\n\n\t\tDatos Actuales: ");
                                passwd(password1,usuario1);
                                u=strcmpi(password,password1);
                                c=strcmpi(usuario,usuario1);
                                if(u==0 && c==0){
                                    printf("\n\n\t\tNuevos Datos: ");
                                    passwd(password1,usuario1);
                                    printf("\n\n\t-->Datos Guardados");
                                }
                                else
                                    printf("\n\n\t-->Datos Incorrectos");
                            }
                            else
                                printf("\n\n\t-->No Existe Contrasena");
                        break;
                        case 3:
                            printf("\n\n\t\t-->Regresar\n");
                        break;
                        default:
                            printf("\n\n\t-->La Opcion es Incorrecta");
                    }
                }while(opcion!=3);
            break;
            case 7:
                printf("\n\n\t-->Gracias por su Visita\n");
            break;
            default:
                printf("\n\n\t-->Opcion Incorrecta");
        }
    }while(opc!=7);
}


