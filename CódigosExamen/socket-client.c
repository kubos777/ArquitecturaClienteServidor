#include <stdio.h>  //Biblioteca estándar de entrada y salida
#include <string.h> //Biblioteca estándar de C
#include <sys/socket.h> //Utilizamos esta biblioteca para sockaddr y len 
#include <sys/un.h> //Para poder usar sockaddr_un
#include <unistd.h> //Biblioteca para utilizar POSIX

void write_text (int socket_fd, const char* text)   //creamos la función para alamcenar parámetros
{						     //del mensaje que mandaremos al servidor
	int length = strlen (text) + 1;		     //primero capturamos la longitud del mensaje
	write (socket_fd, &length, sizeof (length)); //apartamos la memoria necesaria
	write (socket_fd, text, length); 	     //y tenemos los parámetros necesarios
}

int main (int argc, char* const argv[]) //creamos la función para el envio del mensaje
{			
	const char* const socket_name = argv[1]; //tenemos un apuntador para el socket
	const char* const message = argv[2];	 //y uno mas para el mensaje
	int socket_fd; //creamos el file descriptor 
	struct sockaddr_un name; //almacenamos las direcciones 
	socket_fd = socket (PF_LOCAL, SOCK_STREAM, 0); //socket devolvera al file descriptor
	
	name.sun_family = AF_LOCAL; //inicializamos sun_family
	strcpy (name.sun_path, socket_name); //inicializamos sun_path con el nombre del archivo
	connect (socket_fd, (struct sockaddr *)&name, SUN_LEN (&name)); //conectamos el socket con los argumentos
	write_text (socket_fd, message);				//file descriptor, esrructura y longitud
	close (socket_fd);						//escribe el mensaje y finaliza el proceso
	return 0;
}
