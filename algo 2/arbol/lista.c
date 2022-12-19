#include "lista.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

//Inicio funciones auxiliares.
typedef struct nodo nodo_t;

struct nodo{
	void* valor;
	nodo_t* ref_sgte;
};

//Crea un nodo para la lista enlazada.
nodo_t* nodo_crear(){
	nodo_t* nodo_nuevo = malloc(sizeof(nodo_t));
	if( nodo_nuevo == NULL) return NULL;
	nodo_nuevo -> ref_sgte = NULL;
	return nodo_nuevo;
}
//fin funciones auxiliares.

struct lista{
	nodo_t* prim;
	nodo_t* ult;
	size_t largo;
};

// crea una lista enlazada.
//Post: devuelve una lista vacia.
lista_t* lista_crear(){
	lista_t* lista_nueva = malloc(sizeof(lista_t));
	if( lista_nueva == NULL ) return NULL;
	lista_nueva -> prim = NULL;
	lista_nueva -> ult = NULL;
	lista_nueva -> largo = 0;
	return lista_nueva;
}
//Da un true si la lista esta vacia y da un false si la lista esta con elementos.
//Pre:La lista fue creada.
bool lista_esta_vacia(const lista_t *lista){
	return lista -> prim == NULL;
}

//Insertar un elemento al principio de la lista.
//Pre: la lista fue creada.
//Post: el elemento esta en el principio de la lista. Si se puede realizar tal accion devuelve true
// y false en el caso de que no sea posible.
bool lista_insertar_primero(lista_t *lista, void *dato){
	nodo_t* nodo = nodo_crear();
	if( nodo == NULL ) return false;
	nodo -> valor = dato;
	nodo -> ref_sgte = lista -> prim;
	lista -> prim = nodo;
	if( lista -> ult == NULL  ){
		lista -> ult = nodo;
	}
	lista -> largo +=1;
	return true;
}

//Insertar un elemento al final de la lista.
//pre: la lista fue creada.
//post: el elemento esta en el final de la lista. Si se puede realizar tal accion devuelve true
// y false en el caso de que no sea posible.
bool lista_insertar_ultimo(lista_t *lista, void *dato){
	nodo_t* nodo = nodo_crear();
	if( nodo == NULL ) return false;
	nodo -> valor = dato;
	if( lista_esta_vacia(lista) ) { lista -> prim = nodo; }
	else { lista -> ult -> ref_sgte = nodo; }
	lista -> ult = nodo;
	lista -> largo += 1;
	return true;
}

// Muestra el primer elemento que contiene la lista.
//Pre: La lista fue creada.
void *lista_ver_primero(const lista_t *lista){
	if(lista -> prim == NULL) return NULL;
	return lista -> prim -> valor;
}
// Muestra el ultimo elemento que contiene la lista.
//Pre: La lista fue creada.
void *lista_ver_ultimo(const lista_t* lista){
	if(lista -> ult == NULL) return NULL;
	return lista -> ult -> valor;
}

//borra el primer elemento de la lista y lo devuelve.
//Pre: la lista fue creada.
void *lista_borrar_primero(lista_t *lista){
	if( lista-> prim == NULL ) return NULL;
	
	nodo_t* nodo_borrado = lista -> prim;
	void* dato = nodo_borrado -> valor;
	
	lista -> prim = nodo_borrado -> ref_sgte;
	if( nodo_borrado -> ref_sgte == NULL) lista -> ult = NULL;
	
	lista -> largo -= 1;
	free(nodo_borrado);
	return dato; 
}

//Devuelve el largo de la lista.
//Pre:La lista fue creada.
size_t lista_largo(const lista_t *lista){
	return lista -> largo;
}

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la cola llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la cola, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)){
	if ( destruir_dato != NULL ){
		while( !lista_esta_vacia(lista) ){
			destruir_dato( lista_borrar_primero(lista) );
		}
	}
	while(!lista_esta_vacia(lista)){
		lista_borrar_primero(lista);
	}
	free(lista);
}

//Itera sobre la lista y realiza la operacion/funcion que es pasada por parametro a los elementos de la lista.
//Pre: La lista fue creada.
//Post: Realiza operacion siempre y cuando se le pase una funcion, en caso contrario no hace nada.
void lista_iterar(lista_t *lista, bool (*visitar)(void *dato, void *extra), void *extra){
	bool iter_valida = true;
	if( lista -> prim == NULL) return;
	if( visitar == NULL ) return;
	nodo_t* nodo_act = lista -> prim;
	while( iter_valida && nodo_act != NULL ){
		iter_valida = visitar( nodo_act -> valor , extra);
		nodo_act = nodo_act -> ref_sgte;
	}
}
/*fin de primitivas de iterador interno*/

/* Parte de las primitivas del iterarador externo*/

struct lista_iter{
	lista_t* lista;
	nodo_t* anterior;
	nodo_t* actual;
};

//Crea un iter con el cual recorre la lista.
//Pre: La lista fue creada.
//Post: Devuelve un iter apuntando al principio de la lista. 
lista_iter_t* lista_iter_crear(lista_t *lista){
	lista_iter_t* iter = malloc(sizeof(lista_iter_t));
	if( iter == NULL) return NULL;
	iter -> lista = lista; 
	iter -> anterior = NULL;
	iter ->  actual = lista -> prim;
	return iter;
}

//Pregunta al iter si se encuentra al final con un True en el caso de asi sea o False en caso contrario.
//Pre: La lista y el iter fueron creados.
bool lista_iter_al_final(const lista_iter_t *iter){
	return iter -> actual == NULL;
} 

//funcion que sirve para avanzar sobre lista.
//Pre: La lista y el iter fueron creados.
//Post: Da true si avanzo y false en caso contrario.
bool lista_iter_avanzar(lista_iter_t *iter){
	if( lista_iter_al_final(iter) ) return false;
	iter -> anterior = iter -> actual;
	iter -> actual = iter -> actual -> ref_sgte;
	return true;
}

//Devuelve el elemento que se encuentra en la posicion actual de la lista.
//Pre: La lista y el iter fueron creados.
//Post: Devuele el elemento si la lista no es vacia o estoy al final y en caso contrario NULL.
void *lista_iter_ver_actual(const lista_iter_t *iter){
	if ( lista_iter_al_final(iter) ) return NULL;
	return iter -> actual -> valor;
}

//Destruye el iter.
//Pre: La lista y el iter fueron creados.
void lista_iter_destruir(lista_iter_t *iter){
	free(iter);
}

//inserta un elemento en la lista. si es posible y se realiza la accion da un true, sino False.
//Pre: La lista y el iter fueron creados.
bool lista_iter_insertar(lista_iter_t *iter, void *dato){
	nodo_t* nodo = nodo_crear();
	if( nodo == NULL ) return false;
	nodo -> valor = dato;
	// caso en cual estas al principio de la lista.
	if( iter -> anterior == NULL){
		nodo -> ref_sgte = iter -> lista -> prim;
		iter -> lista -> prim = nodo;
	}
	// caso generico.
	else{
		iter -> anterior -> ref_sgte = nodo;
		nodo -> ref_sgte = iter -> actual;
	}
	if( iter -> actual == NULL) iter -> lista -> ult = nodo;
	iter -> actual = nodo;
	iter -> lista -> largo++;
	return true;
}

//Saca el elemento de la lista y lo devuelve. 
//Pre: La lista y el iter fue creada.
// Post: Devuelve el puntero si puedo sacar el elemento o NULL en caso contrario.
void *lista_iter_borrar(lista_iter_t *iter){
	if( iter-> anterior == iter -> actual ) return NULL;
	if( lista_iter_al_final(iter) ) return NULL;
	nodo_t* nodo_a_borrar = iter -> actual;
	void* dato = nodo_a_borrar -> valor;
	// caso en el que estoy al principio.
	if( iter-> anterior == NULL){
		iter -> lista -> prim = nodo_a_borrar -> ref_sgte;
		if( nodo_a_borrar -> ref_sgte == NULL ) iter -> lista -> ult = NULL;
	}
	// caso generico.
	else{	
		iter -> anterior -> ref_sgte = nodo_a_borrar -> ref_sgte;
		if( nodo_a_borrar-> ref_sgte == NULL ) iter -> lista -> ult = iter -> anterior;
	}
	iter -> actual = nodo_a_borrar -> ref_sgte;
	iter -> lista -> largo -= 1 ;
	free(nodo_a_borrar);
	return dato;
}

/*fin de primitivas de iterador externo*/

