#include <stdio.h>
#include <stdlib.h>

#include "list.c"
#include "hashmap.c"
#include "treemap.c"
#include "menu.c"
#include "games.c"

int lower_than_string(void * key1, void * key2){
    char * k1 = (char *) key1;
    char * k2 = (char *) key2;
    if(strcmp(k1, k2) < 0) return 1;
    return 0;
}

int main(void) {
  short choice = -1; 

  HashMap * mapGames = createMap(100);
  
  TreeMap * mapPrices = createTreeMap(lower_than_string);
  TreeMap * mapRatings = createTreeMap(lower_than_string);
  TreeMap * mapDates = createTreeMap(lower_than_string);
  
  do {
    showMenu();
    
    fflush(stdin);
		scanf("%hi", &choice);

		if(choice > 1 && choice < 10) {
      if(!firstMap(mapGames)) {
        printf("\nNo se ha abierto archivo alguno. Cerrando.");
        break;
      }
    }
    
		showChoice(mapGames, mapPrices, mapRatings, mapDates, choice);
	} while(choice != 0);
  
  return 0;
}