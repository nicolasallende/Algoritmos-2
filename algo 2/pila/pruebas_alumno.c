#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_pila_alumno() {
    pila_t* ejemplo = NULL;

    print_test("Puntero inicializado a NULL", ejemplo == NULL);
    
	printf("**********INICIO DE PRUEBAS PILA**************\n");
	
	pila_t* mi_pila = pila_crear();
	
	printf("PRUEBAS DE PILA RECIEN CREADA\n");
	//veo si creo la pila, pruebo el "esta vacia" y controlo que no 
	//pase nada con el tope
	
	print_test("Crea una pila", mi_pila != NULL);
	print_test("Veo si esta vacia, true", pila_esta_vacia(mi_pila) == true);
	print_test("Obtener top pila, no se puede", pila_ver_tope(mi_pila) == NULL);
	print_test("Trata de desapilar, no se puede",pila_desapilar(mi_pila) == NULL);
	
	printf("PRUEBAS DE APILAR Y TOPE\n");
	
	//pruebo el apilar y el tope (controlo el tope dos veces en algunos 
	//para ver que no modifique nada)
	
	int num = 3;
	void* var = &num;
	print_test ("Guardo 3 en posicion 0", pila_apilar(mi_pila, &var));
	print_test("Tope de la pila es 3", pila_ver_tope(mi_pila) == &var);
	print_test("Tope de la pila es 3", pila_ver_tope(mi_pila) == &var);
	num = 9;
	print_test("Guardo 9 en posicion 1", pila_apilar(mi_pila, &var));
	print_test("Tope de la pila es 9", pila_ver_tope(mi_pila) == &var);
	num = 10;
	print_test("Guardo 10 en posicion 2", pila_apilar(mi_pila, &var));
	print_test("Tope de la pila es 10", pila_ver_tope(mi_pila) == &var);
	num = 45;
	print_test("Guardo 45 en posicion 3", pila_apilar(mi_pila, &var));
	print_test("Tope de la pila es 45", pila_ver_tope(mi_pila) == &var);
	print_test("Tope de la pila es 45", pila_ver_tope(mi_pila) == &var);
	num = 7;
	print_test("Guardo 7 en posicion 4", pila_apilar(mi_pila, &var));
	print_test("Tope de la pila es 7", pila_ver_tope(mi_pila) == &var);
	char* let = "g";
	var = &let;
	print_test("Guardo g en posicion 5", pila_apilar(mi_pila, &var));
	print_test("Tope de la pila es g", pila_ver_tope(mi_pila) == &var);
	print_test("Tope de la pila es g", pila_ver_tope(mi_pila) == &var);
	let = "d";
	print_test("Guardo d en posicion 6", pila_apilar(mi_pila, &var));
	print_test("Tope de la pila es d", pila_ver_tope(mi_pila) == &var);
	let = "o";
	print_test("Guardo o en posicion 7", pila_apilar(mi_pila, &var));
	print_test("Tope de la pila es o", pila_ver_tope(mi_pila) == &var);
	let = "q";
	print_test("Guardo q en posicion 8", pila_apilar(mi_pila, &var));
	print_test("Tope de la pila es q", pila_ver_tope(mi_pila) == &var);
	let = "s";
	print_test("Guardo s en posicion 9 ", pila_apilar(mi_pila,&var));
	print_test("Tope de la pila es s", pila_ver_tope(mi_pila) == &var);
	
	printf("PRIMERA PRUEBA DE REDIMENSIONAMIENTO\n" );
	let = "u";
	print_test("Guardo u en posicion 10", pila_apilar(mi_pila, &var));
	print_test("Veo si esta vacia, falso",pila_esta_vacia(mi_pila) == false);
	print_test("Tope de la pila es u",pila_ver_tope(mi_pila) == &var);
	
	printf("PRUEBAS DE DESAPILAR\n");
	
	let = "u";
	print_test("Quito el ultimo elemento u", pila_desapilar(mi_pila) == &var);
	let = "s";
	print_test("Quito el ultimo elemento s", pila_desapilar(mi_pila) == &var);
	let = "q";
	print_test("Quito el ultimo elemento q", pila_desapilar(mi_pila) == &var);
	let = "o";
	print_test("Quito el ultimo elemento o", pila_desapilar(mi_pila) == &var);
	let = "d";
	print_test("Quito el ultimo elemento d", pila_desapilar(mi_pila) == &var);
	
	printf("SEGUNDA PRUEBA DE REDIMENSIONAMIENTO\n");
	
	//Pruebo el redimensionar cuando disminuye la cantidad y veo
	//si siguen los elementos anterirores
	
	let = "g";
	print_test("Quito el ultimo elemento g", pila_desapilar(mi_pila) == &var);
	print_test("Veo si esta vacia, falso",pila_esta_vacia(mi_pila) == false);
	num = 7;
	var = &num;
	print_test("Tope de la pila ahora es 7", pila_ver_tope(mi_pila) == &var);
	print_test("Quito el ultimo elemento 7", pila_desapilar(mi_pila) == &var); 
	num = 45;
	print_test("Tope de la pila ahora es 45", pila_ver_tope(mi_pila) == &var);
	print_test("Quito el ultimo elemento 45", pila_desapilar(mi_pila) == &var);
	
	printf("DESAPILAR HASTA VACIARLA\n");
	
	//Desapilo hasta que llegue a vaciarla 
	
	num = 10;
	print_test("Quito el ultimo elemento 10", pila_desapilar(mi_pila) == &var);
	num = 9;
	print_test("Quito el ultimo elemento 9", pila_desapilar(mi_pila) == &var);
	num = 3;
	print_test("Quito el ultimo elemento 3", pila_desapilar(mi_pila) == &var);
	print_test("Veo si esta vacia, true",pila_esta_vacia(mi_pila) == true);
	print_test("Obtener top pila, no se puede", pila_ver_tope(mi_pila) == NULL);
	
	//compruebo que se comporta como si fuera recien creada
	
	print_test("Veo si esta vacia, true", pila_esta_vacia(mi_pila) == true);
	print_test("Obtener top pila, no se puede", pila_ver_tope(mi_pila) == NULL);
	print_test("Trata de desapilar, no se puede",pila_desapilar(mi_pila) == NULL);
	
	//destruyo la pila
	
	pila_destruir(mi_pila);
	print_test("La pila fue destruida", true);
}
