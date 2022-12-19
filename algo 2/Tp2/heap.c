#include "heap.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define MAX 0
#define TAM 499  
#define DIV_CAPAC_MIN 4 
#define DIV_CAPAC_INTER 2 
#define MULT_TAM 2

struct heap{
	void** arreglo;
	size_t cantidad;
	size_t tamanio;
	cmp_func_t cmp;
};

//intercambia los punteros de posicion.
void swap(size_t max, size_t pos,void* arr[]) {
	void* temp = arr[max];
	arr[max] = arr[pos];
	arr[pos] = temp;
}

// Mueve el valor de la posicion segun el valor de sus hijos segun sea un max heap o min heap de manera que;
// en el caso del max heap donde el padre es mayor a sus hijos o en min heap donde el padre es menor a 
// a sus hijos aplicando swap en las posiciones correspondientes.
void down_heap(void *arr[], size_t cant, size_t pos, cmp_func_t cmp){
	if(pos >= cant) return;
	size_t max = pos;
	size_t hijo_izq = (2*pos)+1;
	size_t hijo_der = (2*pos)+2;
	if((hijo_izq < cant) && (cmp(arr[hijo_izq], arr[max]) > 0) ) max = hijo_izq;
	if((hijo_der < cant) && (cmp(arr[hijo_der], arr[max]) > 0) ) max = hijo_der; 
	if(max != pos){
		swap(max, pos, arr);
		down_heap(arr, cant, max, cmp);
	}
}

// Mueve el valor de la posicion segun el valor de sus hijos segun sea un max heap o min heap de manera que;
// en el caso del max heap donde el padre es mayor a sus hijos o en min heap donde el padre es menor a 
// a sus hijos aplicando swap en las posiciones correspondientes.
void up_heap(void *elementos[], size_t pos, cmp_func_t cmp){
	if(pos == 0) return;
	size_t padre = (pos - 1)/2;
	if( cmp(elementos[padre], elementos[pos]) < 0){
		swap(padre,pos,elementos);
		up_heap(elementos, padre, cmp);
	}
}

//Intercambia  los valores de las posiciones para generar un max heap o min heap segun la funcion de comparacion. 
void heapify(void *elementos[], size_t cant, cmp_func_t cmp){
	size_t u;
	if((cant % 2) == 0){
		u = (cant - 2)/2;
	}else{
		u = (cant - 3)/2;
	}
	for(size_t i = u; i > 0; i--){
		down_heap(elementos, cant, i, cmp);
	}
	down_heap(elementos, cant, MAX, cmp);
} 
	
/* Función de heapsort genérica. Esta función ordena mediante heap_sort
 * un arreglo de punteros opacos, para lo cual requiere que se
 * le pase una función de comparación. Modifica el arreglo "in-place".
 * Nótese que esta función NO es formalmente parte del TAD Heap.
 */
void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
	heapify(elementos, cant, cmp);
	size_t i = cant-1;
	while( i > 0 ){
		swap(0,i,elementos);
		down_heap(elementos,i,0,cmp);
		i--;
	}
} 

//Pre: el heap fue creado.
//Redimensiona el heap segun la cantidad de elementos haya en el heap.
bool redimensionar_arreglo_heap(heap_t* heap,size_t tam_nuevo){
	void** arreglo_nuevo = realloc( heap -> arreglo,tam_nuevo * sizeof(void*));
	if( arreglo_nuevo == NULL) return false;
	heap -> arreglo = arreglo_nuevo;
	heap -> tamanio = tam_nuevo; 
	return true;
}


/* Agrega un elemento al heap. El elemento no puede ser NULL.
 * Devuelve true si fue una operación exitosa, o false en caso de error.
 * Pre: el heap fue creado.
 * Post: se agregó un nuevo elemento al heap.
 */
bool heap_encolar(heap_t *heap, void *elem){
	if(elem == NULL) return false;
	if(heap->cantidad == heap->tamanio){
		if(!redimensionar_arreglo_heap(heap, (heap->tamanio * MULT_TAM))) return NULL;
	}
	heap->arreglo[heap->cantidad] = elem;
	up_heap(heap->arreglo, heap->cantidad, heap->cmp);
	heap->cantidad++; 
	return true;
}

/* Crea un heap. Recibe como único parámetro la función de comparación a
 * utilizar. Devuelve un puntero al heap, el cual debe ser destruido con
 * heap_destruir().
 */
heap_t *heap_crear(cmp_func_t cmp){
	heap_t* heap = malloc(sizeof(heap_t));
	if(!heap) return NULL;
	void** arr = malloc(sizeof(void*) * TAM);
	if(!arr){
		free(heap);
		return NULL;
	} 
	heap->arreglo = arr;
	heap->cmp = cmp;
	heap->cantidad = 0;
	heap->tamanio = TAM;
	return heap;
}

/*
 * Constructor alternativo del heap. Además de la función de comparación,
 * recibe un arreglo de valores con que inicializar el heap. Complejidad
 * O(n).
 *
 * Excepto por la complejidad, es equivalente a crear un heap vacío y encolar
 * los valores de uno en uno
*/
heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
	heap_t* heap = heap_crear(cmp);
	if( heap == NULL ) return NULL;
	for (int i = 0; i < n; ++i){
		heap_encolar(heap,arreglo[i]);
	}
	return heap;
}

/* Elimina el elemento con máxima prioridad, y lo devuelve.
 * Si el heap esta vacío, devuelve NULL.
 * Pre: el heap fue creado.
 * Post: el elemento desencolado ya no se encuentra en el heap.
 */
void *heap_desencolar(heap_t *heap){
	if( heap->cantidad == 0 ) return NULL;
	void* dato_a_borrar = heap->arreglo[MAX];
	if( heap->cantidad == 1 ){
		heap->cantidad--;
		return dato_a_borrar;
	}
	swap( MAX, heap->cantidad -1, heap->arreglo);
	heap->cantidad--;
	down_heap( heap->arreglo, heap->cantidad, (size_t)MAX, heap->cmp);
	if( heap->cantidad <= ( heap->tamanio/ DIV_CAPAC_MIN) ){
		if ( !redimensionar_arreglo_heap(heap,heap->tamanio/ DIV_CAPAC_INTER) ) return NULL;
	}	
	return dato_a_borrar;
}

/* Elimina el heap, llamando a la función dada para cada elemento del mismo.
 * El puntero a la función puede ser NULL, en cuyo caso no se llamará.
 * Post: se llamó a la función indicada con cada elemento del heap. El heap
 * dejó de ser válido. */
void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
	while( heap->cantidad > 0  && destruir_elemento != NULL){
		destruir_elemento( heap->arreglo[heap->cantidad -1] );
		heap->cantidad--;
	}
	free( heap->arreglo );
	free( heap );
}

/* Devuelve la cantidad de elementos que hay en el heap. */
size_t heap_cantidad(const heap_t *heap){
	return heap->cantidad; 
}

/* Devuelve true si la cantidad de elementos que hay en el heap es 0, false en
 * caso contrario. */
bool heap_esta_vacio(const heap_t *heap){
	if( heap -> cantidad == 0) return true;
	return false;
}

/* Devuelve el elemento con máxima prioridad. Si el heap esta vacío, devuelve
 * NULL.
 * Pre: el heap fue creado.
 */
void *heap_ver_max(const heap_t *heap){
	if( heap-> cantidad == 0) return NULL;
	return heap->arreglo[MAX];
}
