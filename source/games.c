#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/games.h"

#define FILENAME_LENGTH 30
#define LINE_LENGTH 99

/* Estructura para asignar juegos a mapas y listas */
struct game {
  char name[40];
  char date[5];
  char rating[3];
  char price[8];
  unsigned short favourite;
};

/* Función para insertar o crear una lista para cada nodo del árbol */
void insertListOnTree(TreeMap * map, game * gameFromHash, char * key) {
  TreePair * searchTree = searchTreeMap(map, key);

  /* Si el key buscado existe. Si no existe, se crea nueva lista */
  if(searchTree) {
    /* Obtención de la lista desde el árbol de precios. Insertamos un nuevo juego a la lista */
    List * listAux = (List *) searchTree->value;
    pushBack(listAux, gameFromHash);
  } else {
    /* Crear lista, insertar el juego en ella y asignar la lista al nodo correspondiente */
    List * newList = createList();
    pushBack(newList, gameFromHash);
    insertTreeMap(map, key, newList);
  }
}

/* Función para separar un juego a partir del archivo .csv */
game * createGame(char readLine[]) {
  game * newGame = (game *) malloc(sizeof(game));
  char * split;

  /* Separamos los siguientes datos del juego: nombre, año, valoración y precio. También, por defecto no es favorito */
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

  /* Si el archivo no existe o ya había sido importado, se termina y retorna error */
  if(!file || firstMap(mapGames)) return 1;

  /* Eliminamos primera línea */
  fgets(readLine, LINE_LENGTH, file);

  /* Ciclo para leer las líneas y asignar cada propiedad a un mapa con tabla hash */
  while(fgets(readLine, LINE_LENGTH, file)) {
    game * newGame = createGame(readLine);
    insertMap(mapGames, newGame->name, newGame);
  }

  /* Recorremos el mapa de juegos */
  for(HashPair * map = firstMap(mapGames); map != NULL; map = nextMap(mapGames)) {
    game * gameFromHash = (game *) map->value;

    /* Inserción en árboles a partir de tabla hash (mapGames) */
    insertListOnTree(mapPrices, gameFromHash, gameFromHash->price);
    insertListOnTree(mapRatings, gameFromHash, gameFromHash->rating);
    insertListOnTree(mapDates, gameFromHash, gameFromHash->date);
  }

  /* Cerramos el archivo y mensaje de éxito */
  fclose(file);
  return 0;
}

/* Función para añadir una nueva propiedad a los mapas */
int addGame(HashMap * mapGames, TreeMap * mapPrices, TreeMap * mapRatings, TreeMap * mapDates)  {
  game * newGame = (game *) malloc(sizeof(game));
  char temp;
  fflush(stdin);

  /* Menú para el ingreso de datos del juego. */
  printf("\nIngrese nombre del juego: ");
  scanf("%c", &temp);
  fgets(newGame->name, sizeof(newGame->name), stdin);
  newGame->name[strcspn(newGame->name, "\n")] = 0;

  /* Si el nombre está ocupado retorna error */
  if(searchMap(mapGames, newGame->name)) return 1;

  printf("Ingrese año del juego: ");
  scanf("%5s", newGame->date);
  getchar();

  printf("Ingrese valoración del juego: ");
  scanf("%3s", newGame->rating);
  getchar();

  printf("Ingrese precio del juego: ");
  scanf("%8s", newGame->price);
  getchar();

  newGame->favourite = 0;

  /* Asignación a mapas */
  insertMap(mapGames, newGame->name, newGame);
  insertListOnTree(mapDates, newGame, newGame->date);
  insertListOnTree(mapRatings, newGame, newGame->rating);
  insertListOnTree(mapPrices, newGame, newGame->price);

  /* Mensaje de éxito */
  return 0;
}

/* Función que muestra todos los juegos según el precio, incluyendo los que son agregados posteriormente */
int showByPrice(TreeMap * mapPrices) {
  unsigned short i = 1;
  char sType[12];
  fflush(stdin);

  /* Escaneo del tipo de búsqueda */
  printf("\nIngrese tipo de búsqueda de precios (creciente/decreciente): ");
  scanf("%12s", sType);
  getchar();
  
  /* Si no existe algún juego, muestra mensaje y termina el programa. */
  if(!firstTreeMap(mapPrices)) return 1;

  if(strcmp(sType, "creciente") == 0) {
    /* Recorremos el mapa de precios y sus nodos, con su respectiva lista de juegos */
    for(TreePair * newSearch = firstTreeMap(mapPrices); newSearch != NULL; newSearch = nextTreeMap(mapPrices)) {
      for(game * juego = (game *) firstList((List *) newSearch->value); juego != NULL; juego = (game *) nextList((List *) newSearch->value)) {
        printf("\n");
        printf("Juego %d\n", i);
        printf("Nombre: %s\n", juego->name);
        printf("Fecha: %s\n", juego->date);
        printf("Valoración: %s\n", juego->rating);
        printf("Precio: $ %s\n", juego->price);
      
        i++;
      }
    }
  } else if(strcmp(sType, "decreciente") == 0) {
    printf("\nNo implementado. Pruebe con creciente.");
    return 1;
  } else {
    printf("\nOpción inválida. Pruebe con creciente.");
    return 1;
  }

  /* Se mostraron todos los juegos */
  if(i == 1) return 1;
  else return 0;
}

/* Función que muestra todos los juegos según el rating, incluyendo los que son agregados posteriormente */
int showByRating(TreeMap * mapRatings) {
  unsigned short i = 1;
  char rating[3];
  fflush(stdin);

  /* Si no existe algún juego con rating mayor, muestra mensaje y termina el programa. */
  if(!firstTreeMap(mapRatings)) return 1;

  /* Escaneo del rating */
  printf("\nIngrese rating mínimo a buscar: ");
  scanf("%3s", rating);
  getchar();

  /* Ingresamos al value de cada nodo, para entrar a la lista que contiene los juegos que tienen la misma key */
  for(TreePair * newSearch = upperBound(mapRatings, rating); newSearch != NULL; newSearch = nextTreeMap(mapRatings)) {
    for(game * juego = (game *) firstList((List *) newSearch->value); juego != NULL; juego = (game *) nextList((List *) newSearch->value)) {
      printf("\n");
      printf("Juego %d\n", i);
      printf("Nombre: %s\n", juego->name);
      printf("Fecha: %s\n", juego->date);
      printf("Valoración: %s\n", juego->rating);
      printf("Precio: $ %s\n", juego->price);
    
      i++;
    }
  }

  /* Se mostraron todos los juegos */
  if(i == 1) return 1;
  else return 0;
}

/* Función que muestra todos los juegos según la fecha, incluyendo los que son agregados posteriormente */
int showByDate(TreeMap * mapDates) {
  unsigned short i = 1;
  char date[5];
  fflush(stdin);

  /* Si no existe algún juego, muestra mensaje y termina el programa. */
  if(!firstTreeMap(mapDates)) return 1;

  /* Escaneo del año*/
  do {
    printf("\nIngrese año a buscar: ");
    scanf("%5s", date);
    getchar();
  } while(!searchTreeMap(mapDates, date));

  /* Buscamos en el árbol de fechas la indicada */
  TreePair * newSearch = searchTreeMap(mapDates, date);
  for(game * juego = (game *) firstList((List *) newSearch->value); juego != NULL; juego = (game *) nextList((List *) newSearch->value)) {
    printf("\n");
    printf("Juego %d\n", i);
    printf("Nombre: %s\n", juego->name);
    printf("Fecha: %s\n", juego->date);
    printf("Valoración: %s\n", juego->rating);
    printf("Precio: $ %s\n", juego->price);
    
    i++;
  }

  /* Se mostraron todos los juegos */
  return 0;
}

int searchGame(HashMap * mapGames, TreeMap * mapPrices, TreeMap * mapRatings, TreeMap * mapDates) {
  char temp;
  char name[40];
  char whatToDo[2];
  fflush(stdin);

  /* Pedimos el nombre del juego a buscar */
  printf("\nIngrese nombre del juego a buscar: ");
  scanf("%c", &temp);
  fgets(name, sizeof(name), stdin);
  name[strcspn(name, "\n")] = 0;

  /* Buscamos si el juego existe. Si no, error */
  HashPair * newSearch = searchMap(mapGames, name);
  if(!newSearch) return 1;

  /* Ya que el juego existe, obtenemos sus datos */
  game * currentGame = (game *) newSearch->value;

  /* Datos del juego */
  printf("Año: %s\n", currentGame->date);
  printf("Valoración: %s\n", currentGame->rating);
  printf("Precio: $ %s\n", currentGame->price);

  /* Se pregunta si desea otra operación */
  printf("\n¿Desea modificar o eliminar el juego? (m/e): ");
  scanf("%c", whatToDo);
  getchar();

  /* Comparamos la opción ingresada con las posibles */
  if(strcmp(whatToDo, "m") == 0) {
    /* Preguntamos los nuevos datos y se reemplazan */
    printf("\nHa seleccionado modificar datos.");
    
    printf("Ingrese año del juego: ");
    scanf("%5s", currentGame->date);
    getchar();

    printf("Ingrese valoración del juego: ");
    scanf("%3s", currentGame->rating);
    getchar();

    printf("Ingrese precio del juego: ");
    scanf("%8s", currentGame->price);
    getchar();
  } else if(strcmp(whatToDo, "e") == 0) {
    printf("\nHa seleccionado eliminar el juego. Eliminando...\n");

    /* Se borra en el mapa de juegos */
    eraseMap(mapGames, currentGame->name);
  } else {
    printf("\nOpción inválida.");
    return 1;
  }

  /* Mensaje de éxito */
  return 0;
}

/* Función para añadir un favorito al mapa de juegos */
int addFavourite(HashMap * mapGames) {
  char temp;
  char name[40];
  fflush(stdin);

  /* Pedimos el nombre del juego a buscar */
  printf("\nIngrese nombre del nuevo favorito: ");
  scanf("%c", &temp);
  fgets(name, sizeof(name), stdin);
  name[strcspn(name, "\n")] = 0;

  /* Buscamos si el juego existe. Si no, error */
  if(!searchMap(mapGames, name)) return 1;

  /* Ciclo para determinar si una propiedad será favorita o si no existen favoritos. */
  for(HashPair * favGame = firstMap(mapGames); favGame != NULL; favGame = nextMap(mapGames)) {
    if(is_equal_hash(((game *) favGame->value)->name, name)) {
      if(((game *) favGame->value)->favourite == 0) ((game *) favGame->value)->favourite = 1;
      else return 1;
    }
  }

  /* Mensaje de éxito */
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

  /* Mensaje de error o éxito */
  if(totalFavs == 0) return 1;
  else return 0;
}

/* Función para exportar juegos hacia archivo */
int exportAll(HashMap * mapGames) {
  /* Nombre de archivo */
  char filename[30];
  fflush(stdin);
  
  /* Menú para indicar el nombre, le añadimos la extensión .csv al final */
  printf("\nIndique nombre del archivo: ");
  scanf("%30s", filename);
  getchar();
  strcat(filename, ".csv");

  /* Abrimos el archivo en modo escritura. Si existe, se reemplaza */
  FILE * file = fopen(filename, "w");

  /* Si el archivo no se puede abrir, simplemente se termina el programa */
  if(!file) return 1;

  /* Escribimos la primera línea */
  fprintf(file, "%s", "Nombre,año de salida,valoracion,precio\n");
  
  /* Recorriendo el mapa de juegos e imprimiendo sus datos */
  for(HashPair * exportGame = firstMap(mapGames); exportGame != NULL; exportGame = nextMap(mapGames)) {
    fprintf(file, "%s,", (char *) exportGame->key);
    fprintf(file, "%s,", ((game *) exportGame->value)->date);
    fprintf(file, "%s,", ((game *) exportGame->value)->rating);
    fprintf(file, "%s\n", ((game *) exportGame->value)->price);
  }
  
  /* Cerramos el archivo y muestra mensaje de éxito */
  fclose(file);
  return 0;
}