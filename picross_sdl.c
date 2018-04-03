#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int N = 25;
int dim_case = 50;

/* Redimensionne la fenêtre en plein écran */
//SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
/* Redimensionne la fenêtre en fenêtrée plein écran */
//SDL_SetWindowFullscreen(window, 0);

int set_WindowColor(SDL_Renderer * renderer, SDL_Color color){
	/* Choix de la couleur de travail pour le render */
	if(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) < 0){
		fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s\n", SDL_GetError());
		return -1;
	}

	/* Charge la couleur dans le render */
	if(0 != SDL_RenderClear(renderer)){
		fprintf(stderr, "Erreur SDL_RenderClear : %s\n", SDL_GetError());
		return -1;
	}

	return 0;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination ) { 
	SDL_Rect offset; 

	offset.x = x; 
	offset.y = y;

	//On blitte la surface 
	SDL_BlitSurface( source, NULL, destination, &offset ); 
}

void matrice_5(SDL_Renderer * renderer, SDL_Rect rect[N]){
	int i;
	int j;
	int n_rect=0;

	for(i=0; n_rect<N; i++){
		for(j=0; j<5; j++){
			rect[n_rect].x = 110+i*dim_case;
			rect[n_rect].y = 110+j*dim_case;
			rect[n_rect].w = dim_case;
			rect[n_rect].h = dim_case;
			n_rect++;
		}
	}
}

void peri_h(SDL_Renderer * renderer, SDL_Rect rect[N]){
	int i;
	int j;
	int n_rect=0;

	for(i=0; i<sqrt(25); i++){
		for(j=0; j<5/2; j++){
			rect[n_rect].x = 110+i*dim_case;
			rect[n_rect].y = j*dim_case;
			rect[n_rect].w = dim_case;
			rect[n_rect].h = dim_case;
			n_rect++;
		}
	}
}

void peri_v(SDL_Renderer * renderer, SDL_Rect rect[N]){
	int i;
	int j;
	int n_rect=0;

	for(i=0; i<5/2; i++){
		for(j=0; j<sqrt(25); j++){
			rect[n_rect].x = i*dim_case;
			rect[n_rect].y = 110+j*dim_case;
			rect[n_rect].w = dim_case;
			rect[n_rect].h = dim_case;
			n_rect++;
		}
	}
}

int main(int argc, char *argv[])
{

	/* Initialisation de la fenêtre et du render SDL */ 
	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL;

	/* Permet de dire si le programme s'est bien ou mal déroulé */
	int statut = EXIT_FAILURE;

	/* Les surfaces */
	SDL_Surface * message = NULL;

	/* La structure d'évènement */
	SDL_Event event;

	/* Le fond que l'on va utiliser */
	TTF_Font * font;

	/* Les rectangles pour l'affichage de la grille */
	SDL_Rect rect[N];

	/* Prendre en compte une position */
	int texW = 0;
	int texH = 0;

	/* Couleur */
	SDL_Color white = {255, 255, 255, 255};
	SDL_Color black = {0, 0, 0, 255};

	/* Initialisation des fonctions SDL (temps, vidéo, audio, touches) */
	if(0 != SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER)){
		/* S'il y a une erreur avec l'initialisation, l'afficher et aller à la fin du programme (label "Quit") pour quitter (fct goto) */
		fprintf(stderr, "Erreur SDL_Init : %s\n", SDL_GetError());
    	goto Quit;
	}

	if(0 != TTF_Init()){
		fprintf(stderr, "Erreur TTF_Init : %s\n", TTF_GetError());
    	goto Quit;
	}

	/* Création de la fenêtre SDL redimensionnable et du render */
	if(0 != SDL_CreateWindowAndRenderer(360, 360, SDL_WINDOW_SHOWN, &window, &renderer)){
		fprintf(stderr, "Erreur SDL_CreateWindowAndRenderer : %s\n", SDL_GetError());
		goto Quit;
	}

	/* Change le fond en blanc */
	if(0 != set_WindowColor(renderer, white))
		goto Quit;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	matrice_5(renderer, rect);

	/* Dessine tous les rectangles d'un coup */
	SDL_RenderDrawRects(renderer, rect, N);

	peri_h(renderer, rect);
	SDL_RenderDrawRects(renderer, rect, N);
	peri_v(renderer, rect);
	SDL_RenderDrawRects(renderer, rect, N);


 	/* Ecriture dans la fenêtre */

	font = TTF_OpenFont("arial.ttf", 12);

	if(font == NULL){
		fprintf(stderr, "Erreur TTF_OpenFont : %s\n", TTF_GetError());
		goto Quit;
	}

	message = TTF_RenderText_Blended(font, "Test", black);

	if(message == NULL){
		fprintf(stderr, "Erreur TTF_RenderText_Solid : %s\n", TTF_GetError());
		goto Quit;
	}

	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, message);
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = {0, 0, texW, texH};
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);

	/* Rafraichit l'affichage de la fenêtre */
	SDL_RenderPresent(renderer);

	SDL_Delay(4000);

	/* Les initialisitions se sont bien déroulées donc le programme se déroulera bien */
	statut = EXIT_SUCCESS;

	/* Permet à la fenêtre de rester ouverte */
	SDL_Delay(0);

Quit:
	/* Destruction de la fenêtre et du render pour éviter les fuites de mémoire */
	if(NULL != renderer)
		SDL_DestroyRenderer(renderer);
	if(NULL != window)
		SDL_DestroyWindow(window);

	if(NULL != font)
		TTF_CloseFont(font);
	if(NULL != texture)
		SDL_DestroyTexture(texture);
	if(NULL != message)
		SDL_FreeSurface(message);

	/* Fermeture de TTF pour éviter les fuites de mémoire */
	TTF_Quit();

	/* Fermeture de l'accès aux fonctions SDL pour éviter les fuites de mémoire */
	SDL_Quit();

	return statut;
}