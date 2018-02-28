#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

void pause() {
    int continuer = 1;
    SDL_Event event;

    while(continuer) {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}

int main(int argc, char *argv[]) {
    if(SDL_Init(SDL_INIT_VIDEO) == -1) {
        fprintf(stderr,"Erreur d'initialisation de la SDL Vidéo : %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_CreateWindow("Picross",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,640,480,SDL_WINDOW_OPENGL);
    pause();

    SDL_Quit();

    return 0;
}
