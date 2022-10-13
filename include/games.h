#ifndef GAME_H

#include "hashmap.h"
#include "treemap.h"

typedef struct game game;

/* Función para separar un juego a partir del archivo .csv */
game * createGame(char readLine[]);

int importGames(HashMap * mapGames, TreeMap * mapPrices, TreeMap * mapRatings, TreeMap * mapDates);

int addGame(HashMap * mapGames, TreeMap * mapPrices, TreeMap * mapRatings, TreeMap * mapDates);

int showByPrice(TreeMap * mapPrices);

int showByRating(TreeMap* mapRatings);

int showByDate(TreeMap * mapDates);

int addFavourite(HashMap * mapGames);

int showFavourites(HashMap * mapGames);

int exportAll(HashMap * mapGames);

#endif