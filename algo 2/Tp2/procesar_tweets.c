#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include "counting_filters.h"
#include "strutil.h"


//En el caso de que el hashtag tenga un salto de linea se lo saca.
void sacar_salto_de_linea(char* hashtag){
	if( hashtag[strlen(hashtag)-1] == '\n' ) hashtag[strlen(hashtag)-1] = '\0'; 
}// lo separe para que el codigo se más legible.

//Proceso lo twees de manera que cada n lineas imprima un trending topic de k elementos.
void procesar_tweets( size_t n, size_t k){
	counting_filters_t* counting_filters = counting_filters_crear();
	char* linea = NULL;
	size_t capacidad = 0;
	char sep = ',';
	size_t cant_lineas = 0;
	while( getline(&linea,&capacidad,stdin) != -1 ){
		char** hashtags = split(linea,sep);
		for (int i = 1; hashtags[i] != NULL; ++i){
			sacar_salto_de_linea(hashtags[i]);
			counting_filters_agregar_aparicion_hashtag(counting_filters,hashtags[i]);
		}// esto es aprox O(3), porque son 3 tweets aprox por linea. aproximando queda O(1).
		cant_lineas++;
		if( cant_lineas % n == 0 ){
			//Cuando llega a esta instancia lleva recorrido O(n).
			datos_trend_top_t** trending_topic = trending_topic_crear(counting_filters,k);	
			imprimir_trending_topic(trending_topic,k);
			trending_topic_destruir(trending_topic,k);
			//Realizar el trending topic cuesta O(nlogk).
			if( !counting_filters_reestableciendo_historial(counting_filters) ) break;
		}
		free_strv(hashtags);
	}
	free(linea);	
	counting_filters_destruir(counting_filters);
}//fin de procesar_tweets.

//valide el numero que es ingresado por parametro.
bool validando_ingreso_numero(char const* pos_num){
	bool datos_validos = true;
	for (int i = 0; i < strlen(pos_num); ++i){
		if( !isdigit(pos_num[i]) ){
			datos_validos = false;
			break;
		} 	 
	}
	return datos_validos;
}// fin de validacion de numero.

//Programa principal.
int main(int argc, char const *argv[]){
	if( argc != 3 ){
		fprintf(stderr, "No ingesaste la cantidad de parametros correcta\n");
		return EXIT_FAILURE;
	}
	bool datos_validos1 = validando_ingreso_numero(argv[1]);
	bool datos_validos2 = validando_ingreso_numero(argv[2]);
	if( !datos_validos1 && !datos_validos2 ){
		fprintf(stderr, "Uno de los datos ingresados no es un numero\n");
		return EXIT_FAILURE;
	}
	if( atoi(argv[1]) < atoi(argv[2]) ){
		fprintf(stderr, "El primer parametro es menor al segundo.ERROR\n");
		return EXIT_FAILURE;
	}
	procesar_tweets((size_t)atoi(argv[1]) ,(size_t)atoi(argv[2]) );
	return 0;
}