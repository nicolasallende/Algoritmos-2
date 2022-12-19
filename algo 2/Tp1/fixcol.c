#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int divisor_de_columnas(const char *nombre, int n){
	FILE *archivo = fopen(nombre,"r");
	if(!archivo) return -1;
	char str[n+1];
	while(!(feof(archivo))){
		fgets(str, n+1, archivo);
		printf("%s\n", str);
	}
	fclose(archivo);
	return 0;
}


int main(int argc, char* argv[]){
	if(argc != 3){
		fprintf(stderr,"ERR:Cantidad de parametros invalida");
		return EXIT_FAILURE;
	}
	if(!(atoi(argv[2]))){
		fprintf(stderr,"ERR:No ingreso un numero");
		return EXIT_FAILURE;
	}
	int j = divisor_de_columnas(argv[1], atoi(argv[2]));
	if(j == -1){
		fprintf(stderr,"ERR:Nombre de archivo inexistente");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
