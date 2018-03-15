#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

main()
{
 // este es el descriptor de archivo o file descriptor
 // para el socket cliente
 // se le asignara el valor devuelto por la funcion socket
 int socket_fd;

 // creamos el socket
 // la funcion socket devuelve un int que es el file descriptor
 socket_fd = socket (AF_UNIX, SOCK_STREAM, 0);

 // una variable de tipo struct sockaddr_un
 // que sera nuestra estructura socket cliente
 struct sockaddr_un cliente;

 // un apuntador a la variable anterior
 struct sockaddr* pcliente = (struct sockaddr*)&cliente;

 // este int almacenara el size de la estructura
 // sockaddr_un que es nuestra estructura socket cliente
 int size_cliente = sizeof(cliente);

 // el archivo con el que se nombro al socket del servidor
 const char* const socket_name = "/tmp/socket";

 // inicializamos el atributo sun_family de la struct
 cliente.sun_family = AF_UNIX;

 // inicializamos el atributo sun_path con el nombre del archivo
 strcpy( cliente.sun_path, socket_name );

 // Hacemos la peticion de conexion al servidor
 int result = connect( socket_fd, pcliente, size_cliente);

 if(result==-1){
 printf("connect devolvió: %d  porque el servidor no esta funcionando!\n", result);	
 }
 else{
 	printf("connect devolvió: %d \n", result);

 }
 if( result == 0 )
 {
  printf("Enviaré el mensaje \"Hola papu\" al servidor.\n");
  const char* const mensaje = "Hola papu";
  int longitud = strlen( mensaje ) + 1;
  //write para escribir al socket, es un flujo de salida
  //lee la longitud, a través de su file descriptor
  write ( socket_fd, &longitud, sizeof(longitud) );
  //Este write es el mensaje
  write ( socket_fd, mensaje, longitud );
 }
 //Se ciera el file descriptor del cliente
 close( socket_fd );
 exit(0);
 
}