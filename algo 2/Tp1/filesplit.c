#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int separador_de_archivos(const char *nombre, size_t n){
	FILE *archivo = fopen(nombre, "r");
	if(!archivo) return -1;
	char str[n+1];
	int contador = 1;
	while(!(feof(archivo))){
		fread(str, 1, n, archivo);
		char arch_nue[255];
		sprintf(arch_nue,"%s_%04d",nombre,contador);
		FILE* archivo2 = fopen(arch_nue, "w");
		fprintf(archivo2,"%s",str);
		contador++;
		fclose(archivo2);
	}
	fclose(archivo);
	return 1;
}
			
int main(int argc, char* argv[]){
	if(argc != 3){
		fprintf(stderr,"ERR:Falta algun dato");
		return EXIT_FAILURE;
	}
	if (!(atoi(argv[2]))){
		fprintf(stderr,"ERR:No escribio un numero");
		return EXIT_FAILURE;
	} 
	int j = separador_de_archivos(argv[1], atoi(argv[2]));
	if(j == -1){
		fprintf(stderr,"ERR:Nombre de archivo inexistente");
		return EXIT_FAILURE;
	}
	if(j == -2){
		fprintf(stderr,"ERR:Memoria insuficiente");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

