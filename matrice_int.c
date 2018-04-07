#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int * init_matrice(int dim_mat){
	int * mat = malloc(dim_mat*dim_mat*sizeof(int));
	int i,j;

	for(i=0 ; i < dim_mat ; i++) {
		for(j=0 ; j < dim_mat ; j++) {
			mat[dim_mat*i+j] = 0;
		}
	}
	return mat;
}

void detruire_matrice(int *mat) {
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

void afficher_bas(int *mat_verti, int *mat_prin, int dim_mat){
	int i,j;

	for(i = 0; i < dim_mat; i++) {
		for(j = 0; j < dim_mat; j++) {
			printf("%i ", mat_verti[dim_mat*i+j]);
		}
		printf(" ");
		for(j = 0; j < dim_mat; j++){
			printf("%i ",mat_prin[dim_mat*i+j]);
		}
		printf("\n");
	}
}

void affichage_jeu(int *mat_hori, int *mat_verti, int *mat_prin, int dim_mat){
	afficher_haut(mat_verti, dim_mat);
	afficher_bas(mat_verti, mat_prin, dim_mat);
}