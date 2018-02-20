#include <stdio.h>
#include <unistd.h>

int main ()
{
    pid_t id_hijo;
    printf( "1: El ID del proceso main es %d\n", getpid() );
    id_hijo = fork ();
    printf( "2: Este printf saldra duplicado\n");
    printf( "3: El ID del proceso hijo es %d\n", id_hijo );
    if( id_hijo != 0 )
    {
        printf( "\n PADRE:proceso main con id %d\n", getpid());
        printf( " PADRE: ID del hijo es %d\n", id_hijo );
        //EL id del abuelo, es decir la shell 
        printf( " PADRE: ID del padre del padre %d\n",getppid());
    }
    else
    {
        printf( "\n HIJO:proceso hijo con id %d\n", getpid() );
        printf( " HIJO: ID del hijo es %d\n", id_hijo );
        printf( " HIJO: ID del padre es %d\n", getppid() );
        //A veces aquí el ID del padre da 1 porque se quedó huerfáno el proceso
        //ya que el padre murió y es adoptado por el proceso init que tiene el PID=1
    }
    return 0;
}
