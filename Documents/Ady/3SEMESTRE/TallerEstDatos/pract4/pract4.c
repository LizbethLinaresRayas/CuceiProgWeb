#include <conio.h>
#include <stdio.h>
#include <string.h>

struct Empleado{
	unsigned int Id_empleado;
    char Nombre[16];
    char apellidoPaterno[15];
    char apellidoMaterno[15];
    char fecha_nac[10];
    char sexo;
    char asegurado;
    float sueldoDiario;
    int No_seg;
    char RFC[15];
}empleado[1000];

void Captura(int num){
	int i;
    for(i=1;i<=num;i++){
        printf("\n\t-->Datos Empleado No.%d",i);
        printf("\n\n\tId.Empleado: ");
        scanf("%d",&empleado[i].Id_empleado);
        printf("\n\tApellido Paterno: ");
        scanf("%s",&empleado[i].apellidoPaterno);
        strupr(empleado[i].apellidoPaterno);
        printf("\n\tApellido Materno: ");
        scanf("%s",&empleado[i].apellidoMaterno);
        strupr(empleado[i].apellidoMaterno);
        printf("\n\tNombre: ");
        scanf("%s",&empleado[i].Nombre);
        strupr(empleado[i].Nombre);
        printf("\n\tFecha de Nacimiento aa/mm/dd: ");
        scanf("%s",&empleado[i].fecha_nac);
        printf("\n\tSexo F o M: ");
        scanf("%s",&empleado[i].sexo);
        if(empleado[i].sexo=='f')
            empleado[i].sexo='F';
        else
            if(empleado[i].sexo=='m')
                empleado[i].sexo='M';
            else
                if(empleado[i].sexo!='F' || empleado[i].sexo!='M'){
                    printf("\n-->Sexo Invalido");
                    printf("\n\tSexo F o M: ");
                    scanf("%s",&empleado[i].sexo);
                }
        printf("\n\tSueldo Diario: ");
        scanf("%f",&empleado[i].sueldoDiario);
        printf("\n\tEl empleado esta asegurado S o N: ");
        scanf("%s",&empleado[i].asegurado);
        if(empleado[i].asegurado=='S' || empleado[i].asegurado=='s'){
            printf("\n\tNo. de Seguro Social: ");
            scanf("%d",&empleado[i].No_seg);
        }
        printf("\n-->Datos Capturados\n");
    }
}

void Mostrar(int num){
	int i;
    for(i=1;i<=num;i++){
        if(empleado[i].Id_empleado!=0){
            printf("\n\n\t\tDatos Empleado: \n");
            printf("\n\tId.Empleado: %d",empleado[i].Id_empleado);
            printf("\n\tApellido Paterno: %s",empleado[i].apellidoPaterno);
            printf("\n\tApellido Materno: %s",empleado[i].apellidoMaterno);
            printf("\n\tNombre: %s",empleado[i].Nombre);
            printf("\n\tFecha de Nacimiento: %s",empleado[i].fecha_nac);
            printf("\n\tSexo: %c",empleado[i].sexo);
            printf("\n\tSueldo Diario: $%.2f",empleado[i].sueldoDiario);
            printf("\n\tNo. de Seguro: %d",empleado[i].No_seg);
            printf("\n\tRFC: %s",empleado[i].RFC);
        }
    }
}

void MostrarSeg(int num){
	int i;
	long no_seg;
	for(i=1; i<=num ; i++){
	    if(empleado[i].Id_empleado!=0){
            if(empleado[i].asegurado == 'N' || empleado[i].asegurado == 'n'){
                printf("\n\n\t\tDatos Empleado: \n");
                printf("\n\tApellido Paterno: %s",empleado[i].apellidoPaterno);
                printf("\n\tApellido Materno: %s",empleado[i].apellidoMaterno);
                printf("\n\tNombre: %s",empleado[i].Nombre);
                printf("\n\tFecha de Nacimiento: %s",empleado[i].fecha_nac);
                printf("\n\tSexo: %c",empleado[i].sexo);
                printf("\n\tSueldo Diario: $%.2f",empleado[i].sueldoDiario);
                printf("\n\tRFC: %s ",empleado[i].RFC);
                empleado[i].No_seg = rand() % 1111111111;
                printf("\n\tNo. de Seguro: %d",empleado[i].No_seg);
            }
	    }
	}
	printf("\n\n-->Numero de Seguro Social Calculado");
}

void RFC(int num){
	int i,cont,n=3;
	char homo[3];
	for(i=1;i<=num;i++){
	    for(cont=1;cont<=n;cont++){
			homo[cont]='A'+rand() % 26;
		}
		empleado[i].RFC[0]=empleado[i].apellidoPaterno[0];
		empleado[i].RFC[1]=empleado[i].apellidoPaterno[1];
		empleado[i].RFC[2]=empleado[i].apellidoMaterno[0];
		empleado[i].RFC[3]=empleado[i].Nombre[0];
		strcat(empleado[i].RFC,empleado[i].fecha_nac);
		strcat(empleado[i].RFC,homo);
		printf("\n-->FRC Calculado ");
	}
}

void Busqueda(int num){
	int i,v;
	char apellido[15];
	printf("\nIngresa Apellido Paterno: ");
	scanf("%s",&apellido);
	for(i=0;i<=num;i++){
	    if(empleado[i].Id_empleado!=0){
            v=strcmpi(apellido,empleado[i].apellidoPaterno);
            if(v==0){
                printf("\n\n\t\tDatos Empleado: \n");
                printf("\n\tId.Empleado: %d",empleado[i].Id_empleado);
                printf("\n\tApellido Paterno: %s",empleado[i].apellidoPaterno);
                printf("\n\tApellido Materno: %s",empleado[i].apellidoMaterno);
                printf("\n\tNombre: %s",empleado[i].Nombre);
                printf("\n\tFecha de Nacimiento: %s",empleado[i].fecha_nac);
                printf("\n\tSexo: %c",empleado[i].sexo);
                printf("\n\tSueldo Diario: $%.2f",empleado[i].sueldoDiario);
                printf("\n\tNo. de Seguro: %d",empleado[i].No_seg);
                printf("\n\tRFC: %s ",empleado[i].RFC);
            }
            else
                printf("\n\t->Empleado no Encontrado");
	    }
	}
}

void Eliminar(int num){
	int i,a,n;
	char apellido[15],nombre[15];
	printf("\n\tIngresa Apellido Paterno: ");
	scanf("%s",&apellido);
	printf("\n\tIngresa Nombre: ");
	scanf("%s",&nombre);
	for(i=1;i<=num;i++){
	    if(empleado[i].Id_empleado!=0){
            a=strcmpi(apellido,empleado[i].apellidoPaterno);
            n=strcmpi(nombre,empleado[i].Nombre);
            if((a==0) && (n==0)){
                empleado[i].Id_empleado=0;
                printf("\n-->Elemento Eliminado");
            }
            else
                printf("\n\t->Empleado no Encontrado");
	    }
	}

}

main()
{
	int op,num,band;
	do{
		printf("\n\n\t\t\tMENU");
		printf("\n\n\t\t1. Capturar");
		printf("\n\n\t\t2. Eliminar");
		printf("\n\n\t\t3. Mostrar");
		printf("\n\n\t\t4. Empleados sin Seguro Social");
		printf("\n\n\t\t5. Calcular RFC");
		printf("\n\n\t\t6. Busqueda");
		printf("\n\n\t\t7. Salir");
		printf("\n\n\t-->Seleccione una Opcion: ");
		scanf("%d",&op);
		switch(op){
			case 1:
				band=1;
				printf("\n\t\t<< Captura de Datos >>\n");
				printf("\n   ->No. de Empleados a Capturar: ");
				scanf("%d",&num);
				Captura(num);
			break;
			case 2:
                if(band==1){
					printf("\n\t\t<< Eliminar Datos >>\n");
					Eliminar(num);
				}
				else
					printf("\n-->No hay Datos Capturados\n");
			break;
			case 3:
				if(band==1){
					printf("\n\t\t<< Datos Capturados >>\n");
					Mostrar(num);
				}
				else
					printf("\n-->No hay Datos Capturados\n");
			break;
			case 4:
				if(band==1){
					printf("\n\t\t<< Empleados sin Numero de Seguro Social >>\n");
					MostrarSeg(num);
				}
				else
					printf("\n-->No hay Datos Capturados\n");
			break;
			case 5:
				if(band==1){
					printf("\n\t\t<<Calcular RFC>>\n");
                    RFC(num);
				}
				else
					printf("\n-->No hay Datos Capturados\n");
			break;
			case 6:
				if(band==1){
				    printf("\n\t\t<<Busqueda>>\n");
                    Busqueda(num);
                    }
				else
					printf("\n-->No hay Datos Capturados\n");
			break;
			case 7:
				printf("\n\t\t**Gracias por tu Visita**\n\n");
			break;
			default:
				printf("\n-->Opcion Incorrecta");
		}
	}while(op!=7);
}


