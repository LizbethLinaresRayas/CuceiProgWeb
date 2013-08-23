#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int fd;
    char dir[37];
    fd=open("C:\\Documents and Settings\\usuario\\Escritorio\\archivo.txt",0);
    if(fd > 0)
    {
        fd=read(fd,dir,37);
        write(1,&dir,fd);
    }
    else
        perror("");
    return 0;
}
