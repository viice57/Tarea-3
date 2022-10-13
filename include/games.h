#ifndef GAME_H
#define GAME_H

#include "hashmap.h"
#include "treemap.h"

typedef struct game game;

/* Función para separar un juego a partir del archivo .csv */
game * createGame(char readLine[]);

int importGames(HashMap * mapGames, TreeMap * mapPrices, TreeMap * mapRatings, TreeMap * mapDates);

int addGame(HashMap * mapGames, TreeMap * mapPrices, TreeMap * mapRatings, TreeMap * mapDates);

int showByPrice(HashMap * mapPrices);

int showByRating(HashMap * mapRatings);

int showByDate(HashMap * mapDates);

int addFavourite(HashMap * mapGames);

int showFavourites(HashMap * mapGames);

int exportAll(HashMap * mapGames);

#endif