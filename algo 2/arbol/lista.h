#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stddef.h>


typedef struct lista lista_t;

// crea una lista enlazada.
//Post: devuelve una lista vacia.
lista_t *lista_crear(void);

//Da un true si la lista esta vacia y da un false si la lista esta con elementos.
//Pre:La lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

//Insertar un elemento al principio de la lista.
//Pre: la lista fue creada.
//Post: el elemento esta en el principio de la lista. Si se puede realizar tal accion devuelve true.
// y false en el caso de que no sea posible.
bool lista_insertar_primero(lista_t *lista, void *dato);

//Insertar un elemento al final de la lista
//pre: la lista fue creada
//post: el elemento esta en el final de la lista. Si se puede realizar tal accion devuelve true
// y false en el caso de que no sea posible.
bool lista_insertar_ultimo(lista_t *lista, void *dato);


// Muestra el primer elemento que contiene la lista.
//Pre: La lista fue creada.
void *lista_ver_primero(const lista_t *lista);


// Muestra el ultimo elemento que contiene la lista.
//Pre: La lista fue creada.
void *lista_ver_ultimo(const lista_t* lista);

//borra el primer elemento de la lista y lo devuelve.
//Pre: la lista fue creada.
void *lista_borrar_primero(lista_t *lista);

//Devuelve el largo de la lista.
//Pre: La lista fue creada.
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la cola llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la cola, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));


/* Parte de las primitivas del iterarador interno*/


//Itera sobre la lista y realiza la operacion/funcion que es pasada por parametro a los elementos de la lista.
//Pre: La lista fue creada.
//Post: Realiza operacion siempre y cuando se le pase una funcion, en caso contrario no hace nada.
void lista_iterar(lista_t *lista, bool (*visitar)(void *dato, void *extra), void *extra);

/*fin de primitivas de iterador interno*/

/* Parte de las primitivas del iterarador externo*/
///////////////////  PRIMITIVAS ITER EXTERNO /////////////////////////

typedef struct lista_iter lista_iter_t;

//Crea un iter con el cual recorre la lista
//Pre: La lista fue creada.
//Post: Devuelve un iter apuntando al principio de la lista 
lista_iter_t *lista_iter_crear(lista_t *lista);


//funcion que sirve para avanzar sobre lista.
//Pre: La lista y el iter fueron creados.
//Post: Da true si avanzo y false en caso contrario.
bool lista_iter_avanzar(lista_iter_t *iter);

//Devuelve el elemento que se encuentra en la posicion actual de la lista
//Pre: La lista y el iter fueron creados.
//Post: Devuele el elemento si la lista no es vacia o estoy al final y en caso contrario NULL
void *lista_iter_ver_actual(const lista_iter_t *iter);

//Pregunta al iter si se encuentra al final con un True en el caso de asi sea o False en caso contrario.
//Pre: La lista y el iter fueron creados.
bool lista_iter_al_final(const lista_iter_t *iter);

//Destruye el iter
//Pre: La lista y el iter fueron creados.
void lista_iter_destruir(lista_iter_t *iter);

//inserta un elemento en la lista. si es posible y se realiza la accion da un true, sino False.
//Pre: La lista y el iter fueron creados.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

//Saca el elemento de la lista en la posicion que se encuentra el iter y lo devuelve
//Pre: La lista y el fueron creados.
//Post: Devuele el elemento si la lista no es vacia o estoy al final y en caso contrario NULL 
void *lista_iter_borrar(lista_iter_t *iter);  

/*fin de primitivas de iterador externo*/

/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

// Realiza pruebas sobre la implementación del alumno.
//
// Las pruebas deben emplazarse en el archivo ‘pruebas_alumno.c’, y
// solamente pueden emplear la interfaz pública tal y como aparece en cola.h
// (esto es, las pruebas no pueden acceder a los miembros del struct lista).
//
// Para la implementación de las pruebas se debe emplear la función
// print_test(), como se ha visto en TPs anteriores.
void pruebas_lista_alumno(void);


#endif // LISTA_H