#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stddef.h>


struct lista; 
typedef struct lista lista_t;

typedef struct lista_iter lista_iter_t;


/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/
 
 
// Crea una lista
// Post: Devuelve una lista
lista_t* lista_crear(void);


// Devuelve verdadero o falso segun si la lista tiene elementos o no
// Pre: La lista fue creada 
bool lista_esta_vacia(const lista_t *lista);


// Inserta el dato pasado en la primer posicion de la lista y
// devuelve falso en caso de no poder hacerlo
// Pre: La lista fue creada
// Post: Se agrego el dato en la primera posicion de la lista
bool lista_insertar_primero(lista_t *lista, void *dato);


// Inserta el dato pasado en la ultima posicion de la lista y
// devuelve falso en caso de no poder hacerlo
// Pre: La lista fue creada
// Post: Se agrego el dato en la ultima posicion de la lista
bool lista_insertar_ultimo(lista_t *lista, void *dato);


// Quita el primer elemento de la lista. Si la lista tiene elementos
// devuelve el valor del primer elemento, si esta vacia, devuelve NULL
// Pre: La lista fue creada.
// Post: Se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void* lista_borrar_primero(lista_t *lista);


// Quita el ultimo elemento de la lista. Si la lista tiene elementos
// devuelve el valor del ultimo elemento, si esta vacia, devuelve NULL
// Pre: La lista fue creada.
// Post: Se devolvió el valor del ultimo elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
//void* lista_borrar_ultimo(lista_t *lista);


// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: La lista fue creada.
// Post: Se devolvió el primer elemento de la lista, cuando no está vacía.
void* lista_ver_primero(const lista_t *lista);


// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: La lista fue creada.
// Post: Se devolvió el ultimo elemento de la lista, cuando no está vacía.
void* lista_ver_ultimo(const lista_t *lista);


// Te devuelve el largo de la lista
// Pre: La lista fue creada
// Post: Devuelve la cantidad de elementos que tiene la lista
size_t lista_largo(const lista_t *lista);


// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la cola fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void*));



/* ******************************************************************
 *                    PRIMITIVAS DE LOS ITERADORES
 * *****************************************************************/



 // Crea el iterador
 // Pre: Tiene que haber una lista ya creada
 // Post: Devuelve el iterador de la lista que le pasaste, devuelve NULL
 // de no poder
lista_iter_t *lista_iter_crear(lista_t *lista);

 // Avanza la posicion del iterador en la lista
 // Pre: La lista y su iterador fueron creados
 // Post: Avanza la posicion del iterador, devuelve true si se puede,
 // false en caso contrario
bool lista_iter_avanzar(lista_iter_t *iter);

 // Muestra el elemento de la posicion en la que se encuentra el iterador
 // Pre: La lista y su iterador fueron creados
 // Post: Devuelve el elemento de la posicion, de no poder devuelve NULL
void *lista_iter_ver_actual(const lista_iter_t *iter); 

// Te dice si el iterador se encuntra en la 
// Pre: La lista y su iterador fueron creados
// Post: Devuelve true si se encuentra al final, sino devuelve true
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador
// Pre: La lista y su iterador fueron creados
// Post: Elimina el iterador 
void lista_iter_destruir(lista_iter_t *iter);

// Inserta un elemento en la posicion que se encuentre el iterador
// Pre: La lista y su iterador fueron creados
// Post: Devuelve true si logro insertar el elemento, false en caso contrario 
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Elimina un elemento en la posicion que se encuentra el iterador
// Pre: La lista y el iterador fueron creados
// Post: Quito el elemento de la lista  y devuelveel valor, devuelve
// NULL en caso de que este vacia
void *lista_iter_borrar(lista_iter_t *iter);

// Itera internamente la lista
// Pre: La lista y el iterador fueron creados, y se le pasa la 
// funcion con lo que tiene que hacer
// Post: Cuando la funcion visitar de false se va a dejar de iterear
void lista_iterar(lista_t* lista, bool visitar(void *dato, void *extra), void *extra);


#endif //FILA_H
