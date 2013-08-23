#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int conex;
    conex=open("C:\\Documents and Settings\\usuario\\Escritorio\\archivo.txt",1);
    if(conex > 0)
    {
        write(conex,"hola mundo",10);
    }
    else
        perror("");
    return 0;
}
