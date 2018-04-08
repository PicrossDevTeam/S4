#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int dim_case = 30;

/* Redimensionne la fenêtre en plein écran */
//SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
/* Redimensionne la fenêtre en fenêtrée plein écran */
//SDL_SetWindowFullscreen(window, 0);

/****************************************** Autres fct ******************************************/

int mat[5][5];

void mat_solu(int nb_case, int dim_mat){
	int i;
	int j;

	for(i=0;i<dim_mat;i++){
		for(j=0;j<dim_mat;j++){
			mat[i][j]=1;
		}
	}
}

int return_val(int i, int j){
	return mat[i][j];
}

/************************************************************************************************/

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

void mat_ori(TTF_Font * font, SDL_Renderer * renderer, SDL_Surface * message, int dim_mat, int nb_case, SDL_Rect rect[nb_case]){
	int i;
	int j;
	int n_rect=0;
	char text[128];

	/* Taille police */
	int texW = 0;
	int texH = 0;

	/* Permet de dire si le programme s'est bien ou mal déroulé */
	int statut = EXIT_FAILURE;

	/* Couleur */
	SDL_Color white = {255, 255, 255, 255};
	SDL_Color black = {0, 0, 0, 255};

	for(i=0; n_rect<nb_case; i++){
		for(j=0; j<dim_mat; j++){
			
			rect[n_rect].x = (dim_case*2+(15*dim_mat/2))+i*dim_case;
			rect[n_rect].y = (dim_case*2+(15*dim_mat/2))+j*dim_case;
			rect[n_rect].w = dim_case;
			rect[n_rect].h = dim_case;
			
			sprintf(text, "%i", mat[i][j]);
			message = TTF_RenderText_Blended(font, text, black);
			
			if(message == NULL){
			fprintf(stderr, "Erreur TTF_RenderText_Solid : %s\n", TTF_GetError());
			return;
			}

			SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, message);
			SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
			SDL_Rect dstrect = {rect[n_rect].x+10, rect[n_rect].y+5, texW, texH};
			SDL_RenderCopy(renderer, texture, NULL, &dstrect);

			n_rect++;
		}
	}
}

void peri_h(SDL_Renderer * renderer, int dim_mat, int nb_case, SDL_Rect rect[nb_case]){
	int i;
	int j;
	int n_rect=0;

	if(dim_mat == 3){
		for(i=0; i<dim_mat; i++){
			for(j=0; j<2; j++){
				rect[n_rect].x = (dim_case*2+(15*dim_mat/2))+i*dim_case;
				rect[n_rect].y = j*dim_case;
				rect[n_rect].w = dim_case;
				rect[n_rect].h = dim_case;
				n_rect++;
			}
		}
	}

	for(i=0; i<dim_mat; i++){
		for(j=0; j<dim_mat/2; j++){
			rect[n_rect].x = (dim_case*2+(15*dim_mat/2))+i*dim_case;
			rect[n_rect].y = j*dim_case;
			rect[n_rect].w = dim_case;
			rect[n_rect].h = dim_case;
			n_rect++;
		}
	}
}

void peri_v(SDL_Renderer * renderer, int dim_mat, int nb_case, SDL_Rect rect[nb_case]){
	int i;
	int j;
	int n_rect=0;

	if(dim_mat == 3){
		for(i=0; i<2; i++){
			for(j=0; j<dim_mat; j++){
				rect[n_rect].x = i*dim_case;
				rect[n_rect].y = (dim_case*2+(15*dim_mat/2))+j*dim_case;
				rect[n_rect].w = dim_case;
				rect[n_rect].h = dim_case;
				n_rect++;
			}
		}
	} else
		for(i=0; i<dim_mat/2; i++){
			for(j=0; j<dim_mat; j++){
				rect[n_rect].x = i*dim_case;
				rect[n_rect].y = (dim_case*2+(15*dim_mat/2))+j*dim_case;
				rect[n_rect].w = dim_case;
				rect[n_rect].h = dim_case;
				n_rect++;
			}
		}
}

int main(int argc, char *argv[]){
	int nb_case;
	int dim_mat;

	printf("Entrez la dimension d'une matrice carée (entre 3 et 5 car la dimension des niveaux sera comprise entre ces valeurs): ");
	scanf("%i", &dim_mat);

	nb_case=dim_mat*dim_mat;

	/* Création d'une matrice solution */
	mat_solu(nb_case, dim_mat);

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
	SDL_Rect rect[nb_case];

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

	if(dim_mat == 6){
		if(0 != SDL_CreateWindowAndRenderer(285, 285, SDL_WINDOW_SHOWN, &window, &renderer)){
			fprintf(stderr, "Erreur SDL_CreateWindowAndRenderer : %s\n", SDL_GetError());
			goto Quit;
		}
	}

	if(dim_mat == 5){
		if(0 != SDL_CreateWindowAndRenderer(247, 247, SDL_WINDOW_SHOWN, &window, &renderer)){
			fprintf(stderr, "Erreur SDL_CreateWindowAndRenderer : %s\n", SDL_GetError());
			goto Quit;
		}
	}

	if(dim_mat == 4){
		if(0 != SDL_CreateWindowAndRenderer(210, 210, SDL_WINDOW_SHOWN, &window, &renderer)){
			fprintf(stderr, "Erreur SDL_CreateWindowAndRenderer : %s\n", SDL_GetError());
			goto Quit;
		}
	}

	if(dim_mat == 3){
		if(0 != SDL_CreateWindowAndRenderer(172, 172, SDL_WINDOW_SHOWN, &window, &renderer)){
			fprintf(stderr, "Erreur SDL_CreateWindowAndRenderer : %s\n", SDL_GetError());
			goto Quit;
		}
	}

	/* Change le fond en blanc */
	if(0 != set_WindowColor(renderer, white))
		goto Quit;

	/* Ecriture dans la fenêtre */

	font = TTF_OpenFont("arial.ttf", 18);

	if(font == NULL){
		fprintf(stderr, "Erreur TTF_OpenFont : %s\n", TTF_GetError());
		goto Quit;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	mat_ori(font, renderer, message, dim_mat, nb_case, rect);

	/* Dessine tous les rectangles d'un coup */
	SDL_RenderDrawRects(renderer, rect, nb_case);

	peri_h(renderer, dim_mat, nb_case, rect);
	SDL_RenderDrawRects(renderer, rect, nb_case);
	peri_v(renderer, dim_mat, nb_case, rect);
	SDL_RenderDrawRects(renderer, rect, nb_case);

	/* Rafraichit l'affichage de la fenêtre */
	SDL_RenderPresent(renderer);

	SDL_Delay(5000);

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
	//if(NULL != texture)
		//SDL_DestroyTexture(texture);
	if(NULL != message)
		SDL_FreeSurface(message);

	/* Fermeture de TTF pour éviter les fuites de mémoire */
	TTF_Quit();

	/* Fermeture de l'accès aux fonctions SDL pour éviter les fuites de mémoire */
	SDL_Quit();

	return statut;
}