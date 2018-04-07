#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int * init_matrice(int dim_mat){
	int * mat = malloc(dim_mat*dim_mat*sizeof(int));
	int i,j;

	for(i=0 ; i< dim_mat ; i++) {
		for(j=0 ; j< dim_mat ; j++) {
			mat[dim_mat*i+j] = 0;
		}
	}
	return mat;
}

void detruire_matrice(int *mat) {
	free(mat);
}

void afficher_matrice(int *mat, int dim_mat){
	int i,j;

	for(i = 0; i < dim_mat; i++) {
		for(j = 0; j < dim_mat; j++) {
			printf("%i ",mat[dim_mat*i+j]);
		}
		printf("\n");
	}
}
