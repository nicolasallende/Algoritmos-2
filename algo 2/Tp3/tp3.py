import sys 
from grafo import Grafo
from utilidades import cargar_datos_grafo
from comandos import parecidos
from comandos import camino
from comandos import centralidad
from comandos import distancias
from comandos import estadisticas
from comandos import comunidades 

# with open("comandos.txt","w") as arch:
# 	arch.writelines("similares 5 4\n")
# 	arch.writelines("recomenadar 12 2\n")
# 	arch.writelines("camino 12 431274\n")
# 	arch.writelines("centralidad 20\n")
# 	arch.writelines("distancias 124\n")
# 	arch.writelines("estadisticas\n")
# 	arch.writelines("comunidades\n")

def main(lista_param):
	"""Programa ppal"""
	print("\nBienvenido a la aplicacion")
	print("Ingrese el comando correspondiente o 'salir' ")
	grafo = Grafo()

	if len(lista_param) != 1 or not ".txt" in lista_param[0]:
		print("Parametro/s incorrecto/s")
		return 

	linea_entrada = sys.stdin.readline().rstrip("\n").replace(",","")
	if linea_entrada.lower() == "salir":
		return 		

	nombre_arch = lista_param[0]
	print("Espere mientras el programa esta iniciando.....")
	cargar_datos_grafo(nombre_arch,grafo)
	print("El programa ya esta listo para procesar su pedido.")
	# se la carga una sola vez.
	es_valido = False
	while linea_entrada and not es_valido:

		lista_param = linea_entrada.split(" ")
		nombre_comando = lista_param[0]		
		if len(lista_param) == 3 :
			if nombre_comando.lower() == "similares" :
				parecidos(lista_param[1:],grafo)
			elif nombre_comando.lower() == "recomendar" :
				parecidos(lista_param[1:],grafo,True)
			elif  nombre_comando.lower() == "camino":
				camino(lista_param[1:],grafo)
			else:
				print("Incorrecto.El nombre del comando ingresado no existe")
		
		if len(lista_param) == 2:
			if nombre_comando.lower() == "centralidad" :
				centralidad(lista_param[1:],grafo)
			elif nombre_comando.lower() == "distancias" :
				distancias(lista_param[1:],grafo)
			else:
				print("Incorrecto.El nombre del comando ingresado no existe")

		if len(lista_param) == 1:
			if nombre_comando.lower() == "estadisticas":
				estadisticas(grafo)
			elif nombre_comando.lower() == "comunidades":
				comunidades(grafo)
			elif nombre_comando.lower() == "salir":
				es_valido = True
				continue
			else:
				print("Incorrecto.El nombre del comando ingresado no existe")

		print("\nIngrese un nuevo comando o 'salir': \n")
		linea_entrada = sys.stdin.readline().rstrip("\n").replace(",","")

if __name__ == '__main__':
	main(sys.argv[1:])
