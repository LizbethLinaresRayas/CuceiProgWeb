#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int i,PILA[50];
    for(i=0;i<50;i++)
    {
        PILA[i]='A'+rand()/27;
        printf("%c\n",PILA[i]);
    }
}
