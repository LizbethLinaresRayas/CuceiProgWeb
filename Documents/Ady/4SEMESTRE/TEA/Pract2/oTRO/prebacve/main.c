#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,i,band=0,b=0,j;
    char cve[10];

    printf("Palabra: ");
    gets(cve);
    if(band == 0)
    {
        for(i=0; i<10; i++)
        {
            a=cve[i];
            j=0;
            while((j<10) && (j != i))
            {
                if(a == cve[j])
                    b++;
                j++;
            }
        }
    }
    printf("%d",b);

    return 0;
}
