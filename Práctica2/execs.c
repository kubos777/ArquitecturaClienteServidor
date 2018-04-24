#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(){
	//Proceso inicial
	char *args[]={"/bin/ls", NULL};
	
	//Sintaxis de execve(arg1,{arg1,NULL},NULL)
	//El -1 indica que hubo error
	if(execve("/bin/ls", args, NULL) == -1){
	
	//Manda la cadena a stderr en caso de error
	perror("execv");

	exit(EXIT_FAILURE);
	} 
	//Esto nunca se va a imprimir,porque execv muere
	//al terminar de ejecutar un comando	
	puts("No deberiais estar aqui");

	exit(EXIT_SUCCESS);
}