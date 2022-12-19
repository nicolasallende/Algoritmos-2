from datetime import datetime

def cargar_datos_grafo(nombre_arch,grafo):
	with open(nombre_arch,"r") as arch:
		for linea in arch:
			if( linea[0] == "#" ):
				continue 
			cad_vertice1,cad_vertice2 = linea.rstrip("\n").split("	")
			grafo.agregar_vertice(cad_vertice1)
			grafo.agregar_vertice(cad_vertice2)
			grafo.agregar_arista(cad_vertice1,cad_vertice2)

def imprimir_lista_de_mayor_a_menor(lista,largo):
	"""Imprime la lista de semejantes"""
	for pos in range(largo,0,-1):
		print(lista[pos-1][1],end = " ")
	print()

def tiempo_de_ejecucion(inicial = None,final = False): 
	if inicial is None:
		inicial = datetime.now()
		return inicial
	if final: 
		final = datetime.now()

	tiempo_estimado = final - inicial if inicial and final else None 
	if tiempo_estimado:  
		if int(tiempo_estimado.seconds) > 60:
			# print("El programa tardo en correr {} minutos.".format(int(tiempo_estimado.seconds)/ 60) )
			print( "El programa tardo en correr {} segundos.".format(tiempo_estimado.seconds) )
		else:
			print( "El programa tardo en correr {} segundos.".format(tiempo_estimado.seconds) )
