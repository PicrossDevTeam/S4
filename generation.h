#include "Case.h"

// Fonctions basiques
int* init_matrice_periph(t_difficulte taille_max);
void lecture_fic_v1(char *nom_fic, int puzzle, int taille);
//void lecture_fic_v1(char *nom_fic, int puzzle, t_couleurs **soluce, int taille);
void afficher_matrice(int *mat, t_difficulte taille, char cle);
void gen_peripheriques(t_couleurs *soluce, int *colonnes, int *lignes, int taille);

// Sous-fonctions du solveur
void lecture_fic_v2(char *nom_fic, int puzzle, int *colonnes, int *lignes, int taille);
int init_compteur_groupes(t_couleurs *soluce, int taille_mat, int rangee, char type_rangee);
void verif_adequation_globale(t_couleurs *soluce, int *colonnes, int *lignes, int *respect_colonnes, int *respect_lignes, int taille);
int adequation_rangee_et_nombres(t_couleurs *soluce, int *periph, int taille, int nb_groupes_defaut, int rangee, char type_rangee);
void init_compteurs_periph(int *periph, int taille);

// Fonction principale du solveur
void gen_solution(t_couleurs *soluce, int *colonnes, int *lignes, int taille);
