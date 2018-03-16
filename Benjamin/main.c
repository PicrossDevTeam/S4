#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "f.h"

/* Variables globales */

/* Taille de base de la matrice */
const int N = 5;

/* Taille après le choix de la difficulté */
int T;

/* Taille des matrices périphérique pour éviter un parcours trop long */
int P;

/* Programme */

int main(){
	/* Taille matrice globale */
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

/* 
int main(){
	int matrice_globale[tlle_mat_glo_l][tlle_mat_glo_h];

	if(validation(matrice_globale) == 1)
		printf("Vous avez réussi !");
	else
		printf("Vous avez échoué !")
}
*/