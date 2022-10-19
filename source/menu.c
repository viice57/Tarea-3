#include <stdio.h>
#include <stdlib.h>

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

void showChoice(HashMap * mapGames, TreeMap * mapPrices, TreeMap * mapRatings, TreeMap * mapDates, short choice) {
  int msg;

  switch(choice) {
    case 0:
      printf("*********************\n");
  		printf("* Fin del programa. *\n");
  		printf("*********************\n");
      break;
		case 1:
      msg = importGames(mapGames, mapPrices, mapRatings, mapDates);

      if(msg) {
        printf("Archivo no encontrado. ");
        exit(EXIT_FAILURE);
      } else {
        printf("***********************\n");
        printf("* ¡Archivo importado! *\n");
        printf("***********************\n");
      }
  		break;
  	case 2:
      msg = addGame(mapGames, mapPrices, mapRatings, mapDates);

      if(!msg) {
        printf("********************\n");
        printf("* ¡Juego agregado! *\n");
        printf("********************\n");  
      }
  		break;
  	case 3:
  		msg = showByPrice(mapPrices);

      if(msg) {
        printf("No se ha encontrado alguna propiedad por tal precio. Pruebe otro valor.");
      } else {
        printf("**************************************\n");
        printf("* ¡Se han mostrado todos los juegos! *\n");
        printf("**************************************\n");  
      }
  		break;
  	case 4:
  		msg = showByRating(mapRatings);

      if(msg) {
        printf("No se ha encontrado algún juego con tal valoración. Pruebe otro valor.");
      } else {
        printf("**************************************\n");
        printf("* ¡Se han mostrado todos los juegos! *\n");
        printf("**************************************\n");  
      }
  		break;
  	case 5:
  		msg = showByDate(mapDates);

      if(msg) {
        printf("No se ha encontrado algun juego con tal fecha. Pruebe otra.");
      } else {
        printf("**************************************\n");
        printf("* ¡Se han mostrado todos los juegos! *\n");
        printf("**************************************\n");  
      }
      break;
  	case 6:
  		//msg = searchGame(mapGames);
      msg = 0;

      if(msg) {
        printf("No se ha encontrado algun juego con tal nombre. Pruebe otro.");
      } else {
        printf("**************************************\n");
        printf("* ¡Se han mostrado todos los juegos! *\n");
        printf("**************************************\n");  
      }
  		break;
  	case 7:
      msg = addFavourite(mapGames);

      if(msg) {
        printf("Fallo al añadir: El juego ya había sido marcado.\n");
      } else {
        printf("**********************\n");
  	    printf("* ¡Favorito añadido! *\n");
  	    printf("**********************\n");
      }
  		break;
  	case 8:
  		msg = showFavourites(mapGames);

      if(msg) {
        printf("Fallo en la búsqueda: No se han encontrado favoritos.\n");
      } else {
        printf("********************************************\n");
  	    printf("* ¡Todas los favoritos han sido mostrados! *\n");
  	    printf("********************************************\n");
      }
  		break;
  	case 9:
  		msg = exportAll(mapGames);

      if(msg) {
        printf("Archivo no encontrado. ");
        exit(EXIT_FAILURE);
      } else {
        printf("***********************\n");
        printf("* ¡Archivo exportado! *\n");
        printf("***********************\n");
      }
  		break;
  	default:
  		printf("**************************************\n");
  		printf("* ¡No existe tal opcion, elija otra! *\n");
  		printf("**************************************\n");
  		break;
	}
  printf("\n");
}