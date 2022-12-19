from TDA import Cola
from random import choice

def random_walk(grafo,n,vertice = None):
	"""camino aleatorio de largo n"""
	if n == 0:
		return []
	if vertice is None:
		lista_de_vertices = grafo.obtener_todos_los_vertices()	
		vertice = choice(lista_de_vertices) # se escoge uno cualquiera.

	lista_recorrido = [ vertice ]
	largo = 0
	while largo < n:
		lista_de_ady = grafo.obtener_adyacentes_a_vertice(vertice) 
		vertice = choice( lista_de_ady )
		lista_recorrido.append( vertice ) 	
		largo+=1
	return lista_recorrido


def random_walk_bis(grafo,n,vertice,vertice_corte):
	"""Variante del random walk, con condicion de corte"""
	if n == 0:
		return []
	lista_recorrido = [ vertice ]
	largo = 0
	while largo < n:
		lista_de_ady = grafo.obtener_adyacentes_a_vertice(vertice) 
		vertice = choice( lista_de_ady )
		lista_recorrido.append( vertice )
		if vertice_corte in grafo.obtener_adyacentes_a_vertice(vertice):
			lista_recorrido.append(vertice_corte)
			return lista_recorrido
		largo+=1

	return lista_recorrido


def bfs_visitar(grafo, origen, visitados, padre, orden,vertice_corte=None, busqueda=False,distancias =None ):
	cola = Cola()
	cola.encolar( origen )
	visitados[origen] = True
	while not cola.esta_vacia():
		vertice = cola.desencolar()
		for w in grafo.obtener_adyacentes_a_vertice(vertice):
			if not w in visitados:
				visitados[w] = True
				padre[w] = vertice
				orden[w] = orden[vertice] + 1
				if vertice_corte == w and busqueda:
					return orden
				if distancias is not None:
					if orden[w] in distancias:
						distancias[ orden[w] ] += 1
					else:
						distancias[ orden[w] ] = 1
				cola.encolar(w)

def recorrido_particular_bfs(grafo,vertice,vertice_corte,busqueda):
	visitados = {vertice : True}
	padre = {vertice : None}
	orden = {vertice : 0}
	bfs_visitar(grafo,vertice,visitados,padre,orden,vertice_corte,busqueda)
	return orden[vertice_corte]
 

def recorrido_bfs(grafo):
	"""Recorrido por profundidad"""
	visitados = {}
	padre = {}
	orden = {}
	for v in grafo:
		if v not in visitados:
			padre[v] = None
			orden[v] = 0
			bfs_visitar(grafo, v, visitados, padre, orden)
	return padre,orden,visitados

