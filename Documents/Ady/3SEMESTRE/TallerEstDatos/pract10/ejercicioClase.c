/*Adriana Lizbeth Linares Rayas Cod. 210596378 Lic. Informatica Secc. D-15*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int factorial(int n){
    if(n == 0)
        return 1;
    else
        return n*factorial(n-1);
}

int fibonacci(int n){
    if(n < 2)
        return n;
    else
        return fibonacci(n-1) + fibonacci(n-2);
}

int potencia(int x, int y){
    if(y == 0)
        return 1;
    else
        return x*potencia(x,(y-1));
}

int suma(int n){
    if(n == 1)
        return 1;
    else
        return n+suma(n-1);
}

int main()
{
    system("COLOR f0");
    int op,n,x,y,i,res;
    do{
        system("cls");
        printf("\n\n\t\t\tMENU");
        printf("\n\n\t\t1. FACTORIAL");
        printf("\n\n\t\t2. SERIE FIBONACCI");
        printf("\n\n\t\t3. POTENCIA");
        printf("\n\n\t\t4. SUMA DE NUMEROS");
        printf("\n\n\t\t5. SALIR");
        printf("\n\n\t->ELIGE TU OPCION: ");
        scanf("%d",&op);
        switch(op){
            case 1:
                system("cls");
                printf("\n\n\t\tINGRESA EL NUMERO A CALCULAR SU FACTORIAL: ");
                scanf("%d",&n);
                printf("\n\n\t\t\tFACTORIAL DE %d ES: %d ",n,factorial(n));
                getch();
            break;
            case 2:
                system("cls");
                printf("\n\n\t\tINGRESA EL NUMERO LIMITE DE LA SERIE FIBONACCI: ");
                scanf("%d",&n);
                printf("\n");
                for(i=0; i<=n-1; i++){
                    res=fibonacci(i);
                    printf("\t%d",res);
                }
                getch();
            break;
            case 3:
                system("cls");
                printf("\n\n\t\tINGRESA EL NUMERO BASE Y LA POTENCIA:");
                printf("\n");
                scanf("%d %d",&x,&y);
                printf("\n\n\t\t%d ELEVADO A LA POTENCIA %d ES: %d",x,y,potencia(x,y));
                getch();
            break;
            case 4:
                system("cls");
                printf("\n\n\t\tINGRESA EL NUMERO LIMITE PARA LA SUMA: ");
                scanf("%d",&n);
                printf("\n\n\n\t\tLA SUMA DE: ");
                for(i=1; i<=n; i++){
                    printf("\t%d",i);
                    if(i<n)
                        printf("+");
                }
                printf("\n\n\n\t\t\tDA EL TOTAL DE: %d",suma(n));
                getch();
            break;
            case 5:
                system("cls");
                printf("\n\n\t\tGRACIAS POR TU VISITA\n");
                getch();
            break;
        }
    }while(op != 5);
    return 0;
    getch();
}


