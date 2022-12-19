#include "pila.h"
#include <stdlib.h>

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// ...

//Modifica el tamaño de la pila segun sea necesario
//Pre: La pila necesita mas de la capacidad establecida o le sobran 
//varias posiciones (3/4 libres)
//Post:Se aumenta la cantidad al doble previamente establecido o
//se la reduce a la mitad
bool pila_redimensionar(pila_t *pila, bool faltan ){
	size_t tam_new;
	if (faltan == true){
		tam_new = (pila->capacidad)*2;
	}
	else {
		tam_new = (pila->capacidad)/2;
	}
	void* datos_new = realloc(pila->datos, tam_new * sizeof(void*));
	if (datos_new ==NULL){
		return false;
		}
		pila->datos = datos_new;
		pila->capacidad = tam_new;
		return true;
}

const size_t MAX = 10;//lo estoy usando solamente para el "pila_crear"

pila_t* pila_crear(void){
	pila_t* tu_pila = malloc(sizeof(pila_t));
	tu_pila->datos = malloc(MAX * sizeof(void*));
	if (tu_pila->datos == NULL){
		free(tu_pila->datos);
		free(tu_pila);
		return NULL;
	} 
	tu_pila->cantidad = 0;
	tu_pila->capacidad = MAX;
	return tu_pila;
}

void pila_destruir(pila_t *pila){
	free(pila->datos);
	free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
	if (pila->cantidad > 0){
		return false;
	}
	return true;
}

bool pila_apilar(pila_t *pila, void* valor){
	bool funciono = true;
	if (pila->cantidad == (pila->capacidad)){
		bool faltan = true;
		funciono = pila_redimensionar(pila, faltan);
	}
	pila->datos[pila->cantidad] = valor; 
	pila->cantidad++;
	return funciono;
}

void* pila_ver_tope(const pila_t *pila){
	if (pila->cantidad ==0){
		return NULL;
	}
	void* top; 
	top = pila->datos[pila->cantidad-1];
	return top;
}

void* pila_desapilar(pila_t *pila){
	void* valor;
	valor = NULL;
	if (pila->cantidad != 0){
		valor = pila_ver_tope(pila);
		pila->datos[(pila->cantidad)-1] = NULL;
		pila->cantidad--;
	}
	if ((pila->cantidad < (pila->capacidad)/4) && (pila->capacidad > MAX)){
		bool faltan = false;
		pila_redimensionar(pila, faltan);
	}
	return valor;
}
