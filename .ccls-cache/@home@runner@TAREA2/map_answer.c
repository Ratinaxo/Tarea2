#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {

  long indice = hash(key,map->capacity);
  Pair *nuevo = createPair(key,value);

  if(map->buckets[indice] == NULL){
    map->buckets[indice] = nuevo;
    map->current = indice;
    
  }else{

    for(long i=indice ; i < map->capacity + indice ; i++){

      long j = i % map->capacity;
      if(map->buckets[j] == NULL || map->buckets[j]->key == NULL){

        map->buckets[j] = nuevo;
        map->current = j;
        
        break;
      }
    }
    
  }
  
  map->size++;

}

void enlarge(HashMap * map) {
  enlarge_called = 1; //no borrar (testing purposes)

  Pair **aux = map->buckets;
  map->capacity *= 2; 
  map->size = 0;
  
  map->buckets = (Pair **) calloc(map->capacity, sizeof(Pair *));
  for(long i = 0; i < map->capacity /2 ; i++){

    if(aux[i] != NULL) insertMap(map, aux[i]->key, aux[i]->value);
    
  }
  free(aux);
}


HashMap * createMap(long capacity) {

  HashMap *mapa = (HashMap*)malloc(sizeof(HashMap));
  if(mapa == NULL) exit(EXIT_FAILURE);
  
  mapa->buckets = (Pair**)malloc(sizeof(Pair*) * capacity);
  if(mapa->buckets == NULL) exit(EXIT_FAILURE);

  for(long i=0 ; i<capacity ; i++){

    mapa->buckets[i] = NULL;
  }
  
  mapa->size = 0;
  mapa->current = -1;
  mapa->capacity = capacity;
  return mapa;
}

void eraseMap(HashMap * map,  char * key) {    

  long indice = hash(key,map->capacity);

  if(map->buckets[indice] == NULL){
    return;
  }

  if(strcmp(map->buckets[indice]->key,key) == 0){

    map->buckets[indice]->key = NULL;
    map->size--;
    
    return;

  }else{

    for(long i=indice ; i < map->capacity + indice ; i++){
      
      long j = i % map->capacity;
      if(map->buckets[j] == NULL) return;
      
      if(strcmp(map->buckets[j]->key,key) == 0){
        map->buckets[j]->key = NULL;
        return;
      }
    
    }
    
  }

}

Pair * searchMap(HashMap * map,  char * key) { 
  
  long indice = hash(key,map->capacity);

  if(map->buckets[indice] == NULL){
    return NULL;
  }

  if(strcmp(map->buckets[indice]->key,key) == 0){

    map->current = indice;
    return map->buckets[indice];

  }else{

    for(long i=indice ; i < map->capacity + indice ; i++){
      
      long j = i % map->capacity;
      if(map->buckets[j] == NULL) return NULL;
      
      if(strcmp(map->buckets[j]->key,key) == 0){
        map->current = j;
        return map->buckets[j];
      }
    
    }
    return NULL;
  }
  
}

Pair * firstMap(HashMap * map) {

  for(long i = map->current ; i < map->capacity + map->current ; i++){
    
    if(map->buckets[i] != NULL && map->buckets[i]->key != NULL ){
      map->current = i;
      return map->buckets[i];
    }
  }
  return NULL;
}

Pair * nextMap(HashMap * map) {

  for (long i = map->current + 1 ; i < map->capacity ; i++) {
    if (map->buckets[i] != NULL && map->buckets[i]->key != NULL) {
      map->current = i;
      return map->buckets[i];
    }
  }
 return NULL;
}
