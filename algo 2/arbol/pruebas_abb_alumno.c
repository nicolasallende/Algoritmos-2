#include "abb.h"
#include "cola.h"
#include "testing.h"
#include "vector_dinamico.h"
#include "pila.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <time.h>


#define MAX_VOLUMEN 1000
#define TAM_VECTOR 100

//Prueba el funcionamiento del abb cuando el mismo se encuentra vacio.
void prueba_abb_vacio(){
	
	printf("\n-----PRUEBA-ABB-VACIO-----\n");

	abb_t* abb_vacio = abb_crear(strcmp,NULL);

	print_test("Prueba abb, crear abb vacio", abb_vacio );
	print_test("Prueba abb, la cantidad de elementos es de 0 ", abb_cantidad(abb_vacio) == 0 );
	print_test("Prueba abb, la clave CEPITA DEL VALLE, no existe",!abb_obtener(abb_vacio,"CEPITA DEL VALLE") );
	print_test("Prueba abb, la clave CEPITA DEL VALLE, no existe",!abb_pertenece(abb_vacio,"CEPITA DEL VALLE"));
	print_test("Prueba abb, borrar CEPITA DEL VALLE,es NULL no existe",!abb_borrar(abb_vacio,"CEPITA DEL VALLE") );

	abb_destruir(abb_vacio);
}

//Prueba el funcionamiento del abb cuando se le insertar algunos elementos.
static void prueba_abb_insertar(){

	printf("\n-----PRUEBA-ABB-INSERTAR-----\n");

	abb_t* abb = abb_crear(strcmp, NULL);
	
	char *clave1 = "Roy" , *valor1 = "Mustang";
    char *clave2 = "Edward", *valor2 = "Elric";
    char *clave3 = "Van", *valor3 = "Hohenheime";
    char *clave4 = "Alphonse", *valor4 = "Elric";
    char *clave5 = "Riza" , *valor5 = "Hawkeye";
    char *clave6 = "Winry", *valor6 = "Rockbell";
    char *clave7 = "Trisha", *valor7 = "Elric";
    
    //guardo como raiz
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba abb pertenece clave1, es true", abb_pertenece(abb, clave1));
    print_test("Prueba abb pertenece clave2, es false", !abb_pertenece(abb, clave2));
    
    //hijo izquierdo de la raiz
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb pertenece clave2, es true", abb_pertenece(abb, clave2));
    
    //hijo derecho de la raiz
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb la cantidad de elementos es 3", abb_cantidad(abb) == 3);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba abb pertenece clave3, es true", abb_pertenece(abb, clave3));
    
    //hijo izquierdo del hijo izquierdo
	print_test("Prueba abb insertar clave4", abb_guardar(abb, clave4, valor4));
    print_test("Prueba abb la cantidad de elementos es 4", abb_cantidad(abb) == 4);
    print_test("Prueba abb obtener clave4 es valor4", abb_obtener(abb, clave4) == valor4);
    print_test("Prueba abb obtener clave4 es valor4", abb_obtener(abb, clave4) == valor4);
    print_test("Prueba abb pertenece clave4, es true", abb_pertenece(abb, clave4));

	//hijo derecho del hijo izquierdo
	print_test("Prueba abb insertar clave5", abb_guardar(abb, clave5, valor5));
    print_test("Prueba abb la cantidad de elementos es 5", abb_cantidad(abb) == 5);
    print_test("Prueba abb obtener clave5 es valor5", abb_obtener(abb, clave5) == valor5);
    print_test("Prueba abb obtener clave5 es valor5", abb_obtener(abb, clave5) == valor5);
    print_test("Prueba abb pertenece clave5, es true", abb_pertenece(abb, clave5));

	//hijo derecho del hijo derecho
	print_test("Prueba abb insertar clave6", abb_guardar(abb, clave6, valor6));
    print_test("Prueba abb la cantidad de elementos es 6", abb_cantidad(abb) == 6);
    print_test("Prueba abb obtener clave6 es valor6", abb_obtener(abb, clave6) == valor6);
    print_test("Prueba abb obtener clave6 es valor6", abb_obtener(abb, clave6) == valor6);
    print_test("Prueba abb pertenece clave6, es true", abb_pertenece(abb, clave6));

	//hijo izquierdo del hijo derecho
	print_test("Prueba abb insertar clave7", abb_guardar(abb, clave7, valor7));
    print_test("Prueba abb la cantidad de elementos es 7", abb_cantidad(abb) == 7);
    print_test("Prueba abb obtener clave7 es valor7", abb_obtener(abb, clave7) == valor7);
    print_test("Prueba abb obtener clave7 es valor7", abb_obtener(abb, clave7) == valor7);
    print_test("Prueba abb pertenece clave7, es true", abb_pertenece(abb, clave7));

	abb_destruir(abb);
	
}

//Prueba el funcionamiento del abb cuando se le borran elementos.
static void prueba_abb_borrar(){
	
	printf("\n-----PRUEBA-ABB-BORRAR-----\n");

	abb_t* abb = abb_crear(strcmp, NULL);
	
	char *clave1 = "Greed" , *valor1 = "4";
    char *clave2 = "Pride",  *valor2 = "1";
    char *clave3 = "Van",    *valor3 = "Hohenheime";
    char *clave4 = "Father", *valor4 = "0";
    char *clave5 = "Sloth" , *valor5 = "3";
    char *clave6 = "Envy",   *valor6 = "2";
    char *clave7 = "A",      *valor7 = "truth";
	
	/*inserto seis valores para hacer los distintos casos de borrado*/
	print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
	print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
	print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
	print_test("Prueba abb insertar clave4", abb_guardar(abb, clave4, valor4));
	print_test("Prueba abb insertar clave5", abb_guardar(abb, clave5, valor5));
	print_test("Prueba abb insertar clave6", abb_guardar(abb, clave6, valor6));
	print_test("Prueba abb insertar clave7", abb_guardar(abb, clave7, valor7));
	
	//borro un nodo con un solo hijo
	print_test("Prueba abb, la cantidad de elementos es 7",abb_cantidad(abb) == 7 );
	print_test("Prueba abb pertenece clave4, es true", abb_pertenece(abb, clave4));
	print_test("Prueba abb borrar con un solo hijo, es valor4", abb_borrar(abb, clave4) == valor4);
	print_test("Prueba abb la clave6 existe",abb_pertenece(abb, clave6) );
	print_test("Prueba abb borrar con un solo hijo, es NULL", !abb_borrar(abb, clave4));
	print_test("Prueba abb pertenece clave4, es falso", !abb_pertenece(abb, clave4));
    print_test("Prueba abb obtener clave4, es NULL", !abb_obtener(abb, clave4));
    print_test("Prueba abb la cantidad de elementos es 6", abb_cantidad(abb) == 6);
	
	//borro un nodo sin hijos
	print_test("Prueba abb pertenece clave7, es true", abb_pertenece(abb, clave7));
	print_test("Prueba abb borrar con un hijo, es valor7", abb_borrar(abb, clave7) == valor7);
	print_test("Prueba abb borrar con un hijo, es NULL", !abb_borrar(abb, clave7));
	print_test("Prueba abb pertenece clave7 es falso", !abb_pertenece(abb, clave7));
    print_test("Prueba abb obtener clave7, es NULL", !abb_obtener(abb, clave7));
    print_test("Prueba abb la cantidad de elementos es 5", abb_cantidad(abb) == 5);
	
	//borro un nodo con dos hijos
	print_test("Prueba abb pertenece clave2, es true", abb_pertenece(abb, clave2));
	print_test("Prueba abb borrar con dos hijo, es valor2", abb_borrar(abb, clave2) == valor2);
	print_test("Prueba abb borrar con dos hijo, es NULL", !abb_borrar(abb, clave2));
	print_test("Prueba abb pertenece clave2, es falso", !abb_pertenece(abb, clave2));
    print_test("Prueba abb obtener clave2, es NULL", !abb_obtener(abb, clave2));
    print_test("Prueba abb la cantidad de elementos es 4", abb_cantidad(abb) == 4);
	
	//borro la raiz que tiene dos hijos en este caso
	print_test("Prueba abb pertenece clave1, es true", abb_pertenece(abb, clave1));
	print_test("Prueba abb borrar dos hijo, es valor1", abb_borrar(abb, clave1) == valor1);
	print_test("Prueba abb borrar dos hijo, es NULL", !abb_borrar(abb, clave1));
	print_test("Prueba abb pertenece clave1, es falso", !abb_pertenece(abb, clave1));
    print_test("Prueba abb obtener clave1, es NULL", !abb_obtener(abb, clave1));
    print_test("Prueba abb la cantidad de elementos es 3", abb_cantidad(abb) == 3);
	
	abb_destruir(abb);
}

//Prueba el funcionamiento del abb cuando se le inserta una clave vacia, del tipo "".
static void prueba_abb_insertar_clave_vacia(){

	printf("\n-----PRUEBA-ABB-INSERTAR-CLAVE-VACIA-----\n");
    
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave = "", *valor = "";

    print_test("Prueba abb insertar clave vacia", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

//Prueba el funcionamiento del abb cuando se le inserta una clave que apunta al NULL.
static void prueba_abb_insertar_valor_NULL(){

	printf("\n-----PRUEBA-ABB-INSERTAR-VALOR-NULL----\n");
	
	abb_t* abb = abb_crear(strcmp, NULL);

    char *clave = "", *valor = NULL;

    print_test("Prueba abb insertar clave vacia", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

//Prueba el funcionamiento del abb cuando se le insertar algunos elementos que ya existen dentro del mismo.
static void prueba_abb_reemplazar(){
	
	printf("\n-----PRUEBA-ABB-REEMPLAZAR-----\n");

	abb_t* abb = abb_crear(strcmp, NULL);
	
	char *clave1 = "Bradley", *valor1a = "King", *valor1b = "Wrath";
    char *clave2 = "Ling", *valor2a = "Yao", *valor2b = "Greed";

	print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);
}


//Prueba el funcionamiento del abb cuando se le insertar algunos elementos que fueron pedidos con memoria 
//dinamica.
void prueba_abb_con_funcion_de_destruccion(){
	
	printf("\n-----PRUEBA-ABB-CON-FUNCION-DE-DESTRUCCION-----\n");

	abb_t* abb_pila = abb_crear(strcmp,(abb_destruir_dato_t)pila_destruir);
	
	char *clave1 = "PERRO", *clave2 = "GATO", *clave3 = "MONO";
	
	pila_t* pila1 = pila_crear();
	pila_t* pila2 = pila_crear();
	pila_t* pila3 = pila_crear();

	print_test("Prueba abb, crear abb_pila", abb_pila );
	print_test("Prueba abb, la cantidad de elementos es de 0", abb_cantidad(abb_pila) == 0);
	print_test("Prueba abb, se guardo la clave  PERRO",abb_guardar(abb_pila,clave1,pila1) );
	print_test("Prueba abb, se guardo la clave  GATO", abb_guardar(abb_pila,clave2,pila2) );
	print_test("Prueba abb, se guardo la clave  MONO", abb_guardar(abb_pila,clave3,pila3) );
	print_test("Prueba abb, la cantidad de elementos es de 3",abb_cantidad(abb_pila) == 3);
	print_test("Prueba abb, la clave PERRO existe", abb_obtener(abb_pila,clave1) == pila1);
	print_test("Prueba abb, la clave GATO existe", abb_obtener(abb_pila,clave2) == pila2);
	print_test("Prueba abb, la clave MONO existe", abb_obtener(abb_pila,clave3) == pila3);

	abb_destruir(abb_pila);
	//Fin de la prueba con pilas 

	abb_t* abb_vector_d = abb_crear(strcmp,(abb_destruir_dato_t)vector_destruir);

	char *clave4 = "LIEBRE", *clave5 = "JIRAFA", *clave6 = "LEON";

	vector_t* vector_d1 = vector_crear(TAM_VECTOR);
	vector_t* vector_d2 = vector_crear(TAM_VECTOR);
	vector_t* vector_d3 = vector_crear(TAM_VECTOR);

	print_test("Prueba abb, crear abb_vector_d", abb_vector_d );
	print_test("Prueba abb, la cantidad de elementos es de 0", abb_cantidad(abb_vector_d) == 0);
	print_test("Prueba abb, se guardo la clave  LIEBRE", abb_guardar(abb_vector_d,clave4,vector_d1));
	print_test("Prueba abb, se guardo la clave  JIRAFA", abb_guardar(abb_vector_d,clave5,vector_d2));
	print_test("Prueba abb, se guardo la clave  LEON",   abb_guardar(abb_vector_d,clave6,vector_d3));
	print_test("Prueba abb, la cantidad de elementos es de 3",abb_cantidad(abb_vector_d) == 3);
	print_test("Prueba abb, la clave LIEBRE existe", abb_obtener(abb_vector_d,clave4) == vector_d1);
	print_test("Prueba abb, la clave JIRAFA existe", abb_obtener(abb_vector_d,clave5) == vector_d2);
	print_test("Prueba abb, la clave LEON existe",   abb_obtener(abb_vector_d,clave6) == vector_d3);

	abb_destruir(abb_vector_d);
	//Fin de la prueba con vectores dinamicos.
}

//Prueba el funcionamiento del abb cuando se le insertar algunos elementos que ya existen dentro del mismo.
static void prueba_abb_reemplazar_con_destruir(){

	printf("\n-----PRUEBA-ABB-REEMPLAZAR-CON-DESTRUIR-----\n");
	
	abb_t* abb = abb_crear(strcmp,free);
	char *clave1 = "toque", *valor1a, *valor1b;
    char *clave2 = "perro", *valor2a, *valor2b;
    
    valor1a = malloc(2 * sizeof(char));
    valor1b = malloc(2 * sizeof(char));
    valor2a = malloc(2 * sizeof(char));
    valor2b = malloc(2 * sizeof(char));

 /* Inserta 2 valores y luego los reemplaza (debe liberar lo que reemplaza) */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
    /* Se destruye el hash (se debe liberar lo que quedó dentro) */
    
    abb_destruir(abb);
}

//Prueba el funcionamiento del abb y el abb iter ext.
void prueba_abb_iter_externo(){
	
	printf("\n-----PRUEBA-ABB-CON-ITER-EXTERNO-----\n");

	abb_t* abb_iter_ext = abb_crear(strcmp,NULL);
	
	char *clave1 = "E", *clave2 = "C", *clave3 = "D", *clave4 = "B", *clave5 = "A";	
	char *clave6 = "F", *clave7 = "G", *clave8 = "I", *clave9 = "H", *clave10 = "J";

	abb_guardar(abb_iter_ext,clave1,NULL);
	abb_guardar(abb_iter_ext,clave2,NULL);
	abb_guardar(abb_iter_ext,clave3,NULL);
	abb_guardar(abb_iter_ext,clave4,NULL);
	abb_guardar(abb_iter_ext,clave5,NULL);
	abb_guardar(abb_iter_ext,clave6,NULL);
	abb_guardar(abb_iter_ext,clave7,NULL);
	abb_guardar(abb_iter_ext,clave8,NULL);
	abb_guardar(abb_iter_ext,clave9,NULL);
	abb_guardar(abb_iter_ext,clave10,NULL);

	abb_iter_t* iter_ext_abb = abb_iter_in_crear(abb_iter_ext);
	
	print_test("Prueba abb, no estoy al final",!abb_iter_in_al_final(iter_ext_abb));

	print_test("Prueba abb, estoy en A", strcmp(abb_iter_in_ver_actual(iter_ext_abb), clave5 ) == 0);
	print_test("Prueba abb, Avanzo con el iter", abb_iter_in_avanzar(iter_ext_abb) );

	print_test("Prueba abb, estoy en B", strcmp(abb_iter_in_ver_actual(iter_ext_abb), clave4 ) == 0);
	print_test("Prueba abb, Avanzo con el iter", abb_iter_in_avanzar(iter_ext_abb) );

	print_test("Prueba abb, estoy en C", strcmp(abb_iter_in_ver_actual(iter_ext_abb), clave2 ) == 0);
	print_test("Prueba abb, Avanzo con el iter", abb_iter_in_avanzar(iter_ext_abb) );

	print_test("Prueba abb, estoy en D", strcmp(abb_iter_in_ver_actual(iter_ext_abb), clave3 ) == 0);
	print_test("Prueba abb, Avanzo con el iter", abb_iter_in_avanzar(iter_ext_abb) );

	print_test("Prueba abb, estoy en E", strcmp(abb_iter_in_ver_actual(iter_ext_abb), clave1 ) == 0);
	print_test("Prueba abb, Avanzo con el iter", abb_iter_in_avanzar(iter_ext_abb) );

	print_test("Prueba abb, estoy en F", strcmp(abb_iter_in_ver_actual(iter_ext_abb), clave6 ) == 0);
	print_test("Prueba abb, Avanzo con el iter", abb_iter_in_avanzar(iter_ext_abb) );
	
	print_test("Prueba abb, estoy en G", strcmp(abb_iter_in_ver_actual(iter_ext_abb), clave7 ) == 0);
	print_test("Prueba abb, Avanzo con el iter", abb_iter_in_avanzar(iter_ext_abb) );

	print_test("Prueba abb, estoy en H", strcmp(abb_iter_in_ver_actual(iter_ext_abb), clave9 ) == 0);
	print_test("Prueba abb, Avanzo con el iter", abb_iter_in_avanzar(iter_ext_abb) );

	print_test("Prueba abb, estoy en I", strcmp(abb_iter_in_ver_actual(iter_ext_abb), clave8) == 0);
	print_test("Prueba abb, Avanzo con el iter", abb_iter_in_avanzar(iter_ext_abb) );

	print_test("Prueba abb, estoy en J", strcmp(abb_iter_in_ver_actual(iter_ext_abb), clave10 ) == 0);
	print_test("Prueba abb, Avanzo con el iter", abb_iter_in_avanzar(iter_ext_abb) );

	print_test("Prueba abb, estoy al final",abb_iter_in_al_final(iter_ext_abb));

	abb_iter_in_destruir(iter_ext_abb);

	abb_destruir(abb_iter_ext);

	//crear iterador con arbol vacio
	printf("\n------PRUEBA-ITER-EXTERNO-CON-ABB-VACIO-------\n");
	abb_t* abb_vacio = abb_crear(strcmp,NULL);
	abb_iter_t* iter = abb_iter_in_crear(abb_vacio);
	print_test("Prueba iter, estoy al final",abb_iter_in_al_final(iter));
	print_test("Prueba iter, no puedo avanzar", !abb_iter_in_avanzar(iter));
	print_test("Prueba iter, esta vacio, NULL", abb_iter_in_ver_actual(iter) == NULL);
	
	abb_iter_in_destruir(iter);

	abb_destruir(abb_vacio);
}

//Realiza en el contedo de digitos, como func. auxiliar de la prueba de volumen.
int conteo_de_digitos(int num){
	int num_aux = num;
	int num_digitos = 1;
	while( num_aux / 10 != 0){
		num_digitos++;
		num_aux = num_aux/10;
	}
	return num_digitos;
}

//Prueba el funcionamiento del abb cuando se le inserta muchos elem y luego se los borra. 
static void prueba_abb_volumen(size_t largo, bool debug){
	
	printf("\n-----PRUEBA-ABB-VOLUMEN-----\n");

	abb_t* abb = abb_crear(strcmp, NULL);

	cola_t* cola = cola_crear();
	
	char** claves = malloc( largo*sizeof(char*));

	bool ok = true;
	printf("ACA EMPIEZA\n");
	
	/* Inserta 'largo' parejas en el arbol */
	unsigned int num;
	for(size_t i = 0; i < largo; ++i){
		num = rand();
		claves[i] = malloc( (conteo_de_digitos(num) + 1 )*sizeof(char) );
		sprintf(claves[i], "%d", num);
		cola_encolar(cola,claves[i]);
		ok = abb_guardar(abb, claves[i], claves[i]);
		if(!ok) break;
	}
	if (debug) print_test("Prueba abb almacenar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

	/* Verifica que borre y devuelva los valores correctos */
  	int i = 0;
    while(!cola_esta_vacia(cola)){
		char* clave = (char*)cola_desencolar(cola);
        ok = (abb_borrar(abb, clave) == claves[i]);
        if (!ok) break;
        i++;
    }
	
	if (debug) print_test("Prueba abb borrar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    for (int pos = 0; pos < largo; ++pos){
    	free(claves[pos]);
    }
	free(claves);
	cola_destruir(cola, NULL);
	abb_destruir(abb);

}

//funcion visitar del iter interno.
bool imprimir(const char *clave, void *dato, void*  extra){
	if(extra == dato){
		extra = NULL;
		printf("son iguales, cortando ciclo\n\n");
		return false;
	}
	printf("Prueba abb, la clave es: %s\n", (char*)clave );
	printf("Prueba abb, el dato : %s\n", (char*)dato );
	
	return true;
}
	

//Prueba el funcionamiento del abb y del abb iter interno.	
static void prueba_abb_iterador_interno(bool (*visitar)(const char *clave, void *dato, void *extra) ){
	
	printf("\n-----PRUEBA-ABB-ITER-INTERNO----\n");

	abb_t* abb = abb_crear(strcmp, NULL);
	
	char *clave1 = "Greed" , *valor1 = "1";
    char *clave2 = "Pride",  *valor2 = "2";
    char *clave3 = "Van",    *valor3 = "3";
    char *clave4 = "Father", *valor4 = "4";
    char *clave5 = "Sloth" , *valor5 = "5";
    char *valor = "jaja";
	
	
	print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
	print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
	print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
	print_test("Prueba abb insertar clave4", abb_guardar(abb, clave4, valor4));
	print_test("Prueba abb insertar clave5", abb_guardar(abb, clave5, valor5));
	
	
	//con corte
	void* extra = valor2;
	abb_in_order(abb, visitar, extra);

	//sin corte
	extra = valor;
	abb_in_order(abb, visitar, extra);
	
	//si le pasan NULL para visitar no hace nada
	abb_in_order(abb, NULL, extra);
	
	abb_destruir(abb);
}

//Prueba que buscan ver el funcionamiento del abb en todos sus apectos.
void pruebas_abb_alumno(){
	prueba_abb_vacio();
	prueba_abb_con_funcion_de_destruccion();
 	prueba_abb_iter_externo();
	prueba_abb_insertar();
	prueba_abb_insertar_clave_vacia();
	prueba_abb_insertar_valor_NULL();
	prueba_abb_reemplazar();
	prueba_abb_reemplazar_con_destruir();
	prueba_abb_borrar();
	prueba_abb_iterador_interno(imprimir);
	prueba_abb_volumen(MAX_VOLUMEN,true);
}
