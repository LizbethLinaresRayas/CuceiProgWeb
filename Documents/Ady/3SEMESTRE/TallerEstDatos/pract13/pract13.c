/*Adriana Lizbeth Linares Rayas Secc. D-15
Practica No. 13 Cod. 210596378 Lic. Informatica*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


typedef struct{
    long telef;
    char tipo[10];
}telefono;

typedef struct{
    char nom[15];
    char ape[20];
    char dir[35];
    char correo[30];
    telefono tel[4];
}Datos;

typedef struct Nodo{
    Datos dat;
    struct Nodo *sig;
    struct Nodo *ant;
}Nodo;

typedef Nodo *Lista;
typedef Nodo *posicion;

void inicializa(Lista *L){
    (*L)=(Nodo *)malloc(sizeof(Nodo));
	(*L)->sig=*L;
    (*L)->ant=*L;
}

void inserta(Datos datos, Lista L){
    Nodo *aux;

    aux=(Nodo *)malloc(sizeof(Nodo));
    aux->dat=datos;
    aux->sig=L->sig;
    aux->ant=L;
    L->sig=aux;
    aux->sig->ant=aux;
}

void suprimir(Lista L){
    Nodo *aux;

    if(L != NULL){
        aux=L->sig;
        L->sig=L->sig->sig;
        L->sig->ant=L;
        free(aux);
    }
    else
        printf("\n\n\t\tDIRECCION INVALIDA");
}

void modifica(Lista L, char cadena[30], int x){

    if(L != NULL){
        switch(x){
            case 1:
                strcpy(L->sig->dat.ape, cadena);
            break;
            case 2:
                strcpy(L->sig->dat.nom, cadena);
            break;
            case 3:
                strcpy(L->sig->dat.dir,cadena);
            break;
            case 4:
                strcpy(L->sig->dat.correo,cadena);
            break;
        }


    }
    else printf("\n\n\t\tDIRECCION INVALIDA");
}

posicion localizaNombre(char nombre[15],Lista L){
    Nodo *q;
    int x;

	q=L;
	x=strcmp(q->sig->dat.nom,nombre);
	while(q->sig != L && x != 0)
        q=q->sig;
	if(q->sig == L)
        return NULL;
    else
        return q;
}

int validaCorreo(char mail[30]){
    int i,j,c,lg,band=0,bandera=0,bnd=0,b,cont1=0,cont2=0,cont3=0,cont4=0,cont5=0,cont6=0,cont7=0;

    lg=strlen(mail);
    for(i=0; i<lg; i++){
        if(mail[i] == '@'){
            cont1++;
            b=i;
        }
    }
    if(cont1 == 1){
        for(j=0; j<b; j++){
            if(mail[j] < 45)
                cont2++;
            if(mail[j] > 45 && mail[j] < 48)
                cont3++;
            if(mail[j] > 57 && mail[j] < 65)
                cont4++;
            if(mail[j] > 90 && mail[j] <95)
                cont5++;
            if(mail[j] > 95 && mail[j] < 97)
                cont6++;
        }
        if((cont2 == 0) && (cont3 == 0) && (cont4 == 0) && (cont5 == 0) && (cont6 == 0))
            band=1;
        cont2=0;
        cont3=0;
        cont4=0;
        cont5=0;
        cont6=0;
        cont7=0;
        if(band == 1){
            for(i=b; i<lg ;i++){
                if(mail[i] == '.'){
                    cont2++;
                    c=i;
                    bandera=1;
                }
            }
            if(bandera == 1){
                for(j=b; j<c; j++){
                    if(mail[j] < 45)
                        cont3++;
                    if(mail[j] > 45 && mail[j] < 48)
                        cont4++;
                    if(mail[j] > 57 && mail[j] < 64)
                        cont5++;
                    if(mail[j] > 90 && mail[j] <95)
                        cont6++;
                    if(mail[j] > 95 && mail[j] < 97)
                        cont7++;
                }

                if((cont3 == 0) && (cont4 == 0) && (cont5 == 0) && (cont6 == 0) && (cont7 == 0))
                    bnd=1;
                cont2=0;
                if(bnd == 1){
                    for(j=c; j<lg; j++){
                        if((mail[j] == 'c') || (mail[j] == 'o') || (mail[j] == 'm'))
                            cont2++;
                        else{
                            if((mail[j] == 'g') || (mail[j] == 'o') || (mail[j] == 'b'))
                                cont2++;
                            else{
                                if((mail[j] == 'n') || (mail[j] == 'e') || (mail[j] == 't'))
                                    cont2++;
                            }
                        }
                    }
                }
            }
        }
    }

    if((cont1 == 1) && (band == 1) && (bandera == 1) && (bnd == 1) && (cont2 == 3))
        return 1;
    else
        return -1;
}

Datos captura(Datos datos){
    int i=0,val=0,band=0,opp;

    printf("\n\n\t\tAPELLIDO: ");
    fflush(stdin);
    gets(datos.ape);
    strupr(datos.ape);
    printf("\n\n\t\tNOMBRE: ");
    fflush(stdin);
    gets(datos.nom);
    strupr(datos.nom);
    printf("\n\n\t\tDIRECCION: ");
    fflush(stdin);
    gets(datos.dir);
    strupr(datos.dir);
    do{
        printf("\n\n\t\tTELEFONO: ");
        scanf("%ld",&datos.tel[i].telef);
        printf("\n\n\t\tTIPO DE TELEFONO: ");
        printf("\n\n\t\t*CELULAR\n\n\t\t*PARTICULAR\n\n\t\t*TRABAJO\n\n\t\t*OTRO:\n\n\t\t-> ");
        fflush(stdin);
        gets(datos.tel[i].tipo);
        strupr(datos.tel[i].tipo);
        i++;
        printf("\n\n\t\tAGREGAR OTRO TELEFONO: 1.SI\t2.NO: ");
        scanf("%d",&opp);
        switch(opp){
            case 1:
                band=1;
            break;
            case 2:
                band=0;
            break;
            default:
                printf("\n\n\t\t...OPCION INCORRECTA...");
        }
    }while(band == 1 && i<4);

    do{
        printf("\n\n\t\tCORREO ELECTRONICO: ");
        fflush(stdin);
        gets(datos.correo);
        val=validaCorreo(datos.correo);
        if(val != 1)
            printf("\n\n\t\tFORMATO INCORRECTO");
    }while(val != 1);
    return datos;
}

void imprimeElemento(Nodo *q){
    int i=0;

    system("cls");
    printf("\n\n\t\t<< CONTACTO >>\n");
    printf("\n\n\t\tAPELLIDO: %s",q->sig->dat.ape);
    printf("\n\n\t\tNOMBRE: %s",q->sig->dat.nom);
    printf("\n\n\t\tDIRECCION: %s",q->sig->dat.dir);
    printf("\n\n\t\tTELEFONO: %ld",q->sig->dat.tel[i].telef);
    printf("\n\n\t\tTIPO DE TELEFONO: %s",q->sig->dat.tel[i].tipo);
    printf("\n\n\t\tCORREO: %s",q->sig->dat.correo);
    getch();
}

void imprime(Lista L){
    Nodo *q;
    int b=1,opcion;

    if(L->sig != L){
        q=L;
        while(q->sig != L && b == 1){
            imprimeElemento(q);
            do{
                printf("\n\n\n\t\t1. ELEMENTO SIGUIENTE");
                printf("\n\n\t\t2. ELEMENTO ANTERIOR");
                printf("\n\n\t\t3. SALIR");
                printf("\n\n\t\t-> ");
                scanf("%d",&opcion);
                if(opcion == 1){
                    q=q->sig;
                    imprimeElemento(q);
                }
                else{
                    if(opcion == 2){
                        q=q->ant;
                        imprimeElemento(q);
                    }
                }
            }while(opcion != 3);
            b=0;
        }
    }
    else
        printf("\n\n\t\tLISTA VACIA");
}



int main(){
    system("COLOR f5");
    int opc,op,x,b=0;
    char nombre[15];
    char cadena[30];
    Lista L;
    Datos datos;


    inicializa(&L);
    do{
        system("cls");
        printf("\n\n\t\t\tMENU");
        printf("\n\n\t\t1. CAPTURAR CONTACTO");
        printf("\n\n\t\t2. ELIMINAR CONTACTO");
        printf("\n\n\t\t3. BUSCAR CONTACTO");
        printf("\n\n\t\t4. MODIFICAR CONTACTO");
        printf("\n\n\t\t5. MOSTRAR CONTACTOS");
        printf("\n\n\t\t6. SALIR");
        printf("\n\n\t\t->ELIGE TU OPCION: ");
        scanf("%d",&opc);
        switch(opc){
            case 1:
                system("cls");
                printf("\n\n\t\t\t<< CAPTURA >>");
                datos=captura(datos);
                inserta(datos, L);
                b=1;
                printf("\n\n\t\t...SE HAN GUARDADO LOS CAMBIOS...");
                getch();
            break;
            case 2:
                system("cls");
                printf("\n\n\t\t\t<< ELIMINAR >>");
                if(b == 1){
                    printf("\n\n\t\tINGRESA EL NOMBRE DEL CONTACTO A ELIMINAR: ");
                    fflush(stdin);
                    gets(nombre);
                    strupr(nombre);
                    suprimir(localizaNombre(nombre, L));
                    printf("\n\n\t\t...SE HAN GUARDADO LOS CAMBIOS...");
                }
                else
                    printf("\n\n\t\tLISTA VACIA");
                getch();
            break;
            case 3:
                system("cls");
                printf("\n\n\t\t\t<< BUSCAR >>");
                if(b == 1){
                    printf("\n\n\t\tINGRESA EL NOMBRE DEL CONTACTO A BUSCAR: ");
                    fflush(stdin);
                    gets(nombre);
                    strupr(nombre);
                    imprime(localizaNombre(nombre,L));
                }
                else
                    printf("\n\n\t\tLISTA VACIA");
                getch();
            break;
            case 4:
                system("cls");
                printf("\n\n\t\t\t<< MODIFICAR >>");
                if(b == 1){
                    printf("\n\n\t\tINGRESA EL NOMBRE DEL CONTACTO A MODIFICAR: ");
                    fflush(stdin);
                    gets(nombre);
                    strupr(nombre);
                    if(localizaNombre(nombre,L) != NULL){
                        printf("\n\n\t\tQUE DECEAS MODIFICAR DEL CONTACTO: ");
                        printf("\n\n\t\t1. APELLIDO");
                        printf("\n\n\t\t2. NOMBRE");
                        printf("\n\n\t\t3. DIRECCION");
                        printf("\n\n\t\t4. CORREO ELECTRONICO");
                        printf("\n\n\t\t5. SALIR");
                        printf("\n\n\t\tELIGE TU OPCION: ");
                        scanf("%d",&op);
                        switch(op){
                            case 1:
                                system("cls");
                                printf("\n\n\t\t\t<< MODIFICAR APELLIDO >>");
                                printf("\n\n\t\tINGRESA EL NUEVO APELLIDO: ");
                                fflush(stdin);
                                gets(cadena);
                                strupr(cadena);
                                modifica(localizaNombre(nombre, L),cadena,op);
                                printf("\n\n\t\t...SE HAN GUARDADO LOS CAMBIOS...");
                                getch();
                            break;
                            case 2:
                                system("cls");
                                printf("\n\n\t\t\t<< MODIFICAR NOMBRE >>");
                                printf("\n\n\t\tINGRESA EL NUEVO NOMBRE: ");
                                fflush(stdin);
                                gets(cadena);
                                strupr(cadena);
                                modifica(localizaNombre(nombre, L),cadena,op);
                                printf("\n\n\t\t...SE HAN GUARDADO LOS CAMBIOS...");
                                getch();
                            break;
                            case 3:
                                system("cls");
                                printf("\n\n\t\t\t<< MODIFICAR DIRECCION >>");
                                printf("\n\n\t\tINGRESA LA NUEVA DIRECCION: ");
                                fflush(stdin);
                                gets(cadena);
                                strupr(cadena);
                                modifica(localizaNombre(nombre, L),cadena,op);
                                printf("\n\n\t\t...SE HAN GUARDADO LOS CAMBIOS...");
                                getch();
                            break;
                            case 4:
                                system("cls");
                                printf("\n\n\t\t\t<< MODIFICAR CORREO >>");
                                printf("\n\n\t\tINGRESA EL NUEVO CORREO: ");
                                fflush(stdin);
                                gets(cadena);
                                x=validaCorreo(cadena);
                                if(x != -1){
                                    modifica(localizaNombre(nombre, L),cadena,op);
                                    printf("\n\n\t\t...SE HAN GUARDADO LOS CAMBIOS...");
                                }
                                else
                                    printf("\n\n\t\tFORMATO INCORRECTO");
                                getch();
                            break;
                            case 5:
                                printf("\n\n\t\t...REGRESAR MENU PRINCIPAL");
                            break;
                            default:
                                printf("\n\n\t\t...OPCION INCORRECTA");
                        }
                    }
                }
                else
                    printf("\n\n\t\tLISTA VACIA");
                getch();
            break;
            case 5:
                system("cls");
                printf("\n\n\t\t\tMOSTRAR");
                imprime(L);
                getch();
            break;
            case 6:
                system("cls");
                printf("\n\n\t\tGRACIAS POR TU VISITA");
                getch();
            break;
            default:
                system("cls");
                printf("\n\n\t\t\t...OPCION INCORRECTA");
                getch();
        }
    }while(opc != 6);
    return 0;
    getch();
}
