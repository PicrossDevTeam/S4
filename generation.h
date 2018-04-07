#include <stdbool.h>

// Fonctions basiques
int* init_matrice(int taille_max);
void afficher_matrice(int *mat, int niveau, int taille, char cle);
int lecture_fic(char *nom_fic, int puzzle, int *colonnes, int *lignes, int taille, _Bool solveur);
void gen_peripheriques(t_couleurs *soluce, int *colonnes, int *lignes, int taille);

// Sous-fonctions du solveur
int init_compteur_groupes(t_couleurs *soluce, int taille_mat, int rangee, char type_rangee);
void verif_adequation_globale(t_couleurs *soluce, int *colonnes, int *lignes, int *respect_C, int *respect_L, int taille);
int adequation_rangee_et_nombres(t_couleurs *soluce, int *periph, int taille, int nb_groupes_defaut, int rangee, char type_rangee);
void init_compteurs_periph(int *periph, int taille);

// Fonction principale du solveur
void gen_solution(t_couleurs *soluce, int *colonnes, int *lignes, int taille);
