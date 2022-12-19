#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strutil.h"
#include "hash.h"
#include "cola.h"

#define SEP ','
#define DIV 100

typedef struct nodo nodo_t;

struct nodo{
	char* clave;
	int dato;
};

//Devuelve un numero elevado segun el exponente.
int elevar(int base, int exp){
	if(exp <= 0) return 1;
	return base*elevar(base, exp-1);
}

//Metodo de ordenamiento a traves de buckets(urnas) el cual ordena en O(u+t). 
void counting_sort(nodo_t* arreglo[],void* arregloaux[], int pot, long int cant_user){
	long int pos;
	for(int i = 0; i < cant_user; i++){
		pos = arreglo[i]->dato;
		pos = pos % elevar(DIV, pot);
		pos = pos / elevar(DIV, pot-1);
		if(pos == 0) pos = 100;
		cola_encolar(arregloaux[pos-1], arreglo[i]);
	}
	int j = 0;
	for(int i = 0; i < DIV; i++){
		while(!cola_esta_vacia(arregloaux[i])){
			arreglo[j] = cola_desencolar(arregloaux[i]);
			j++;
		}
	}
}

//Funcion que ordena los elementos en funciones de la cantidad tweets que hizo cada uno. 
void ordenar(nodo_t* arreglo[], int potencia, long int cant_user){
	void*  arregloaux[DIV];
	//inicializo el arreglo auxiliar
	for(int i = 0; i < DIV; i++){
		arregloaux[i] = cola_crear();
	}
	//lo ordena......espero
	for(int i = 1; i <= potencia; i++){
		 counting_sort(arreglo, arregloaux, i, cant_user);
	}
	
	//destruyo todas las colas que ya no me sirven
	for(int i = 0; i < DIV; i++){
		cola_destruir(arregloaux[i],NULL);
	} 
} 

//Imprime por pantalla, en orden,de menos a mayor,el numero de tweets que se hizo y los nombres de los usuarios
// que hicieron ese numero de tweets.
int procesador(const char *nombre){
	FILE *archivo = fopen(nombre, "r");
	if(!archivo) return -1;
	char* linea = NULL;
	size_t largo = 0;
	hash_t* hash = hash_crear(NULL);
	
	//leo todo el archivo y guardo los datos competentes(nombre usuario y cant tuits )
	while(!feof(archivo)){ // O(u + t) = O(t)
		getline(&linea, &largo, archivo);
		char** separado = split(linea, SEP);
		long int cant_tuit = 0;
		while(separado[cant_tuit]){
			cant_tuit++;
		}
		cant_tuit = cant_tuit -1;//el nombre de usuario es el primero por eso resto 1
		if( !hash_pertenece(hash, separado[0]) ){
			int* dato = malloc(sizeof(int));
			*dato = (int)cant_tuit;
			hash_guardar(hash,separado[0],dato);
		}else{
			int* dato = (int*)hash_obtener(hash, separado[0]);
			*dato += (int)cant_tuit;
			hash_guardar(hash, separado[0], dato);
		}
		free_strv(separado);	
		}
	free(linea);
	fclose(archivo);
	
	//aca tengo que recorrer todo, obtener el valor maximo y pasar los datos a un arreglo
	size_t cantidad = hash_cantidad(hash);
	hash_iter_t* iter = hash_iter_crear(hash);
	long int i  = 0, max_cant_tuit = 0;	
	nodo_t** arreglo = malloc(sizeof(nodo_t*) * cantidad);
	while(i < cantidad){// este while es 0(v) 
		nodo_t* nodo = malloc(sizeof(nodo_t));
		arreglo[i] = nodo;
		arreglo[i]->clave = (char*)hash_iter_ver_actual(iter);
		int* dato_borrado = (int*)hash_obtener(hash, arreglo[i]->clave);
		arreglo[i]->dato = *dato_borrado;
		if(arreglo[i]->dato > max_cant_tuit) max_cant_tuit = arreglo[i]->dato;
		i++;
		free(dato_borrado);
		hash_iter_avanzar(iter);
	}
	hash_iter_destruir(iter);
	
	char numero[10];
	sprintf(numero,"%li",max_cant_tuit);
	int potencia = (int)((strlen(numero)/3)+1);
	ordenar(arreglo, potencia, cantidad); // esto es O( d*(v + DIV)) = O(v)
	long int num = 0;
	
	//se encarga de imprimir
	for(long int i = 0; i < cantidad; i++){
		if(num != arreglo[i]->dato){
			num = arreglo[i]->dato;
			printf("\n%li:%s", num, arreglo[i]->clave);
		}else{
			printf(", %s", arreglo[i]->clave);
		}
		free(arreglo[i]);
	}
	free(arreglo);
	printf("\n");
	hash_destruir(hash);
	return 0;
}

//Programa principal.
int main(int argc, char* argv[]){
	if(argc != 2){
		fprintf(stderr,"ERR:Cantidad de parametros invalida");
		return EXIT_FAILURE;
	}
	int j = procesador(argv[1]);
	if(j == -1){
		fprintf(stderr,"ERR:Nombre de archivo inexistente");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
