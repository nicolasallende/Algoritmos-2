#DECLARACION DE CTES.
SEP = "-"

class Grafo():
	"""Crea un grafo"""
	def __init__(self,dirigido = False ):
		self.dicc_vertices = {}
		self.dicc_aristas = {}
	
	def agregar_vertice(self,vertice):
		if vertice in self.dicc_vertices:
			return False  
		self.dicc_vertices[vertice] = []
		return True

	def obtener_adyacentes_a_vertice(self,vertice):
		if not vertice in self.dicc_vertices:
			return []
		return self.dicc_vertices[vertice]


	def quitar_vertice(self,vertice):

		if not vertice in self.dicc_vertices:
			return False

		lista_ady = self.obtener_adyacentes_a_vertice(vertice)

		for otro_vertice in lista_ady:	
			self.dicc_vertices[otro_vertice].remove(vertice)
		#fin del borrado de vertices adyacentes a este vertice.

		lista_claves = [clave for clave in self.dicc_aristas.keys() ]

		for pos,clave in enumerate( lista_claves ):
			vertice2,vertice3 = lista_claves[pos].split(SEP)
			if vertice == vertice2 or vertice == vertice3 :
				self.dicc_aristas.pop( lista_claves[pos] )
		#fin del borrado de aristas.

		self.dicc_vertices.pop(vertice)
		#Borro el vertice de dicc_vertices por ultimo
		return True


	def agregar_arista(self,vertice1,vertice2):
		"""Agrega una arista al grafo"""
		arista = "{0}-{1}".format(vertice1,vertice2)
		arista2 = "{1}-{0}".format(vertice1,vertice2)

		if not vertice1 in self.dicc_vertices or not vertice2 in self.dicc_vertices: 
			print("Uno de los vertices no existe")
			return False

		if arista in self.dicc_aristas or arista2 in self.dicc_aristas:
			return False

		lista_ady_vertice1 = self.dicc_vertices[vertice1]
		lista_ady_vertice2 = self.dicc_vertices[vertice2]

		self.dicc_aristas[arista] = None # Esto se hace porque despues buscar en el mismo cuesta menos.

		lista_ady_vertice1.append(vertice2)
		lista_ady_vertice2.append(vertice1)

		return True

	def quitar_arista(self,vertice1,vertice2):
		"""Quita una arista del grafo"""
		arista = "{0}-{1}".format(vertice1,vertice2)
		arista2 = "{1}-{0}".format(vertice1,vertice2)

		if not vertice1 in self.dicc_vertices or not vertice2 in self.dicc_vertices: 
			print("Uno de los vertices no existe")
			return False

		if not arista in self.dicc_aristas and not arista2 in self.dicc_aristas:
			return False

		lista_ady_vertice1 = self.dicc_vertices[vertice1]
		lista_ady_vertice2 = self.dicc_vertices[vertice2]

		lista_ady_vertice1.remove(vertice2)
		lista_ady_vertice2.remove(vertice1)

		#Si llegue hasta aca es porque estaba alguno de los dos, no los dos.
		if not arista in self.dicc_aristas:
			self.dicc_aristas.pop( arista2 )
		else:
			self.dicc_aristas.pop( arista )
		return True

	def son_adyacentes(self,vertice1,vertice2):
		"""Verifica si un vertice es ady a otro"""
		arista = "{0}-{1}".format(vertice1,vertice2)
		arista2 = "{1}-{0}".format(vertice1,vertice2)
		return arista in self.dicc_aristas or arista2 in self.dicc_aristas		
	

	def vertice_existe(self,vertice):
		"""Se fija si el vertice pertenece al grafo"""
		return vertice in self.dicc_vertices


	def cantidad_vertices(self):
		return len(self.dicc_vertices)

	def obtener_todos_los_vertices(self):
		return [ vertice for vertice in self.dicc_vertices.keys() ]

	#Hacer que el grafo sea iterable, quiere decir que es iterable entre los vertices ----> Preguntar 
	def __iter__(self):
		for vertice in self.dicc_vertices.keys():
			yield vertice
