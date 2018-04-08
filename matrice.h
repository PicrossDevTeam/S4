/**
* \file matrice.h
* \author NOUVELIERE Benjamin
* \version 1.0
* \date 08/04/2018
* \brief Fichier contenant les définitions de "matrice.c".
*/

typedef enum couleurs {Blanche, Noire, Croix} t_couleurs;
typedef enum difficulte {facile=3, normal=4, difficile=5} t_diff

iculte;

t_couleurs * init_matrice_prin(t_difficulte);
int * init_matrice_peri(t_difficulte);
void detruire_matrice_peri(int *);
void detruire_matrice_prin(t_couleurs *);
void afficher_haut(int *, t_difficulte);
void afficher_bas(int *, t_couleurs *, t_difficulte);
void affichage_jeu(int *, int *, t_couleurs *, t_difficulte);