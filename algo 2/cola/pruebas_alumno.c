#include "cola.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include "pila.h"

void pruebas_cola_recien_creada(){
	cola_t* tu_cola = cola_crear();
	print_test("Crea una cola", tu_cola);
	print_test("Veo si esta vacia, true", cola_esta_vacia(tu_cola));
	print_test("Obtener el primer elemento, no se puede", cola_ver_primero(tu_cola) == NULL);
	print_test("Trata de desencolar, no se puede",cola_desencolar(tu_cola) == NULL);
	cola_destruir(tu_cola, NULL);
}

void pruebas_encolar_y_desencolar(){
	cola_t* tu_cola = cola_crear();
	
	//Empiezo a encolar
	int pos1 = 3;
	print_test("Se pudo encolar 3",cola_encolar(tu_cola, &pos1));
	int pos2 = 7;
	print_test("Se pudo encolar 7",cola_encolar(tu_cola, &pos2));
	int pos3 = 85;
	print_test("Se pudo encolar 85",cola_encolar(tu_cola, &pos3));
	int pos4 = 67;
	print_test("se pudo encolar 67",cola_encolar(tu_cola, &pos4));
	print_test("Se pudo encolar a",cola_encolar(tu_cola, "a"));
	print_test("Se pudo encolar b",cola_encolar(tu_cola, "b"));
	print_test("Se pudo encolar g",cola_encolar(tu_cola, "g"));
	print_test("Se pudo encolar J",cola_encolar(tu_cola, "J"));
	print_test("3 es el primero",cola_ver_primero(tu_cola) == &pos1);
	
	//Empiezo a desencolar
	print_test("Desencola 3", cola_desencolar(tu_cola) == &pos1);
	print_test("Desencola 7", cola_desencolar(tu_cola) == &pos2);
	print_test("Desencola 85", cola_desencolar(tu_cola) == &pos3);
	print_test("Desencola 67", cola_desencolar(tu_cola) == &pos4);
	char* let1 = "a";
	print_test("a es el primero",(cola_ver_primero(tu_cola) == let1));
	print_test("Desencola a", cola_desencolar(tu_cola) == let1);
	char* let2 = "b";
	print_test("Desencola b", cola_desencolar(tu_cola) == let2);
	print_test("Veo si esta vacia, false", !cola_esta_vacia(tu_cola));
	char* let3 = "g";
	print_test("Desencola g", cola_desencolar(tu_cola) == let3);
	char* let4 = "J";
	print_test("Desencola J", cola_desencolar(tu_cola) == let4);
	print_test("Desencola aunque no hay nada", cola_desencolar(tu_cola) == NULL);
	
	//Destruyo la cola
	cola_destruir(tu_cola, NULL);
}

void pruebas_volumen(){
	bool ok = true;
	size_t num = 200;
	int v[num];
	cola_t* tu_cola = cola_crear();
	
	//cargo un vector y encolo el valor 
	for(int i = 0; i<num; i++){
		v[i] = i;
		ok &= cola_encolar(tu_cola, &v[i]);
	}  
	print_test("Se pudieron guardar todos los elementos", ok);
	
	// Pruebo que lo guardado sea correcto
	ok = true;
	for (int i = 0; i < num; i++) {
		ok &= (cola_desencolar(tu_cola) == &v[i]);
	}
	print_test("Se pudieron obtener todos los elementos", ok);
	
	cola_destruir(tu_cola, NULL );
}
void pruebas_cola_destruir(){
	pila_t* pila_1 = pila_crear();
	pila_t* pila_2 = pila_crear();
	pila_apilar(pila_1, "h");
	pila_apilar(pila_1, "o");
	pila_apilar(pila_1, "l");
	pila_apilar(pila_1, "a");
	pila_apilar(pila_2, "m");
	pila_apilar(pila_2, "u");
	pila_apilar(pila_2, "n");
	pila_apilar(pila_2, "d");
	pila_apilar(pila_2, "o");
	pila_apilar(pila_2, "!");
	cola_t* la_cola = cola_crear();
	cola_encolar(la_cola, pila_1);
	cola_encolar(la_cola, pila_2);
	void* aux = pila_destruir;
	cola_destruir(la_cola,aux);
}
void pruebas_cola_alumno(){
	 pruebas_cola_recien_creada(); 
	 pruebas_encolar_y_desencolar();
	 pruebas_volumen();
	 pruebas_cola_destruir();
}
