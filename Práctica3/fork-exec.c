#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int spawn (char* program, char** arg_list)
{
	pid_t child_pid;
	/* Creamos el proceso hijo */
	child_pid = fork ();
	//sleep(5);
	if (child_pid != 0) /*Proceso padre*/
		return child_pid;
	else {
		/*Se ejecuta el programa, buscando en la ruta dicha. */
		execvp (program, arg_list);
		/*  La función execvp manda error solamente si ocurre*/
		fprintf (stderr, "Ha ocurrido un error en execvp\n");
		abort ();
	}
}

int main ()
{
	int child_status;
	/* Pasamos "ls" a la lista de argumentos como comando.*/
	char* arg_list[] = {
		"ls", /* argv[0], El nombre del programa*/
		"-l",
		"/",
		NULL /*  El fin del arreglo debe terminar con NULL. */
	};
	/* El proceso hijo llama a la función spawn corriendo el comando "ls".
	Ignora el process ID que regreso el hijo*/
	spawn ("ls", arg_list);
	/* El padre espera a que termine el proceso padre para terminar
	en comparación con el de la práctica 2 que el padre moría antes que el hijo.*/
	wait (&child_status);
	//Esperamos 10 segundos
	//sleep(2);
	printf("%d\n",child_status);
	if (WIFEXITED (child_status))
		printf ("El proceso hijo ha terminado con éxito, con exit code:  %d\n", WEXITSTATUS (child_status));
	else
		printf ("El proceso hijo terminó anormalmente\n");
	return 0;
}
