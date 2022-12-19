#include "prom_movil.h"
#include <stdio.h>
#include <stdlib.h>


double* obtener_promedio_movil(int* arreglo, size_t n, size_t k){
	double* arr = malloc(sizeof(double) * n);
	if(!arr) return NULL;
	double cantidad = 0;
	for(int i = 0; i < n; i++){
		cantidad = arreglo[i];
		int dividir = 1;
		int j = 1;
		while(((i-j) >= 0) && (j <= k)){//este ve los de atras
			cantidad += arreglo[i-j];
			dividir++;
			j++;
		}
		j = 1;
		while(((i+j) < n) && ( j <= k)){//este ve lo de adelante
			cantidad += arreglo[i+j];
			dividir++;
			j++;
		}
		arr[i] = ((double) cantidad) /dividir;
	}
	return arr;
}

double* obtener_promedio_movil_optimizado(int* arreglo, size_t n, size_t k){
	double arreglo2[n];
	double* arregloFinal = malloc(sizeof(double) * n);
	if (!arregloFinal) return NULL; 
	size_t i = 0;
	size_t j = 1;
	int contador = 1;
	if(k == 0){
		for(i = 0; i < n; i++){
			arregloFinal[i] = arreglo[i];
		}
		return arregloFinal;
	}
	double valor = arreglo[i];
	while((j <= k) && (j < n)){
		valor += arreglo[j];
		j++;
		contador++;
	}
	if(k == n ){
		for(i = 0; i < n; i++){
			arregloFinal[i] = valor/contador;
		}
		return arregloFinal;
	}
	arreglo2[i] = valor; 
	arregloFinal[i] = valor/contador;
	for(i = 1; i < n; i++){
		valor = arreglo2[i-1];
		int menor = i-k;
		int mayor = i+k;
		if(( menor <= 0) && (mayor < n)){
			valor += arreglo[mayor];
			contador++; 
			arreglo2[i] = valor;
		}
		if(( menor > 0) && (mayor < n) ){
			valor -= arreglo[menor-1];
			valor += arreglo[mayor];
			arreglo2[i] = valor;
		}
		if((menor > 0) && (mayor >= n)){
			valor -= arreglo[menor-1];
			contador--;
			arreglo2[i] = valor;
		}
		if((menor <= 0) && (mayor >= n)){
			valor = arreglo2[i-1];
		}
		arregloFinal[i] = valor/contador;
		}
		return arregloFinal;
}
