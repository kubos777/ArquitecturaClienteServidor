#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main ()
{
	pid_t child_pid;
	/*Creamos el proceso hijo*/
	child_pid = fork ();
	if (child_pid > 0) {
	/* El padre se pone a dormir*/
		sleep (60);
	}else {
	/* El proceso hijo sale inmediatamente*/
		exit (0);
	}
	return 0;
}