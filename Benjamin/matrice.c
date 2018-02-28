#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int N = 5;
int T;

void matrice_origine(int mat_ori[T][T]){
	int i,j;

	/* Taille de la grande matrice */
	T = N * 3;

	for(i=0;i<T;i++){
		for(j=0;j<T;j++){
			mat_ori[i][j]=0;
		}
	}
}

void afficher_grd_matrice(int mat_ori[T][T]){
	int i,j;
	
	/* Taille de la grande matrice */
	T = N * 3;

	for(i=0;i<T;i++){
		for(j=0;j<T;j++){
			printf("%i ", mat_ori[i][j]);
		}
		printf("\n");
	}
}

int main(){
	int mat_ori;

	matrice_origine(mat_ori);
	afficher_grd_matrice(mat_ori);
}