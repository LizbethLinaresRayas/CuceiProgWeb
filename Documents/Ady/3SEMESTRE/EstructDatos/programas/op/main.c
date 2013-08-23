#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#define Max 100
/*backspace*/

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

void Captura(Emp Empleado[],int num);

main()
{

    Emp E[Max];
    int opc,num;
    do{
        printf("\nMENU");
        printf("\n1. Capturar ");
        printf("\n2. Eliminar");
        printf("\n3. Mostrar");
        printf("\n4. Consulta");
        printf("\n5. Sueldo Mensual");
        printf("\n6. Salir");
        printf("\Elige una Opcion");
        scanf("%d",&opc);
        switch(opc){
            case 1:
                printf("\nCaptura de Datos");
                printf("\nNo. de Empleados a Capturar: ");
                scanf("%d",&num);
                Captura(E,num);
            break;

            default:
                printf("\nOpcion Incorrecta");
        }
    }while(opc!=6);
}


void Captura(Emp Empleado[],int num){
    int i,j,n=3,op;
    for(i=1;i<=num;i++){
        printf("\nDatos Empleado:");
        printf("\nNombre: ");
        scanf("%s",&Empleado[i].Nom.Nombre);
        strupr(Empleado[i].Nom.Nombre);
        printf("\nApellido Paterno: ");
        scanf("%s",&Empleado[i].Nom.ApellidoP);
        strupr(Empleado[i].Nom.ApellidoP);
        printf("\nApellido Materno: ");
        scanf("%s",&Empleado[i].Nom.ApellidoM);
        strupr(Empleado[i].Nom.ApellidoM);
        printf("\nCURP: ");
        scanf("%s",&Empleado[i].Nom.CURP);
        strupr(Empleado[i].Nom.CURP);
        for(j=1;j<=n;j++){
            if(j==1){
                printf("\nTelefono de Emergencia: ");
                scanf("%u",&Empleado[i].Nom.telefono[j]);
            }
            else{
                if(j==2){
                    printf("\nCelular: ");
                    scanf("%u",&Empleado[i].Nom.telefono[j]);
                }
                else{
                    if(j==3){
                        printf("\nTelefono fijo: ");
                        scanf("%u",&Empleado[i].Nom.telefono[j]);
                    }
                }
            }
        }
        printf("\nDomicilio: ");
        printf("\nCalle: ");
        scanf("%s",&Empleado[i].Domicilio.calle);
        strupr(Empleado[i].Domicilio.calle);
        printf("\nNumero: ");
        scanf("%d",&Empleado[i].Domicilio.num);
        printf("\nColonia: ");
        scanf("%s",&Empleado[i].Domicilio.col);
        strupr(Empleado[i].Domicilio.col);
        printf("\nCiudad: ");
        scanf("%s",&Empleado[i].Domicilio.cd);
        strupr(Empleado[i].Domicilio.cd);
        printf("\nCodigo Postal: ");
        scanf("%d",&Empleado[i].Domicilio.cp);
        printf("\nDatos Laborales: ");
        printf("\nDepartamento: ");
        scanf("%s",&Empleado[i].Lab.dep);
        strupr(Empleado[i].Lab.dep);
        printf("\nArea: ");
        scanf("%s",&Empleado[i].Lab.area);
        strupr(Empleado[i].Lab.area);
        printf("\nPuesto: ");
        scanf("%s",&Empleado[i].Lab.puesto);
        strupr(Empleado[i].Lab.puesto);
        printf("\ntipo de Contrato");
        printf("\n1.Tiempo completo\n2.Medio Tiempo");
        printf("\nElige una Opcion:");
        scanf("%d",&op);
        switch(op){
            case 1:
                Empleado[i].Lab.contrato=8;
            break;
            case 2:
                Empleado[i].Lab.contrato=4;
            break;
        }
        printf("\nSueldo por Hora: ");
        scanf("%f",&Empleado[i].Lab.sueldohr);
        printf("\nFecha de ingreso: ");
        printf("\nDia dd: ");
        scanf("%d",&Empleado[i].Ingreso.dia);
        printf("\nMes mm: ");
        scanf("%d",&Empleado[i].Ingreso.mes);
        printf("\nAño aa: ");
        scanf("%d",&Empleado[i].Ingreso.ano);
    }
}
