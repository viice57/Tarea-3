#include <stdio.h>
#include "../include/games.h"
#include "../include/menu.h"

void showMenu() {
  printf("\n%sMenú de opciones%s\n\n", "\x1B[1m", "\x1B[0m");

  printf("(1) Importar archivo de juegos\n");
  printf("(2) Agregar juego\n");
  printf("(3) Mostrar juegos por precio\n");
  printf("(4) Mostrar juegos por valoración\n");
  printf("(5) Mostrar juegos por año\n");
  printf("(6) Buscar juego\n");
  printf("(7) Agregar juego a favoritos\n");
  printf("(8) Mostrar mis favoritos\n");
  printf("(9) Exportar datos\n");
  printf("(0) Terminar el programa\n");
  
  printf("\nIndique la accion deseada (solo números): ");
}

void showChoice(HashMap * mapGames, short choice) {
  switch(choice) {
    case 0:
      printf("*********************\n");
  		printf("* Fin del programa. *\n");
  		printf("*********************\n");
      break;
		case 1:
      importProperties(listProperties, mapIDs, mapCities, mapTypes);
  		break;
  	case 2:
      addProperty(listProperties, mapIDs, mapCities, mapTypes);
  		break;
  	case 3:
  		showByAll(mapIDs);
  		break;
  	case 4:
  		showByCity(mapCities);
  		break;
  	case 5:
  		showByType(mapTypes);
      break;
  	case 6:
  		showByCapacity(mapIDs);
  		break;
  	case 7:
      addFavourite(listProperties, mapIDs);
  		break;
  	case 8:
  		showMyFavourites(listProperties);
  		break;
  	case 9:
  		exportProperties(mapIDs);
  		break;
  	default:
  		printf("**************************************\n");
  		printf("* ¡No existe tal opcion, elija otra! *\n");
  		printf("**************************************\n");
  		break;
	}
  printf("\n");
}