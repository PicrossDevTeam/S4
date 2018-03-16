#include <SDL2/SDL.h>
#include <iostream>

void pause() {
    bool terminer(false);
    SDL_Event event;

    while(!terminer) {
        SDL_WaitEvent(&event);
        if(event.window.event == SDL_WINDOWEVENT_CLOSE) terminer = true;
    }
}

int main(int argc, char *argv[]) {
    // Définition de la fenêtre principale et du contexte OpenGL
    SDL_Window* fenetre_jeu(0);
    SDL_GLContext contexteOpenGL(0);

    if(SDL_Init(SDL_INIT_VIDEO) < 0) { // Si le module vidéo de SDL n'est pas fonctionnelle
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();
    }

    // Version d'OpenGL utilisée (3.1)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,1);

    // Double buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);

    // Création de la fenêtre principale
    fenetre_jeu = SDL_CreateWindow("Picross 1.0",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if(fenetre_jeu == 0) {
        std::cout << "Erreur lors de la creation de la fenetre de jeu : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return -1;
    }

    // Création du contexte OpenGL
    contexteOpenGL = SDL_GL_CreateContext(fenetre_jeu);
    if(contexteOpenGL == 0) {
        std::cout << SDL_GetError() << std::endl;
        SDL_DestroyWindow(fenetre_jeu);
        SDL_Quit();

        return -1;
    }

    // On met la fenêtre en pause pour voir ce que la fenêtre de jeu affiche
    pause();

    // On détruit le contexte OpenGL et la fenêtre principale
    SDL_GL_DeleteContext(contexteOpenGL);
    SDL_DestroyWindow(fenetre_jeu);

    // On quitte la bibliothèque SDL
    SDL_Quit();

    return 0;
}
