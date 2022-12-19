#include "hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define FACTOR_CARGA 70
#define REDIM_SUP 2
#define REDIM_INF 0.5
#define MIN_CAPAC 0.25
#define TAM_INICIAL 10007


typedef enum {BORRADO,VACIO,OCUPADO} estado_t;

typedef struct campo_hash campo_hash_t;

struct campo_hash{
	char* clave;
	void* dato;
	estado_t estado;
};

struct hash{
	size_t cantidad;
	size_t tamanio;
	campo_hash_t* tabla;
	hash_destruir_dato_t destructor;
};

// funcion de hash la cual al introducir un clave me devuelve una posicion de la tabla.
size_t func_hash(const char *word, size_t hashTableSize){
	int hashAddress = 0;
	for (int counter = 0; word[counter]!='\0'; counter++){
	    hashAddress = word[counter] + (hashAddress << 6) + (hashAddress << 16) - hashAddress;
	}
	return (size_t)(hashAddress%hashTableSize);
}


//funciona auxiliar la cual me permite buscar la posicion en la que se encuentra una clave existente
//en la tabla de hash. Si encontro la posicion devuelvo true.
//En caso de que corte porque encontre una posicion con estado VACIO o BORRADO si esp_guardar es true.
bool buscando_pos_en_tabla( const hash_t* hash, size_t* pos_hash, const char *clave,bool esp_guardar){
	// Parto de que si no es OCUPADO no me interesa, es decir no me interesa BORRADO.
	bool clave_encontrada = false;
	while( hash -> tabla[*pos_hash].estado != VACIO && !clave_encontrada ) {
		if( hash->tabla[*pos_hash].estado == OCUPADO && strcmp( hash -> tabla[*pos_hash].clave ,clave ) == 0 ){
			clave_encontrada = true;
		}
		else{
			if ( esp_guardar && hash->tabla[*pos_hash].estado == BORRADO ) break;
			(*pos_hash)++;
			if( *pos_hash == hash -> tamanio ) *pos_hash = 0;
		}
	}
	return clave_encontrada;
}

/* Guarda un elemento en el hash, si la clave ya se encuentra en la
 * estructura, la reemplaza. De no poder guardarlo devuelve false.
 * Pre: La estructura hash fue inicializada
 * Post: Se almacenó el par (clave, dato)
 */
bool guardar_elem_en_tabla(hash_t *hash, const char *clave, void *dato){
	size_t h = func_hash(clave,hash -> tamanio);
	if( hash_pertenece( hash,clave ) ){
		buscando_pos_en_tabla(hash,&h,clave,false);
		if( hash->destructor != NULL ){
			hash->destructor(hash->tabla[h].dato);	 
		}
		hash->tabla[h].dato = dato;
		return true;
	}
	buscando_pos_en_tabla(hash,&h,clave,true);
	if( hash->tabla[h].estado == BORRADO){
		hash ->tabla[h].clave = realloc( hash ->tabla[h].clave,(strlen(clave)+1)*sizeof(char) );
	}
	else{
		// pido strlen(clave) + 1 porque tengo que contemplar el largo de la cadena y el '\0' de al final.
		hash->tabla[h].clave = malloc( ( strlen(clave) + 1 )*sizeof(char) );
	}
	if( hash ->tabla[h].clave == NULL ) return false;
	strcpy( hash->tabla[h].clave , clave );
	hash->tabla[h].dato = dato;
	hash->cantidad++;
	hash->tabla[h].estado = OCUPADO;
	return true;
}

//Inicializa los estados de cada campo en VACIO.
void inicializar_tabla(campo_hash_t *tabla, size_t tam){
	for(int i = 0; i < tam; i++){
		tabla[i].estado = VACIO;
	}
} 

//Destruye el contenido de la tabla pero según el caso.
//Si el ultimo parametro es false solo destruyos las claves y si  es true destruyo el par (clave,dato).
void destruir_contenido_tabla(campo_hash_t* tabla,size_t tamanio,hash_destruir_dato_t destructor,bool dest_todo){
	for (int pos_hash = 0; pos_hash < tamanio; ++pos_hash){
		if( tabla[pos_hash].estado == VACIO ) continue;
		if( dest_todo && destructor && tabla[pos_hash].estado == OCUPADO ) destructor( tabla[pos_hash].dato );
		free( tabla[pos_hash].clave );
	}
}

//Redimensiona la tabla segun el caso,agrandar como achicar, de manera que se pueda seguir usando.
//Devuelve un True si la redimension se pudo llevar a cabo y en caso contrario False.
bool redimensionar_tabla(hash_t* hash,size_t tam_nuevo){
	campo_hash_t* tabla_nueva = malloc( tam_nuevo * sizeof(campo_hash_t) );
	if( tabla_nueva == NULL ) return false;
	campo_hash_t* tabla_vieja = hash -> tabla;
	hash -> tabla = tabla_nueva;
	size_t tam_viejo = hash -> tamanio;
	hash -> tamanio = tam_nuevo;
	inicializar_tabla( hash-> tabla, hash -> tamanio);
	//tengo que hashear cada par (clave,dato) de nuevo.
	for (int indice_hash = 0; indice_hash < tam_viejo; indice_hash++){
		if( tabla_vieja[indice_hash].estado == OCUPADO){
			guardar_elem_en_tabla( hash , tabla_vieja[indice_hash].clave , tabla_vieja[indice_hash].dato);
			hash->cantidad--;
		}
	}
	destruir_contenido_tabla(tabla_vieja,tam_viejo,hash->destructor,false);
	free(tabla_vieja);
 	return true;
}


/* Crea el hash
 */
hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
	hash_t* tu_hash = malloc( sizeof(hash_t) );
	if( !tu_hash ) return NULL;
	tu_hash -> tamanio = TAM_INICIAL;
	tu_hash -> cantidad = 0;
	tu_hash -> destructor = destruir_dato;
	tu_hash -> tabla = (campo_hash_t*)malloc( sizeof(campo_hash_t)* tu_hash->tamanio );
	if( !tu_hash -> tabla ){ 
		free( tu_hash );
		return NULL;
	}
	inicializar_tabla( tu_hash->tabla , tu_hash->tamanio );
	return tu_hash;
}


/* Determina si clave pertenece o no al hash.
 * Pre: La estructura hash fue inicializada
 */
bool hash_pertenece(const hash_t *hash, const char *clave){
	size_t pos_hash = func_hash( clave,  hash -> tamanio );
	return buscando_pos_en_tabla(hash,&pos_hash,clave,false);
}


/* Guarda un elemento en el hash, si la clave ya se encuentra en la
 * estructura, la reemplaza. De no poder guardarlo devuelve false.
 * Pre: La estructura hash fue inicializada
 * Post: Se almacenó el par (clave, dato)
 */
bool hash_guardar(hash_t *hash, const char *clave, void *dato){
	if (!guardar_elem_en_tabla(hash,clave,dato)) return false;
	if( ( (float)hash->cantidad / (float)hash->tamanio ) * 100   >= FACTOR_CARGA ){
		if( !redimensionar_tabla( hash , (size_t)( (float)hash->tamanio * REDIM_SUP ) )  ) return false;
	}
	return true;
} 


/* Borra un elemento del hash y devuelve el dato asociado.  Devuelve
 * NULL si el dato no estaba.
 * Pre: La estructura hash fue inicializada
 * Post: El elemento fue borrado de la estructura y se lo devolvió,
 * en el caso de que estuviera guardado.	
 */
void *hash_borrar(hash_t *hash, const char *clave){
	if( !hash_pertenece(hash,clave) || clave == NULL ) return NULL;
	// ahora se que la clave existe dentro de mi tabla de hash.
	size_t pos_hash = func_hash(clave,hash -> tamanio);
	buscando_pos_en_tabla(hash,&pos_hash,clave,false);
	void* dato_a_borrar = hash -> tabla[pos_hash].dato;
	hash -> tabla[pos_hash].estado = BORRADO;	
	hash -> cantidad--;
	if( hash -> cantidad < ( (float)hash->tamanio * MIN_CAPAC ) && hash -> tamanio != TAM_INICIAL ){
		redimensionar_tabla( hash,(size_t)( (float)hash-> tamanio * REDIM_INF ) );
	}
	return dato_a_borrar;
}


/* Obtiene el valor de un elemento del hash, si la clave no se encuentra
 * devuelve NULL.
 * Pre: La estructura hash fue inicializada
 */
void *hash_obtener(const hash_t *hash, const char *clave){
	if( !hash_pertenece(hash,clave) ) return NULL;
	size_t pos_hash = func_hash(clave,hash -> tamanio);
	buscando_pos_en_tabla(hash,&pos_hash,clave,false); 
	return hash -> tabla[pos_hash].dato;
}

/* Devuelve la cantidad de elementos del hash.
 * Pre: La estructura hash fue inicializada
 */
size_t hash_cantidad(const hash_t *hash){
	return hash -> cantidad;
}

/* Destruye la estructura liberando la memoria pedida y llamando a la función
 * destruir para cada par (clave, dato).
 * Pre: La estructura hash fue inicializada
 * Post: La estructura hash fue destruida
 */
void hash_destruir(hash_t *hash){
	destruir_contenido_tabla( hash->tabla , hash->tamanio , hash->destructor, true);
	free( hash -> tabla );
	free( hash );
}


 /* ITERADOR DEL HASH */

struct hash_iter{
	hash_t* hash;
	size_t indice;
};


// Crea iterador
hash_iter_t *hash_iter_crear(const hash_t *hash){
	hash_iter_t* iter_hash = malloc( sizeof(hash_iter_t) );
	if( iter_hash == NULL ) return NULL;
	iter_hash -> hash = (hash_t*)hash;
	iter_hash -> indice = 0;
	while( iter_hash -> hash->tabla[iter_hash ->indice].estado != OCUPADO && !hash_iter_al_final(iter_hash) ){
		iter_hash -> indice++;
	} 
	return iter_hash;
} 

// Avanza iterador
bool hash_iter_avanzar(hash_iter_t *iter){
	if( hash_iter_al_final(iter) ) return false;
	iter->indice++;
	while( !hash_iter_al_final(iter) && (iter -> hash -> tabla[ iter -> indice ].estado != OCUPADO) ){
		iter->indice++;
	}
	if( hash_iter_al_final(iter) ) return false;
	return true;
}

// Devuelve clave actual, esa clave no se puede modificar ni liberar.
const char *hash_iter_ver_actual(const hash_iter_t *iter){
	if( hash_iter_al_final(iter) ) return NULL;
	return iter -> hash -> tabla[ iter -> indice ].clave;
}

// Comprueba si terminó la iteración
bool hash_iter_al_final(const hash_iter_t *iter){
	if ( iter -> indice == iter->hash->tamanio || iter-> hash->cantidad == 0 ) return true;
	return false;
}

// Destruye iterador
void hash_iter_destruir(hash_iter_t* iter){
	free(iter);	
}








