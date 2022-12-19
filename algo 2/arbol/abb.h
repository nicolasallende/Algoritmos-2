#ifndef ABB_H
#define ABB_H

#include <stddef.h>
#include <stdbool.h>

typedef struct abb abb_t;
	
typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *);


// Crea un arbol binario de busqueda.
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

//Pre: El abb fue creado.
//Post: Devuelve un true si pudo guardar el par (clave,dato) en el abb y false en caso contrario 
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

//Pre:El arbol fue creado.
//Post: Si la clave no existe dentro del abb o el abb esta vacio devuelve NULL.
//En caso de que la clave exista dentro del abb este, devuelve el dato asociado al par (clave,dato) y 
//borra la clave asociada a ese dato.
void *abb_borrar(abb_t *arbol, const char *clave);

//Pre:El arbol fue creado.
//Post:Si la clave no existe dentro del abb o el abb esta vacio devuelve NULL.
//En caso de que la clave exista dentro del abb este, devuelve el dato asociado al par (clave,dato).
void *abb_obtener(const abb_t *arbol, const char *clave);

//Pre:El arbol fue creado.
//Post:devuelve true si la clave existe dentro del abb y en caso contrario false.
bool abb_pertenece(const abb_t *arbol, const char *clave);

//Pre:El arbol fue creado.
//Post:Devuelve la cantidad de elementos, par(clave,dato) ,que hay en el abb.
size_t abb_cantidad(abb_t *arbol);

//Pre:El arbol fue credo.
//Post:Destruye el abb.
void abb_destruir(abb_t *arbol);


//recorrido interno inorder.
//Aplica lo que se que le pase a la funcion visitar sobre cada elem del abb.
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

//iter externo para recorrido externo.
typedef struct abb_iter abb_iter_t;

//Crea el iter ext sobre el cual es posible hacer el recorrido inorder.
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

//Pre:El iter ext fue creado.
//Post:Devuelve true si el iter ext no esta al final del abb y en caso contrario false.
bool abb_iter_in_avanzar(abb_iter_t *iter);

//Pre:El iter ext fue creado.
//Post: Devuelve la clave por la cual estas posicionado. Si el iter ext esta al final del abb devuelve NULL.
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

//Pre:El iter ext fue creado.
//Post: Devuelve true o false si el iter ext se encuentra al final.
bool abb_iter_in_al_final(const abb_iter_t *iter);

//Pre:El iter fue creado.
//Destruye el iter ext.
void abb_iter_in_destruir(abb_iter_t* iter);


/* PRUEBAS UNITARIAS */
void pruebas_abb_alumno(void);

#endif // ABB_H 
