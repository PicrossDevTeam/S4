/**
* \file generation.h
* \author KAJAK Rémi
* \version 1.0
* \date 08/04/2018
* \brief Fichier contenant les définitions des fonctions de "generation.c". Fait appel à "Case.h" pour obtenir les définitions et les structures de "Case.c".
*/
#include "Case.h"

// Fonctions basiques
int* init_matrice_periph(t_difficulte taille_max);
void afficher_matrice(int *mat, t_difficulte taille, char cle);
void lecture_fic_v1(char *nom_fic, int puzzle, t_couleurs *soluce, t_difficulte taille);
void gen_peripheriques(t_couleurs *soluce, int *colonnes, int *lignes, t_difficulte taille);

// Sous-fonctions du solveur
void lecture_fic_v2(char *nom_fic, int puzzle, int *colonnes, int *lignes, t_difficulte taille);
int* init_compteur_groupes(t_couleurs *soluce, t_difficulte taille_mat, int rangee, char type_rangee);
void verif_adequation_globale(t_couleurs *soluce, int *colonnes, int *lignes, int *respect_colonnes, int *respect_lignes, t_difficulte taille);
int adequation_rangee_et_nombres(t_couleurs *soluce, int *periph, t_difficulte taille, int nb_groupes_defaut, int rangee, char type_rangee);
int* init_compteurs_periph(int *periph, t_difficulte taille);

// Fonction principale du solveur
void gen_solution(t_couleurs *soluce, int *colonnes, int *lignes, t_difficulte taille);
