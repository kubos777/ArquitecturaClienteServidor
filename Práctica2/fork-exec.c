#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
//program es una cadena, arg_list es un arreglo de caractreres
int spawn (char* program, char** arg_list)
{
	pid_t child_pid;
	child_pid = fork ();
	if (child_pid != 0) /* Proceso padre. */
		return child_pid;
	else {
		/* Se ejecuta el programa, buscando en la ruta dicha. */
		execvp (program, arg_list);
		/* La función execvp manda error solamente si ocurre*/
		fprintf (stderr, "Ha ocurrido un error en execvp\n");
		//abort es como un suicidio, porque el proceso manda una señal para morir
		abort ();
	}
}

int main ()
{
	/* Pasamos "ls" a la lista de argumentos como comando. */
	char* arg_list[] = {
		"ls", /* argv[0], el nombre del programa. */
		"-l",  
		"/",
		NULL /* El fin del arreglo debe terminar con NULL. */
	};
	/*El proceso hijo llama a la función spawn corriendo el comando "ls".
	Ignora el process ID que regreso el hijo*/
	spawn ("ls", arg_list);
	//Esta frase la imprime el padre
	printf ("Hecho con el programa principal: \n");
	return 0;
}
