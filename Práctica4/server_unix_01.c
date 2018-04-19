#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
/*
Pasos: Crear el socket y nombrar el socket
*/
int main()
{
 // Este es el descriptor de archivo o file descriptor
 // que se le asignara el valor devuelto por la funcion socket
 int socket_fd;

 // Creamos el socket
 // la funcion socket devuelve un int que es el file descriptor
 // socket_fd es el file descriptor
 
 socket_fd = socket (AF_UNIX, SOCK_STREAM, 0);

 // Una variable de tipo struct sockaddr_un
 // que sera nuestra estructura server socket
 struct sockaddr_un servidor;

 // Un apuntador a la variable anterior
 struct sockaddr* pservidor = (struct sockaddr*)&servidor;

 // Este int almacenara el size de la estructura
 // sockaddr_un que es nuestra estructura server socket
 int size_servidor = sizeof(servidor);

 // El archivo con el que se nombrara al socket
 // el archivo no debe existir y se creara con size 0
 const char* const socket_name = "/tmp/socket";

 // Inicializamos el atributo sun_family de la struct
 servidor.sun_family = AF_UNIX;

 // Inicializamos el atributo sun_path con el nombre del archivo
 //stringcopy
 strcpy(servidor.sun_path, socket_name);

 bind(socket_fd,pservidor,size_servidor);
 sleep(10);
 close(socket_fd);
 unlink(socket_name);

return 0;
}