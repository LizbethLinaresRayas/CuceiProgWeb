#include <stdio.h>
#include <stdlib.h>

void lineBres(int x0,int y0, int xEnd, int yEnd)
{
    int dx=abs(xEnd - x0);
    int dy = dy=abs(yEnd - y0);
    int p = 0;
    int contx = 0;
    int conty = 0;
    int x;
    int y;

    //Toman valores iniciales
    x=x0;
    y=y0;

    //Determinan incremento/decremento
    if(x0 > xEnd)
        contx=-1;
    else
        contx=1;
    if(y0 > yEnd)
        conty=-1;
    else
        conty=1;

    //primer pixel
    printf("\n\tx: %d\ty: %d",x,y);

    //si la pendiente es mayor a 0 y menor a 1
    if(dy <= dx)
    {
        p=2 * dy - dx;
        while(x != xEnd)
        {
            x+=contx;
            if(p < 0)
                p += 2 * dy;
            else
            {
                y+=conty;
                p += 2 * (dy - dx);
            }
            printf("\n\tx: %d\ty: %d",x,y);
        }
    }
    else
    {
        if(dy > dx)
        {
            p=2 * dx - dy;
            while(y != yEnd)
            {
                y+=conty;
                if(p < 0)
                    p += 2 * dx;
                else
                {
                    x+=contx;
                    p += 2 * (dx - dy);
                }
                printf("\n\tx: %d\ty: %d",x,y);
            }
        }
    }
}

int main()
{

    int opc;
    int x1=0;
    int y1=0;
    int x2=0;
    int y2=0;

    printf("\n\t1. Bresenham");
    printf("\n\tOpcion: ");
    scanf("%d",&opc);
    switch(opc)
    {
        case 1:
            system("cls");
            printf("\n\tx1: ");
            scanf("%d",&x1);
            printf("\n\ty1: ");
            scanf("%d",&y1);
            printf("\n\tx2: ");
            scanf("%d",&x2);
            printf("\n\ty2: ");
            scanf("%d",&y2);
            lineBres(x1,y1,x2,y2);
        break;
    }
    return 0;
}
