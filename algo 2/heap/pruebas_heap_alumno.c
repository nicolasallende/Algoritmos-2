#include "heap.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

#define TAM_VOLUMEN 10000

//funcion de comparacion para hacer un max-heap
int intcmp(const void* num1, const void* num2){
	if( *(int*)num1 > *(int*)num2 ) return 1;
	if( *(int*)num1 < *(int*)num2 ) return -1;
	return 0;
}

//funcion de comparacion para hacer un min-heap
int intcmp2(const void* num1, const void* num2){
	if( *(int*)num1 > *(int*)num2 ) return -1;
	if( *(int*)num1 < *(int*)num2 ) return  1;
	return 0;
}

//imprime el arreglo que se le pasa por parametro.
void imprimir_arreglo(void** arreglo,size_t tam_arreglo){
	printf("\n");
	for (int i = 0; i < tam_arreglo; ++i){
		if( i < tam_arreglo -1) printf("%d-",*(int*)arreglo[i] );
		else{ printf("%d\n",*(int*)arreglo[i]); }
	}
	printf("\n");
}

//funcion de comparacion de cadenas para hacer un max-heap.
int strcmp_bis(const void* elem1, const void* elem2){
	return strcmp( (const char*)elem1,(const char*) elem2 );
}

//Prueba el funcionamiento del Heap cuando esta vacio.
void prueba_heap_vacio(){
	
	printf("\n-----PRUEBA-HEAP-VACIO-----\n");

	heap_t* heap_vacio = heap_crear(intcmp);

	print_test("Prueba heap, crear heap vacio", heap_vacio );
	print_test("Prueba heap, la cantidad de elementos es de 0 ", heap_cantidad(heap_vacio) == 0 );
	print_test("Prueba heap, esta vacio, true", heap_esta_vacio(heap_vacio));
	print_test("Prueba heap, ver el maximo, es NULL", heap_ver_max(heap_vacio) == NULL);
	print_test("Prueba heap, desencolar, es NULL ", heap_desencolar(heap_vacio) == NULL);

	heap_destruir(heap_vacio, NULL);
}

//pruebas de encolar
void prueba_heap_encolar(){
	
	printf("\n-----PRUEBA-HEAP-ENCOLAR-----\n");

	heap_t* heap = heap_crear(intcmp);
	
	int elem1 = 10, elem2 = 4, elem3 = 6, elem4 = 25;
	
	print_test("Prueba heap, encolo 10, es true", heap_encolar(heap, &elem1));
	print_test("Prueba heap, esta vacio, false", !heap_esta_vacio(heap));
	print_test("Prueba heap, la cantidad de elementos es 1", heap_cantidad(heap) == 1 );
	print_test("Prueba heap, ver el maximo, es 10", heap_ver_max(heap) == &elem1);
	
	print_test("Prueba heap, encolo 4, es true", heap_encolar(heap, &elem2));
	print_test("Prueba heap, la cantidad de elementos es 2", heap_cantidad(heap) == 2 );
	print_test("Prueba heap, ver el maximo, es 10", heap_ver_max(heap) == &elem1);
	
	print_test("Prueba heap, encolo 6, es true", heap_encolar(heap, &elem3));
	print_test("Prueba heap, la cantidad de elementos es 3", heap_cantidad(heap) == 3 );
	print_test("Prueba heap, ver el maximo, es 10", heap_ver_max(heap) == &elem1);

	print_test("Prueba heap, encolo 25, es true", heap_encolar(heap, &elem4));
	print_test("Prueba heap, la cantidad de elementos es 4", heap_cantidad(heap) == 4 );
	print_test("Prueba heap, ver el maximo, es 25", heap_ver_max(heap) == &elem4);
	
	print_test("Prueba heap, encolo NULL, es false", !heap_encolar(heap, NULL));
	print_test("Prueba heap, la cantidad de elementos es 4", heap_cantidad(heap) == 4 );
	print_test("Prueba heap, ver el maximo, es 25", heap_ver_max(heap) == &elem4);
	
	heap_destruir(heap, NULL);

}

//Prueba que denota el funcionamiento del heap_desencolar().
void prueba_heap_desencolar(){
	printf("\n-----PRUEBA-HEAP-DESENCOLAR-----\n");
	
	int num1 =21,num2=17,num3=20,num4=12,num5=15,num6=14,num7=8;
	int* arreglo[] ={&num1,&num2,&num3,&num4,&num5,&num6,&num7};
	size_t tam_arreglo = 7;
	heap_t* heap = heap_crear_arr( (void**)arreglo,tam_arreglo,intcmp);
	
		
	print_test("Prueba Heap La cantidad actual en el heap es de 7",tam_arreglo == heap_cantidad(heap) );
	print_test("Prueba Heap El mayor elem es el 21", arreglo[0] == heap_ver_max(heap) );

	print_test("Prueba Heap El elem. borrado es el 21, el max del heap", arreglo[0] == heap_desencolar(heap) );
	print_test("Prueba Heap La cantidad actual en el heap es de 6", tam_arreglo-1 == heap_cantidad(heap) );		
	print_test("Prueba Heap El elem. borrado es el 20, el max del heap", arreglo[2] == heap_desencolar(heap) );
	

	print_test("Prueba Heap El elem. borrado es el 17, el max del heap", arreglo[1] == heap_desencolar(heap) );
	print_test("Prueba Heap La cantidad actual en el heap es de 4",tam_arreglo-3 == heap_cantidad(heap) );
	print_test("Prueba Heap El mayor elem es el 15", arreglo[4] == heap_ver_max(heap) );
	print_test("Prueba Heap El elem. borrado es el 15, el max del heap", arreglo[4] == heap_desencolar(heap) );
			
	print_test("Prueba Heap La cantidad actual en el heap es de 3", tam_arreglo-4 == heap_cantidad(heap) );
	print_test("Prueba Heap El mayor elem es el 14", arreglo[5] == heap_ver_max(heap) );
	print_test("Prueba Heap El elem.  borrado es el 14 el max del heap", arreglo[5] == heap_desencolar(heap) );
	print_test("Prueba Heap La cantidad actual en el heap es de 2", tam_arreglo-5 == heap_cantidad(heap) );
			
	print_test("Prueba Heap El mayor elem es el 12", arreglo[3] == heap_ver_max(heap) );
	print_test("Prueba Heap El elem. borrado es el 12, el max del heap", arreglo[3] == heap_desencolar(heap) );
	print_test("Prueba Heap La cantidad actual en el heap es de 1",tam_arreglo-6 == heap_cantidad(heap) );
	print_test("Prueba Heap El mayor elem es el 8", arreglo[6] == heap_ver_max(heap) );
		
	print_test("Prueba Heap El elem. borrado es el 8, el max del heap", arreglo[6] == heap_desencolar(heap) );
	print_test("Prueba Heap La cantidad actual en el heap es de 0",tam_arreglo-7 == heap_cantidad(heap) );
	print_test("Prueba Heap No hay elem mayor, porque el heap esta vacio", NULL == heap_ver_max(heap) );
	print_test("Prueba Heap No hay elem a deseconlar, porque el heap esta vacio",NULL==heap_desencolar(heap));

	heap_destruir(heap,NULL);
	//Fin de la pruebas del desencolar.
}

//Prueba que denota el funcionamiento del heap_destuir segun se pase elem con memoria dinamica o no.
void prueba_heap_destruir(){
	printf("\n-----PRUEBA-HEAP-DESTRUIR-----\n");
	printf("\n--PARTE-SIN-PEDIDO-DE-MEM---\n");

	heap_t* heap1 = heap_crear(strcmp_bis);

	char* p1 = "A", *p2 = "B", *p3="C", *p4="D", *p5="E", *p6="F", *p7="G";

	print_test("Prueba Heap El elem ,A, fue encolado en el heap",heap_encolar(heap1,p1));
	print_test("Prueba Heap El elem ,B, fue encolado en el heap",heap_encolar(heap1,p2));
	print_test("Prueba Heap El elem ,C, fue encolado en el heap",heap_encolar(heap1,p3));
	print_test("Prueba Heap El elem ,D, fue encolado en el heap",heap_encolar(heap1,p4));
	print_test("Prueba Heap El elem ,E, fue encolado en el heap",heap_encolar(heap1,p5));
	print_test("Prueba Heap El elem ,F, fue encolado en el heap",heap_encolar(heap1,p6));
	print_test("Prueba Heap El elem ,G, fue encolado en el heap",heap_encolar(heap1,p7));
	print_test("Prueba Heap la cantidad de elem en el heap es 7", 7 == heap_cantidad(heap1) );
	print_test("Prueba Heap El elem,G, es el max del heap", p7 == heap_ver_max(heap1) );

	heap_destruir(heap1,NULL);

	// fin de la parte sin pedido de memoria.
	printf("\n--PARTE-CON-PEDIDO-DE-MEM---\n");
	heap_t* heap2 = heap_crear(strcmp_bis);
	
	char* p8 = malloc( 2*sizeof(char) );
	char* p9 = malloc( 2*sizeof(char) );
	char* p10 = malloc( 2*sizeof(char) );
	char* p11 = malloc( 2*sizeof(char) );
	char* p12 = malloc( 2*sizeof(char) );
	char* p13 = malloc( 2*sizeof(char) );
	char* p14 = malloc( 2*sizeof(char) );

	strcpy(p8,"H");
	strcpy(p9,"I");
	strcpy(p10,"J");
	strcpy(p11,"K");
	strcpy(p12,"L");
	strcpy(p13,"M");
	strcpy(p14,"N");

	print_test("Prueba Heap El elem ,H, fue encolado en el heap",heap_encolar(heap2,p8));
	print_test("Prueba Heap El elem ,I, fue encolado en el heap",heap_encolar(heap2,p9));
	print_test("Prueba Heap El elem ,J, fue encolado en el heap",heap_encolar(heap2,p10));
	print_test("Prueba Heap El elem ,K, fue encolado en el heap",heap_encolar(heap2,p11));
	print_test("Prueba Heap El elem ,L, fue encolado en el heap",heap_encolar(heap2,p12));
	print_test("Prueba Heap El elem ,M, fue encolado en el heap",heap_encolar(heap2,p13));
	print_test("Prueba Heap El elem ,N, fue encolado en el heap",heap_encolar(heap2,p14));
	print_test("Prueba Heap la cantidad de elem en el heap es 7", 7 == heap_cantidad(heap2) );
	print_test("Prueba Heap El elem,N, es el max del heap", p14 == heap_ver_max(heap2) );

	heap_destruir(heap2,free);

	// fin de la parte con pedido de memoria.
}

//Prueba que denota el funcionamiento cuando se encolan y desencolan muchos elementos.
static void prueba_de_volumen(size_t largo, bool debug){

	printf("\n-----PRUEBA-HEAP-VOLUMEN-----\n");

	heap_t* heap = heap_crear(intcmp);
	int* arreglo = malloc( TAM_VOLUMEN*sizeof(int) );
	if( arreglo == NULL ) return;
	bool ok = true;
	for (int i = 0; i < TAM_VOLUMEN; ++i){
		arreglo[i] = i;
		ok = heap_encolar(heap,&arreglo[i]);
		if( !ok ) break;
	}

	if (debug) print_test("Prueba heap almacenar muchos elementos", ok);
    if (debug) print_test("Prueba heap la cantidad de elem. es correcta",heap_cantidad(heap) == TAM_VOLUMEN);
    if (debug) print_test("Prueba heap El max es 999 ", heap_ver_max(heap) == &arreglo[TAM_VOLUMEN-1] ) ;

	/* Verifica que borre y devuelva los valores correctos */
    for (int i = TAM_VOLUMEN - 1; i >= 0; --i){
    	int* elem = (int*)heap_desencolar(heap);
    	ok = (elem == &arreglo[i]);
    	if(!ok) break;
    }
    if (debug) print_test("Prueba heap borrar muchos elementos", ok);
    if (debug) print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);

    free(arreglo);
    heap_destruir(heap,NULL);
}

//pruebas de heapsort
void prueba_heapsort(){
	
	printf("\n-----PRUEBA-HEAPSORT-----\n");
	int num1 =1, num2 = 12, num3 = 15, num4 = 28, num5 = 45, num6 = 4, num7 = 34;
	int* arreglo[] ={&num1, &num2, &num3, &num4, &num5, &num6, &num7};
	size_t tam_arreglo = 7;

	printf("El arreglo sin que este ordenado por el heap es:");
	imprimir_arreglo((void**)arreglo,tam_arreglo);
	printf("Uso el heapsort en el arreglo y lo ordeno de menor a mayor \n");
	heap_sort((void*)arreglo, tam_arreglo, intcmp);
	print_test("El minimo tiene que ser 1", arreglo[0] == &num1); 
	print_test("El hijo izquierdo de 1 es 4", arreglo[1] == &num6 );
	print_test("El hijo derecho de 1 es 12", arreglo[2] == &num2 );
	print_test("El hijo izquierdo de 4 es 15", arreglo[3] == &num3 );
	print_test("El hijo derecho de 4 es 28", arreglo[4] == &num4 );
	print_test("El hijo izquierdo de 12 es 34", arreglo[5] == &num7 );
	print_test("El hijo derecho de 12 es 45", arreglo[6] == &num5 );
	
	imprimir_arreglo((void**)arreglo,tam_arreglo);
	
	int* arr[] ={&num1, &num2, &num3, &num4, &num5, &num6, &num7};
	
	printf("El arreglo sin que este ordenado por el heap es:");
	imprimir_arreglo((void**)arr,tam_arreglo);
	printf("Uso el heapsort en el arreglo y lo ordeno de mayor a menor\n");
	heap_sort((void*)arr, tam_arreglo, intcmp2);
	print_test("El maximo tiene que ser 45", arr[0] == &num5 );
	print_test("Su hijo izquierdo es 34", arr[1] == &num7 );
	print_test("Su hijo derecho es 28", arr[2] == &num4 );
	print_test("El hijo izquierdo de 34 es 15", arr[3] == &num3 );
	print_test("El hijo derecho de 34 es 12", arr[4] == &num2 );
	print_test("El hijo izquierdo de 28 es 4", arr[5] == &num6 );
	print_test("El hijo derecho de 28 es 1", arr[6] == &num1 );
	
	imprimir_arreglo((void**)arr,tam_arreglo);

}

//Serie de pruebas que denota el funcionamiento del heap en cada una de sus primitivas.
void pruebas_heap_alumno(){
	prueba_heap_vacio();
	prueba_heap_encolar();
	prueba_heapsort();
	prueba_heap_desencolar();
	prueba_heap_destruir();
	prueba_de_volumen((size_t)TAM_VOLUMEN,true);
}
