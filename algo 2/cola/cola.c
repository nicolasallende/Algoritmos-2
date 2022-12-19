#include "cola.h"
#include <stdlib.h>
#include <stdio.h>
#include "pila.h"

struct nodo{
	void* dato;
	struct nodo* sig;
}typedef nodo_t;

struct cola{
	nodo_t* ini;
	nodo_t* fin;
}typedef cola_t;


cola_t* cola_crear(void){
	cola_t* tu_cola = malloc(sizeof(cola_t));
	if (!tu_cola){
		return NULL;
	}
	tu_cola->ini = (nodo_t *)malloc(sizeof(nodo_t));
	tu_cola->fin = tu_cola->ini;
	if (!tu_cola->ini){
		free(tu_cola);
		return NULL;
	}
	tu_cola->ini->sig = NULL;
	return tu_cola;
}

bool cola_esta_vacia(const cola_t *cola){
	if (cola->fin == cola->ini){
		return true;
	}
	return false;
}

bool cola_encolar(cola_t *cola, void* valor){
	cola->fin->sig = (nodo_t *)malloc(sizeof(nodo_t));
	if (cola->fin->sig == NULL){
		return false;
	}
	cola->fin = cola->fin->sig;
	cola->fin->sig =NULL;
	cola->fin->dato = valor;
	return true;
} 

void* cola_ver_primero(const cola_t *cola){
	if (cola_esta_vacia(cola)){
		return NULL;
	} 
	return(cola->ini->sig->dato);
}  

void* cola_desencolar(cola_t *cola){
	if (cola_esta_vacia(cola)){
		return NULL;
	} 
	void* valor;
	valor = cola->ini->sig->dato;
	void *aux;
	aux = cola->ini;
	cola->ini = cola->ini->sig;
	free(aux);
	return valor;
}
void cola_destruir(cola_t *cola,void(*destruir_dato)(void*)){
	while (!cola_esta_vacia(cola)){
		if (destruir_dato != NULL){
			void *aux;
			aux = cola->ini->sig->dato;
			destruir_dato(aux);
			aux = cola->ini;
			cola->ini = cola->ini->sig;
			free(aux);
		}
		else{
		cola_desencolar(cola);
		}
	}
	free(cola->ini);
	free(cola);
}
