struct pelicula
{
    char nombre[20];
    char director[35];
    char productor[35];
    char clasif[3];
    int duracion;
    int genero;
};

struct hora_sala
{
    char hora;
    int sala;
};

struct horario
{
    struct pelicula movie;
    struct hora_sala horas[10];
}cartelera[30];

int consulta_pelicula(struct pelicula pel)
{
    int i,id;
    for(i=0;i<30;i++)
        printf("Peliculas\nID: %d Nombre: %s",i,cartelera[i].movie.nombre);
    printf("Pelicula que desea buscar\nIngrese ID:");
    scanf("%d",&id);
    i=0;
    while(i<30 && id=cartelera[i])
    {
        i++;
    }
    return cartelera[i];
}

int int consulta cartelera
{
    int i,id;
    for(i=0;i<30;i++)
        printf("Peliculas\nID: %d Nombre: %s",i,cartelera[i].movie.nombre);
    printf("Pelicula que desea buscar\nIngrese ID:");
    scanf("%d",&id);
    i=0;
    while(i<30 && id!=cartelera[i])
    {
        i++;
    }
    return cartelera[i].movie.nombre,cartelera[i].horas[i].hora,cartelera[i].horas[i].sala;
}

int alta_horarioPeli(struct )
{
    int i,j,a,n;
    for(i=0;i<30;i++)
        printf("Peliculas: %d %s",i,cartelera[i].movie.nombre);
    printf("Ingrese el ID de la pelicula:");
    scanf("%d",&a;
    printf("%d %S",i,cartelera[i].movie.nombre);
    printf("Numero de horarios a agregar");
    scanf("%d",&n);
    for(j=o;j<n;j++)
    {
        printf("Ingresa horario: ");
        gets(cartelera[i].horas[i].hora);
        printf("Ingresa la sala:");
        scanf("%s",&cartelera[i].horas[i].sala);
    }
}

void alta_pelicula()
{
    int i,n;
    for(i=0;i<30;i++)
    {
        printf("ID: %d",i);
        printf("Ingresa los siguientes datos: ");
        printf("Nombre de Pelicula:");
        gets(cartelera[i].movie.nombre);
        printf("Nombre del Director: ");
        gets(cartelera[i].movie.director);
        printf("Nombre del Productor: ");
        gets(cartelera[i].movie.productor);
        printf("Clasificacion: ");
        gets(cartelera[i].movie.clasif);
        printf("Duracion en segundos: ");
        scanf("%d",&cartelera[i].movie.duracion);
        printf("Elige el genero: ");
        scanf("%d",&cartelera[i].movie.genero);
        printf("Ingresa el numero de horarios que tiene la pelicula");
        scanf("%d",&n);
        for(j=0;j<n;j++)
        {
            printf("Ingresa horario: )";
            gets(cartelera[i].horas[i].hora);
            printf("Ingresa la sala: ");
            gets(cartelera[i].horas[i].sala);
        }
    }
}

int ordena_insercion(struct pelicula movie,int n)
{
    register int i,j,aux;
    for(i=1;i<n;i++)
    {
        aux=cartelera[i];
        j=i-1;
        while(j>=0 && aux<cartelera[j])
        {
            cartelera[j+1]=cartelera[j];
            j--;
        }
        cartelera[j+1]=aux;
    }

int ordena_quicksore(struct pelicula movie,int primero,int ultimo)
{
    register int i,j;
    int pivote;
    i=primero;
    j=ultimo;
    pivote=cartelera[(primero+ultimo)/2);
    do
    {
        while(cartelera[i]<pivote)
        {
            i++;
        }
        while(cartelera[i]>pivote)
        {
            j--;
        }
        if(i<=j)
        {
            intercambia(&cartelera[i],&cartelera[j]);
            i++;
            j--;
        }
    }while(i<=j);
    if(primero<j)
    {
        ordena(cartelera,primero,j);
    }
    if(ultimo>i)
    {
        ordena(cartelera,i,ultimo);
    }
}

void intercambia(int *valor1, int *valor2)
{
    if(valor1 != valor2)
    {
        int aux= *valor1;
        *valor1=*valor2;
        *valor2=aux;
    }
}



/*struct pelicula...tipo de dato que vas a recibir....le das un nombre como le vas a llamar a la funcion*/

int consulta_peli(struct pelicula movie)
{
    int i,x;
    for(i=0;i<30;i++)
    {
        return pelicula;
    }
    printf("Ingresa el ID de la pelicula que deceas consultar");
    scanf("%d",&x);
    while(x==cartelera[i].movie.idPelicula)
    {
        return horario
        ;
    }
}

void baja_peli()
{
    printf("Se eliminara una Pelicula");
    printf("Ingrese el ID de la pelicula a eliminar");
    scanf("%d",&x);
    for(i=0;i>x;i++)
    {
        i--;
        gets(cartelera[i].movie);
        gets(cartelera[i].alta_horario);
    }
}



