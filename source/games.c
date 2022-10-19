#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/games.h"

#define FILENAME_LENGTH 30
#define LINE_LENGTH 99

/* Estructura para asignar juegos a mapas */
struct game {
  char name[40];
  char date[20];
  char rating[10];
  char price[15];
  unsigned short favourite;
};

/* Función para separar un juego a partir del archivo .csv */
game * createGame(char readLine[]) {
  game * newGame = (game *) malloc(sizeof(game));
  char * split;

  /* Escaneamos los siguientes datos del juego: nombre, fecha, valoración y precio. También, por defecto no es favorito */
  split = strtok(readLine, ",");
  strncpy(newGame->name, split, sizeof(newGame->name));

  split = strtok(NULL, ",");
  strncpy(newGame->date, split, sizeof(newGame->date));
  
  split = strtok(NULL, ",");
  strncpy(newGame->rating, split, sizeof(newGame->rating));

  split = strtok(NULL, "\n");
  strncpy(newGame->price, split, sizeof(newGame->price));

  newGame->favourite = 0;

  /* Retornamos el juego */
  return newGame;
}

/* Función para importar el archivo .csv y asignar a los mapas respectivos. */
int importGames(HashMap * mapGames, TreeMap * mapPrices, TreeMap * mapRatings, TreeMap * mapDates) {
  /* Variables para guardar nombre de archivo y líneas a leer */
  char filename[FILENAME_LENGTH];
  char readLine[LINE_LENGTH];
  fflush(stdin);

  /* Menú para indicar el nombre de archivo, le añadimos la extensión .csv al final*/
  printf("Indique nombre del archivo: ");
  scanf("%30s", filename);
  getchar();
  strcat(filename, ".csv");

  /* Abrimos el archivo en modo lectura */
  FILE * file = fopen(filename, "r");

  /* Si el archivo no existe, simplemente se termina el programa */
  if(!file) return 1;

  /* Ciclo para leer las líneas y asignar cada propiedad a un mapa con tabla hash */
  while(fgets(readLine, LINE_LENGTH, file)) {
    game * newGame = createGame(readLine);
    insertMap(mapGames, newGame->name, newGame);
  }

  /* Cerramos el archivo y eliminamos primera línea */
  //fclose(file);
  eraseMap(mapGames, "Nombre");

  /* Recorremos el mapa de juegos */
  for(game * map = firstMap(mapGames); map != NULL; map = nextMap(mapGames)) {
    /* Asignacion del elemento del mapa al árbol respectivo */
    //insertTreeMap(mapPrices, map->price, map);
    //insertTreeMap(mapRatings, map->rating, map);
    //insertTreeMap(mapDates, map->date, map);
  }

  return 0;
}

/* Función para añadir una nueva propiedad a los mapas */
int addGame(HashMap * mapGames, TreeMap * mapPrices, TreeMap * mapRatings, TreeMap * mapDates)  {
  /* Nueva asignación de propiedad */
  game * newGame = (game *) malloc(sizeof(game));
  fflush(stdin);

  /* Menú para el ingreso de datos del juego. */
  printf("Ingrese nombre del juego: ");
  fgets(newGame->name, sizeof(newGame->name), stdin);
  getchar();
  newGame->name[strcspn(newGame->name, "\n")] = 0;

  printf("Ingrese fecha del juego (formato DD/MM/AAAA): ");
  fgets(newGame->date, sizeof(newGame->date), stdin);
  getchar();
  newGame->date[strcspn(newGame->date, "\n")] = 0;

  printf("Ingrese valoración del juego: ");
  fgets(newGame->rating, sizeof(newGame->rating), stdin);
  getchar();
  newGame->rating[strcspn(newGame->rating, "\n")] = 0;

  printf("Ingrese precio del juego: ");
  fgets(newGame->price, sizeof(newGame->price), stdin);
  getchar();
  newGame->price[strcspn(newGame->price, "\n")] = 0;

  newGame->favourite = 0;

  /* Asignación a mapas */
  insertMap(mapGames, newGame->name, newGame);
  //insertTreeMap(mapPrices, newGame->price, newGame);
  //insertTreeMap(mapRatings, newGame->rating, newGame);
  //insertTreeMap(mapDates, newGame->date, newGame);

  /* Mensaje de éxito */
  return 0;
}

/* Función que muestra todos los juegos según el precio, incluyendo los que son agregados posteriormente */
int showByPrice(TreeMap * mapPrices) {
  unsigned short i = 1;
  char sType[11];
  fflush(stdin);

  /* Escaneo del tipo de búsqueda */
  printf("Ingrese tipo de búsqueda de precios (creciente/decreciente): ");
  scanf("%11s", sType);
  getchar();

  /*switch(sType) {
    case "creciente":
      break;
    case "decreciente":
      break;
    default:
      break;
  } */
  
  /* Si no existe algún juego con ese precio, muestra mensaje y termina el programa. */
  if(!firstTreeMap(mapPrices)) return 1;
  
  for(TreePair * newSearch = firstTreeMap(mapPrices); newSearch != NULL; newSearch = nextTreeMap(mapPrices)) {
    printf("Juego %d\n", i);
    printf("Nombre: %s\n", ((game *) newSearch->value)->name);
    printf("Fecha: %s\n", ((game *) newSearch->value)->date);
    printf("Valoración: %s\n", ((game *) newSearch->value)->rating);
    printf("Precio: $ %s\n", (char *) newSearch->key);
    printf("\n");
    i++;
  }

  /* Se mostraron todos los juegos */
  return 0;
}

/* Función que muestra todos los juegos según el rating, incluyendo los que son agregados posteriormente */
int showByRating(TreeMap * mapRatings) {
  unsigned short i = 1;
  char rating[2];
  fflush(stdin);

  //Agregar for para mostrar los ratings disponibles

  /* Escaneo del rating */
  printf("Ingrese rating mínimo a buscar: ");
  scanf("%2s", rating);
  getchar();
  
  for(TreePair * newSearch = firstTreeMap(mapRatings); newSearch != NULL; newSearch = nextTreeMap(mapRatings)) {
    if((char *) newSearch->key > rating) {
      printf("Juego %d\n", i);
      printf("Nombre: %s\n", ((game *) newSearch->value)->name);
      printf("Fecha: %s\n", ((game *) newSearch->value)->date);
      printf("Valoración: %s\n", (char *) newSearch->key);
      printf("Precio: $ %s\n", ((game *) newSearch->value)->price);
      printf("\n");
    
      i++;
     }
  }

  /* Se mostraron todos los juegos */
  return 0;
}

/* Función que muestra todos los juegos según la fecha, incluyendo los que son agregados posteriormente */
int showByDate(TreeMap * mapDates) {
  unsigned short i = 1;
  char date[10];
  fflush(stdin);

  /* Escaneo de la fecha */
  printf("Ingrese fecha a buscar (formato DD/MM/AAAA): ");
  scanf("%10s", date);
  getchar();

  /* Si no existe algún juego con esa fecha, muestra mensaje y termina el programa. */
  if(!searchTreeMap(mapDates, date)) return 1;
  
  for(TreePair * newSearch = firstTreeMap(mapDates); newSearch != NULL; newSearch = nextTreeMap(mapDates)) {
    printf("Juego %d\n", i);
    printf("Nombre: %s\n", ((game *) newSearch->value)->name);
    printf("Fecha: %s\n", (char *) newSearch->key);
    printf("Valoración: %s\n", ((game *) newSearch->value)->rating);
    printf("Precio: $ %s\n", ((game *) newSearch->value)->price);
    printf("\n");
    
    i++;
  }

  /* Se mostraron todos los juegos */
  return 0;
}

/* Función para añadir un favorito al mapa de juegos */
int addFavourite(HashMap * mapGames) {
  char name[20];
  fflush(stdin);

  /* Entramos y preguntamos si existe el juego dentro del mapa */
  do {
    printf("Ingrese nombre del nuevo favorito: ");
    scanf("%20s", name);
    getchar();
  } while(!searchMap(mapGames, name));

  /* Ciclo para determinar si una propiedad será favorita o si no existen favoritos. */
  for(game * favGame = (game *) firstMap(mapGames); favGame != NULL; favGame = (game *) nextMap(mapGames)) {
    if(is_equal_hash(favGame->name, name)) {
      if(favGame->favourite == 0) favGame->favourite = 1;
      else return 1;
    }
  }

  /* Mensaje de éxito o error */
  return 0;
}

/* Función que muestra los favoritos */
int showFavourites(HashMap * mapGames) {
  unsigned short totalFavs = 0;

  /* Recorremos el mapa de juegos busca de favoritos */
  for(game * favGame = (game *) firstMap(mapGames); favGame != NULL; favGame = (game *) nextMap(mapGames)) {
    if(favGame->favourite == 1) {
      printf("%s\n", favGame->name);
      totalFavs++;
    }
  }

  if(totalFavs == 0) return 1;
  else return 0;
}

/* Función para exportar items hacia archivo */
int exportAll(HashMap * mapGames) {
  /* Nombre de archivo */
  char filename[30];
  fflush(stdin);
  
  /* Menú para indicar el nombre, le añadimos la extensión .csv al final */
  printf("Indique nombre del archivo: ");
  scanf("%30s", filename);
  getchar();
  strcat(filename, ".csv");

  /* Abrimos el archivo en modo lectura */
  FILE * file = fopen(filename, "r");
  
  /* Si el archivo no existe, simplemente se termina el programa */
  if(!file) return 1;

  /* Eliminamos el contenido actual del archivo */
  remove(filename);

  /* Abrimos el archivo en modo escritura */
  file = fopen(filename, "w");

  /* Escribimos la primera línea */
  fprintf(file, "%s", "Nombre,año de salida,valoracion,precio\n");
  
  /* Recorriendo el mapa de juegos e imprimiendo sus datos */
  for(HashPair * Game = firstMap(mapGames); Game != NULL; Game = nextMap(mapGames)) {
    fprintf(file, "%s,", (char *) Game->key);
    fprintf(file, "%s,", ((game *) Game->value)->date);
    fprintf(file, "%s,", ((game *) Game->value)->rating);
    fprintf(file, "%s\n", ((game *) Game->value)->price);
  }
  
  /* Cerramos el archivo  y mensaje de éxito */
  fclose(file);
  return 0;
}