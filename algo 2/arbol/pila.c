#include "pila.h"
#include <stdlib.h>
#include <stdbool.h>

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

#define TAM_INICIAL 20 
#define DIV_CAPAC_MIN 4 
#define DIV_CAPAC_INTER 2 
#define REDIM_SUP 2

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

// Crea una pila.
// Post: devuelve una nueva pila vacía.
pila_t* pila_crear(void){
	pila_t* pila_nueva = malloc(sizeof(pila_t));
	if(pila_nueva == NULL){
		return NULL;
	}
	pila_nueva -> capacidad = TAM_INICIAL; 
	pila_nueva -> cantidad = 0;
	pila_nueva -> datos = malloc( pila_nueva -> capacidad * sizeof(void*));
	if(pila_nueva -> datos == NULL){
		free(pila_nueva);
		return NULL;
	}
	return pila_nueva;
}
// Destruye la pila.
// Pre: la pila fue creada.
// Post: se eliminaron todos los elementos de la pila.
void pila_destruir(pila_t *pila){
	free(pila -> datos); 
	free(pila);
}

// Devuelve verdadero o falso, según si la pila tiene o no elementos apilados.
// Pre: la pila fue creada.
bool pila_esta_vacia(const pila_t *pila){
	return pila -> cantidad == 0;
}

// Obtiene el valor del tope de la pila. Si la pila tiene elementos,
// se devuelve el valor del tope. Si está vacía devuelve NULL.
// Pre: la pila fue creada.
// Post: se devolvió el valor del tope de la pila, cuando la pila no está
// vacía, NULL en caso contrario.
void* pila_ver_tope(const pila_t *pila){
	if( pila_esta_vacia(pila) ) return NULL;
	return pila -> datos[pila -> cantidad - 1];
}

/*funcion de uso interno la cual redimensiona la pila 
pre: la pila no debe estar vacia
post: la pila cambia de tamaño de acuerdo a la cantidad de elem que contenga
*/ 
bool redimensionar_pila(pila_t* pila,size_t tam_nuevo){
	void** datos_nuevos = realloc( pila -> datos,tam_nuevo * sizeof(void*));
	if(datos_nuevos == NULL){
		return false;
	}
	pila -> datos = datos_nuevos;
	pila -> capacidad = tam_nuevo; 
	return true;
}

// Agrega un nuevo elemento a la pila. Devuelve falso en caso de error.
// Pre: la pila fue creada.
// Post: se agregó un nuevo elemento a la pila, valor es el nuevo tope.
bool pila_apilar(pila_t *pila, void* valor){ 
	if( pila -> cantidad == pila -> capacidad ){
		if( redimensionar_pila(pila, REDIM_SUP * pila -> capacidad ) == false ) return false; 
	}
	pila -> datos[ pila -> cantidad ] = valor;
	pila -> cantidad++;
	return true;
}

// Saca el elemento tope de la pila. Si la pila tiene elementos, se quita el
// tope de la pila, y se devuelve ese valor. Si la pila está vacía, devuelve
// NULL.
// Pre: la pila fue creada.
// Post: si la pila no estaba vacía, se devuelve el valor del tope anterior
// y la pila contiene un elemento menos.
void* pila_desapilar(pila_t *pila){
	if( pila_esta_vacia(pila)) return NULL;
	if( pila->cantidad <= ((pila->capacidad)/ DIV_CAPAC_MIN)){
		if ( redimensionar_pila(pila,(pila->capacidad)/ DIV_CAPAC_INTER)  == false ){
			return NULL;
		}
	}
	pila -> cantidad--;
	return pila->datos[ pila->cantidad ];
}

