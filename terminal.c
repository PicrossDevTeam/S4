/**
* \file terminal.c
* \author KAJAK Rémi
* \version 1.0
* \date 03/04/2018
* \brief Fichier permettant la génération d'une partie de Picross à partir d'un terminal de commande.
*/
#include <stdio.h>
#include <stdlib.h>

typedef enum couleurs {Blanche, Noire, Croix} t_couleurs;
typedef enum difficulte {facile=3, normal=5, difficile=7, expert=10} t_difficulte;

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

int * init_matrice_peri(t_difficulte dim_mat){
	int * mat = malloc(dim_mat*dim_mat*sizeof(int));
	int i,j;

	for(i=0 ; i < dim_mat ; i++) {
		for(j=0 ; j < dim_mat ; j++) {
			mat[dim_mat*i+j] = 0;
		}
	}
	return mat;
}

void detruire_matrice_peri(void * mat) {
	free(mat);
}

void detruire_matrice_prin(void * mat){
	free(mat);
}

void afficher_haut(int *mat_hori, t_difficulte dim_mat){
	int i,j;

	for(i = 0; i < dim_mat; i++) {
		for(j = 0; j < dim_mat; j++) {
			printf("  ");
		}
		printf(" ");
		for(j = 0; j < dim_mat; j++){
			printf("%i ",mat_hori[dim_mat*i+j]);
		}
		printf("\n");
	}
	printf("\n");
}

void afficher_bas(int *mat_verti, t_couleurs *mat_prin, t_difficulte dim_mat){
	int i,j;

	for(i = 0; i < dim_mat; i++) {
		for(j = 0; j < dim_mat; j++) {
			printf("%i ", mat_verti[dim_mat*i+j]);
		}
		printf(" ");
		for(j = 0; j < dim_mat; j++){
			printf("%i ", mat_prin[dim_mat*i+j]);
		}
		printf("\n");
	}
}

void affichage_jeu(int *mat_hori, int *mat_verti, t_couleurs *mat_prin, t_difficulte dim_mat){
	afficher_haut(mat_verti, dim_mat);
	afficher_bas(mat_verti, mat_prin, dim_mat);
}

/* -------------------------------------- */

void changerEtat(t_couleurs *mat_prin, t_difficulte dim_mat, int x, int y) {
	if(mat_prin[dim_mat*x+y] == Blanche)
		mat_prin[dim_mat*x+y] = Noire;
	else if(mat_prin[dim_mat*x+y] == Noire)
		mat_prin[dim_mat*x+y] = Croix;
	else
		mat_prin[dim_mat*x+y] = Blanche;
}

int saisir_coord(t_couleurs *mat_prin, t_difficulte dim_mat) {
	int x = 0, y = 0;

	while((x < 1 || x > dim_mat) || (y < 1 || y > dim_mat)) {
		printf("\nEntrez les coordonnées de l'abscisse et de l'ordonnée de la case à cocher (comprises entre 1 et %i). Pour valider votre grille, entrez -1 aux deux coordonnées : ",dim_mat);
		scanf("%i %i",&y,&x);
		
		if(x != -1 || y != -1) {
			if(x < 1 || x > dim_mat)
				printf("\nERREUR : La coordonnée x n'est pas comprise entre les nombres indiqués !");
			if(y < 1 || y > dim_mat)
				printf("\nERREUR : La coordonnée y n'est pas comprise entre les nombres indiqués !\n");
		}
		else
			return 1;
 	}
	changerEtat(mat_prin,dim_mat,x-1,y-1);
	return 0;
}

/* -------------------------------------- */

int main(void){
	t_difficulte dim_mat=difficile;
	t_couleurs * mat_prin = init_matrice_prin(dim_mat);
	int quit;

	int * mat_verti =  init_matrice_peri(dim_mat);
	int * mat_hori =  init_matrice_peri(dim_mat);
	
	do{
		affichage_jeu(mat_hori, mat_verti, mat_prin, dim_mat);
		quit=saisir_coord(mat_prin, dim_mat);
	} while(quit!=1);

	detruire_matrice_prin(mat_prin);
	detruire_matrice_peri(mat_verti);
	detruire_matrice_peri(mat_hori);

	return 0;
}