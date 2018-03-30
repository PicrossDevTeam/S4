#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

/* Redimensionne la fenêtre en plein écran */
SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
/* Redimensionne la fenêtre en fenêtrée plein écran */
SDL_SetWindowFullscreen(window, 0);

int main(int argc, char *argv[])
{
	/* Initialisation de la fenêtre SDL */ 
	SDL_Window * window = NULL;

	/* Permet de dire si le programme s'est bien ou mal déroulé */
	int statut = EXIT_FAILURE;

	/* Initialisation des fonctions SDL (temps, vidéo, audio, touches) */
	if(0 != SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER)){
		/* S'il y a une erreur avec l'initialisation, l'afficher et aller à la fin du programme (label "Quit") pour quitter (fct goto) */
		fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
    	goto Quit;
	}

	/* Création de la fenêtre SDL redimensionnable */
	window = SDL_CreateWindow("Picross", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_RESIZABLE);
	if(NULL == window){
		fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        goto Quit;
	}

	/* Les initialisitions se sont bien déroulées donc le programme se déroulera bien */
	statut = EXIT_SUCCESS;

	/* Permet à la fenêtre de rester ouverte */
	SDL_Delay(9000);

	/* Destruction de la fenêtre pour éviter les fuites de mémoire */
	SDL_DestroyWindow(window);

Quit:
	/* Fermeture de l'accès aux fonctions SDL pour éviter les fuites de mémoire */
	SDL_Quit();
	return statut;
}