#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>

#define CAD_VACIA 1


/* Devuelve en un arreglo dinámico terminado en NULL con todos los subsegmentos
 * de ‘str’ separados por el carácter ‘sep’. Tanto el arreglo devuelto como las
 * cadenas que contiene son allocadas dinámicamente.
 *
 * Quien llama a la función toma responsabilidad de la memoria dinámica del
 * malloc(), o si ‘sep’ es '\0'.
 * arreglo devuelto. La función devuelve NULL si falló alguna llamada a
 */
char** split(const char* str, char sep){
	size_t tam_str = strlen(str);
	if( sep == '\0') return NULL;
	int cantidad_sep = 0;
	for (int i = 0; str[i] != '\0'; ++i)
		if (str[i] == sep) ++cantidad_sep;	
	
	char** arreglo_de_chars = (char**)malloc( (cantidad_sep + 2) * sizeof(char*));
	if( arreglo_de_chars == NULL ) return NULL;

	if( cantidad_sep == 0 ){
		arreglo_de_chars[cantidad_sep] =(char*)malloc( (tam_str + 1)* sizeof(char) );
		strcpy(arreglo_de_chars[0],str);
		arreglo_de_chars[ cantidad_sep  + 1 ] = NULL;
		return arreglo_de_chars;
	}

	int inicio = 0;
	int fin = 0;
	
	for(int i = 0; i <= cantidad_sep; ++i){
		for(fin = inicio; (str[fin] != sep) && (str[fin] != '\0'); ++fin);
		int tam_cad = fin - inicio;
		char* cadena = (char*)malloc((tam_cad + 1) * sizeof(char));
		for (int j = 0; (inicio + j) < fin; ++j)
			cadena[j] = str[inicio + j];
		cadena[tam_cad] = '\0';
		arreglo_de_chars[i] = cadena;
		inicio = fin + 1;
	
	}
	arreglo_de_chars[cantidad_sep + 1] = NULL;
	return arreglo_de_chars;
}

//genera un vector con los tamaños de cada cadena contenida en strv y tambien da la cant de sep.
long* generar_cant_letras_y_sep(long* cant_sep,char** strv,long* cant_letras){
	for (int i = 0; strv[i] != NULL; ++i){
		(*cant_sep)++;
	}

	long* vec_tam_cad = (long*)malloc( (*cant_sep)*sizeof(long) );
	*cant_sep -= 1;// ya que cada dos palabras tiene que haber un separador.

	if( vec_tam_cad == NULL ) return NULL;

	for (int i = 0; strv[i] != NULL; ++i){
		long tam_cad = (long)strlen( strv[i] );
		(*cant_letras) += tam_cad;
		vec_tam_cad[i] = tam_cad; 
	}
	return vec_tam_cad;
}


/* Devuelve una cadena, allocada dinámicamente, resultado de unir todas las
 * cadenas del arreglo terminado en NULL ‘strv’.
 *
 * Quien llama a la función toma responsabilidad de la memoria dinámica de la
 * cadena devuelta. La función devuelve NULL si no se pudo allocar memoria.
 */
char* join(char** strv, char sep){
	if( strv == NULL ) return NULL;
	if( (strv[0] == NULL)  || (strcmp(strv[0],"") && strv + 1 == NULL) ){
		char* cadena = (char*)malloc( CAD_VACIA * sizeof(char) );
		if( cadena == NULL ) return NULL;
		cadena[0] = '\0';
		return cadena;
	}
	long cant_letras = 1; // tengo que contar el '\0' del final de la cadena.
 	long cant_sep = 0;
 
 	// creo un vector con el largo de cada cadena para que lo recorra con for que une las cadenas.
 	long* vec_tam_cad = generar_cant_letras_y_sep(&cant_sep,strv,&cant_letras);
 	if( vec_tam_cad == NULL ) return NULL;

	char* cadena = (char*)malloc( (cant_letras + cant_sep) * (long)sizeof(char));
	if( cadena == NULL) return NULL;
	long pos_cad = 0;
	for (int i = 0; strv[i] != NULL; ++i){
		for (int j = 0; j < vec_tam_cad[i] ; ++j){
			cadena[pos_cad] = strv[i][j];
			pos_cad++;
		}
		if( cant_sep > 0){
			cadena[pos_cad] = sep;
			cant_sep--;
			pos_cad++;
		}
	}
	cadena[pos_cad] = '\0';
	free(vec_tam_cad);
	return cadena;
}

/* Libera un arreglo dinámico de cadenas, y todas las cadenas que contiene. */
void free_strv(char *strv[]){
	size_t pos_cadenas = 0;
	while( strv[pos_cadenas] != NULL ){
		free(strv[pos_cadenas]);
		pos_cadenas++;
	}
	free(strv[pos_cadenas]);
	free(strv);
}

