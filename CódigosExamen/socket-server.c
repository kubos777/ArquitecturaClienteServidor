#include <stdio.h> //Biblioteca estándar de entrada y salida
#include <stdlib.h> //Biblioteca estándar de C
#include <string.h> //Biblioteca para el manejo de cadenas
#include <sys/socket.h> //Biblioteca para manejar sockets
#include <sys/un.h> //Biblioteca para manejar las familias de sockets
#include <unistd.h> //Biblioteca para utilizar POSIX
#define p printf //Definimos la letra p como si fuera un printf

int server(int client_socket){ //Se declara una función que recibe el socket cliente
	while(1){ //Entramos a un ciclo infinito
		int length; //Variable para el tamaño del mensaje
		char* text; //Apuntador donde se guardará el mensaje
		if(read(client_socket,&length,sizeof(length)) == 0){ /*Si la lectura del cliente
		es igual a cero, es decir no hay cadena, regresa un cero y no sale.*/
			return 0;
			}
		text = (char*) malloc (length); //Se reserva la memoria para el mensaje
		read(client_socket,text,length); // Se lee del socket el mensaje y su tamaño
		//sleep(2);
		p("%s\n",text); //Se muestra en pantalla el mensaje
		int cmp = strcmp(text,"quit"); /*Se guarda en una variable la comparación entre
		el texto y la palabra "quit"*/
		if(!cmp){ /*Si el mensaje no es igual a quit se cicla nuevamente, 
			en caso contrario sale del ciclo*/
			return 1;
	}
	}
} 


int main(int argc, char* const argv[]){

	int socket_fd; //File descriptor para el socket servidor
	
	struct sockaddr_un name; //Estructura socket servidor

	int client_sent_quit_message; /*Variable que almacena el 1 o 0 
	regresado por la función server*/
	
	//Cadena que almacena el nombre del socket
	const char* const socket_name = argv[1];

	socket_fd = socket(AF_UNIX,SOCK_STREAM,0); //Se crea el socket AF_UNIX
 	//Se inicializa el atributo sun_family de la struct
	name.sun_family = AF_UNIX;
	
	//Se inicializa el atributo sun_path con el nombre del archivo
	strcpy(name.sun_path,socket_name);
	//Se asocia el socket al archivo, para que sea un socket nombrado
	bind(socket_fd,(struct sockaddr *)&name,SUN_LEN (&name));
	//Se pone al servidor a escuchar conexiones entrantes de un cliente
	listen(socket_fd,1);
	//Ciclo infinito para recibir mensajes
	do{
		//Estructura para el socket cliente
		struct sockaddr_un client_name;
		//Variable para el tamaño del mensaje del cliente
		socklen_t client_name_len;
		//File descriptor del socket cliente
		int client_socket_fd;
		//El servidor acepta la conexión del cliente
		client_socket_fd = accept(socket_fd,(struct sockaddr *)&client_name,&client_name_len);
		//Se guarda el valor de retorno de la función server
		client_sent_quit_message = server(client_socket_fd);
		//Se cierra el file descriptor del socket servidor
		//close(socket_fd);
	}while(!client_sent_quit_message); //Mientras el valor de retorno sea falso, seguira
	//dentro del ciclo

//Se cierra el file descriptor del socket servidor
	close(socket_fd);
	//Se desliga el archivo del socket servidor
	unlink(socket_name);
	//Buena ejecución 
	return 0;
}