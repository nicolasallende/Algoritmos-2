#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "pila.h"

struct nodo{
	void* dato;
	struct nodo* sig;
}typedef nodo_t;

struct lista{
	nodo_t* ini;
	nodo_t* fin;
	size_t cant;
}typedef lista_t;


struct lista_iter{
	lista_t* lista;
	nodo_t* act;
	nodo_t* ant;
}typedef lista_iter_t;



/******************************************************************
 *     				PRIMITIVAS DE LA LISTA
 *****************************************************************/
nodo_t* crear_nodo(void){
	nodo_t* tu_nodo = (nodo_t*)malloc(sizeof(nodo_t) );
	if (!tu_nodo) return NULL;
	return tu_nodo;
}

lista_t* lista_crear(void){
	lista_t* tu_lista = malloc(sizeof(lista_t));
	if (!tu_lista) return NULL;
	tu_lista->ini = NULL;
	tu_lista->fin = NULL;
	tu_lista->cant = 0;
	return tu_lista;
}

bool lista_esta_vacia(const lista_t *lista){
	if (lista->cant == 0) return true;
	return false;
}

bool lista_insertar_por_primera_vez(lista_t *lista, void *dato){
	nodo_t* nuevo;
	nuevo = crear_nodo();
	if (!nuevo) return false;
	nuevo->sig = NULL;
	nuevo->dato = dato;
	lista->cant++;
	lista->ini = nuevo;
	lista->fin = nuevo;
	return true;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
	if (lista_esta_vacia(lista) ) return lista_insertar_por_primera_vez(lista, dato);
	nodo_t* nuevo;
	nuevo = crear_nodo();
	if (!nuevo) return false;
	nuevo->sig = lista->ini;
	nuevo->dato = dato;
	lista->ini = nuevo;
	lista->cant++;
	return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
	if (lista_esta_vacia(lista) ) return lista_insertar_por_primera_vez(lista, dato);
	nodo_t* nuevo;
	nuevo = crear_nodo();
	if (!nuevo) return false;
	nuevo->dato = dato;
	nuevo->sig = NULL;
	lista->fin->sig = nuevo;
	lista->fin = lista->fin->sig;
	lista->cant++;
	return true;
} 

void* lista_borrar_primero(lista_t *lista){
	if (lista_esta_vacia(lista)) return NULL;
	void* valor;
	valor = lista->ini->dato;
	nodo_t *aux;
	aux = lista->ini;
	if (lista_largo(lista) == 1){
		lista->ini = NULL;
		lista->fin = NULL;
	}else{
		lista->ini = lista->ini->sig;
	}
	free(aux);
	lista->cant--;
	return valor;
}

void* lista_ver_primero(const lista_t *lista){
	if (lista_esta_vacia(lista)) return NULL;
	return (lista->ini->dato);
}

void* lista_ver_ultimo(const lista_t *lista){
	if (lista_esta_vacia(lista)) return NULL;
	return (lista->fin->dato);
}

size_t lista_largo(const lista_t *lista){
	return lista->cant;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void*)){
	while ( !lista_esta_vacia(lista ) ){
		if (destruir_dato != NULL){
			void *aux;
			aux = lista->ini->dato;
			destruir_dato(aux);
			aux = lista->ini;
			if (lista_largo(lista) == 1){
				lista->ini = NULL;
				lista->fin = NULL;
			}else{
				lista->ini = lista->ini->sig;
				}
			free(aux);
			lista->cant--;
		}
		else{
		lista_borrar_primero(lista);
		}
	}
	free(lista);
}


/******************************************************************
 *     			PRIMITIVAS DE LOS ITERADORES
 *****************************************************************/

lista_iter_t *lista_iter_crear(lista_t *lista){
	lista_iter_t* iter = malloc(sizeof(lista_iter_t));
	if (!iter) return NULL;
	iter->lista = lista;
	iter->ant = NULL;
	if (lista_esta_vacia(lista)){
		iter->act = NULL;
	}else{
		iter->act = iter->lista->ini;
	}
	return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter){
	if (lista_iter_al_final(iter)) return false;
	iter->ant = iter->act;
	iter->act = iter->act->sig;
	return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
	if (lista_iter_al_final(iter)) return NULL;
	return iter->act->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter){
	if (!iter->act) return true;
	return false;
}

void lista_iter_destruir(lista_iter_t *iter){
	free(iter);
}


bool lista_iter_insertar(lista_iter_t *iter, void *dato){
	if (lista_esta_vacia(iter->lista)){
		bool aux = lista_insertar_por_primera_vez(iter->lista, dato);
		iter->ant = NULL;
		iter->act = iter->lista->ini;
		iter->act->sig = NULL;
		return aux;
	}
	if (lista_iter_al_final(iter)){
		bool aux = lista_insertar_ultimo(iter->lista, dato);
		iter->ant = iter->act;
		iter->act = iter->lista->fin;
		iter->act->sig = NULL;
		return aux;
	}
	if (iter->act == iter->lista->ini){
		bool aux = lista_insertar_primero(iter->lista, dato);
		iter->ant = NULL;
		iter->act = iter->lista->ini;
		iter->act->sig = iter->lista->ini->sig;
		return aux;
	}
	nodo_t* nuevo;
	nuevo = crear_nodo();
	if (!nuevo) return false;
	nuevo->dato = dato;
	nuevo->sig = iter->act;
	iter->ant->sig = nuevo;
	iter->act = nuevo;
	iter->lista->cant++;
	return true;
}

void *lista_iter_borrar(lista_iter_t *iter){
	if ((lista_esta_vacia(iter->lista)) || (lista_iter_al_final(iter))) return NULL;
	void *aux;
	aux = iter->act;
	void *valor;
	valor = iter->act->dato;
	if (iter->lista->cant == 1){
		iter->ant = NULL;
		iter->act = NULL;
		iter->lista->ini = NULL;
		iter->lista->fin = NULL;
	}else if (iter->act == iter->lista->ini){
		iter->ant = NULL;
		iter->act = iter->act->sig;
		iter->lista->ini = iter->act;
	}else if (iter->act == iter->lista->fin){
		iter->act = iter->act->sig;
		iter->lista->fin = iter->ant;
	}else{
		iter->act = iter->act->sig;
		iter->ant->sig = iter->act;
	}
	free(aux);
	iter->lista->cant--;
	return valor;
}

void lista_iterar(lista_t* lista, bool (*visitar)(void *dato, void *extra), void *extra){
	if (lista_esta_vacia(lista)) return;
	lista_iter_t* iter = lista_iter_crear(lista);
	void *dato;
	bool aux;
	do{
		dato = lista_iter_ver_actual(iter);
		aux = visitar(dato, extra);
		lista_iter_avanzar(iter);
	}while(!lista_iter_al_final(iter) && aux );
	lista_iter_destruir(iter);
}
