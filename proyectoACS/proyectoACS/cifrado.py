from Crypto.Cipher import AES

#Vector de inicialización, debe ser el mismo para encriptar y desencriptar
vectorInicial="IVV's12345667890"

def cifrar(llave,mensaje,vectorInicial):
	'''Función que nos permite cifrar con una llave de 16, 32 o 64 bytes'''
	suiteParaCifrar = AES.new(llave, AES.MODE_CFB, vectorInicial)
	mensajeAcifrar = suiteParaCifrar.encrypt(mensaje)
	return mensajeAcifrar

def descifrar(llave,mensajeCifrado,vectorInicial):
	'''Función que nos permite descifrar con una llave de 16, 32 o 64 bytes'''
	suiteParaDescifrar = AES.new(llave, AES.MODE_CFB, vectorInicial)
	mensajeAdescifrar = suiteParaDescifrar.decrypt(mensajeCifrado)
	
	return mensajeAdescifrar.decode("UTF-8")

if __name__ == '__main__':
	#Probando el modulo de cifrado para implementarlo, esto no se importa al importarlo 
	#en otro script

	suiteParaCifrar = AES.new('Llave de 16 bits', AES.MODE_CFB, 'Vector de inicia')
	textoAcifrar = suiteParaCifrar.encrypt("Probando los cifrados...")
	
	print(textoAcifrar)

	suiteParaDescifrar = AES.new('Llave de 16 bits', AES.MODE_CFB, 'Vector de inicia')
	textoDescifrado=suiteParaDescifrar.decrypt(textoAcifrar)
	print(textoDescifrado.decode("UTF-8"))