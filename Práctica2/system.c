#include <stdio.h>
#include <stdlib.h>

int main ()
{
	int return_value;
	int return_value2;
	
	return_value = system ("ls -l /");
	return_value2 = system ("pwd");
	
	//Si el valor de la cadena es NULL devuelve un valor diferente de 0
	//Si el valor de la cadena es diferente de NULL devuelve 0
	printf("Primer valor devuelto=%d\n", return_value);
	printf("Segundo valor devuelto=%d\n", return_value2);
	return 0;
}