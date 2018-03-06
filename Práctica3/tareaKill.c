/* Usando el código de kill.c, crear otro proceso hijo e indicar qué es lo que pasa con el
programa, modificar el proceso creado anterior para que después de 20 segundos termine su
ejecución.*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
int main()
{
 pid_t pid;
 pid_t pid2;
 //Se llama a la función fork
 //fork devuelve el pid del proceso creado
 //pid !=0 es el PADRE
 //pid =0 es el HIJO
 if (( pid = fork()) == 0) {
   while(1) {
     printf("HIJO PID = %d, getpid()=%d\n", pid,getpid());
     sleep(1);
   }
 }
 if (( pid2 = fork()) == 0) {
  while(1) {
    printf("HIJO PID = %d, getpid()=%d\n", pid,getpid());
    sleep(1);
  }
 }

 //El padre se salta el if y llega aquí, se duerme 10 segundos
 sleep(10);
 printf("PADRE getpid()= %d. Terminacion del proceso hijo: getpid()= %d\n",getpid(), pid);
 //Señal 15
 //kill (pid,SIGTERM);
 kill(pid,SIGKILL);
 sleep(10);
 printf("PADRE getpid()= %d. Terminacion del proceso hijo: getpid()= %d\n",getpid(), pid2);
 kill(pid2,SIGKILL);



 exit(0);

}
