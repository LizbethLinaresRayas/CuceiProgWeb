#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int fd;
    fd=creat("archi.txt",755);
    if(fd > 0)
        printf("\n\tCreacion Exitosa");
    else
        perror("");
    return 0;
}
