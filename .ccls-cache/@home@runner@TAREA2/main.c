#include "Map.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{



} acciones;

typedef struct {

  char *nombre;
  int ph;
  int cantItems;
  Map *inventario;
  acciones accionJ;
} jugador;

int is_equal_string(void *key1, void *key2) {
  if (strcmp((char *)key1, (char *)key2) == 0)
    return 1;
  return 0;
}

void menuTexto(int *opcion) {

  printf("\nElija una opcion para continuar:\n");
  printf("\n1. Crear perfil.\n");
  printf("2. Mostrar perfil.\n");
  printf("3. Agregar item.\n");
  printf("4. Eliminar item.\n");
  printf("5. Agregar puntos de habilidad.\n");
  printf("6. Mostrar jugadores con item especifico.\n");
  printf("7. Deshacer última acción.\n");
  printf("8. Importar datos desde un archivo CSV.\n");
  printf("9. Exportar datos a un archivo CSV.\n");
  // en proceso
  printf("0. Salir del menu.\n");

  /*
    Usar string para comprobar que lo ingresa el usuario es un numero valido
    para nuestro menu
  */
  char comprobar[2];
  while (1) {
    scanf("%s", comprobar);

    if (isdigit(comprobar[0]) && strlen(comprobar) == 1)
    // ver que sea un numero de un digito
    {

      *opcion = atoi(comprobar);
      // ya cuando se comprueba se actualiza opcion
      return;
    }
    printf("Entrada invalida, ingrese una opcion valida entre 0 y 9\n");
  }
} // Importado de Tarea 1.

void crearPerfil(Map *jugadores) {

  jugador *aux = (jugador *)malloc(sizeof(jugador));
  char nombre[50];
  puts("\nIngrese el nombre del jugador:");
  scanf("%s[^\n]", nombre);
  getchar();

  aux->nombre = (char *)malloc(sizeof(char) * (strlen(nombre)+1));
  strcpy(aux->nombre, nombre);
  aux->cantItems = 0;
  aux->ph = 0;
  aux->inventario = createMap(is_equal_string);

  insertMap(jugadores, aux->nombre, aux);
}

void mostrarPerfil(Map *jugadores) {
  char nombre[50];
  puts("\nIngrese el nombre del jugador:");
  scanf("%s[^\n]", nombre);
  getchar();
  jugador *info = searchMap(jugadores, nombre);

  if (info == NULL) {
    printf("El jugador no se encuentra registrado");
    return;
  }

  printf("Nombre: %s\n", info->nombre);
  printf("Puntos de Habilidad: %i\n", info->ph);
  printf("\n***Items de %s***\n", info->nombre);

  Map *invJugador = info->inventario;
  char *item =
      (char *)firstMap(invJugador); // llamoa l primer item que hay en el mapa
                                    // de inventario del jugador
  if (item == NULL) {
    printf("El jugador no tiene items\n");
    return;
  }
  while (item != NULL) {
    printf("- %s\n", item); // pero me muestra el nombre del jugador ....
    item = nextMap(invJugador);
  }
  printf("\n*****************\n");
}

void agregarItem(Map *jugadores) {
  char item[50], nombre[50]; //usar array dinamico
  char *itemD;
  puts("\nIngrese el nombre del jugador:");
  scanf("%s[^\n]", nombre);
  getchar();
  jugador *aux = searchMap(jugadores, nombre);
  
  if (aux == NULL) {
    puts("El jugador buscado no se encuentra registrado.\n");
    return;
    
  } else {
    puts("\nIngrese el nombre del item:");
    scanf("%s[^\n]", item);
    itemD = (char*)malloc(sizeof(char) * (strlen(item) +1));
    strcpy(itemD,item);
    insertMap(aux->inventario, itemD, itemD);
    aux->cantItems++; // aqui en teoria se agrega un item al mapa de inventario
  }

  // probando
  jugador *info = searchMap(
      jugadores, nombre); // aqui reviso se actualizo en el mapa jugador
  char *obj = (char *)firstMap(info->inventario); //
  printf("- %s\n",
         obj); // y en teoria se muestra correctamente pero al llamar a
               // mostrarPerfil y practicamente hacer lo mismo que esta escrito
               // aca, este me muestra el nombre del jugador, no tengo idea de
               // como sucede eso, deber haber un problema entre medio, tal vez
               // en el uso de las funciones tipo mapa pero realmente no
               // entiendo que suecede
}

void eliminarItem(Map *jugadores) {}

void agregarPH(Map *jugadores) {}

void mostrarItemEspecifico(Map *jugadores) {}

void deshacerUltima(Map *jugadores) {}

void importarArchivo(Map *jugadores) {
  /*char archivo[100];
  printf("Ingrese el nombre del archivo CSV:\n");
  scanf("%s", archivo);
  FILE *csv = fopen(archivo, "r");

  if (csv == NULL){
    printf("Error al leer archivo\n");
    return;
  }

  char buffer[1024];

  */
}

void exportarArchivo(Map* jugadores) {
//ARREGLAR CASO DE MUCHOS ITEMS
    //test.csv es de prueba, falta agregar lectura de nombre
  FILE* fp = fopen("test.csv", "w");
  if (fp == NULL) {
    printf("Error al abrir/crear archivo %s\n", "test.csv");
    return;
  }
  //encabezados/headers
  fprintf(fp, "nombre,ph,item1,item2,item3\n");


  void* key = firstMap(jugadores);
  while (key != NULL) {
    jugador* info = (jugador*) searchMap(jugadores, key);


    fprintf(fp, "%s,%i,", info->nombre, info->ph);


    Map* invJugador = info->inventario;
    void* item = firstMap(invJugador);
    while (item != NULL) {
      fprintf(fp, "%s,", (char*)item);
      item = nextMap(invJugador);
    }


    fprintf(fp, "\n");

    key = nextMap(jugadores);
  }
 printf("Se ha exportado correctamente\n\n");
  fclose(fp);
}

int main() {
  int opcion;
  Map *jugadores = createMap(is_equal_string);

  printf("~~~~~~BIENVENIDO AL MENU DE JUGADOR~~~~~~\n\n");
  while (1) {

    menuTexto(&opcion);

    switch (opcion) {
    case 1:
      crearPerfil(jugadores);
      break;
    case 2:
      mostrarPerfil(jugadores);
      break;
    case 3:
      agregarItem(jugadores);
      break;
    case 4:
      eliminarItem(jugadores);
      break;
    case 5:
      agregarPH(jugadores);
      break;
    case 6:
      mostrarItemEspecifico(jugadores);
      break;
    case 7:
      deshacerUltima(jugadores);
      break;
    case 8:
      // importarArchivo(jugadores);
      break;
    case 9:
      exportarArchivo(jugadores);
      break;
    case 0:

      exit(EXIT_SUCCESS);

    default:
      printf("Elija una opcion del menu para continuar:\n\n");
    }
  }

  return 0;
}
