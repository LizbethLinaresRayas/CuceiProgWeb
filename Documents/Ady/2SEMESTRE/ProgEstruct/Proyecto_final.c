/*
Taller de Programacion Estructurada
Secc. D-06
Profesor: Teresa Marquez Frausto
Elaborado por:
Adriana Lizbeth Linares Rayas
Lic. en Informatica
210596378
Miguel Esteban Hernandez Orozco
Ing. en Computacion
207598076

Este programa esta elaborado para apoyo a las carreras de computacion e informatica.
Contiene 14 funciones:
*Conversion de un caracter a codigo ascii               (Secuenciación)
*Calculadora para operaciones basicas                   (Secuenciación)
*Impresion de lista de dispositivos de ent. y salida    (Selección)
*Conversion a distintas capacidades de almacenamiento   (Selección)
*Impresion de una nota de remision                      (Selección múltiple)
*Catalogo de equipo de computo                          (Selección múltiple)
*Calculo del promedio de un numero                      (Repetitiva while)
*Multiplicacion rusa                                    (Repetitiva while)
*Conversor de moneda                                    (Repetitiva do-while)
*Promedio de cantidades                                 (Repetitiva do-while)
*Tablas de multiplicar                                  (Repetitiva for)
*Serie de fibonacci                                     (Repetitiva for)
*Operaciones con                                        (Matrices-Arreglos)
*Operaciones con                                        (Vectores-Arreglos)


*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void calculadora ();
void equipo ();
void udea ();
void prom ();
void moneda ();
void tablas ();
void ascii();
void dispositivos();
void nota();
void rusa();
void numero();
void fibonacci();
void matriz();
void suma();
void resta();
void escalar();
void trans();
void pot();
void prod();
void ascii();
void escv();
void restv ();
void sumv ();
void vector();

main()
{
    int op, sv;

    do {
    system("cls");
    printf("Este programa, le ofrecera diferentes opciones\n");
    printf("Porfavor elija una de las siguientes: \n\n");
    printf("01. Calculadora de dos Numeros (Secuenciacion) \n");
    printf("02. Caonversion de codigo ASCII (Secuenciacion) \n");
    printf("03. Conversion de unidades de Almacenamientio (Seleccion)\n");
    printf("04. Clasificacion de Dispositivos (Seleccion)\n");
    printf("05. Compra de Equipo de Computo (Seleccion Multiple) \n");
    printf("06. Nota de Remision (Seleccion Multiple) \n");
    printf("07. Promedio de Cantidades (While)\n");
    printf("08. Multiplicacion Rusa (While)\n");
    printf("09. Convertidor Peso/Dolar/Euro (Do While)\n");
    printf("10. Promedio de numero entero (Do While)\n");
    printf("11. Creador de tablas de Multiplicar (For)\n");
    printf("12. Serie de Fibonacci (For)\n");
    printf("13. Operaciones con Matrices (Arreglos)\n");
    printf("14. Operaciones con Vectores(Arreglos)\n");
    printf("15. Salir del Programa\n");
    scanf("%d", &op);

    switch (op)
    {
        case 1:
            system("cls");
            calculadora();
            break;

        case 2:
            system("cls");
            ascii();
            break;


        case 3:
            system("cls");
            udea();
            break;

        case 4:
            system("cls");
            dispositivos();
            break;

        case 5:
            system("cls");
            equipo();
            break;

        case 6:
            system("cls");
            nota();
            break;

        case 7:
            system("cls");
            prom();
            break;

        case 8:
            system("cls");
            rusa();
            break;

        case 9:
            system("cls");
            moneda();
            break;

        case 10:
            system("cls");
            numero();
            break;

        case 11:
            system("cls");
            tablas();
            break;

        case 12:
            system("cls");
            fibonacci();
            break;

        case 13:
            system("cls");
            matriz();
            break;

        case 14:
            system("cls");
            vector();
            break;

        case 15:
            system("cls");
            printf("\nGracias por Utilizar el Programa\n");
            break;

        default:
            system("cls");
            printf ("\a\aOpcion no encontrada intentelo de nuevo\n\n");
            break;
    }
            printf("\nDeseas regresar al menu principal: \n1. No\n2. Si\n");
            scanf("%d", &sv);
            if (sv==1)
            printf ("\nGracias por Utilizar el Programa\n");
    }
    while (sv==2);
    }

void calculadora()
{
    float n1, n2, sum, res, mult, div;
    printf("Programa que sirve para calcular las operaciones basicas de dos numeros.\n\n");
    printf("Porfavor introduce el primer numero: ");
    scanf ("%f", &n1);
    printf("Porfavor introduce el segundo numero: ");
    scanf ("%f", &n2);
    system("cls");

    sum=n1+n2;
    res=n1-n2;
    mult=n1*n2;
    div=n1/n2;

    printf("La suma de %.2f + %.2f = %.2f\n", n1, n2, sum);
    printf("La resta de %.2f - %.2f = %.2f\n", n1, n2, res);
    printf("La multiplicacion de %.2f * %.2f = %.2f\n", n1, n2, mult);
    printf("La division de %.2f / %.2f = %.2f\n", n1, n2, div);
}
void equipo()
{
    int op, sv;
    char cor;
            menu:
            system("cls");

            printf("Nouvelles Technologies! \nLe ofrece el equipo de computo mas novedoso del mercado.");

            printf("\n\nSi gusta de observar las caracteristicas y precios de algun producto \nbasta con que introdusca en numero que le antecede.\n\n");
                {
                printf("1. Computadora de Escritorio NT M-3456\n");
                printf("2. Computadora de Escritorio NT X-869\n");
                printf("3. Computadora Portatil NT M-457\n");
                printf("4. Computadora Portatil NT M-0067\n");
                printf("5. Computadora Netbook NT A-2309\n");
                scanf("%d", &op);
                }
                switch (op)
                {
                    case 1:
                        system("cls");
                        printf("Computadora de Escritorio NT M-3456\n");
                        printf("MARCA:\t\tNT \nMODELO:\t\tM-3456 NT \nU. DE VENTA:\tPIEZA \nPROCESADOR:\tCORE I3 \nDISCO DURO:\t500GB \nMEMORIA RAM:\t4GB\n");
                        printf("U. DE DISCO:\tCD/DVD \nPANTALLA:\t14.5 PULGADAS \nSIST OP:\tWINDOWS 7 PREMIUM \nPRECIO:\t\t$13,500 \nGARANTIA:\t12 MESES DE GARANTIA CON EL PROVEEDOR\n\n");
                        printf("Hacer Compra: \n1. Si\n2. No\n");
                        scanf("%d", &sv);
                            if (sv==1)
                                {
                                    system("cls");
                                    printf("Intrduce tu correo electronico: ");
                                    scanf ("%s", &cor);
                                    system("cls");
                                    printf("En un momento te llegara un correo de confiramcion de compra. \nSigue los pasos indicados.");

                                }
                                else
                                goto menu;
                        break;


                    case 2:
                        system("cls");
                        printf("Computadora de Escritorio NT X-869\n");
                        printf("MARCA:\t\tNT \nMODELO:\t\tX-869 NT \nU. DE VENTA:\tPIEZA \nPROCESADOR:\tCORE I2 \nDISCO DURO:\t300GB \nMEMORIA RAM:\t3GB\n");
                        printf("U. DE DISCO:\tCD/DVD \nPANTALLA:\t14.5 PULGADAS \nSIST OP:\tWINDOWS 7 PREMIUM \nPRECIO:\t\t$10,290 \nGARANTIA:\t12 MESES DE GARANTIA CON EL PROVEEDOR\n\n");
                        printf("Hacer Compra: \n1. Si\n2. No\n");
                        scanf("%d", &sv);
                            if (sv==1)
                                {
                                    system("cls");
                                    printf("Intrduce tu correo electronico: ");
                                    scanf ("%s", &cor);
                                    system("cls");
                                    printf("En un momento te llegara un correo de confiramcion de compra. \nSigue los pasos indicados.");

                                 }
                                 else
                                 goto menu;
                        break;

                    case 3:
                        system("cls");
                        printf("Computadora Portatil NT M-457\n");
                        printf("MARCA:\t\tNT \nMODELO:\t\tM-457 \nU. DE VENTA:\tPIEZA \nPROCESADOR:\tCORE I3 \nDISCO DURO:\t500GB \nMEMORIA RAM:\t4GB\n");
                        printf("U. DE DISCO:\tCD/DVD \nPANTALLA:\t15 PULGADAS \nSIST OP:\tWINDOWS 7 PREMIUM \nPRECIO:\t\t$15,000 \nGARANTIA:\t12 MESES DE GARANTIA CON EL PROVEEDOR\n\n");
                        printf("Hacer Compra: \n1. Si\n2. No\n");
                        scanf("%d", &sv);
                            if (sv==1)
                                {
                                    system("cls");
                                    printf("Intrduce tu correo electronico: ");
                                    scanf ("%s", &cor);
                                    system("cls");
                                    printf("En un momento te llegara un correo de confiramcion de compra. \nSigue los pasos indicados.");

                                 }
                                 else
                                 goto menu;
                        break;

                    case 4:
                        system("cls");
                        printf("Computadora Portatil NT M-0067\n");
                        printf("MARCA:\t\tNT \nMODELO:\t\tM-0067 NT \nU. DE VENTA:\tPIEZA \nPROCESADOR:\tCORE I2 \nDISCO DURO:\t300GB \nMEMORIA RAM:\t3GB\n");
                        printf("U. DE DISCO:\tCD/DVD \nPANTALLA:\t14 PULGADAS \nSIST OP:\tWINDOWS 7 PREMIUM \nPRECIO:\t\t$13,359 \nGARANTIA:\t12 MESES DE GARANTIA CON EL PROVEEDOR\n\n");
                        printf("Hacer Compra: \n1. Si\n2. No\n");
                        scanf("%d", &sv);
                            if (sv==1)
                                {
                                    system("cls");
                                    printf("Intrduce tu correo electronico: ");
                                    scanf ("%s", &cor);
                                    system("cls");
                                    printf("En un momento te llegara un correo de confiramcion de compra. \nSigue los pasos indicados.");

                                 }
                                 else
                                 goto menu;
                    break;

                    case 5:
                        system("cls");
                        printf("Computadora Netbook NT A-2309\n");
                        printf("MARCA:\t\tNT \nMODELO:\t\tNetbook NT A-2309 \nU. DE VENTA:\tPIEZA \nPROCESADOR:\tCORE I2 \nDISCO DURO:\t250GB \nMEMORIA RAM:\t2GB\n");
                        printf("U. DE DISCO:\tNO DISPONIBLE \nPANTALLA:\t10 PULGADAS \nSIST OP:\tWINDOWS 7 PREMIUM \nPRECIO:\t\t$6,200 \nGARANTIA:\t12 MESES DE GARANTIA CON EL PROVEEDOR\n\n");
                        printf("Hacer Compra: \n1. Si\n2. No\n");
                        scanf("%d", &sv);
                            if (sv==1)
                                {
                                    system("cls");
                                    printf("Intrduce tu correo electronico: ");
                                    scanf ("%s", &cor);
                                    system("cls");
                                    printf("En un momento te llegara un correo de confiramcion de compra. \nSigue los pasos indicados.");
                                 }
                                 else
                                 goto menu;
                        break;

                    default :
                    {
                        system("cls");
                        printf ("\a\aOpcion no encontrada intentelo de nuevo\n\n");
                    }
}
}
void udea()
{
    int conv, sv;
    float b, kb, mb, gb, tb;

    printf("Conversiones entre las distintas unidades de almacenamiento \nutilizadas en computadoras.\n\n");
    printf("Que unidad quieres convertir: \n1 Byte\n2 Kilo Byte\n3 Mega Byte\n4 Giga Byte\n5 Tera Byte\n\nIntroduce tu opcion: ");
    scanf("%d", &conv);

    system("cls");
    if (conv==1)
    {
        printf("Introduce la cantidad de Bytes a convertir: ");
        scanf("%f", &b);
        printf("A que unidad deseas convertir: \n1 Kilo Byte\n2 Mega Byte\n3 Giga Byte\n4 Tera Byte\n\nIntroduce tu opcion: ");
        scanf("%d", &conv);
        if (conv==1)
        {
            kb=b/1024;
            printf ("\nLa cantidad de %.2f Bytes es equivalente a %.10f Kilo Bytes\n\n", b, kb);
        }

        if (conv==2)
        {
            mb=b/1048576;
            printf ("\nLa cantidad de %.2f Bytes es equivalente a %.10f Mega Bytes\n\n", b, mb);
        }

        if (conv==3)
        {
             gb=b/1073741824;
             printf ("\nLa cantidad de %.2f Bytes es equivalente a %.15f Giga Bytes\n\n", b, gb);
        }

        if (conv==4)
        {
            tb=b/1099511627776;
            printf ("\nLa cantidad de %.2f Bytes es equivalente a %.15f Tera Bytes\n\n", b, tb);
        }
    }
    else

        if (conv==2)
        {
             printf("Introduce la cantidad de Kilo Bytes a convertir: ");
             scanf("%f", &kb);
             printf("A que unidad deseas convertir: \n1 Byte\n2 Mega Byte\n3 Giga Byte\n4 Tera Byte\n\nIntroduce tu opcion: ");
             scanf("%d", &conv);
             if (conv==1)
             {
                  b=kb*1024;
                  printf ("\nLa cantidad de %.2f K Bytes es equivalente a %.2f  Bytes\n\n", kb, b);
             }

             if (conv==2)
             {
                 mb=kb/1024;
                 printf ("\nLa cantidad de %.2f K Bytes es equivalente a %.10f Mega Bytes\n\n", kb, mb);
             }

             if (conv==3)
             {
                 gb=kb/1048576;
                 printf ("\nLa cantidad de %.2f K Bytes es equivalente a %.10f Giga Bytes\n\n", kb, gb);
             }

             if (conv==4)
             {
                 tb=kb/1073741824;
                 printf ("\nLa cantidad de %.2f K Bytes es equivalente a %.10f Tera Bytes\n\n", kb, tb);
             }
        }
        else

             if (conv==3)
             {
                 printf("Introduce la cantidad de Mega Bytes a convertir: ");
                 scanf("%f", &mb);
                 printf("A que unidad deseas convertir: \n1 Byte\n2 Kilo Byte\n3 Giga Byte\n4 Tera Byte\n\nIntroduce tu opcion: ");
                 scanf("%d", &conv);
                 if (conv==1)
                 {
                     b=mb*1048576;
                     printf ("\nLa cantidad de %.2f M Bytes es equivalente a %.2f  Bytes\n\n", mb, b);
                 }

                 if (conv==2)
                 {
                     kb=mb*1024;
                     printf ("\nLa cantidad de %.2f M Bytes es equivalente a %.2f Kilo Bytes\n\n", mb, kb);
                 }

                 if (conv==3)
                 {
                     gb=mb/1024;
                     printf ("\nLa cantidad de %.2f M Bytes es equivalente a %.10f Giga Bytes\n\n", mb, gb);
                 }

                 if (conv==4)
                 {
                     tb=mb/1048576;
                     printf ("\nLa cantidad de %.2f M Bytes es equivalente a %.10f Tera Bytes\n\n", mb, tb);
                 }
        }
        else

             if (conv==4)
             {
                 printf("Introduce la cantidad de Giga Bytes a convertir: ");
                 scanf("%f", &gb);
                 printf("A que unidad deseas convertir: \n1 Byte\n2 Kilo Byte\n3 Mega Byte\n4 Tera Byte\n\nIntroduce tu opcion: ");
                 scanf("%d", &conv);
                 if (conv==1)
                 {
                     b=gb*1073741824;
                     printf ("\nLa cantidad de %.2f G Bytes es equivalente a %.2f  Bytes\n\n", gb, b);
                 }

                 if (conv==2)
                 {
                      kb=gb*1048576;
                      printf ("\nLa cantidad de %.2f G Bytes es equivalente a %.2f Kilo Bytes\n\n", gb, kb);
                 }

                 if (conv==3)
                 {
                       mb=gb*1024;
                       printf ("\nLa cantidad de %.2f G Bytes es equivalente a %.2f Mega Bytes\n\n", gb, mb);
                 }

                 if (conv==4)
                 {
                       tb=gb/1024;
                       printf ("\nLa cantidad de %.2f G Bytes es equivalente a %.10f Tera Bytes\n\n", gb, tb);
                 }
            }
        else

            if (conv==5)
            {
                  printf("Introduce la cantidad de Tera Bytes a convertir: ");
                  scanf("%f", &tb);
                  printf("A que unidad deseas convertir: \n1 Byte\n2 Kilo Byte\n3 Mega Byte\n4 Giga Byte\n\nIntroduce tu opcion: ");
                  scanf("%d", &conv);
                  if (conv==1)
                  {
                        b=tb*1099511627776;
                        printf ("\nLa cantidad de %.2f T Bytes es equivalente a %.2f  Bytes\n\n", tb, b);
                  }

                  if (conv==2)
                  {
                        kb=tb*1073741824;
                        printf ("\nLa cantidad de %.2f T M Bytes es equivalente a %.2f Kilo Bytes\n\n", tb, kb);
                  }

                  if (conv==3)
                  {
                        mb=tb*1048576;
                        printf ("\nLa cantidad de %.2f T Bytes es equivalente a %.2f Mega Bytes\n\n", tb, mb);
                  }

                  if (conv==4)
                  {
                        gb=tb/1024;
                        printf ("\nLa cantidad de %.2f T Bytes es equivalente a %.10f Giga Bytes\n\n", tb, gb);
                  }
            }

}
void prom()
{
    int vc=0, ac=0;
    float prome, num, can;

            printf ("Esta aplicacion, servira para sacar el promedio de un numero de cantidades.\n\n");
            printf ("Cuatas cantidades se van a promediar?: ");
            scanf ("%f", &num);

                while (vc<num)
                {
                    printf ("Dame la cantidad: ");
                    scanf ("%f", &can);
                    ac=ac+can;
                    vc++;
                }
            prome=ac/num;
            printf ("\n\nEl promedio de las cantidades es: %.2f\n\n",prome);
}
void moneda()
{
    int cn, conv;
    float mx, usd, eu;

            printf ("Convertidor de Moneda\n\n");
            do
            {
               system("cls");
               printf ("Que tipo de moneda desea convertir\n\n");
               printf ("1. Peso Mexicano MX$\n");
               printf ("2. Dolar US$\n");
               printf ("3. Euro  €\n");
               scanf("%d", &conv);

               switch (conv)
                {
                   case 1:
                    system("cls");
                    printf ("Introduce la cantidad de MX$: ");
                    scanf ("%f", &mx);
                    printf ("\nA que unidad lo deseas convertir: \n");
                    printf ("1. Dolar US$\n");
                    printf ("2. Euro  EUR€\n");
                    scanf("%d", &conv);
                        switch (conv)
                        {
                            case 1:
                            system("cls");
                            usd=mx*0.083505;
                            printf ("La cantidad de %.2f MX$ es igual a %.2f USD$ \n\n", mx, usd);
                            break;
                            case 2:
                            system("cls");
                            eu=mx*0.0593496802;
                            printf ("La cantidad de %.2f MX$ es igual a %.2f EUR€ \n\n", mx, eu);
                            break;
                        }
                        break;

                   case 2:
                    system("cls");
                    printf ("Introduce la cantidad de US$: ");
                    scanf ("%f", &usd);
                    printf ("\nA que unidad lo deseas convertir: \n");
                    printf ("1. Peso Mexicano MX$\n");
                    printf ("2. Euro  EUR€\n");
                    scanf("%d", &conv);
                        switch (conv)
                        {
                            case 1:
                            system("cls");
                            mx=usd*11.9753308;
                            printf ("La cantidad de %.2f US$ es igual a %.2f MX$ \n\n", usd, mx);
                            break;
                            case 2:
                            system("cls");
                            eu=usd*0.710732054;
                            printf ("La cantidad de %.2f US$ es igual a %.2f EUR€ \n\n", usd, eu);
                            break;
                        }
                    break;
                   case 3:
                   system("cls");
                    printf ("Introduce la cantidad de EUR€: ");
                    scanf ("%f", &eu);
                    printf ("\nA que unidad lo deseas convertir: \n");
                    printf ("1. Peso Mexicano MX$\n");
                    printf ("2. Dolar  US$\n");
                    scanf("%d", &conv);
                        switch (conv)
                        {
                            case 1:
                            system("cls");
                            mx=eu*16.8492905;
                            printf ("La cantidad de %.2f EUR€ es igual a %.2f MX$ \n\n", eu, mx);
                            break;
                            case 2:
                            system("cls");
                            usd=eu*1.40700;
                            printf ("La cantidad de %.2f EUR€ es igual a %.2f US$ \n\n", eu, usd);
                            break;
                        }
                    break;

                    default :
                    system("cls");
                    printf ("\a\aOpcion no encontrada intentelo de nuevo\n\n");
               }
            printf("Deseas hacer otra conversion: \n1. Si\n2. No\n");
            scanf ("%d", &cn);
            }
            while (cn==1);
}
void tablas()
{
    int nume, tab, i, multi;

            printf("Esta aplicacion te dara la tabla de multiplicar de un numero.\n");
            printf("Hasta el numero que deseas que se multiplique.\n\n");
            printf("Ingrese un numero: ");
            scanf("%d",&nume);
            printf("Hasta que tabla deseas multiplicar: ");
            scanf ("%d", &tab);

                for(i=0;i<=tab;i++)
                {
                    multi=i*nume;
                    printf("%d x %d = %d\n",nume,i,multi);
                }
}
void ascii()
{
    char A1;
    printf("Codigo ASCII");
    printf("\nIntroduce un caracter: ");
    scanf("%s",&A1);
    printf("El caracter es: %c\n",A1);
    printf("El caracter en codigo ASCII es :%i\n",A1);
}
void dispositivos()
{
    int disp;
    printf("Este programa muetsra una lista de los Tipos de Dispositivos");
    printf("\nIntroduce tipo de dispositivo: 1 entrada o 2 salida: ");
    scanf("%i",&disp);
    if(disp==1)
       printf("Dispositivos de Entrada:\nJoystick\nLappiz Optico\nMouse\nScanner\nTeclado\nWebcam");
    else
       printf("\nDispositivos de salida:\nAltavoces\nAuriculares\nBocinas\nFax\nImpresoras\nMonitor\nPloters");
}
void nota()
{
    int cant,tot;
    char nombre[50],dom[50],fec[50],prod;
    printf("\nSe Imprimira una Nota de Remision \n");
    printf("Ingresa el nombre del Cliente: ");
    fflush(stdin);
    gets(nombre);
    printf("Ingresa el Domicilio de la Empresa: ");
    gets(dom);
    printf("Ingresa la fecha: ");
    gets(fec);
    printf("\nPRODUCTOS:\na: Monitor 19 pulgadas $6500.00\nb: Teclado LG $500.00\nc: Mouse optico $350.00\nd: Impesora Laser $4560.00\ne: Webcam $650.00\n");
    printf("\nElija el producto de venta ");
    fflush(stdin);
    scanf("%c",&prod);
    switch(prod)
    {
        case'a': printf("Ingrese la cantidad de productos comprados: ");
                 scanf("%i",&cant);
                 tot=cant*6500;
                 puts("Nombre: ");
                 puts(nombre);
                 puts("Domicilio: ");
                 puts(dom);
                 puts("Fecha: ");
                 puts(fec);
                 printf("Total:%i ",tot);
        break;
        case'b': printf("Ingrese la cantidad de productos comprados: ");
                 scanf("%i",&cant);
                 tot=cant*500;
                 puts("Nombre: ");
                 puts(nombre);
                 puts("Domicilio: ");
                 puts(dom);
                 puts("Fecha: ");
                 puts(fec);
                 printf("Total:%i ",tot);
        break;
        case'c': printf("Ingrese la cantidad de productos comprados: ");
                 scanf("%i",&cant);
                 tot=cant*350;
                 puts("Nombre: ");
                 puts(nombre);
                 puts("Domicilio: ");
                 puts(dom);
                 puts("Fecha: ");
                 puts(fec);
                 printf("Total:%i ",tot);
        break;
        case'd': printf("Ingrese la cantidad de productos comprados: ");
                 scanf("%i",&cant);
                 tot=cant*350;
                 puts("Nombre: ");
                 puts(nombre);
                 puts("Domicilio: ");
                 puts(dom);
                 puts("Fecha: ");
                 puts(fec);
                 printf("Total:%i ",tot);
        break;
        case'e': printf("Ingrese la cantidad de productos comprados: ");
                 scanf("%i",&cant);
                 tot=cant*350;
                 puts("Nombre: ");
                 puts(nombre);
                 puts("Domicilio: ");
                 puts(dom);
                 puts("Fecha: ");
                 puts(fec);
                 printf("Total:%i ",tot);
        break;
    }
}
void rusa()
{
    int a,b,c;
    printf("Se imprimira la multiplicacion rusa de 2 numeros\n");
    printf("Introduce dos numeros enteros: ");
    scanf("%d %d",&a,&b);
    c=0;
    while(a>=1)
    {
        printf("%d %d\n",a,b);
        if(a%2!=0)
        c=c+b;
        a=a/2;
        b=b*2;
    }
    printf("La multiplicacion rusa es:%d",c);
}
void promedio()
{
    int vc=0;
    float prome, num, can,ac;

    printf ("Esta aplicacion, servira para sacar el promedio de un numero de cantidades.\n\n");
    printf ("Cuatas cantidades se van a promediar?: ");
    scanf ("%f", &num);
    while (vc<num)
    {
        printf ("Dame la cantidad: ");
        scanf ("%f", &can);
        ac=ac+can;
        vc++;
    }
    prome=ac/num;
    printf ("\n\nEl promedio de las cantidades es: %.2f\n\n",prome);
}
void matriz ()
{
    int opc, op;
    do {
        menu:
        system("cls");
        printf ("Programa que resuelve operaciones basicas con matrices.\n");

        printf ("\nElige la operacion que deseas realizar: ");
        printf ("\n1. Suma de Matrices");
        printf ("\n2. Resta de Matrices");
        printf ("\n3. Afectar la matriz por un escalar");
        printf ("\n4. Transpuesta de la Matriz");
        printf ("\n5. Potencia de una Matriz");
        printf ("\n6. Producto de Matrices cuadradas");
        printf ("\n7. Salir\n");
        scanf ("%d", &opc);

        switch (opc)
        {
            case 1:
                system ("cls");
                suma();
                break;

            case 2:
                system ("cls");
                resta();
                break;

            case 3:
                system ("cls");
                escalar();
                break;

            case 4:
                system ("cls");
                trans();
                break;

            case 5:
                system ("cls");
                pot();
                break;

            case 6:
                system ("cls");
                prod();
                break;

            case 7:
                system("cls");
                printf ("\n\n\nGracias por utilizar el programa.\n\n\n");
                break;

            default:
                system("cls");
                printf ("\n\a\aOpcion no encontrada intentelo de nuevo.\n\n\n");
                break;
            }
                printf("Deseas regresar al menu principal: \n1. Si\n2. No\n");
                scanf("%d", &op);
                if (op==2)
                printf ("\nGracias por Utilizar el Programa\n");
    }
    while (op==1);

}
void suma()
{
    int opc, n, i, j, ope;

                           printf ("Recuerda que para sumar matrices estas deben ser del mismo orden y tamano.");
                           printf ("\nIngresa el numero de filas y columnas de tus matrices (siendo de nxn): ");
                           scanf ("%d", &n);

                           int matA[n][n], matB[n][n], sum[n][n];


                           printf ("\n\nEn la Matriz A:\n");

                           for (i=0;i<n;i++)
                            for (j=0;j<n;j++)
                            {
                                printf ("Introduce en valor en el espacio (%d,%d): ", i+1, j+1);
                                scanf ("%d", &matA[i][j]);
                            }
                            printf ("\nEn la Matriz B:\n");

                           for (i=0;i<n;i++)
                            for (j=0;j<n;j++)
                            {
                                printf ("Introduce en valor en el espacio (%d,%d): ", i+1, j+1);
                                scanf ("%d", &matB[i][j]);
                            }

                           for (i=0;i<n;i++)
                            for (j=0;j<n;j++)
                            {
                                sum[i][j]=matA[i][j]+matB[i][j];
                            }

                           printf ("\nLa matriz resultante de la suma es:\n\n");

                           for (i=0;i<n;i++)
                            for (j=0;j<n;j++)
                            {
                                printf ("%d\t", sum[i][j]);
                                if (j==n-1)
                                printf ("\n");
                            }


}
void resta()
{
    int opc, n, i, j, ope;

                           printf ("Recuerda que para sumar matrices estas deben ser del mismo orden y tamano.");
                           printf ("\nIngresa el numero de filas y columnas de tus matrices (siendo de nxn): ");
                           scanf ("%d", &n);

                           int matA[n][n], matB[n][n], res[n][n];

                           printf ("\n\nEn la Matriz A:\n");

                           for (i=0;i<n;i++)
                            for (j=0;j<n;j++)
                            {
                                printf ("Introduce en valor en el espacio (%d,%d): ", i+1, j+1);
                                scanf ("%d", &matA[i][j]);
                            }
                            printf ("\nEn la Matriz B:\n");

                           for (i=0;i<n;i++)
                            for (j=0;j<n;j++)
                            {
                                printf ("Introduce en valor en el espacio (%d,%d): ", i+1, j+1);
                                scanf ("%d", &matB[i][j]);
                            }

                           for (i=0;i<n;i++)
                            for (j=0;j<n;j++)
                            {
                                res[i][j]=matA[i][j]-matB[i][j];
                            }

                           printf ("\nLa matriz resultante de la resta es:\n\n");

                           for (i=0;i<n;i++)
                            for (j=0;j<n;j++)
                            {
                                printf ("%d\t", res[i][j]);
                                if (j==n-1)
                                printf ("\n");
                            }

}
void escalar()
{
    int n, i, j, m, esc;

                printf ("Afectar la matriz por un escalar, resulta de multiplicar todos los elementos de la matriz por un escalar x.\n");
                printf ("Indica el numero de columnas de tu matriz: ");
                scanf ("%d", &n);
                printf ("Indica el numero de filas de tu matriz: ");
                scanf ("%d", &m);
                printf ("Indica el escalar que afectara la matriz: ");
                scanf ("%d", &esc);

                int mat[n][m], cal[n][m];

                printf ("\nPara la matriz:\n");

                for (i=0;i<n;i++)
                    for (j=0;j<m;j++)
                    {
                        printf ("Introduce en valor en el espacio (%d,%d): ", i+1, j+1);
                        scanf ("%d", &mat[i][j]);

                        cal[i][j]=mat[i][j]*esc;
                    }


                    printf ("\nLa matriz afectada resultante es:\n\n");

                           for (i=0;i<n;i++)
                            for (j=0;j<m;j++)
                            {
                                printf ("%d\t", cal[i][j]);
                                if (j==m-1)
                                printf ("\n");
                            }
}
void trans()
{
    int n, i, j, m;

                printf ("Latranspuesta resulta de cambiar las filas por las columnas de la matriz.\n");
                printf ("Indica el numero de columnas de tu matriz: ");
                scanf ("%d", &n);
                printf ("Indica el numero de filas de tu matriz: ");
                scanf ("%d", &m);

                int matA[n][m];

                printf ("\nPara la matriz:\n");

                for (i=0;i<n;i++)
                    for (j=0;j<m;j++)
                    {
                        printf ("Introduce en valor en el espacio (%d,%d): ", i+1, j+1);
                        scanf ("%d", &matA[i][j]);
                    }


                    printf ("\nLa matriz transpuesta resultante es:\n\n");

                           for (j=0;j<m;j++)
                            for (i=0;i<n;i++)
                            {
                                printf ("%d\t", matA[i][j]);
                                if (i==n-1)
                                printf ("\n");
                            }
}
void pot()
{
    int n, i, j, m, p;

                printf ("Para elevar una matriz a alguna potencia, la matriz debe de ser cuadrada (nxn)");
                printf ("\nIngresa el numero de filas y columnas de tus matrices (siendo de nxn): ");
                scanf ("%d", &n);
                printf ("\nIndica a que potencia deseas elevar la matriz: ");
                scanf ("%d", &p);

                int matA[n][n], matP[n][n];

                printf ("\n\nEn la Matriz A:\n");

                for (i=0;i<n;i++)
                    for (j=0;j<n;j++)
                    {
                        printf ("Introduce en valor en el espacio (%d,%d): ", i+1, j+1);
                        scanf ("%d", &matA[i][j]);

                        matP[i][j]=pow(matA[i][j],p);

                    }

                printf ("\nLa matriz potencia resultante es:\n\n");

                for (i=0;i<n;i++)
                    for (j=0;j<n;j++)
                    {
                        printf ("%d\t", matP[i][j]);
                        if (j==n-1)
                        printf ("\n");
                    }
}
void prod()
{
   int n, i, j, k;

                printf("Producto de matrices cuadradas.");
                printf("\nIngresa el numero de filas y columnas de tus matrices (siendo de nxn): ");
                scanf("%d", &n);

                int matA[n][n], matB[n][n], matC[n][n];

                printf ("\n\nEn la Matriz A:\n");

                for (i=0;i<n;i++)
                    for (j=0;j<n;j++)
                    {
                        printf ("Introduce en valor en el espacio (%d,%d): ", i+1, j+1);
                        scanf ("%d", &matA[i][j]);
                    }

                printf ("\nEn la Matriz B:\n");

                for (i=0;i<n;i++)
                    for (j=0;j<n;j++)
                    {
                        printf ("Introduce en valor en el espacio (%d,%d): ", i+1, j+1);
                        scanf ("%d", &matB[i][j]);
                    }


                for (i=0; i<n; i++) {
                    for (j=0; j<n; j++) {
                        matC[i][j] = 0;
                        for (k=0; k<n; k++) {
                        matC[i][j] = matC[i][j] + (matA[i][k] * matB[k][j]);
                        }
                    }
                }


                printf("\nEl producto de las matrices es:");
                for (i=0; i<n; i++) {
                    printf("\n\t");
                    for (j=0; j<n; j++) {
                        printf("%3d ", matC[i][j]);
                    }
                }
                printf("\n");
}
void fibonacci()
{
    int n,i;
    long a,b,c;
    printf("EL PROGRAMA MOSTRARA LA SERIE FIBONACCI\n");
    printf("Ingrese el numero limite de la serie ");
    scanf("%i",&n);
    a=0;
    b=1;
    printf(" %d %d ",a,b);
    for (i=0;i<=n;i++)
    {
        c=a+b;
        printf("%ld ",c);
        a=b;
        b=c;
    }
}
void numero()
{
    int vc=0;
    int prome, num, can,ac;
    printf ("Esta aplicacion, servira para sacar el promedio de un numero de cantidades enteras.\n\n");
    printf ("Cuatas cantidades se van a promediar?: ");
    scanf ("%i", &num);
    while (vc<num)
    {
        printf ("Dame la cantidad: ");
        scanf ("%i", &can);
        ac=ac+can;
        vc++;
    }
    prome=ac/num;
    printf ("\n\nEl promedio de las cantidades es: %i\n\n",prome);
}
void vector()
{
    int op,a;
    do
    {
        printf ("\nElige la operacion que deseas realizar: ");
        printf("\n1. Suma de Vectores");
        printf("\n2. Resta de Vectores");
        printf("\n3. Afectar el Vector por un escalar");
        scanf("%d",&op);
        switch(op)
        {
            case 1:
                    system("cls");
                    sumv ();
                    break;

            case 2:
                    system("cls");
                    restv ();
                    break;

            case 3:
                    system("cls");
                    escv ();
                    break;

        }
        printf("\n\nDeceas entrar de nuevo al menu:\n1.SI\n0.NO\n");
        scanf("%d",&a);
    }
    while(a>=1);
}

void sumv ()
{
    int i=0, n;
                    printf("\nSuma de Vectores\n");
                    printf("\nIntroduce el numero de elementos de los vectores: ");
                    scanf("%i",&n);

                    int vect[n], vect1[n];


                    for(i=0;i<n;i++)
                    {
                        printf("\nIntroduce el valor de los elementos del vect 1 en la posicion %d: ", i+1);
                        scanf("%d",&vect[i]);
                    }

                    for(i=0;i<n;i++)
                    {
                        printf("\nIntroduce el valor de los elementos del vect 2 en la posicion %d: \n", i+1);
                        scanf("%d",&vect1[i]);
                    }
                    printf("\nEl vector resultante es:");
                    for(i=0;i<n;i++)
                    {
                        printf("\n");
                        printf("%d ",vect[i]+vect1[i]);
                    }
}
void restv ()
{
     int i=0, n;
                    printf("\nResta de Vectores\n");
                    printf("\nIntroduce el numero de elementos de los vectores: ");
                    scanf("%d",&n);

                    int vect[n], vect1[n];


                    for(i=0;i<n;i++)
                    {
                        printf("\nIntroduce el valor de los elementos del vect A en la posicion %d: \n", i+1);
                        scanf("%d",&vect[i]);
                    }

                    printf("\nIntroduce el valor de los elementos del vect B en la posicion %d: \n", i+1);
                    for(i=0;i<n;i++)
                    {
                        printf("\nIntroduce el valor de los elementos del vect B en la posicion %d: \n", i+1);
                        scanf("%d",&vect1[i]);
                    }

                    printf("\nEl vector resultante es:");
                    for(i=0;i<n;i++)
                    {
                        printf("\n");
                        printf("%d ",vect[i]-vect1[i]);
                    }
}
void escv()
{
                    int n, i, esc;

                    printf("\nRAfectar un vector por un escalar\n");
                    printf("\nIntroduce el numero de elementos de los vectores: ");
                    scanf("%d",&n);

                    int lista[n];


                    for(i=0;i<n;i++)
                    {
                        printf("\nIntroduce el valor de los elementos del primer vector:\n");
                        scanf("%d",&lista[i]);
                    }
                    printf("\nIntroduce el valor del escalar:\n");
                    scanf("%d",&esc);
                    printf("\nEl vector resultante es:");
                    for(i=0;i<n;i++)
                    {
                        printf("\n");
                        printf("%d",lista[i]*esc);
                    }
}
