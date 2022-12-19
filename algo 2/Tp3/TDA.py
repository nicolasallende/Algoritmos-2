import heapq
from heapq import heappush
from heapq import heappop
from queue import Queue

class Cola:
	"""Cola implementada con la libreria queue"""
	def __init__(self):
		self.cola = Queue()
	
	def encolar(self,item):
		"""Encola un elemento en la Cola"""
		self.cola.put_nowait(item)

	def esta_vacia(self):
		"""Devuelve True si la Cola esta vacia, False en caso contrario"""
		return self.cola.empty()

	def desencolar(self):
		"""Desencola un elemento mientras la Cola no este Vacia"""
		if self.esta_vacia():
			return  
		return self.cola.get_nowait()
	
	def ver_primero(self):
		"""Devuelve el primer elemento presente en la Cola"""
		if self.esta_vacia(	):
			return  
		return self.cola[0]

def heapsort(lista):
    l_ord = []
    for valor in lista:
        heappush(l_ord, valor)
    return [heappop(l_ord) for i in range(len(l_ord))]

class Heap:
    """Heap de minimos"""

    def __init__(self):
        """ create a new min-heap. """
        self._heap = []

    def encolar(self,priority, item):
        """ Push an item with priority into the heap.
            Priority 0 is the highest, which means that such an item will
            be popped first."""
        heapq.heappush(self._heap,(priority, item))

    def desencolar(self):
        """ Returns the item with lowest priority. """
        return heapq.heappop(self._heap)

    def __len__(self):
        return len(self._heap)

    def __iter__(self):
        """ Get all elements ordered by asc. priority. """
        for elem,cant in self._heap:
        	yield elem,cant

    def ver_min(self):
    	return self._heap[0]

# #probar con el siguiente 

# h = Heap()
# # add some nonsense:
# h.encolar(10, "I'm a large one")
# h.encolar(20, "Actually I'm larger")
# h.encolar(5, "size is not everything")
# h.encolar(0, "which size?")


# # get it out in a cool way:
# for item,cant in h:
#    print(item,cant)
# print(h.ver_min())
# print(h.desencolar())


