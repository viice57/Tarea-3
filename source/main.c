#include <stdio.h>
#include <stdlib.h>
#include "../include/hashmap.h"
#include "../include/treemap.h"
#include "../include/menu.h"

int lower_than_string(void * key1, void * key2){
    char* k1 = (char *) key1;
    char* k2 = (char *) key2;
    if(strcmp(k1,k2) < 0) return 1;
    return 0;
}

int main(void) {
  short choice = -1; 

  HashMap * mapGames = createMap(50);
  
  TreeMap * mapPrices = createTreeMap(lower_than_string);
  TreeMap * mapRatings = createTreeMap(lower_than_string);
  TreeMap * mapDates = createTreeMap(lower_than_string);
  
  do {
    fflush(stdin);
    
		showMenu();
		scanf("%hi", &choice);
		printf("\n");

		if(choice > 1 && !firstMap(mapGames)) {
      printf("No se ha abierto archivo alguno. Cerrando");
      break;
    }
    
		showChoice(mapGames, mapPrices, mapRatings, mapDates, choice);
	} while(choice != 0);

  free(mapGames);
  free(mapPrices);
  free(mapRatings);
  free(mapDates);
  
  return 0;
}