#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "hash.h"
#include "counting_filters.h"
#include "heap.h"

#define F_CONTADORES 5
#define TAM_CONTADORES 100003  
#define TAM_V_CAD 50000 
#define MULT_TAM 2 
#define DIV_CAPAC_MIN 2

struct counting_filters{
	size_t** contadores;
	hash_t* hash_tags; 
};

typedef size_t (*func_hashing_t) (char *);

/*funciones de hashing*/
size_t hash_sdbm(char *str){
    size_t hash = 0;
    int c;
    while ( (c = *str++) ){
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}

size_t hash_33(char *str){
	size_t hash = 5381;
	int c;	
	while ( (c = *str++) ){
		hash = ( (hash << 5) + hash) + c; //* hash * 33 + c
	}
	return hash;
}

size_t jenkins_one_at_a_time(char* key){

	size_t hash = 0;
	for (int i = 1; i < strlen(key); ++i){
		hash = hash + key[i];
		hash = hash + (hash << 10);
	}
	hash = hash + (hash << 3);
	hash = hash + (hash << 15);
	return (size_t)abs( (int)hash );
}

size_t rolling_hash(char* s){
    size_t ret = 0;
    size_t prime_base = 257;
    size_t prime_mod  = 1000000007;
    for (int i = 0; i < strlen(s); i++){
        ret = ret*prime_base + s[i];
        ret %= prime_mod; //don't overflow
    }
	return ret;
}

size_t hash_weiss(char* clave){
	size_t num = 128;
	size_t num2 = 2132300;
	size_t valorHash = num*num2;
	for ( int i = 0 ; i < strlen(clave) ; ++i){
		valorHash += (37 << strlen(clave) )  + (4 << strlen(clave) ) ;
	}
	return valorHash;
}

/*Fin de la funciones de hashing usadas para el Counting Bloom filters*/

//Inicializa los contadores con 0.
void inicializar_contadores(size_t* tabla,size_t tamanio){
	for (size_t i = 0; i < tamanio; ++i){
		tabla[i] = 0;
	}	
}

//Libera la memoria pedida hasta el momento en caso de alguna falla en un pedido de memoria
void destruir_tda_parcial(counting_filters_t* counting_filters, size_t tam ){
	for (int i = 0; i < tam; ++i){
		free( counting_filters->contadores[i] );
	}
	free( counting_filters->contadores );
	free( counting_filters );	
}

//Crea el counting filters.
counting_filters_t* counting_filters_crear(){
	counting_filters_t* counting_filters_nuevo = malloc( sizeof(counting_filters_t) );
	if( counting_filters_nuevo  == NULL ) return NULL;
	counting_filters_nuevo -> contadores = malloc( F_CONTADORES*sizeof(size_t*) );  
	
	if( counting_filters_nuevo -> contadores == NULL ){
		free( counting_filters_nuevo );
		return NULL;
	}

	counting_filters_nuevo->hash_tags = hash_crear(NULL);
	if( counting_filters_nuevo->hash_tags == NULL ){
		free(counting_filters_nuevo -> contadores);
		free(counting_filters_nuevo);
		return NULL;
	}

	for (int i = 0; i < F_CONTADORES; ++i){
		counting_filters_nuevo->contadores[i] = malloc( TAM_CONTADORES*sizeof(size_t) ); 
		if( counting_filters_nuevo->contadores[i] ==  NULL ){
			destruir_tda_parcial(counting_filters_nuevo,i);
			return NULL;
		}
	}

	for (int i = 0; i < F_CONTADORES; ++i){
		inicializar_contadores( counting_filters_nuevo->contadores[i],(size_t)TAM_CONTADORES);	
	}

	return counting_filters_nuevo;
}

//Comprime el resultado de la funcion de hashing para obtener un valor dentro del tam de los contadores.
size_t compresor_de_claves(size_t res_clave,size_t tam_tabla){
	if( res_clave < tam_tabla ) return res_clave;
	return res_clave % tam_tabla;
}


//Pre: el counting filters fue creado.
//obtener de los resultados de la funciones de hashing, el menor resultado el cual sera la menor aparicion de
//de ese tweet.
size_t obtener_menor_aparicion(counting_filters_t* counting_filters,size_t* vec_pos){
	size_t menor_aparac = counting_filters->contadores[0][vec_pos[0]];
	for (size_t i = 1; i < F_CONTADORES; ++i){
		if( menor_aparac > counting_filters->contadores[i][ vec_pos[i] ] ){
			menor_aparac = counting_filters->contadores[i][ vec_pos[i] ];
		}
	}
	return menor_aparac;
}


//Pre: el counting filters fue creado.
//Post:Agrega el hashtag al counting filters.
void counting_filters_agregar_aparicion_hashtag(counting_filters_t* counting_filters,char* hashtag){
	func_hashing_t  vec_func[]= {hash_sdbm,hash_33,jenkins_one_at_a_time,hash_weiss,rolling_hash};
	size_t vec_pos[F_CONTADORES];
	if( !hash_pertenece(counting_filters->hash_tags,hashtag) ){
		hash_guardar(counting_filters->hash_tags,hashtag,NULL);	
	}

	for (size_t i = 0; i < F_CONTADORES; ++i){
		vec_pos[i] = vec_func[i](hashtag);
		vec_pos[i] = compresor_de_claves(vec_pos[i],(size_t)TAM_CONTADORES );	
		counting_filters->contadores[i][ vec_pos[i] ]++;
	}
}

//obtiene la menor aparcion de los resultados de la func de hashing luego de que fue pasado por el compresor
//de claves y se pudo obtener un valor dentro de los contadores.
size_t obtener_apar_de_hashtag(counting_filters_t* counting_filters, char* hashtag){
	func_hashing_t  vec_func[]= {hash_sdbm,hash_33,jenkins_one_at_a_time,hash_weiss,rolling_hash};
	size_t vec_pos[F_CONTADORES];

	for (size_t i = 0; i < F_CONTADORES; ++i){
		vec_pos[i] = vec_func[i](hashtag);
		vec_pos[i] = compresor_de_claves(vec_pos[i],(size_t)TAM_CONTADORES );	
	}
	return obtener_menor_aparicion(counting_filters,vec_pos);
}

//Destruye el counting filters.
void counting_filters_destruir(counting_filters_t* counting_filters){
	for (int i = 0; i < F_CONTADORES; ++i){
		free( counting_filters->contadores[i] );
	}
	hash_destruir(counting_filters->hash_tags);
	free( counting_filters->contadores );
	free( counting_filters );
}

//Implementacion de la primitivas para el treding topic.
struct datos_trending_topic{
	char* nombre;
	size_t cant_apar;
};

//funcion de comparacion para hacer un min-heap
int trending_topic_cmp(const void* dato1, const void* dato2){
	if( ((datos_trend_top_t*)dato1)->cant_apar > ((datos_trend_top_t*)dato2)->cant_apar ) return -1;
	if( ((datos_trend_top_t*)dato1)->cant_apar < ((datos_trend_top_t*)dato2)->cant_apar ) return  1;
	return 0;
}

//Crea los datos que van a forma parte del trending topic.
datos_trend_top_t* datos_trend_top_crear(char* nombre, size_t cantidad){
	datos_trend_top_t* datos_tt = malloc( sizeof(datos_trend_top_t) );
	if( datos_tt == NULL ) return NULL;
	datos_tt->nombre = nombre;
	datos_tt->cant_apar = cantidad;
	return datos_tt;
}

//Crea un arreglo el cual contiene un listado en orden de los numeros de apariciones.
datos_trend_top_t** trending_topic_crear(counting_filters_t* counting_filters,size_t tam_trend_topic){
	heap_t* heap = heap_crear(trending_topic_cmp);
	hash_iter_t* iter_hash = hash_iter_crear(counting_filters->hash_tags);

	while( !hash_iter_al_final(iter_hash) ){
		char* hashtag_actual = (char*)hash_iter_ver_actual(iter_hash);
		size_t contador_hashtag = obtener_apar_de_hashtag(counting_filters,hashtag_actual);
		if( heap_cantidad(heap) < tam_trend_topic ){
			datos_trend_top_t* dato = datos_trend_top_crear(hashtag_actual,contador_hashtag);
			heap_encolar(heap,dato);	
		} 
		else{
			if( contador_hashtag > ((datos_trend_top_t*)heap_ver_max(heap))->cant_apar){
				datos_trend_top_t* dato_borrado = heap_desencolar(heap);
				datos_trend_top_t* dato = datos_trend_top_crear(hashtag_actual,contador_hashtag);
				free(dato_borrado);
				heap_encolar(heap,dato);
			}
		}
		hash_iter_avanzar(iter_hash);
	}
	hash_iter_destruir(iter_hash);

	datos_trend_top_t** trending_topic = malloc( tam_trend_topic*sizeof(datos_trend_top_t*) );
	if( trending_topic == NULL ) return NULL;

	for (int pos = (int)tam_trend_topic-1; pos >= 0; --pos){
		trending_topic[pos] = (datos_trend_top_t*)heap_desencolar(heap);
	}
	heap_destruir(heap,NULL);
	return trending_topic;
}

//imprime por salida estandar el trending topic.
void imprimir_trending_topic(datos_trend_top_t** trending_topic,size_t tam_trend_topic){
	printf("\nTrending Topic\n");
	for (int i = 0; i < tam_trend_topic; ++i){
		printf("%d-%s\n",i+1,trending_topic[i]->nombre);
	}
	printf("\n");
}

//destruye el trending topic.
void trending_topic_destruir(datos_trend_top_t** trending_topic,size_t tam_trend_topic){
	for (int i = 0; i < tam_trend_topic; ++i){
		free(trending_topic[i]);
	}
	free(trending_topic);
}

//Pre:El counting filters fue creado.
//Restablece el historial de tweets dejandolo vacio, para armar el siguiente trending topic.
bool counting_filters_reestableciendo_historial(counting_filters_t* counting_filters){
	hash_destruir(counting_filters->hash_tags);
	hash_t* hash_nuevo = hash_crear(NULL);
	if( hash_nuevo == NULL ) return false;;
	counting_filters->hash_tags = hash_nuevo;
	return true;
}
