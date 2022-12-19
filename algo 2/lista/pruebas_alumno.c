#include "lista.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include "pila.h"

/******************************************************************
 *     PRUEBA DE LAS LISTAS SIN USAR ITERADORES
 *****************************************************************/

void pruebas_lista_recien_creada(){
	printf("\n");
	printf("PRUEBAS DE LISTA VACIA\n");
	lista_t* tu_lista = lista_crear();
	print_test("Crea una lista", tu_lista);
	print_test("Veo si esta vacia, true", lista_esta_vacia(tu_lista));
	print_test("Obtener el primer elemento, no se puede",!lista_ver_primero(tu_lista));
	print_test("Obtener el ultimo elemento, no se puede", !lista_ver_ultimo(tu_lista));
	print_test("Trata de quitar el primer elemento, no se puede",!lista_borrar_primero(tu_lista));
	print_test("Me dice el largo de la lista, es 0 ",lista_largo(tu_lista) == 0);
	lista_destruir(tu_lista, NULL);
}

void pruebas_agregar_y_quitar_elementos(){
	lista_t* tu_lista = lista_crear();
	printf("\n");
	printf("PRUEBA LISTA AGREGAR Y QUITAR ELEMENTOS\n");
	//Agrego elementos a la lista y compruebo el primer y ultimo
	int pos1 = 3;
	print_test("Se inserto el 3 en la primera posicion", lista_insertar_primero(tu_lista, &pos1));
	int pos0 = 0;
	print_test("Se inserto 0 en la primera posicion",lista_insertar_primero(tu_lista, &pos0));
	int pos2 = 5;
	print_test("Se inserto el 5 en la ultima posicion",lista_insertar_ultimo(tu_lista, &pos2));
	int pos3 =  6;
	print_test("Se inserto 6 en la ultima posicion",lista_insertar_ultimo(tu_lista, &pos3));
	print_test("0 es el primer elemento",lista_ver_primero(tu_lista) == &pos0);
	print_test("6 es el ultimo elemento",lista_ver_ultimo(tu_lista) == &pos3); 
	print_test("Controlo el largo de la lista, es 4",lista_largo(tu_lista) == 4);
	print_test("Veo si la lista esta vacia, falso", !lista_esta_vacia(tu_lista));
	
	 
	//Quito los elementos de la lista 
	print_test("Se quito el primer elemento de la lista, 0",lista_borrar_primero(tu_lista) == &pos0);
	print_test("Controlo el largo de la lista, es 3",lista_largo(tu_lista) == 3);
	print_test("3 es el primer elemento",lista_ver_primero(tu_lista) == &pos1); 
	print_test("Se quito el primer elemento de la lista, 3",lista_borrar_primero(tu_lista) == &pos1);
	print_test("Veo si la llista esta vacia, falso",!lista_esta_vacia(tu_lista));
	print_test("Se quito el primer elemento de la lista, 5",lista_borrar_primero(tu_lista) == &pos2);
	
	//Destruyo la lista
	lista_destruir(tu_lista,NULL);
}

void pruebas_volumen(){
	printf("\n");
	printf("PRUEBA DE VOLUMEN\n");
	bool ok = true;
	size_t num = 100;
	int v[num];
	lista_t* tu_lista = lista_crear();
	
	//cargo un vector y encolo el valor 
	for(int i = 0; i<num; i++){
		v[i] = i;
		ok &= lista_insertar_primero(tu_lista, &v[i]);
	}  
	print_test("Se pudieron guardar todos los elementos", ok);
	
	// Pruebo que lo guardado sea correcto
	ok = true;
	for (int i = 99; i > 0; i--) {
		ok &= (lista_borrar_primero(tu_lista) == &v[i]);
	}
	print_test("Se pudieron obtener todos los elementos", ok);
	
	lista_destruir(tu_lista, NULL );
}

void pruebas_lista_destruir(){
	pila_t* pila_1 = pila_crear();
	pila_t* pila_2 = pila_crear();
	pila_apilar(pila_1, "h");
	pila_apilar(pila_1, "o");
	pila_apilar(pila_2, "m");
	pila_apilar(pila_2, "u");
	lista_t* tu_lista = lista_crear();
	lista_insertar_primero(tu_lista, pila_1);
	lista_insertar_primero(tu_lista, pila_2);
	void* aux = pila_destruir;
	lista_destruir(tu_lista,aux);
}


/******************************************************************
 *     PRUEBA DE LAS LISTAS USANDO ITERADORES
 *****************************************************************/

void pruebas_iter_con_lista_vacia(){
	printf("\n");
	printf("PRUEBA ITERADOR CON LISTA VACIA\n");
	lista_t* tu_lista = lista_crear();
	lista_iter_t* iter = lista_iter_crear(tu_lista);
	print_test("Ver que tiene el elemento en el que estoy, NULL",lista_iter_ver_actual(iter) == NULL);
	print_test("Veo si esta al final, true",lista_iter_al_final(iter));
	print_test("Avanzo la posicion del iterador, false",!lista_iter_avanzar(iter));
	print_test("Elimino un elemento de la lista",lista_iter_borrar(iter) == NULL);
	lista_iter_destruir(iter);
	lista_destruir(tu_lista,NULL);
}

void pruebas_iter_agregar_y_quitar_al_principio(){
	lista_t* tu_lista = lista_crear();
	lista_iter_t* iter = lista_iter_crear(tu_lista);
	printf("\n");
	printf("PRUEBA LISTA AGREGAR Y QUITAR ELEMENTOS AL PRINCIPIO\n");
	int num0 = 0;
	print_test("Inserto en la primera posicion 0",lista_iter_insertar(iter, &num0));
	print_test("Veo que elemento tiene al principio, 0",lista_iter_ver_actual(iter) == &num0);
	int num1 = 1;
	print_test("Inserto en la primera posicion 1",lista_iter_insertar(iter, &num1));
	print_test("Veo que elemento tiene al principio, 1",lista_iter_ver_actual(iter) == &num1);
	print_test("Veo si esta al final, false",!lista_iter_al_final(iter));
	int num3 = 3;
	print_test("Inserto en la primera posicion 3",lista_iter_insertar(iter, &num3));
	print_test("Veo que elemento tiene al principio, 3",lista_iter_ver_actual(iter) == &num3);
	print_test("Quito el primer elemento, 3",lista_iter_borrar(iter) == &num3);
	print_test("Veo que elemento tiene al principio, 1",lista_iter_ver_actual(iter) == &num1);
	print_test("Quito el primer elemento, 1",lista_iter_borrar(iter) == &num1);
	print_test("Quito el primer elemento, 0",lista_iter_borrar(iter) == &num0);
	print_test("Veo si esta al final, true",lista_iter_al_final(iter));
	
	lista_iter_destruir(iter);
	lista_destruir(tu_lista,NULL);
}

void pruebas_iter_agregar_y_quitar_en_el_medio(){
	printf("\n");
	printf("PRUEBA LISTA AGREGAR Y QUITAR ELEMENTOS EN EL MEDIO\n");
	lista_t* tu_lista = lista_crear();
	int pos1 = 3;
	lista_insertar_primero(tu_lista, &pos1);
	int pos0 = 0;
	lista_insertar_primero(tu_lista, &pos0);
	int pos3 = 3;
	lista_insertar_primero(tu_lista, &pos3);
	lista_iter_t* iter = lista_iter_crear(tu_lista);
	
	print_test("Avanzo el iterador, true",lista_iter_avanzar(iter));
	print_test("Veo que elemento tiene en esta posicion, 0",lista_iter_ver_actual(iter) == &pos0);
	int num4 = 4;
	print_test("Inserto en la  posicion el  4",lista_iter_insertar(iter, &num4));
	print_test("Veo que elemento tiene en esta posicion, 4",lista_iter_ver_actual(iter) == &num4);
	print_test("Quito el elemento en esta posicion, 4",lista_iter_borrar(iter) == &num4);
	print_test("Veo que elemento tiene en esta posicion, 0",lista_iter_ver_actual(iter) == &pos0);
	print_test("Veo si esta al final, false",!lista_iter_al_final(iter));
	
	lista_iter_destruir(iter);
	lista_destruir(tu_lista,NULL);
}

void pruebas_iter_agregar_y_quitar_al_final(){
	printf("\n");
	printf("PRUEBA LISTA AGREGAR Y QUITAR ELEMENTOS AL FINAL\n");
	lista_t* tu_lista = lista_crear();
	int pos1 = 3;
	lista_insertar_primero(tu_lista, &pos1);
	lista_iter_t* iter = lista_iter_crear(tu_lista);
	
	print_test("Avanzo el iterador, true",lista_iter_avanzar(iter));
	print_test("Veo si esta al final, true",lista_iter_al_final(iter));
	int num4 = 4;
	print_test("Inserto al final el 4",lista_iter_insertar(iter, &num4));
	print_test("Veo que elemento tiene en esta posicion, 4",lista_iter_ver_actual(iter) == &num4);
	print_test("Quito el elemento en esta posicion, 4",lista_iter_borrar(iter) == &num4);
	print_test("Avanzo el iterador, false",!lista_iter_avanzar(iter));
	print_test("Trato de quitar al final, NULL",!lista_iter_borrar(iter));
	
	lista_iter_destruir(iter);
	lista_destruir(tu_lista,NULL);
}

void pruebas_imprimir_iter_ext(){
	printf("\n");
	printf("PRUEBA ITERADOR EXTERNO\n");
	lista_t* tu_lista = lista_crear();
	char *let2 = "2";
	lista_insertar_primero(tu_lista, let2);
	char *let1 = "1";
	lista_insertar_primero(tu_lista, let1);
	
	lista_iter_t* iter = lista_iter_crear(tu_lista);
	do{
		char* num = lista_iter_ver_actual(iter);
		printf("%s\n",  num);
		lista_iter_avanzar(iter);
	} while(!lista_iter_al_final(iter));
	lista_iter_destruir(iter);
	lista_destruir(tu_lista,NULL);
}

bool imprimir_item(void *dato, void *extra){
	char* num = dato;
	printf("%s",num);
	return true;
}

void pruebas_imprimir_iter_interno(){
	printf("\n");
	printf("PRUEBA ITERADOR INTERNO\n");
	lista_t* tu_lista = lista_crear();
	char *let2 = "2\n";
	lista_insertar_primero(tu_lista, let2);
	char *let1 = "1\n";
	lista_insertar_primero(tu_lista, let1);
	
	lista_iterar(tu_lista, imprimir_item, NULL);
	lista_destruir(tu_lista, NULL);
}

	
void pruebas_lista_alumno(){
	pruebas_lista_recien_creada();
	pruebas_agregar_y_quitar_elementos();
	pruebas_volumen();
	pruebas_lista_destruir();
	pruebas_iter_con_lista_vacia();
	pruebas_iter_agregar_y_quitar_al_principio();
	pruebas_iter_agregar_y_quitar_en_el_medio();
	pruebas_iter_agregar_y_quitar_al_final();
	pruebas_imprimir_iter_ext();
	pruebas_imprimir_iter_interno();

}
