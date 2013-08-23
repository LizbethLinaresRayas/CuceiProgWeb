#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int fd;
    char dir;
    fd=open("C:\\Documents and Settings\\usuario\\Mis documentos\\archivo1.txt",1);
    if(fd > 0)
    {
        while(read(fd,&dir,sizeof(char)))
            printf("%c",dir);
    }
    else
        perror("error");
    return 0;
}
