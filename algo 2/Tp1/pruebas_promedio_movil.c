#include "prom_movil.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


void prueba_1(int k){
	int n = 6;
	int arreglo[n];
	arreglo[0] = 3; 
	arreglo[1] = 5;
	arreglo[2] = 4;
	arreglo[3] = 8;
	arreglo[4] = 2;
	arreglo[5] = 1;
	double* promedios  = obtener_promedio_movil(arreglo, n, k);
	printf("Valor del no optimizado\n");
	for(int i = 0;  i < n; i++){
		double vale = promedios[i];
		printf("%f\n", vale);
	}
	free(promedios);
	promedios  = obtener_promedio_movil_optimizado(arreglo, n, k);
	printf("Valor del optimizado\n");
	for(int i = 0;  i < n; i++){
		double vale = promedios[i];
		printf("%f\n", vale);
	}
}


void prueba_tiempo(int k, int n){
	int arreglo[n];
	for(int i = 0; i < n; i++){
		arreglo[i] = i;
	}
	clock_t start1 = clock();
	double* promedios1  = obtener_promedio_movil(arreglo, n, k);
	clock_t end1 = clock();
	printf("el normal tardo %ld\n", end1-start1);
	clock_t start = clock();
	double* promedios  = obtener_promedio_movil_optimizado(arreglo, n, k);
	clock_t end = clock();
	printf("el optimizado tardo %ld\n", end-start);
	free(promedios);
	free(promedios1);
}


int main(void){
	prueba_1(1);
	//devuelven  4/4/5,6/4,6/3,6/1,5  
	prueba_1(2);
	//devuelven 4/5/4,4/4/3,75/3,66
	prueba_1(6);
	//devuelve 3,83/3,83/3,83/3,83/3,83/3,83
	prueba_tiempo(100,1000);
	prueba_tiempo(500,1000);
	prueba_tiempo(1000,1000);
	prueba_tiempo(500,10000);
	prueba_tiempo(100,10000);
	prueba_tiempo(5000,10000);		
	return 0;
}
