#include <stdio.h>
#include <stdlib.h>
#include "../include/hashmap.h"
#include "../include/treemap.h"
#include "../include/menu.h"

int main(void) {
  short choice = -1; 

  HashMap * mapGames = createMap(50);

  do {
    fflush(stdin);
    
		showMenu();
		scanf("%hi", &choice);
		printf("\n");

		if(choice > 1 && !firstMap(mapGames)) {
      printf("No se ha abierto archivo alguno. Cerrando");
      break;
    }
    
		showChoice(mapGames);
	} while(choice != 0);

  free(mapGames);
  
  return 0;
}