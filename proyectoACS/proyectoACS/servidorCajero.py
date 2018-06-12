import sys,socket,re,time
from cifrado import cifrar,descifrar,vectorInicial  

def consultar(nombreArchivo):
	'''Función que permite realizar la
	   consulta los datos del cliente, 
	   regresa una cadena con el contenido del archivo.'''

	contenido="No hay información del cliente."
	
	try:
		#Manejador de contexto el cual
		#se encarga de cerrar el archivo al finalizar el bloque.
		with open(nombreArchivo, "r") as f:
			contenido=f.read()
	except IOError as ioe:
		print("Ocurrió un error de E/S por: ",ioe)
	except OSError as ose:
		print("Ocurrió un error de permisos: ",ose)
	return contenido

def transaccion(nombreArchivo,monto,tipoTrans):
	'''Función que permite realizar un deposito o un retiro(si hay suficiente),
	   modifica el archivo del cliente.'''
	try:
		with open(nombreArchivo,"r+") as f:
			datos=f.readlines()
			if tipoTrans == "depositar":
				datos[2] = str(float(datos[2])+monto)
			elif tipoTrans=="retiro" and float(datos[2])>=monto:
				datos[2] = str(float(datos[2])-monto)
			else:
				return "No hay fondos suficientes, transacción no realizada!"
			f.seek(0)
			f.truncate()
			f.writelines(datos)
		return "La transacción se realizó con éxito!"
	except IOError as ioe:
		print("Ocurrió un error de E/S por: ",ioe)
	except OSError as ose:
		print("Ocurrió un error de permisos: ",ose)
	return "No se ha podido realizar la transacción"

def iniciarServidor(ip,puerto,llave,vectorInicial):
	''' Esta función inicializa el servidor TCP para empezar a escuchar 
	    en la ip:puerto indicado, además
		de que cifra con AES los mensajes utilizando la llave key. '''
	try:
		s=socket.socket()   
		s.bind((ip,puerto))  
		s.listen(1)
		print('(____  \\                          (_______|_______)/ _____)')
		print(' ____)  )_____ ____   ____ ___     _______ _      ( (____  ')
		print('|  __  ((____ |  _ \\ / ___) _ \\   |  ___  | |      \\____ \\ ')
		print('| |__)  ) ___ | | | ( (__| |_| |  | |   | | |_____ _____) )')
		print('|______/\\_____|_| |_|\\____)___/   |_|   |_|\\______|______/ ')
		print("Cajero del ACS, atiende: "+socket.gethostname()+" en escucha, esperando conexión...")  
		sc,addr=s.accept() 
		print("El cliente: ",addr," se ha conectado.") 
		estadoConsultado=False

		nombreArchivo=llave 
		print(nombreArchivo)
		while True:  
			recibido=sc.recv(1024)
			print("Contenido cifrado: ",recibido)
			recibido=descifrar(llave,recibido,vectorInicial)  
			if recibido=="SALIR":
				print("Ejecución finalizada...")
				sys.exit(0)
			elif re.match(r'CONSULTAR', recibido):
				inform="Información de la cuenta: \n"+consultar(nombreArchivo)
				print("Consultando el servidor...")
				time.sleep(1)
				print("Consultando el servidor...")
				time.sleep(1)
				print("Consultando el servidor...")
				sc.send(cifrar(llave,inform,vectorInicial))
				estadoConsultado = True 
			elif re.match(r'^DEPOSITAR \d+(\.\d{1,2})?$',recibido) and estadoConsultado:
				monto=float(re.split(r'(\d+\.?\d*)',recibido)[1])
				print("Cantidad a depositar: ",monto)
				inform = transaccion(nombreArchivo,monto,"depositar")
				print("Realizando transacción...")
				time.sleep(1)
				print("Realizando transacción...")
				time.sleep(1)
				sc.send(cifrar(llave,inform,vectorInicial))
				print("Transacción realizada con éxito")
				
			elif re.match(r'^RETIRAR \d+(\.\d{1,2})?$',recibido) and estadoConsultado:
				monto=float(re.split(r'(\d+\.?\d*)',recibido)[1])
				print("Cantidad a retirar: ",monto)
				inform=transaccion(nombreArchivo,monto,"retiro")
				sc.send(cifrar(llave,inform,vectorInicial))
			else:
				print("Comando inválido: ",recibido)
				sc.send(cifrar(llave,"\t***OPCIONES DISPONIBLES***\n1. CONSULTAR\n2. DEPOSITAR\n3. RETIRAR\n4. SALIR\nNOTA: Debe consultar su saldo antes de poder depositar o retirar\n",vectorInicial))
			print("Cliente "+socket.gethostname()+":", recibido)
	except socket.error as se:
		print("No fue posible levantar el servidor\n Motivo: %s\n Finalizando ejecución..." % se)
		sys.exit(1)
	except ValueError as ve:
		print("Error con la llave, para el cifrado AES la llave debe ser de  16, 24, o 32 bytes.",ve)
		sys.exit(1)
	finally:
		print("Cerrando la conexión....")
		sc.close()  
		s.close()

if __name__ == '__main__':
	#Esta parte solo se ejecuta cuando se manda a ejecutar directamente el modulo desde línea de comandos
	if len(sys.argv)<4:
		print("El uso del servidor es el siguente:\n $python servidorCajero.py [ip] [puerto] [llave]")
	else:
		iniciarServidor(sys.argv[1],int(sys.argv[2]),sys.argv[3],vectorInicial)