/*Programa que hace un echo de las cadenas de texto que se le pasen como argumentos*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int j;
	for (j = 0; j < argc; j++){
		printf("argv[%d]:%s\n",j,argv[j]);
	}
	exit(EXIT_SUCCESS);
}