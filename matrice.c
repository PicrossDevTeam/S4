/**
* \file matrice.c
* \author NOUVELIERE Benjamin
* \version 1.0
* \date 08/04/2018
* \brief Fichier contenant la création, la destruction et l'affichage des matrices.
*/

#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"

/**
 * \fn init_matrice_prin(t_difficulte dim_mat)
 * \brief Fonction d'initialisation d'une matrice de type "t_couleurs*" (enum).
 *
 * \param dim_mat La taille maximale que la matrice devra posséder.
 *
 * \return La matrice allouée dynamiquement.
 */

t_couleurs * init_matrice_prin(t_difficulte dim_mat){
	t_couleurs * mat = malloc(dim_mat*dim_mat*sizeof(t_couleurs));
	int i,j;

	for(i=0 ; i < dim_mat ; i++) {
		for(j=0 ; j < dim_mat ; j++) {
			mat[dim_mat*i+j] = Blanche;
		}
	}
	return mat;
}

/**
 * \fn init_matrice_peri(t_difficulte dim_mat)
 * \brief Fonction d'initialisation d'une matrice de type "int*".
 *
 * \param dim_mat La taille maximale que la matrice devra posséder.
 *
 * \return La matrice allouée dynamiquement.
 */

int * init_matrice_peri(t_difficulte dim_mat){
	int * mat = malloc(dim_mat*dim_mat*sizeof(int));
	int i,j;

	for(i=0 ; i < dim_mat ; i++) {
		for(j=0 ; j < dim_mat ; j++) {
			mat[dim_mat*i+j] = Blanche;
		}
	}
	return mat;
}

/**
 * \fn detruire_matrice_peri(int * mat)
 * \brief Fonction de destruction d'une matrice de type "int*".
 *
 * \param mat La matrice à détruire.
 */

void detruire_matrice_peri(int * mat) {
	free(mat);
}

/**
 * \fn detruire_matrice_prin(t_couleurs * mat)
 * \brief Fonction de destruction d'une matrice de type "t_couleurs*".
 *
 * \param mat La matrice à détruire.
 */

void detruire_matrice_prin(t_couleurs * mat){
	free(mat);
}

/**
 * \fn afficher_haut(int *mat_hori, t_difficulte dim_mat)
 * \brief Fonction d'affichage d'une matrice vide et de la matrice horizontale l'une à côté de l'autre.
 *
 * \param mat_hori La matrice périphérique horizontale.
 *
 * \param dim_mat La taille maximale que la matrice devra posséder.
 */

void afficher_haut(int *mat_hori, t_difficulte dim_mat){
	int i,j;

	for(i = 0; i < dim_mat; i++) {
		for(j = 0; j < dim_mat; j++) {
			printf("  ");
		}
		printf(" ");
		for(j = 0; j < dim_mat; j++){
			if(mat_hori[dim_mat*i+j]!=0)
				printf("%i ",mat_hori[dim_mat*i+j]);
			if(mat_hori[dim_mat*i+j]==0)
				printf("  ");
		}
		printf("\n");
	}
	printf("\n");
}

/**
 * \fn afficher_bas(int *mat_verti, t_couleurs *mat_prin, t_difficulte dim_mat)
 * \brief Fonction d'affichage de la matrice verticale et de la matrice principale l'une à côté de l'autre.
 *
 * \param mat_verti La matrice périphérique verticale.
 *
 * \param mat_prin La matrice principale.
 *
 * \param dim_mat La taille maximale que la matrice devra posséder.
 */

void afficher_bas(int *mat_verti, t_couleurs *mat_prin, t_difficulte dim_mat){
	int i,j,k;
	int espace=dim_mat;

	for(i = 0; i < dim_mat; i++) {
		for(j = 0; j < dim_mat; j++) {
			if(mat_verti[dim_mat*i+j]!=0){
				printf("%i ", mat_verti[dim_mat*i+j]);
				espace--;
			}
			else
				espace++;
		}

		for(k=0; k<espace; k++)
			printf(" ");
		espace=dim_mat;

		printf(" ");
		for(j = 0; j < dim_mat; j++){
			printf("%i ", mat_prin[dim_mat*i+j]);
		}
		printf("\n");
	}
}

/**
 * \fn affichage_jeu(int *mat_hori, int *mat_verti, t_couleurs *mat_prin, t_difficulte dim_mat)
 * \brief Fonction qui rassemble l'affichage des matrices du haut et celles du bas pour afficher le jeu.
 *
 * \param mat_hori La matrice périphérique horizontale.
 *
 * \param mat_verti La matrice périphérique verticale.
 *
 * \param mat_prin La matrice principale.
 *
 * \param dim_mat La taille maximale que la matrice devra posséder.
 */

void affichage_jeu(int *mat_hori, int *mat_verti, t_couleurs *mat_prin, t_difficulte dim_mat){
	afficher_haut(mat_hori, dim_mat);
	afficher_bas(mat_verti, mat_prin, dim_mat);
}