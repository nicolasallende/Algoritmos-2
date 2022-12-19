#include "pila.h"
#include "abb.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

typedef struct abb_nodo abb_nodo_t; 

struct abb_nodo{
	const char* clave;
	void* dato;
	abb_nodo_t* izq;
	abb_nodo_t* der;
};


struct abb{
	abb_nodo_t* raiz;
	abb_comparar_clave_t cmp; // la funcion de comparacion devuelve un int.
	abb_destruir_dato_t destructor;
	size_t cantidad;
};

//Genera una copia de la clave que se pasa por parametro.
char* generar_clave_copiada(const char* clave){
	char* clave_copia = malloc( (strlen(clave) + 1) * sizeof(char) );
	if( clave_copia == NULL ) return NULL;
	strcpy(clave_copia,clave);
	return clave_copia;
}

//Pre: El abb fue creado.
//Post: Devuelve un nodo el cual tiene el par (clave,dato).
abb_nodo_t* abb_nodo_crear(const char* clave, void* dato){
	abb_nodo_t* abb_nodo = malloc( sizeof(abb_nodo_t) );
	if( abb_nodo == NULL ) return NULL;
	abb_nodo -> clave = generar_clave_copiada(clave);
	if( abb_nodo -> clave == NULL) return NULL;
	abb_nodo -> dato = dato;
	abb_nodo -> izq = NULL;
	abb_nodo -> der = NULL;
	return abb_nodo;
} 

// Crea un arbol binario de busqueda.
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
	abb_t* abb = malloc( sizeof(abb_t) );
	if( abb == NULL ) return NULL;
	abb -> raiz = NULL;
	abb -> cantidad = 0;
	abb -> cmp = cmp;
	abb -> destructor = destruir_dato; 
	return abb;
}

//Pre:El arbol fue creado.
//Post:Devuelve la cantidad de elementos, par(clave,dato) ,que hay en el abb.
size_t abb_cantidad(abb_t *arbol){
	return arbol -> cantidad;
}

//Reemplaza el dato de una clave cuando se quiera guardar una clave que ya existia en el abb.
bool reemplazar_dato(abb_t* abb,abb_nodo_t* abb_nodo, void* dato_nuevo){
	if( abb-> destructor != NULL ) abb -> destructor(abb_nodo-> dato);
	abb_nodo -> dato = dato_nuevo;
	return true;
}


//Busca la posicion donde insertar el par(clave, dato) segun el valor de la clave y la agrega al abb.
bool abb_guardar_aux(abb_t *arbol,abb_nodo_t* nodo_padre,int res_cmp,const char *clave, void *dato){
	if( (res_cmp > 0 && nodo_padre -> der == NULL) || (res_cmp < 0 && nodo_padre -> izq == NULL) ){
		abb_nodo_t* abb_nodo_nuevo = abb_nodo_crear(clave,dato);
		if( abb_nodo_nuevo == NULL ) return false;
		if( res_cmp < 0 ) nodo_padre -> izq = abb_nodo_nuevo; 
		else { nodo_padre -> der = abb_nodo_nuevo; }
		arbol -> cantidad++;
		return true;
	}

	if( res_cmp > 0 && nodo_padre -> der != NULL ){
		return abb_guardar_aux(arbol,nodo_padre->der,arbol->cmp(clave, nodo_padre -> der-> clave),clave,dato);
	}
	else if( res_cmp < 0 && nodo_padre -> izq != NULL ){
		return abb_guardar_aux(arbol,nodo_padre->izq,arbol->cmp(clave, nodo_padre -> izq-> clave),clave,dato);
	}
	// tengo que reemplazar el dato de la clave en la que me encuentro.
	return reemplazar_dato(arbol,nodo_padre,dato);
}

//Pre: El abb fue creado.
//Post: Devuelve un true si pudo guardar el par (clave,dato) en el abb y false en caso contrario 
bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
	if ( clave == NULL ) return false;
	if( arbol -> cantidad == 0 ){
		abb_nodo_t* abb_nodo = abb_nodo_crear(clave,dato);
		if( abb_nodo == NULL ) return false;
		arbol->raiz = abb_nodo;
		arbol -> cantidad++; 
		return true;
	}
	return abb_guardar_aux(arbol, arbol -> raiz, arbol -> cmp(clave, arbol->raiz-> clave),clave,dato);
}

//Busca el nodo correspondiente a la clave asociada al par (clave,valor). Si se encuentra devuelve el nodo
//y en el caso contrario devuelve NULL.
//Si se le pasa como ultimo parametro true, busca el padre del nodo.
abb_nodo_t* buscar_nodo_en_abb(const abb_nodo_t *nodo,const char *clave,abb_comparar_clave_t cmp,bool buscar_padre){
	if( cmp(clave,nodo->clave) == 0 ){
		return (abb_nodo_t*)nodo;	
	}  
	// que la clave sea mayor que la del nodo
	if( cmp(clave,nodo->clave) > 0 && nodo->der != NULL){
		if( buscar_padre == false) return buscar_nodo_en_abb(nodo->der, clave, cmp,buscar_padre);
		//cuando Buscar_padre es true aca buscaria al padre
		if( cmp(clave,nodo->der->clave) == 0 ) return (abb_nodo_t*)nodo;
		return buscar_nodo_en_abb(nodo->der, clave, cmp,buscar_padre);	
	}
	// que la clave sea menor que la del nodo
	if( cmp(clave,nodo->clave) < 0 && nodo->izq != NULL){ 
		if( buscar_padre == false ) return buscar_nodo_en_abb(nodo->izq, clave, cmp,buscar_padre);
		//cuando Buscar_padre es true aca buscaria al padre
		if( cmp(clave,nodo->izq->clave) == 0 ) return (abb_nodo_t*)nodo;
		return buscar_nodo_en_abb(nodo->izq, clave, cmp,buscar_padre); 
	}
	return NULL;
}

//Pre:El arbol fue creado.
//Post:devuelve true si la clave existe dentro del abb y en caso contrario false.
bool abb_pertenece(const abb_t *arbol, const char *clave){
	if( arbol-> cantidad == 0 ) return false;
	if( clave == NULL ) return false;
	if(buscar_nodo_en_abb(arbol->raiz, clave, arbol-> cmp, false) == NULL) return false;
	return true; 
}

//Pre:El arbol fue creado.
//Post:Si la clave no existe dentro del abb o el abb esta vacio devuelve NULL.
//En caso de que la clave exista dentro del abb este, devuelve el dato asociado al par (clave,dato).
void *abb_obtener(const abb_t *arbol, const char *clave){
	if( arbol-> cantidad == 0 ) return NULL;
	if( clave == NULL ) return NULL;
	abb_nodo_t *nodo = buscar_nodo_en_abb(arbol->raiz, clave, arbol -> cmp , false);
	if(!nodo) return NULL;
	return nodo->dato;
}

//Destruye el nodo y la clave que le pase por parametro.
void destruir_nodo_y_clave(abb_nodo_t* nodo,char* clave){
	free( clave );
	free( nodo );
}

//funcion auxiliar de abb_borrar el cual contempla el caso cuando el par(clave,dato) a borrar es una hoja.
void* caso_nodo_sin_hijos(abb_t* arbol,abb_nodo_t* nodo_padre, abb_nodo_t* nodo_hijo){
	void* dato_a_devolver = nodo_hijo -> dato;
	// me fijo si el nodo_hijo esta a la izq o der del nodo_padre.
	if( nodo_padre -> izq != NULL && arbol->cmp(nodo_padre->izq->clave,nodo_hijo->clave) == 0 ){
		nodo_padre -> izq = NULL;
	}
	else{
		nodo_padre-> der = NULL;
	}
	destruir_nodo_y_clave(nodo_hijo,(char*)nodo_hijo->clave);
	arbol->cantidad--;
	return dato_a_devolver;
}

//funcion auxiliar de abb_borrar el cual contempla el caso cuando el par(clave,dato) a borrar es un nodo
// que no es la raiz, y que ese nodo tiene un solo hijo.
void* caso_nodo_con_un_hijo(abb_t* arbol,abb_nodo_t* nodo_padre,abb_nodo_t* nodo){
	void* dato_a_borrar = nodo -> dato;
	abb_nodo_t* nodo_a_borrar = nodo;
	if( nodo_padre -> izq  != NULL && arbol->cmp(nodo_padre -> izq->clave,nodo->clave) == 0 ){
		if( nodo -> izq == NULL ) nodo_padre -> izq = nodo->der;
		else{ nodo_padre -> izq = nodo -> izq; }	
	}
	else{
		if( nodo -> der == NULL ) nodo_padre -> der = nodo->izq;
		else{ nodo_padre -> der = nodo -> der; }
	}
	destruir_nodo_y_clave(nodo_a_borrar,(char*)nodo_a_borrar->clave);
	arbol->cantidad--;	
	return	dato_a_borrar;
}

//funcion auxiliar de abb_borrar el cual contempla el caso cuando el par(clave,dato) a borrar es la raiz.
void* caso_nodo_con_un_hijo_raiz(abb_t* arbol,abb_nodo_t* nodo_raiz,abb_nodo_t* nodo){
	char* clave_a_borrar = (char*)nodo_raiz->clave; 
	void* dato_a_borrar = nodo_raiz -> dato;

	arbol->raiz = nodo;

	destruir_nodo_y_clave(nodo_raiz,clave_a_borrar);
	arbol->cantidad--;
	return dato_a_borrar;
}

//funcion auxiliar del abb_borrar el cual busco al hijo mas izq del lado derecho como remplazante del nodo 
// a borrar.
abb_nodo_t* buscar_nodo_padre_del_mas_a_la_izq(abb_nodo_t* nodo){
	if(  nodo -> izq != NULL && nodo -> izq -> izq == NULL ) return nodo;	
	return buscar_nodo_padre_del_mas_a_la_izq(nodo -> izq); 
}

//funcion auxiliar de abb_borrar el cual contempla el caso cuando el par(clave,dato) a borrar es un nodo
// ya sea la raiz o un nodo, cuando se tiene 2 hijos.
void* caso_nodo_con_dos_hijos(abb_t* arbol,abb_nodo_t* nodo){
	abb_nodo_t* nodo_hijo_der = nodo -> der; 
	abb_nodo_t* nodo_reemplazante;

	char* clave_a_borrar = (char*)nodo -> clave;
	void* dato_a_borrar = nodo -> dato;

	abb_nodo_t* nodo_padre_remp = nodo;	
	if( nodo_hijo_der-> izq != NULL ) {
		nodo_padre_remp = buscar_nodo_padre_del_mas_a_la_izq(nodo_hijo_der);
		nodo_reemplazante = nodo_padre_remp->izq;
	}
	else{
		// si entra aca es porque nodo_padre_remp = nodo 
		nodo_reemplazante = nodo_hijo_der; 
	}

	// AL ser el hijo mas izq es natural que tengo izquierda, no asi la derecha que puede o no tenerla.
	if( nodo_reemplazante -> der != NULL ){
		if( arbol->cmp(nodo_padre_remp->clave,nodo->clave) == 0) nodo_padre_remp->der = nodo_reemplazante->der;
		else {nodo_padre_remp -> izq = nodo_reemplazante -> der; } 
	}
	else{
		if( arbol -> cmp(nodo_padre_remp->clave,nodo->clave) == 0 ) nodo_padre_remp -> der = NULL;	
		else{ nodo_padre_remp -> izq = NULL; }
	} 
	nodo -> clave = nodo_reemplazante -> clave;
	nodo -> dato = nodo_reemplazante -> dato;
	
	destruir_nodo_y_clave(nodo_reemplazante,clave_a_borrar);
	arbol -> cantidad--;

	return dato_a_borrar;
} 

//Funcion_auxiliar que comtempla los casos de la raiz.
void* caso_nodo_raiz_borrar(abb_t* arbol,abb_nodo_t* nodo_raiz){
	if( nodo_raiz -> izq == NULL && nodo_raiz -> der == NULL  ){
		void* dato_a_borrar = nodo_raiz -> dato;
		destruir_nodo_y_clave(nodo_raiz,(char*)nodo_raiz->clave);
		arbol->raiz = NULL;
		arbol->cantidad--;
		return dato_a_borrar;	
	}
	if( nodo_raiz -> izq != NULL && nodo_raiz -> der != NULL   ){
		return caso_nodo_con_dos_hijos(arbol,nodo_raiz);
	}
	if( nodo_raiz -> izq != NULL ){
		return caso_nodo_con_un_hijo_raiz(arbol,nodo_raiz,nodo_raiz->izq);	
	}
	return caso_nodo_con_un_hijo_raiz(arbol,nodo_raiz,nodo_raiz->der);
}

//Pre:El arbol fue creado.
//Post: Si la clave no existe dentro del abb o el abb esta vacio devuelve NULL.
//En caso de que la clave exista dentro del abb este, devuelve el dato asociado al par (clave,dato) y 
//borra la clave asociada a ese dato.
void* abb_borrar(abb_t* arbol, const char* clave){
	if( arbol-> cantidad == 0 ) return NULL;
	if( clave == NULL ) return NULL;
	abb_nodo_t* nodo_padre = buscar_nodo_en_abb(arbol->raiz,clave,arbol->cmp,true);
	if( nodo_padre == NULL ){
		return NULL;	
	}

	abb_nodo_t* nodo = nodo_padre -> izq;
	if( arbol->cmp(clave,nodo_padre->clave) == 0 ){
		return caso_nodo_raiz_borrar(arbol,nodo_padre);	
	}
	if( nodo_padre-> der != NULL && arbol->cmp(clave,nodo_padre-> der ->clave) == 0 ) nodo = nodo_padre -> der;

	if( nodo->izq == NULL && nodo->der == NULL ){
		return caso_nodo_sin_hijos(arbol,nodo_padre,nodo);
	}
	if( (nodo->izq != NULL && nodo->der == NULL ) || (nodo->izq == NULL && nodo->der != NULL) ){
		return caso_nodo_con_un_hijo(arbol,nodo_padre,nodo);
	}
	// si llegue aca, es que porque el porque el nodo tenia 2 hijos.
	return caso_nodo_con_dos_hijos(arbol,nodo);
}

//Pre:El arbol fue credo.
//funcion aux recursiva que hace un recorrido post-order para destruir los nodos.
void abb_destruir_r(abb_t* arbol,abb_nodo_t* nodo){
	if( nodo->izq != NULL){
		abb_destruir_r(arbol,nodo->izq);
		nodo-> izq = NULL;	
	} 
	if( nodo->der != NULL){
		abb_destruir_r(arbol,nodo->der);	
		nodo -> der = NULL;
	}
	if( arbol->destructor != NULL ) arbol -> destructor(nodo->dato);
	destruir_nodo_y_clave(nodo,(char*)nodo->clave);
}

//Pre:El arbol fue credo.
//Post:Destruye el abb.
void abb_destruir(abb_t *arbol){
	if( arbol-> cantidad > 0 ) abb_destruir_r(arbol,arbol->raiz);
	free(arbol);
}

//COMIENZO DEL RECORRIDO INORDER CON ITER EXTERNO
typedef struct abb_iter abb_iter_t;

struct abb_iter{
    pila_t* pila;
};

//funcion auxiliar que mete los nodos en una pila para hacer un recorrido in order
void mas_chico_pila(abb_nodo_t* nodo, pila_t* pila){
    if(!nodo) return;
    pila_apilar(pila, nodo);
    mas_chico_pila(nodo->izq, pila);
}

//Crea el iter ext sobre el cual es posible hacer el recorrido inorder.
abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
    abb_iter_t* iter = malloc(sizeof(abb_iter_t));
    if(!iter) return NULL;
    iter->pila = pila_crear();
    if(!(iter->pila)) return NULL;
    mas_chico_pila(arbol->raiz, iter->pila);
    return iter;
}

//Pre:El iter ext fue creado.
//Post: Devuelve true o false si el iter ext se encuentra al final.
bool abb_iter_in_al_final(const abb_iter_t *iter){
    return pila_esta_vacia(iter->pila);
}

//Pre:El iter ext fue creado.
//Post: Devuelve la clave por la cual estas posicionado. Si el iter ext esta al final del abb devuelve NULL.
const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
    if(abb_iter_in_al_final(iter)) return NULL;
    abb_nodo_t* aux = pila_ver_tope(iter->pila);
    return aux->clave;
}

//Pre:El iter fue creado.
//Destruye el iter ext.
void abb_iter_in_destruir(abb_iter_t* iter){
    pila_destruir(iter->pila);
    free(iter);
}

//Pre:El iter ext fue creado.
//Post:Devuelve true si el iter ext no esta al final del abb y en caso contrario false.
bool abb_iter_in_avanzar(abb_iter_t *iter){
    if(abb_iter_in_al_final(iter)) return false;
    abb_nodo_t* aux = pila_desapilar(iter->pila);
    if(aux->der){
        mas_chico_pila(aux->der, iter->pila);
    }
    return true;
}
//FIN DEL RECORRIDO INORDER CON ITER EXTERNO  

// COMIENZO DEL ITER INTERNO

//funcion recursiva que hace el recorrido in-order con el iterador interno.
void abb_in_order_r(abb_nodo_t *nodo, bool (*visitar)(const char *clave, void *dato, void *extra),void *extra){
    if(!nodo || extra == NULL) return;
    abb_in_order_r(nodo->izq, visitar, extra);
    if(!visitar(nodo->clave, nodo->dato, extra)){
		extra = NULL;
		return;
	}
    abb_in_order_r(nodo->der, visitar, extra);
}

//recorrido interno inorder.
//Aplica lo que se que le pase a la funcion visitar sobre cada elem del abb.
void abb_in_order(abb_t *arbol, bool (*visitar)(const char *clave, void *dato, void *extra), void *extra){
	if(!arbol || visitar == NULL) return;
	if( arbol->cantidad == 0 ) return;
	return abb_in_order_r(arbol->raiz,visitar,extra);
}
//FIN DEL RECORRIDO INORDER CON ITER INTERNO.

