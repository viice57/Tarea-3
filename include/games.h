#ifndef GAME_H
#define GAME_H

typedef struct game game;

void insertListOnTree(TreeMap * map, game * gameFromHash, char * key);

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