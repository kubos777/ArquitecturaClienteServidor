#include <stdio.h>
#include <unistd.h>

main ()
{
    pid_t id_hijo;
    //Con getpid() obtenemos el id del proceso main
    printf( "1: El ID del proceso main es %d\n", getpid() );
    //Aquí se crea el proceso hijo
    id_hijo = fork ();
    printf( "2: Este printf saldra duplicado\n");
    printf( "3: El id del proceso hijo es %d\n", id_hijo );
}