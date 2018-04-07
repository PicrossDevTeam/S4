/**
 * \file Case.c
 * \brief Représentation des cases.
 * \author MAROUF Taous, correction par KAJAK Rémi
 * \version 1.0
 * \date 7 avril 2018
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Case.h"

/**
 * \fn init_case(void)
 * \brief Fonction d'initialisation d'une matrice de type "t_couleurs*" (enum).
 *
 * \param taille_max La taille maximale que la matrice devra posséder
 *
 * \return La matrice allouée dynamiquement
 */
t_couleurs* init_case(int taille_max) {
	t_couleurs* mat = malloc(taille_max * taille_max * sizeof(t_couleurs));
	int i, j;

	for(i = 0; i< taille_max; i++) {
	
		for(j = 0; j< taille_max; j++) {
		
			mat[taille_max*i+j] = Blanche;
			
		}
	}
	return mat;
}
/*********************************************************************************************/
/**
 * \fn verif_matrice(t_couleurs* mat)
 * \brief Fonction qui affiche les cases.
 *
 * \param mat La matrice représentant la grille
 * \param taille_max La taille de la matrice utilisée
 *
 * \return Ne retourne aucune valeur
 */
void verif_matrice(t_couleurs *mat, int taille_max) {
	int i,j;

	for(i=0 ; i< taille_max ; i++){
	
		for(j=0 ; j< taille_max ; j++){
		
			printf("|%d|", mat[taille_max*i+j]);
						
		}
		printf("\n");
	}
}
/*********************************************************************************************/
/**
 * \fn changerEtat(t_couleurs* mat, int x, int y)
 * \brief Fonction qui permet de changer l'état de la case.
 *
 * \param mat La matrice qui représente la grille
 * \param taille La taille de la matrice renseignée
 * \param x Une coordonnée renseignant l'abscisse d'une matrice
 * \param y Une coordonnée renseignant l'ordonnée d'une matrice
 *
 * \return Ne retourne aucune valeur
 */
void changerEtat(t_couleurs *mat, int taille, int x, int y) {
	if(mat[taille*x+y] == Blanche)
		mat[taille*x+y] = Noire;
	else if(mat[taille*x+y] == Noire)
		mat[taille*x+y] = Croix;
	else
		mat[taille*x+y] = Blanche;
}

/*********************************************************************************************/
/**
 * \fn saisir_coord(t_couleurs *mat, int taille)
 * \brief Fonction qui permet à l'utilisateur d'entrer des coordonnées
 *
 * \param mat La matrice qui représente la grille
 * \param taille La taille de la matrice
 *
 * \return Retourne l'état de la sélection, si le joueur souhaite soumettre sa grille à la vérification ou pas
 */
int saisir_coord(t_couleurs *mat, int taille) {
	int x = 0, y = 0;

	while((x < 1 || x > taille) || (y < 1 || y > taille)) {
		printf("\nEntrez les coordonnées de l'abscisse et de l'ordonnée de la case à cocher (comprises entre 1 et %i). Pour valider votre grille, entrez -1 aux deux coordonnées : ",taille);
		scanf("%i %i",&x,&y);
		
		if(x != -1 || y != -1) {
			if(x < 1 || x > taille)
				printf("\nERREUR : La coordonnée x n'est pas comprise entre les nombres indiqués !");
			if(y < 1 || y > taille)
				printf("\nERREUR : La coordonnée y n'est pas comprise entre les nombres indiqués !");
		}
		else
			return 1;
 	}
	changerEtat(mat,taille,x-1,y-1);
	return 0;

}


/*********************************************************************************************/
/**
* \fn verifierGrille(t_couleurs *matd, t_couleurs *matf, int taille)
 * \brief Fonction qui vérifie si les cases la grille du joueur est correcte.
 *
 * \param matd La matrice de type enum qui représente la grille qu'il faut avoir
 * \param matf La matrice de type enum qui représente la grille du joueur
 * \param taille La taille de la matrice
 *
 * \return Le nombre de différences relevé entre les deux matrices
 */
int verifierGrille(t_couleurs *matd, t_couleurs *matf, int taille) {
	int i, j, erreurs = 0;

	for(i = 0; i< taille; i++ ) {
		for(j = 0; j< taille; j++) {
			if(matd[taille*i+j] != matf[taille*i+j])
				erreurs++;

		}
	}
 	return erreurs;
}


/*********************************************************************************************/
 
/**
 * \fn int main(void)
 * \brief Entrée du programme.
 *
 */
/*int main() {
	t_couleurs *U = NULL;
	t_difficulte niveau = facile;
	
	int taille = renvoyerTailleMax(niveau);
	
	if(taille == 0) {
		printf("\n\nTaille nulle ! Êtes-vous certain d'avoir renseigné un niveau existant ?\n\n");
		exit(0);
	}
	
	U = init_case(taille);
	verif_matrice(U,taille);
	printf("---------------\n");

	int etat_saisie = saisir_coord(U,taille);
	verif_matrice(U,taille);
	printf("---------------\n");
	
	if(etat_saisie == 0) printf("Pas de vérification entre les matrices jeu et solution.\n\n");
	else printf("Vérification enclenchée !\n\n");

	free(U);
	U = NULL;
	return 0;
} //*/
