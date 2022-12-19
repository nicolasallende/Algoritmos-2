

def incializando_programa(lista_param,grafo):
	"""Inicializa el programa haciendo las correspondientes validaciones"""
	if len(lista_param) != 2:
		print("La cantidad de parametros que ingreso es incorrecta")
		return []

	if not lista_param[0].isdigit() or not lista_param[1].isdigit():
		print("Parmetros incorrectos.")
		return

	vertice,n = lista_param[0],int(lista_param[1])

	if not grafo.vertice_existe(vertice):
		print("El usuario que ingreso no existe.")
		return []

	if n > grafo.cantidad_vertices(): 
		print("La cantidad de usuarios similares es mayor a la cantidad de usuarios.")
		return [] 

	return [vertice,n]

def incializando_programa_camino(lista_param,grafo):
	# si habia una "," en el 1er parametro, lo saca. Sino no habia no hace nada.
	if len(lista_param) != 2:
		print("La cantidad de parametros que ingreso es incorrecta")
		return []

	if not lista_param[0].isdigit() or not lista_param[1].isdigit():
		print("Parmetros incorrectos.Los dos no son numeros.")
		return []

	if not grafo.vertice_existe(lista_param[0]) or not grafo.vertice_existe(lista_param[1]):
		print("ERROR.Ingreso de parametros incorrecto.Ususario/s inexistente/s")
		return []
	
	return lista_param

def inicializando_programa_distancias(lista_param,grafo):
	if len(lista_param) != 1:
		print("La cantidad de parametros que ingreso es incorrecta")
		return []

	if not lista_param[0].isdigit():
		print("El parametro que ingreso no es un numero entero.")
		return []
	
	if not grafo.vertice_existe(lista_param[0]):
		print("El usuario que ingreso no existe")
		return []

	return lista_param
