#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int conex;
    conex=open("C:\\Users\\LINARES\\Desktop\\archivo.txt",1);
    if(conex > 0)
    {
        write(conex,"hola mundo",10);
        write(conex,"Hello world",11);
    }
    else
        perror("");
    return 0;
}
