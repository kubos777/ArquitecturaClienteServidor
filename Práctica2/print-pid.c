#include<stdio.h>
#include<unistd.h>  //Declara funciones que son parte del estándar POSIX

int main()
{

  //El id del proceso padre no cambia, es el id de la terminal en la que se esta ejecutando
  printf("El id del proceso padre es %d\n", getppid());
  //El id del proceso hijo cambia porque es un nuevo proceso cada que se ejecuta.
  printf("El id del proceso hijo es: %d\n", getpid());
  
  return 0;
}