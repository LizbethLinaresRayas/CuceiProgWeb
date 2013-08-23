#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,i,band=0,b=1,j;
    char cve[10];

    printf("Palabra: ");
    gets(cve);
    i=0;
    while((band == 0) && (i<10))
    {
        a=cve[i];
        j=0;
        while((j<10) && (j != i))
        {
            if(a == cve[j])
            {
                band=1;
                b+=1;
            }
            j++;
        }
        i++;
    }
    printf("%d",b);

    return 0;
}
