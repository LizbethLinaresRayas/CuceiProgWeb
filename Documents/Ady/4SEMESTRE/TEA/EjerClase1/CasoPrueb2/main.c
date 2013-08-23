#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int fd;
    fd=open("C:\\Users\\LINARES\\Desktop\\archivo.txt",0);
    if(fd > 0)
        printf("\n\tApertura Exitosa");
    else
        perror("");
    return 0;
}
