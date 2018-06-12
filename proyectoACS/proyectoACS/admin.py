###################################
#Generador de llaves del banco ACS#
###################################


print('Bienvenido al generador de llaves del banco ACS')
print('Para generar su llave, ingrese los siguientes datos: \n')

nombre = input('Nombre: ')
numeroCuenta = int(input('Número de cuenta: '))
saldo = 0.0

nombreArchivo = 'keyacss'+str(numeroCuenta)

llave = open(nombreArchivo,'w+')

llave.write(nombre+'\n')
llave.write(str(numeroCuenta)+'\n')
llave.write(str(saldo))
