#ifndef __GENERATION_H__
#define __GENERATION_H__

/**
* \def N
* \brief Nombre de lignes de la matrice test
*/
#define N 5

// Fonctions basiques
void init_matrice(int mat[N][N]);
void afficher_matrice(int mat[N][N], int taille_max, char cle);
int lecture_fic(char *nom_fic, int niveau, int C[N][N], int L[N][N], int solveur);
void gen_peripheriques(int S[N][N], int C[N][N], int L[N][N], int taille_max);

// Sous-fonctions du solveur
int init_compteur_groupes(int S[N][N], int nombres[N], int rangee, char type_rangee);
void verif_adequation_globale(int soluce[N][N], int C[N][N], int L[N][N], int respect_C[N], int respect_L[N]);
int adequation_rangee_et_nombres(int S[N][N], int periph[N][N], int nb_groupes_defaut, int rangee, char type_rangee);
void init_compteurs_periph(int periph_C[N][N], int cpt_C[N], int periph_L[N][N], int cpt_L[N]);

// Fonction principale du solveur
void gen_solution(int S[N][N], int C[N][N], int L[N][N], int largeur);

#endif
