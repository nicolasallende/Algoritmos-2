from utilidades import imprimir_lista_de_mayor_a_menor
#fin de Import's generales. 
from validaciones import incializando_programa
#fin Import's de recomendos y similares
from validaciones import incializando_programa_camino
from recorridos import recorrido_particular_bfs
from recorridos import random_walk_bis
from random import choice
#fin Import's de camino
from TDA import Heap
from recorridos import random_walk
from random import randrange
#fin Import's de centralidad
from validaciones import inicializando_programa_distancias
from recorridos import bfs_visitar
from TDA import Cola
#fin Import's de distancias
#Estadisticas no hace Import's.
from random import shuffle
#fin Import's de comunidades


#INICIO DE COMANDO SIMILARES Y RECOMENDAR---------------------------------------------------------

def contar_similitudes(dicc_ady_vertice,lista_de_vertice2):
	"""Cuenta la cantidad de similitudes viendo cuantos elementos de la listas de ady tiene en comun"""
	cant_similitud = 0
	for vertice_ady in lista_de_vertice2:
		if vertice_ady in dicc_ady_vertice:
			cant_similitud += 1
	return cant_similitud


def obtener_lista_semejantes(grafo,vertice,largo,dicc_ady_vertice,es_recomendado = False):
	"""obtiene la lista de semejantes"""
	heap = Heap()
	lista_de_vertices = grafo.obtener_todos_los_vertices()[:] #es una copia de la lista de vertices.
	lista_de_vertices.remove( vertice )
	for otro_vertice in lista_de_vertices:
		lista_ady_otro_vertice = grafo.obtener_adyacentes_a_vertice(otro_vertice)[:] #copia de la lista de ady.
		if es_recomendado and otro_vertice in dicc_ady_vertice:
			continue
		cant_similitud = contar_similitudes(dicc_ady_vertice,lista_ady_otro_vertice)
		if( len(heap) < largo ):
			heap.encolar( cant_similitud,otro_vertice )
		else:
			min_elem = heap.ver_min()[0]
			if cant_similitud > min_elem :
				heap.desencolar()
				heap.encolar(cant_similitud,otro_vertice)

	return [ heap.desencolar() for i in range(0,largo) ]


def parecidos(lista_param,grafo,es_recomendado = False):
	"""Dado un usuario, encuentra los personajes más similares a este pero sin tenerlo como adyacente
	Pre: el id del usuario y el la cantidad de usuarios semejantes son pasados por parametro.
	Post: Devuelve pos salida estandar los usuarios ord de > a < en ord de cant de similtudes """
	lista = incializando_programa(lista_param,grafo)
	if len(lista) == 0:
		return
	vertice,n = lista[0],lista[1] 

	lista_ady_vertice = grafo.obtener_adyacentes_a_vertice(vertice)
	dicc_ady_vertice = dict.fromkeys(lista_ady_vertice)
	#Reduce los costos de operaciones contar similitudes si es un dicc.

	lista_parecidos = obtener_lista_semejantes(grafo,vertice,n,dicc_ady_vertice,es_recomendado)
	imprimir_lista_de_mayor_a_menor(lista_parecidos,n)

#FIN DE COMANDO SIMILARES Y RECOMENDADOS---------------------------------------------------------


#INICIO DE COMANDO CAMINO------------------------------------------------------------------------

#DECLARACION DE CTES.
CANT_CAMINOS = 100000 #con 1.000.000 de cantidad se logra que sea estable.
CANT_PARAM = 2
SEP = ","

def obtener_recorridos(grafo,n,vertice,vertice_fin):
	dicc_recorridos = {}
	for	i in range(0,CANT_CAMINOS):
		recorrido = random_walk_bis(grafo,n,vertice,vertice_fin)
		cad_recorrrido = " ".join(recorrido) 
		if not cad_recorrrido in dicc_recorridos:
			if recorrido[ len(recorrido)-1 ] == vertice_fin:
				dicc_recorridos[cad_recorrrido] = len(recorrido)
			else:
				# si llego aca es porque el ultimo no es vertice fin, con lo cual es < a n.
				if vertice_fin in recorrido:
					posible_recorrido = recorrido[:recorrido.index(vertice_fin)+1]
					dicc_recorridos[" ".join(posible_recorrido)] = len(posible_recorrido)

	lista_de_recorridos = []
	for cad_recorrrido,largo in dicc_recorridos.items():
		if largo <= n + 1:
			lista_de_recorridos.append( (largo, cad_recorrrido.split(" ") ) ) 
	return lista_de_recorridos


def obtener_camino_minimo(lista_de_recorridos,largo_de_recorrido):
	"""Devuelve el min contemplando  el caso en donde son todos los largos diferentes y cuando son iguales."""
	if len(lista_de_recorridos) == 1:
		return lista_de_recorridos[0]	
	mismo_largo = True 
	largo_min = lista_de_recorridos[0][0] #obtengo el largo del primer elemento de la tupla.
	for largo,recorrido in lista_de_recorridos:
		if largo_min != largo:
			mismo_largo = False
			break  
	#Contemplo el caso en donde todos pueden el mismo largo.
	if mismo_largo:
		return choice(lista_de_recorridos)
	return min(lista_de_recorridos)


def imprimir_camino_mas_corto(camino_minimo):
	"""Imprime por salida estandar el recorrido minimo"""
	for pos,vertice in enumerate(camino_minimo):
		if pos < len(camino_minimo)-1 : 
			print( camino_minimo[pos],end = "->" )
		else:
			print( camino_minimo[pos])
	print()


def camino(lista_param,grafo):
	"""Busca el camino más corto de un usuario a otro """
	if len(lista_param) < CANT_PARAM:
		print("La cantida de parametros no es la correcta ")
		return
	lista = incializando_programa_camino(lista_param,grafo)
	if len(lista) == 0:
		return

	vertice1,vertice2 = lista
	largo_de_recorrido =  recorrido_particular_bfs(grafo,vertice1,vertice2,True)
	# El True funciona como condicion de corte.

	if largo_de_recorrido == 0 or vertice1 == vertice2:
		print("No existe el recorrido que lleve de {} a {}".format(vertice1,vertice2) )
		return 

	lista_de_recorridos = []
	while len(lista_de_recorridos) == 0:
		lista_de_recorridos += obtener_recorridos(grafo,largo_de_recorrido,vertice1,vertice2)
	#haciendo esto me aseguro que por lo menos tenga una solucion, aunque pueda tardar más

	camino_min = obtener_camino_minimo(lista_de_recorridos,largo_de_recorrido) 
	imprimir_camino_mas_corto(camino_min[1]) 

#FIN DEL COMANDO CAMINOS---------------------------------------------------------------------------


#INICIO DE COMANDO CENTRALIDAD---------------------------------------------------------------------

#DECLARACION DE CONSTANTES
CANT_ITER = 500  
CANT_LARGO = 8000

def añadir_aparicion(vertice,dicc_de_apariciones):
	"""Añade al dicc de aparicion una aparicion si ya estaba o se agrega al dicc si no estaba."""
	if not vertice in dicc_de_apariciones:
		dicc_de_apariciones[vertice] = 1
	else:
		dicc_de_apariciones[vertice] += 1


def obtener_lista_de_vertices_centrales(grafo,largo):
	"""Pre:Debe pasarse por parametro el grafo y la cantidad de vertices que se espera obtener
	   Post:Devuelve una lista de los vertices mas centrales."""
	dicc_de_apariciones = {}
	lista_de_vertices = grafo.obtener_todos_los_vertices()[:] #copia de la lista de vertices

	for i in range(CANT_ITER):	
		pos_vertice = randrange( len(lista_de_vertices) )
		vertice = lista_de_vertices.pop(pos_vertice)

		recorrido = random_walk(grafo,CANT_LARGO,vertice) 
		anterior,actual = recorrido[0],recorrido[1] 
		añadir_aparicion(anterior,dicc_de_apariciones)
		añadir_aparicion(actual,dicc_de_apariciones)

		for pos in range(2,len(recorrido) ):
			prox_vertice = recorrido[pos] 
			if prox_vertice != anterior:
				añadir_aparicion(prox_vertice,dicc_de_apariciones)
			anterior = actual
			actual = prox_vertice

	heap = Heap()
	#Si llegue aca es porque tengo la cantidad de apariciones generales de todo.  
	for vertice,cant_apar in dicc_de_apariciones.items():
		if len(heap) < largo:
			heap.encolar( cant_apar,vertice )
		else:
			min_elem = heap.ver_min()[0]
			if cant_apar > min_elem :
				heap.desencolar()
				heap.encolar(cant_apar,vertice)

	return [ heap.desencolar() for i in range(0,largo) ]

def centralidad(lista_param,grafo):
	"""Obtiene los vertices centrales de la red e imprime la cantidad dada por entrada estandar"""
	if not lista_param[0].isdigit():
		print("ERROR.No escribio un numero valido")
		return 
	n = int(lista_param[0])
	lista_de_centrales = obtener_lista_de_vertices_centrales(grafo,n)
	imprimir_lista_de_mayor_a_menor(lista_de_centrales,n)

#FIN DEL COMANDO CENTRALIDAD-----------------------------------------------------------------------


#INICIO DE COMANDO DISTANCIAS----------------------------------------------------------------------

def imprimir_distancias_al_vertice(vertice,distancias):
	"""Imprime las distancias a los vertices."""
	print("\ndistancias {}".format(vertice))
	for v in distancias:
		print("Distancia {}: {}".format(v,distancias[v]))

def obtener_distancias(grafo,vertice):
	"""Obtiene las distancias a los vertices """ 
	visitados = {vertice : True}
	padre = {vertice : None}
	orden = {vertice : 0}
	distancias = {}
	bfs_visitar(grafo,vertice,visitados,padre,orden,None,False,distancias)
	return distancias

def distancias(lista_param,grafo):
	"""Pre: Debe recibir un vertice por paremetro
	   Post: Obtiene las distancias y cantidad de vertices a esa distancia, respecto de un vertice"""
	lista = inicializando_programa_distancias(lista_param,grafo) 
	if len(lista) == 0:
		return
	vertice = lista[0]
	distancias = obtener_distancias(grafo,vertice)
	imprimir_distancias_al_vertice(vertice,distancias)

#FIN DE COMANDO DISTANCIAS


#INICIO DE COMANDO ESTADISTICAS

def obtener_cantidad_aristas(grafo):
	"""Pre: Es necesario pasar al grafo por parametro
	   Post:Se obtiene la cantidad de aristas presentes en el grafo."""
	dicc_aristas = {} 
	for vertice in grafo:
		for otro_vertice in grafo.obtener_adyacentes_a_vertice(vertice):
			arista = "{0}-{1}".format(vertice,otro_vertice)
			arista2 = "{1}-{0}".format(vertice,otro_vertice)
			if not arista in dicc_aristas and not arista2 in dicc_aristas :
				dicc_aristas[arista] = None
	
	#fin de la obtencion de las aristas,las cuales no se repiten.
	return len( dicc_aristas.keys() )

def obt_suma_de_nro_ady_de_cada_vertice(grafo):
	"""Obtiene la suma de los vertices que entra o salen de un vertice en este caso"""
	suma_de_ady = 0
	for vertice in grafo:
		suma_de_ady += len( grafo.obtener_adyacentes_a_vertice(vertice) ) 
	return suma_de_ady

def estadisticas(grafo):
	"""Imprime por salida estandar, la cantidad de vertices, aristas, promedio del grado de entrada y salida de cada vertice y por ultimo la densidad del grafo."""
	cant_vertices = grafo.cantidad_vertices()
	print("\nESTADISTICAS:")
	print("La cantidad de vertices es de: ",cant_vertices )
	cantidad_de_aristas = obtener_cantidad_aristas(grafo)*2 #*2 porque es no dirigido
	print("La cantidad de aristas es de: ",obtener_cantidad_aristas(grafo)*2 ) 
	cant_total_ady = obt_suma_de_nro_ady_de_cada_vertice(grafo)
	print("El promedio del grado de entrada de cada vertice es: ",cant_total_ady//cant_vertices )
	print("El promedio del grado de salida de cada vertice es: ",cant_total_ady//cant_vertices )
	#me parecio mas coherente que sea un numero entero el promedio.
	print("La densidad del grafo es de: ",(2*cantidad_de_aristas) / ( cant_vertices * (cant_vertices -1 ) ) ) 
	
	print("\nOBSERVACIONES:")
	cantidad_de_aristas2 = (cant_vertices*( cant_vertices -1 ) ) /2#cant. de aristas de un grafo completo
	print("Un grafo completo tiene {} aristas".format( int(cantidad_de_aristas2) ))
	print("La densidad del grafo completo es de: ",(2*cantidad_de_aristas2)/(cant_vertices*(cant_vertices -1 )) )

#FIN DE COMANDO ESTADISTICAS


#INICIO DE COMANDO COMUNIDADES

#DECLARACION DE CONSTANTES
CANT_VERTICES_MIN = 10000

def max_frequencia(grafo,dicc_etiquetas,lista_vertices_ady):
	"""Obtiene de los adyacentes de un vertice la etiqueta mas frecuente"""
	dicc_frecuencia = {}
	for etiqueta in lista_vertices_ady:
		l_etiqueta = dicc_etiquetas[etiqueta]
		cad_etiqueta = "{} {}".format(l_etiqueta[0],l_etiqueta[1])
		dicc_frecuencia[cad_etiqueta] = dicc_frecuencia.get(cad_etiqueta,0) + 1 

	etiqueta_aux = max(dicc_frecuencia, key = dicc_frecuencia.get)
	l_etiqueta_aux = etiqueta_aux.split(" ")
	return l_etiqueta_aux[0]

#observacion: En algunos casos como la primera donde tiene etiquetas diferentes o en algun otro caso siguiente
#que pueda ocurrir agarra la primera que encuentra ya que todas las etiquetas tiene el mismo numero de
#de aparicion.

def obtener_cant_iter( cantidad_vertices ):
	"""Devuelve la cantidad aproximada de iteraciones"""
	if int(cantidad_vertices) < CANT_VERTICES_MIN:
		return 1
	cant_digitos = len(cantidad_vertices)
	return cant_digitos - 3 
	# con 2 tira 29.000 comunidades aprox y tarda 264 seg. y con 3, 32.000 comunidades aprox y tarda 227 seg. 

def label_propagation(grafo,cant_iter,lista_vertices,dicc_etiquetas):
	for i in range(cant_iter):
		shuffle(lista_vertices) # para obtener un orden aleatorio. 
		for vertice in lista_vertices:
			etiqueta_mas_frec = max_frequencia(grafo,dicc_etiquetas,grafo.obtener_adyacentes_a_vertice(vertice))
			dicc_etiquetas[etiqueta_mas_frec][1] += 1 
			dicc_etiquetas[vertice] = dicc_etiquetas[etiqueta_mas_frec]	

def obtener_comunidades_especificas(dicc_etiquetas):
	"""Pre:Se pasa por parametro el dicc que se obtuvo luego de la propagacion de etiquetas.
	Post:Obtiene las comunidades no menores de 4 vertices y no mayores de 2000 vertices"""
	dicc_comunidades = {}
	for usuario,l_etiqueta in dicc_etiquetas.items():
		etiqueta = l_etiqueta[0]
		if not etiqueta in dicc_comunidades:
			dicc_comunidades[etiqueta] = [usuario]
		else:	
			dicc_comunidades[etiqueta].append(usuario)

	return [comunidad for comunidad in dicc_comunidades.values() if len(comunidad) > 4 and len(comunidad)< 2000]

def imprimir_comunidades(lista_comunidades):
	"""Imprime las comunidades con numeros de intregantes y """ 
	for num,comunidad in enumerate(lista_comunidades):
		print("Comunidad: {} con {} integrantes".format(num+1,len( lista_comunidades[num] ) ) )
		print("Los integrantes son:")
		for persona in comunidad:
			print("Usuario: {}".format(persona))
		print("\n\n")


def obtener_comunidades(grafo):
	"""Se obtiene un lista de las comunidades por medio del etiquetado/label propagation"""
	dicc_etiquetas = {}
	for vertice in grafo:
		dicc_etiquetas[vertice] = [vertice,1]
	#cada vertice tiene una etiqueta diferente al ppo.

	lista_vertices = grafo.obtener_todos_los_vertices()[:]#tengo una copia de la lista de todos los vertices
	cant_iter = obtener_cant_iter( str( grafo.cantidad_vertices() )  )

	label_propagation(grafo,cant_iter,lista_vertices,dicc_etiquetas)
	return obtener_comunidades_especificas(dicc_etiquetas)

def comunidades(grafo):
	"""Obtiene las comunidades y las imprime por salida estandar"""
	lista_comunidades = obtener_comunidades(grafo)
	imprimir_comunidades(lista_comunidades)

#FIN DE COMANDO COMUNIDADES