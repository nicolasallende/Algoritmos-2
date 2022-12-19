#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 50

/* Devuelve un arreglo dinamico terminado en NULL con todos los subsegmentos
 * de "str" separados por el caracter "sep". Tanto el arreglo devuelto
 * como la cadena que contiene son allocadas dinamicamente
 * 
 * Quien llama a la funcion toma responsabilidad de la memoria dinamica
 * del arreglo devuelto. La funcion devuelve NULL si fallo alguna 
 * llamada a malloc o si "sep" es igual a "\0". */

char** split(const char* str, char sep){
	int mat[MAX];//tiene la cantidad de caracteres entre separaciones
	int cant_el = 0;
	int k = 0;
	size_t leng = strlen(str)+1;
	int cant = 1;
	for (int i = 0; i < leng; i++){
		if (str[i] == sep){
			cant++;
			mat[k] = cant_el;
			cant_el = 0;
			k++;
		}else{
			cant_el++;
		}
	}
	mat[k] = cant_el;	
	char **separado = malloc(sizeof(char*) * (cant +1) );
	if (!separado) return NULL;
	for(int i = 0; i< cant; i++){
		separado[i] = malloc(sizeof(char) * ((mat[i])+1));
		if (!separado[i]) return NULL;
	}
	int i = 0;
	int j = 0;
	for(k = 0; k < cant; k++){
		while((str[i] != sep) &&( i < leng)){
			separado[k][j] = str[i];
			i++;
			j++;
		}
		separado[k][j] = '\0';
		j = 0;
		i++;
	}
	separado[cant] = NULL;
	return separado;
}



/* Libera un arreglo dinamico de cadenas, y todas las cadenas que contiene */
void free_strv(char *strv[]){
	int i = 0;
	while(strv[i]){
		free(strv[i]);
		i++;
	}
	free(strv);
}

/* Devuelve una cadena, allocada dinamicaente, resultado de unir
 * todas las cadenas del arreglo terminado en NULL "strv".
 * 
 * Quien llama a la funcion toma responsabilidadde la memoria dinamica 
 * de la cadena devuelta. La funcion devuelve NULL si no se pudo 
 * allocar memoria.*/   
 
 char* join(char** strv, char sep){
	if(strv == NULL) return NULL;
	size_t leng = 0;
	int cant = 0;
	int k = 0;
	while(strv[k]){
		leng += (strlen(strv[k]) +1);
		k++;
		cant++;
	}
	char* junto = malloc((sizeof(char) * leng) + 1);
	if (!junto) return NULL;
	k = 0;
	for(int i = 0; i < cant ; i++){
		size_t largo = strlen(strv[i]);
		for(int j = 0; j < largo; j++){
			junto[k] = strv[i][j];
			k++;
		}
		if(strv[i+1] != NULL){
			junto[k] = sep;
			k++;
		}
	}
	junto[k] = '\0';
	return junto;
}
/*
int main(void){
	char* algo = "ab,cd";
	char** separado = split(algo,',');
	char* junto = join(separado, ';');
	free(junto);
} 
*/