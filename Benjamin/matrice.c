#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Taille de base de la matrice */
const int N = 5;

/* Taille après le choix de la difficulté */
int T;

/* Taille des matrices périphérique pour éviter un parcours trop long */
int P;

void creer_mat_ori(int mat_ori[T][T]){
	int i,j;

	for(i=0;i<T;i++){
		for(j=0;j<T;j++){
			mat_ori[i][j]=0;
		}
	}
}

void creer_peri_haut(int mat_ori[T][T]){
	int i,j;

	for(i=0;i<P;i++){
		for(j=0;j<T;j++){
			mat_ori[i][j]=0;
		}
	}
}

void creer_peri_gauche(int mat_ori[T][T]){
	int i,j;

	for(i=0;i<T;i++){
		for(j=0;j<P;j++){
			mat_ori[i][j]=0;
		}
	}
}

void aff_mat_ori(int mat_ori[T][T]){
	int i,j;

	for(i=0;i<T;i++){
		for(j=0;j<T;j++){
			printf("%i ", mat_ori[i][j]);
		}
		printf("\n");
	}
}

void aff_peri_haut(int mat_ori[T][T]){
	int i,j;

	for(i=0;i<P;i++){
		for(j=0;j<T;j++){
			printf("%i ", mat_ori[i][j]);
		}
		printf("\n");
	}
}

void aff_peri_gauche(int mat_ori[T][T]){
	int i,j;

	for(i=0;i<T;i++){
		for(j=0;j<P;j++){
			printf("%i ", mat_ori[i][j]);
		}
		printf("\n");
	}
}

/*
int main(){
	
	T = N * 5;

	P = N * 2;

	int mat_ori[T][T];
	int mat_peri_haut[P][T];
	int mat_peri_gauche[T][P];

	creer_mat_ori(mat_ori);
	aff_mat_ori(mat_ori);

	printf("\n");
	creer_peri_haut(mat_peri_haut);
	aff_peri_haut(mat_peri_haut);

	printf("\n");
	creer_peri_gauche(mat_peri_gauche);
	aff_peri_gauche(mat_peri_gauche);
}

*/