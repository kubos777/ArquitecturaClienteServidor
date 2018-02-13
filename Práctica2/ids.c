#include <stdio.h>
#include<unistd.h>  //Declara funciones que son parte del estándar POSIX
#define p printf

int main()
{
	p("ID de usuario real: %d\n",getuid());
	p("ID de usuario efectivo: %d\n",geteuid());
	p("ID de grupo real: %d\n",getgid());
	p("ID de grupo efectivo: %d\n",getegid());
	return 0;	
}
