#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
int main()
{
 pid_t pid;
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
 
 //El padre se salta el if y llega aquí, se duerme 10 segundos
 sleep(10);
 printf("PADRE getpid()= %d. Terminacion del proceso hijo: getpid()= %d\n",getpid(), pid);
 //Señal 15
 //kill (pid,SIGTERM);
 kill(pid,SIGKILL);
 exit(0);

}
