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
  char rating[15];
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
  /* Variables para guardar nombre de archivo y línea a leer */
  char filename[FILENAME_LENGTH];
  char readLine[LINE_LENGTH];
  fflush(stdin);

  /* Menú para indicar el nombre de archivo, le añadimos la extensión .csv al final*/
  printf("\nIndique nombre del archivo: ");
  scanf("%30s", filename);
  getchar();
  strcat(filename, ".csv");

  /* Abrimos el archivo en modo lectura */
  FILE * file = fopen(filename, "r");

  /* Si el archivo no existe, simplemente se termina y retorna error */
  if(!file) return 1;

  /* Eliminamos primera línea */
  fgets(readLine, LINE_LENGTH, file);

  /* Ciclo para leer las líneas y asignar cada propiedad a un mapa con tabla hash */
  while(fgets(readLine, LINE_LENGTH, file)) {
    game * newGame = createGame(readLine);
    insertMap(mapGames, newGame->name, newGame);
  }

  /* Recorremos el mapa de juegos */
  for(HashPair * map = firstMap(mapGames); map != NULL; map = nextMap(mapGames)) {
    /*
    game * gameFromHash = (game *) map->value;

    //argumentos: mapa, criterio
    insertListOnTree(mapPrices, gameFromHash->price);
    insertListOnTree(mapRatings, gameFromHash->rating);
    insertListOnTree(mapDates, gameFromHash->date);
    */
    /* Inserción en árbol de precios */
    game * gameFromHash = (game *) map->value;
    TreePair * searchTree = searchTreeMap(mapPrices, gameFromHash->price);

    /* Si el key buscado existe, si no */
    if(searchTree) {
      /* Obtención de la lista desde el árbol. Insertamos un nuevo juego a la lista*/
      List * listAux = (List *) searchTree->value;
      pushBack(listAux, gameFromHash);
    } else {
      /* Asignación del juego a la lista, y posteriormente insertar la lista en el árbol */
      List * newList = createList();
      pushBack(newList, gameFromHash);
      insertTreeMap(mapPrices, gameFromHash->price, newList);
    }
  }

  /* Cerramos el archivo y mensaje de éxito */
  fclose(file);
  return 0;
}

/* Función para añadir una nueva propiedad a los mapas */
int addGame(HashMap * mapGames, TreeMap * mapPrices, TreeMap * mapRatings, TreeMap * mapDates)  {
  /* Nueva asignación de propiedad */
  char temp;
  game * newGame = (game *) malloc(sizeof(game));
  fflush(stdin);

  /* Menú para el ingreso de datos del juego. */
  printf("\nIngrese nombre del juego: ");
  scanf("%c", &temp);
  fgets(newGame->name, sizeof(newGame->name), stdin);
  newGame->name[strcspn(newGame->name, "\n")] = 0;

  printf("Ingrese fecha del juego (formato DD/MM/AAAA): ");
  scanf("%c", &temp);
  fgets(newGame->date, sizeof(newGame->date), stdin);
  newGame->date[strcspn(newGame->date, "\n")] = 0;

  printf("Ingrese valoración del juego: ");
  scanf("%c", &temp);
  fgets(newGame->rating, sizeof(newGame->rating), stdin);
  newGame->rating[strcspn(newGame->rating, "\n")] = 0;

  printf("Ingrese precio del juego: ");
  scanf("%c", &temp);
  fgets(newGame->price, sizeof(newGame->price), stdin);
  newGame->price[strcspn(newGame->price, "\n")] = 0;

  newGame->favourite = 0;

  /* Asignación a mapas */
  insertMap(mapGames, newGame->name, newGame);
  //insertListOnTree(mapPrices, newGame->price);
  //insertListOnTree(mapRatings, newGame->rating);
  //insertListOnTree(mapDates, newGame->date);

  /* Mensaje de éxito */
  return 0;
}

/* Función que muestra todos los juegos según el precio, incluyendo los que son agregados posteriormente */
int showByPrice(TreeMap * mapPrices) {
  unsigned short i = 1;
  char sType[11];
  fflush(stdin);

  /* Escaneo del tipo de búsqueda */
  printf("\nIngrese tipo de búsqueda de precios (creciente/decreciente): ");
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
    for(game * juego = (game *) firstList((List *) newSearch->value); juego != NULL; juego = (game *) nextList((List *) newSearch->value)) {
      printf("Juego %d\n", i);
      printf("Nombre: %s\n", juego->name);
      printf("Fecha: %s\n", juego->date);
      printf("Valoración: %s\n", juego->rating);
      printf("Precio: $ %s\n", juego->price);
      printf("\n");
      
      i++;
    }
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
    if(rating > (char *) newSearch->key) {
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
  printf("Ingrese año a buscar: ");
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
  char name[40];
  char temp;
  fflush(stdin);

  /* Entramos y preguntamos si existe el juego dentro del mapa */
  do {
    printf("\nIngrese nombre del nuevo favorito: ");
    scanf("%c", &temp);
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
  } while(!searchMap(mapGames, name));

  /* Ciclo para determinar si una propiedad será favorita o si no existen favoritos. */
  for(HashPair * favGame = firstMap(mapGames); favGame != NULL; favGame = nextMap(mapGames)) {
    if(is_equal_hash(((game *) favGame->value)->name, name)) {
      if(((game *) favGame->value)->favourite == 0) ((game *) favGame->value)->favourite = 1;
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
  for(HashPair * favGame = firstMap(mapGames); favGame != NULL; favGame = nextMap(mapGames)) {
    if(((game *) favGame->value)->favourite == 1) {
      printf("• %s\n", favGame->key);
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

  /* Abrimos el archivo en modo lectura y escritura */
  FILE * file = fopen(filename, "r+");
  
  /* Si el archivo no existe, simplemente se termina el programa */
  if(!file) return 1;

  /* Eliminamos el contenido actual del archivo */
  remove(filename);

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