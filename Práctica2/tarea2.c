#include <stdio.h>
#include <unistd.h>
/*Programa que crea dos procesos: Uno realiza una cuenta del 0 al 10 y el otro del 10 al 0*/
int main ()
{
    //Variable para identificar al proceso hijo
    pid_t id_hijo;
    //Creamos el proceso hijo
    id_hijo = fork ();
    //Variable para el padre
    int i=0;
    //Variable para el hijo
    int j=10;
    if( id_hijo != 0 )
    {
        for(i;i<=10;i++){
            printf("Padre contando: %d\n",i);
        }
    }
    else
    {
        for(j;j>=0;j--){
            printf("Hijo contando: %d\n",j);
        }
    }
    return 0;
}
