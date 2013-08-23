#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int fd;
    fd=open("D:\\TallerEstArchivos\\EjerClase1\\CasoPrueb3\\archivo1.txt",2);
    if(fd > 0)
        printf("Apertura exitosa");
    else
        perror("");
    return 0;
}
