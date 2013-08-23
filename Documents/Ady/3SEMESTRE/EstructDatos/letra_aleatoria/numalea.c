#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int i;
    unsigned int num;
    for(i=0;i<1;i++){
        num=rand()%999999;
        printf("\n%u",num);
    }
    getch();

}
