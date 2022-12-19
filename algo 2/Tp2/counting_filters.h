#ifndef COUNTING_FILTERS_H
#define COUNTING_FILTERS_H

typedef struct counting_filters counting_filters_t; 

//crea el counting filters
counting_filters_t* counting_filters_crear();


//Pre: el counting filters fue creado.
//Post:Agrega el hashtag al counting filters.
void counting_filters_agregar_aparicion_hashtag(counting_filters_t* counting_filters,char* hashtag);

//Destruye el counting filters. 
void counting_filters_destruir(counting_filters_t* counting_filters);

//Pre:El counting filters fue creado.
//Restablece el historial de tweets dejandolo vacio, para armar el siguiente trending topic.
bool counting_filters_reestableciendo_historial(counting_filters_t* counting_filters);

//IMPLEMENTACIONES DEL TRENDING TOPIC
typedef struct datos_trending_topic datos_trend_top_t;

//Crea el trending topic.
datos_trend_top_t** trending_topic_crear(counting_filters_t* counting_filters,size_t tam_trend_topic);

//Pre:El trending topic fue creado.
//Post: Imprime por salida estandar el trending topic actual.
void imprimir_trending_topic(datos_trend_top_t** trending_topic,size_t tam_trend_topic);

 
//Pre:El trending topic fue creado.
//Post:Destruye el trending topic.
void trending_topic_destruir(datos_trend_top_t** trending_topic,size_t tam_trend_topic);

#endif // FIN DE COUNTING_FILTERS_H