/**
* \file Case.h
* \author MAROUF Taous, corrigé par KAJAK Rémi
* \version 1.0
* \date 08/04/2018
* \brief Contient les définitions des structures enum et des fonctions de "Case.c".
*/

/**
 * \enum t_couleurs
 * \brief Énumère l'état des cases d'une matrice.
 *
 */
typedef enum couleurs {Blanche, Noire, Croix} t_couleurs;

/**
 * \enum t_difficulte
 * \brief Énumère la taille des matrices en fonction d'une difficulté.
 *
 */
typedef enum difficulte {facile = 3, normal, difficile, expert = 10} t_difficulte;

t_couleurs* init_case(t_difficulte taille_max);
void verif_matrice(t_couleurs *mat, t_difficulte taille_max);
void changerEtat(t_couleurs *mat, t_difficulte taille, int x, int y);
int saisir_coord(t_couleurs *mat, t_difficulte taille);
int verifierGrille(t_couleurs *matSoluce, t_couleurs *matJoueur, t_difficulte taille);
