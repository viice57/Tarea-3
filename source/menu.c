#include <stdio.h>
#include <stdlib.h>

#include "../include/games.h"
#include "../include/menu.h"

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"

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
      printf(GREEN "\n*********************\n");
  		printf("* Fin del programa. *\n");
  		printf("*********************\n" RESET);
      break;
		case 1:
      msg = importGames(mapGames, mapPrices, mapRatings, mapDates);

      if(msg) {
        printf(RED "\nEl archivo no fue encontrado o ya se había importado. " RESET);
      } else {
        printf(GREEN "\n***********************\n");
        printf("* ¡Archivo importado! *\n");
        printf("***********************\n" RESET);
      }
  		break;
  	case 2:
      msg = addGame(mapGames, mapPrices, mapRatings, mapDates);

      if(msg) {
        printf(RED "\nFallo al añadir: Ya hay un juego con ese nombre." RESET);
      } else {
        printf(GREEN "\n********************\n");
        printf("* ¡Juego agregado! *\n");
        printf("********************\n" RESET);  
      }
  		break;
  	case 3:
  		msg = showByPrice(mapPrices);

      if(msg) {
        printf(RED "\nNo se han encontrado juegos." RESET);
      } else {
        printf(GREEN "\n**************************************\n");
        printf("* ¡Se han mostrado todos los juegos! *\n");
        printf("**************************************\n" RESET);  
      }
  		break;
  	case 4:
  		msg = showByRating(mapRatings);

      if(msg) {
        printf(RED "\nNo se ha encontrado algún juego mayor a tal valoración. Pruebe otro valor que sea menor." RESET);
      } else {
        printf(GREEN "\n**************************************\n");
        printf("* ¡Se han mostrado todos los juegos! *\n");
        printf("**************************************\n" RESET);  
      }
  		break;
  	case 5:
  		msg = showByDate(mapDates);

      if(msg) {
        printf(RED "\nNo se han encontrado juegos." RESET);
      } else {
        printf(GREEN "\n**************************************\n");
        printf("* ¡Se han mostrado todos los juegos! *\n");
        printf("**************************************\n" RESET);  
      }
      break;
  	case 6:
  		msg = searchGame(mapGames, mapPrices, mapRatings, mapDates);

      if(msg) {
        printf(RED "\nNo se ha encontrado algún juego con ese nombre o la opción es inválida." RESET);
      } else {
        printf(GREEN "\n********************************\n");
        printf("* ¡Se ha modificado con éxito! *\n");
        printf("********************************\n" RESET);  
      }
  		break;
  	case 7:
      msg = addFavourite(mapGames);

      if(msg) {
        printf(RED "\nFallo al añadir: El juego ya había sido marcado o no existe.\n" RESET);
      } else {
        printf(GREEN "\n**********************\n");
  	    printf("* ¡Favorito añadido! *\n");
  	    printf("**********************\n" RESET);
      }
  		break;
  	case 8:
  		msg = showFavourites(mapGames);

      if(msg) {
        printf(RED "\nFallo en la búsqueda: No se han encontrado favoritos.\n" RESET);
      } else {
        printf(GREEN "\n********************************************\n");
  	    printf("* ¡Todas los favoritos han sido mostrados! *\n");
  	    printf("********************************************\n" RESET);
      }
  		break;
  	case 9:
  		msg = exportAll(mapGames);

      if(msg) {
        printf(RED "\nArchivo no encontrado. " RESET);
      } else {
        printf(GREEN "\n***********************\n");
        printf("* ¡Archivo exportado! *\n");
        printf("***********************\n" RESET);
      }
  		break;
  	default:
  		printf(RED "\n**************************************\n");
  		printf("* ¡No existe tal opcion, elija otra! *\n");
  		printf("**************************************\n" RESET);
  		break;
	}
  printf("\n");
}