import sys,socket,time
from cifrado import cifrar,descifrar,vectorInicial

def iniciarCliente(ip,puerto,llave,vectorInicial):
	'''Esta función inicializa el cliente TCP para conectarse con el servidor en la ip:puerto indicado, además
	   de que cifra con AES los mensajes utilizando la llave key.'''
	try:
		s=socket.socket()
		s.connect((ip,puerto))
		print('(____  \\                          (_______|_______)/ _____)')
		print(' ____)  )_____ ____   ____ ___     _______ _      ( (____  ')
		print('|  __  ((____ |  _ \\ / ___) _ \\   |  ___  | |      \\____ \\ ')
		print('| |__)  ) ___ | | | ( (__| |_| |  | |   | | |_____ _____) )')
		print('|______/\\_____|_| |_|\\____)___/   |_|   |_|\\______|______/ ')

		print("Bienvenido al cajero del banco ACS, "+socket.gethostname()+" conexión exitosa.")  
		print("\t***OPCIONES DISPONIBLES---\n1. CONSULTAR\n2. DEPOSITAR\n3. RETIRAR\n4. SALIR\nNOTA: Debe consultar su saldo antes de poder depositar o retirar\n")

		while True:  
			mensaje=input("λ- ")
			if mensaje=="SALIR":
				print("Terminando servicios...") 
				time.sleep(1)
				s.send(cifrar(llave,mensaje,vectorInicial)) 
				time.sleep(1)
				print("Vuelve pronto!")
				break 
			elif mensaje=="":
				#Evitar mandar un mensaje vacio, en TCP se interpreta como un peer disconect
				continue
			else:
				s.send(cifrar(llave,mensaje,vectorInicial)) 
			recibido=descifrar(llave,s.recv(1024),vectorInicial)
			if recibido=="":
				print("Terminando servicios...") 
				time.sleep(1)
				print("Vuelve pronto!")
				break
			else:
				print("# "+recibido)   
	except socket.error as se:
		print("Imposible conectar con el servidor\n Motivo: %s\n Finalizando ejecución..." % se)
		sys.exit(1)
	except ValueError as ve:
		print("Error con la llave, para el cifrado AES la llave debe ser de  16, 24, o 32 bytes.\n",ve)
		sys.exit(1)
	finally:
		print("Cerrando la conexión....")
		s.close()

if __name__ == '__main__':
	#Esta parte solo se ejecuta cuando se manda a ejecutar directamente el modulo desde línea de comandos
	if len(sys.argv)<4:
		print("Forma de correr el cliente:\n $python clienteCajero.py [ip] [puerto] [llave]\n Nota: Recuerda que la llave debe de ser minimo de 16 bytes.")
	else:
		iniciarCliente(sys.argv[1],int(sys.argv[2]),sys.argv[3],vectorInicial)