#include "cola.h"
#include <stdbool.h>
#include <stdlib.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La cola está planteada como una cola de punteros genéricos. */

typedef struct nodo_cola nodo_cola_t;

struct nodo_cola{
	void* dato;
	nodo_cola_t* siguiente; 
};

struct cola{
	nodo_cola_t* prim;
	nodo_cola_t* ult;
};

/* ******************************************************************
 *                    FUNCIONES DE LA COLA
 * *****************************************************************/

// Crea una cola.
// Post: devuelve una nueva cola vacía.
cola_t* cola_crear(void){
	cola_t* cola_nueva = malloc(sizeof(cola_t));
	if( cola_nueva == NULL ){
		return NULL;
	}
	cola_nueva -> prim = NULL;
	cola_nueva -> ult = NULL; 
	return cola_nueva;
}

//creo un nodo_cola el cual se le agrega a la cola
nodo_cola_t* nodo_cola_crear(){
	nodo_cola_t* nodo_cola_nuevo = malloc(sizeof(nodo_cola_t));
	if( nodo_cola_nuevo == NULL ){
		return NULL;
	}
	nodo_cola_nuevo -> siguiente = NULL;
	return nodo_cola_nuevo;
}

// Agrega un nuevo elemento a la cola. Devuelve falso en caso de error.
// Pre: la cola fue creada.
// Post: se agregó un nuevo elemento a la cola, valor se encuentra al final
// de la cola.
bool cola_encolar(cola_t *cola, void* valor){
	nodo_cola_t* nodo_cola = nodo_cola_crear();
	if( nodo_cola == NULL) return false;	
	nodo_cola -> dato = valor;
	if( cola -> prim != NULL){
		cola -> ult -> siguiente = nodo_cola; 
	}
	else{
		cola -> prim = nodo_cola;
	}
	cola -> ult = nodo_cola;
	return true;
}

// Saca el primer elemento de la cola. Si la cola tiene elementos, se quita el
// primero de la cola, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la cola fue creada.
// Post: se devolvió el valor del primer elemento anterior, la cola
// contiene un elemento menos, si la cola no estaba vacía.
void* cola_desencolar(cola_t *cola){
	if(cola -> prim == NULL){
		return NULL;
	}
	nodo_cola_t* nodo_cola_desapilado =  cola -> prim;
	void* dato = nodo_cola_desapilado -> dato;
	cola -> prim = nodo_cola_desapilado -> siguiente;
	if( nodo_cola_desapilado -> siguiente == NULL ){
		cola -> ult = NULL;
	}
	free(nodo_cola_desapilado);
	return dato;
}

	
// Devuelve verdadero o falso, según si la cola tiene o no elementos encolados.
// Pre: la cola fue creada.
bool cola_esta_vacia(const cola_t *cola){
	return cola -> prim == NULL;
}

// Obtiene el valor del primer elemento de la cola. Si la cola tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la cola fue creada.
// Post: se devolvió el primer elemento de la cola, cuando no está vacía.
void* cola_ver_primero(const cola_t *cola){
	if( cola -> prim == NULL) return NULL;
	return cola -> prim -> dato;
}

// Destruye la cola. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la cola llama a destruir_dato.
// Pre: la cola fue creada. destruir_dato es una función capaz de destruir
// los datos de la cola, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la cola.
void cola_destruir(cola_t *cola, void destruir_dato(void*)){
	while ( !cola_esta_vacia(cola) ){
		if( destruir_dato != NULL){
			destruir_dato(cola -> prim -> dato);
		}
		cola_desencolar(cola);
	}
	free(cola);
}	
