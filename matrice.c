#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum couleurs {Blanche, Noire, Croix} t_couleurs;
typedef enum difficulte {facile, normal, difficile, expert} t_difficulte;

t_couleurs * init_matrice_prin(int dim_mat){
	t_couleurs * mat = malloc(dim_mat*dim_mat*sizeof(t_couleurs));
	int i,j;

	for(i=0 ; i < dim_mat ; i++) {
		for(j=0 ; j < dim_mat ; j++) {
			mat[dim_mat*i+j] = Blanche;
		}
	}
	return mat;
}

int * init_matrice_peri(int dim_mat){
	int * mat = malloc(dim_mat*dim_mat*sizeof(int));
	int i,j;

	for(i=0 ; i < dim_mat ; i++) {
		for(j=0 ; j < dim_mat ; j++) {
			mat[dim_mat*i+j] = 0;
		}
	}
	return mat;
}

void detruire_matrice_peri(int *mat) {
	free(mat);
}

void detruire_matrice_prin(t_couleurs *mat){
	free(mat);
}

void afficher_haut(int *mat_hori, int dim_mat){
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

void afficher_bas(int *mat_verti, t_couleurs *mat_prin, int dim_mat){
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

void affichage_jeu(int *mat_hori, int *mat_verti, t_couleurs *mat_prin, int dim_mat){
	afficher_haut(mat_verti, dim_mat);
	afficher_bas(mat_verti, mat_prin, dim_mat);
}