#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Taille matrice périphérique fixée pour éviter un parcours trop long */
const int periph=2;

/* Taille matrice globale en hauteur */
int tlle_mat_glo_h;

/* Taille matrice globale en longueur */
int tlle_mat_glo_l;

/* Taille des matrices qui composent la matrice globale */
int tlle_mat;

/* Valeur pour se déplacer dans la matrice utilisateur après vérification */
int avance;

/* Indices de parcours de la matrice globale de solution par l'utilisateur */
int i,j;

double matrice_peripherique_dessus[tlle_mat_glo_l][periph];
double matrice_peripherique_gauche[periph][tlle_mat_glo_h];

/* La fonction de vérification de la matrice périphérique du haut change également la valeur de avance qui est utile pour la suite */
int verif_peri_h(double matrice_globale[tlle_mat_glo_l][tlle_mat_glo_h]){
	int k;
	int compt;

	/* Parcours de la matrice périphérique située au dessus (parcours uniquement en colonne) */
	for(k=0; k<periph; k++){

		/* Vérification de la matrice globale de solution avec la matrice périphériques du dessus */
		if(matrice_peripherique_dessus[k][j]!=0){

			/* On va garder en mémoire la valeur de la matrice périphérique pour mettre à jour l'avancée de la matrice d'utilisateur après */
			avance=matrice_peripherique_dessus[k][j];

			/* On va regarder si les n cases (nombre donné par la matrice périphérique) sont cochées */
			for(compt=matrice_peripherique_dessus[k][j]-1; compt>=0; compt--){

				/* Si ce n'est pas coché la réponse utilisateur est fausse */
				if(matrice_globale[i][j+compt]!=1)
					return 0;
			}

			/* La case de la matrice utilisateur d'après doit être vide ou doit correspondre à une sortie de matrice */
			if(matrice_globale[i][j+avance]==1 || j+avance>tlle_mat_glo_h)
				return 0;
		}
	}
	matrice_peripherique_dessus[k][j]==0;
	return 1;
}

int verif_peri_g(double matrice_globale[tlle_mat_glo_l][tlle_mat_glo_h]){
	int l;
	int compt;

	/* Parcours de la matrice périphérique située au dessus (parcours uniquement en ligne) */
	for(l=0; l<periph; l++){

		/* Vérification de la matrice globale de solution avec la matrice périphériques du dessus */
		if(matrice_peripherique_gauche[i][l]!=0){

			/* On va regarder si les n cases (nombre donné par la matrice périphérique) sont cochées */
			for(compt=matrice_peripherique_gauche[i][l]-1; compt>=0; compt--){

				/* Si ce n'est pas coché la réponse utilisateur est fausse */
				if(matrice_globale[i+compt][j]!=1)
					return 0;
			}

			/* La case de la matrice utilisateur d'après doit être vide ou doit correspondre à une sortie de matrice */
			if(matrice_globale[i][j+avance]==1 || j+avance>tlle_mat_glo_h)
				return 0;
		}
	}
	matrice_peripherique_gauche[i][l]==0;
	return 1;
}

int validation(double matrice_globale[tlle_mat_glo_l][tlle_mat_glo_h]){

	int verif_h;
	int verif_g;
	

	/* Parcours de la matrice de l'utilisateur */
	for(i=0; i<tlle_mat_glo_l; i++){
		for(j=0, j<tlle_mat_glo_h; j++){

			/* Si une case est cochée */
			if(matrice_globale[i][j]==1){

				/* On vérifie par rapport aux matrices périphériques */

				verif_h=verif_peri_h(matrice_globale, matrice_peripherique_dessus, i, j);
				if(verif_h==0)
					return 0;
				verif_g=verif_peri_g(matrice_globale, matrice_peripherique_gauche, i, j);
				if(verif_g==0)
					return 0;

				/* Utilisation de la variable avance pour continuer le parcours de la matrice remplie par l'utilisateur */
				matrice_globale[i][j]=matrice_globale[i][j+avance];
			}
		}
	}
	return 1;
}

int main(){
	double matrice_globale[tlle_mat_glo_l][tlle_mat_glo_h];

	if(validation(matrice_globale) == 1)
		printf("Vous avez réussi !");
	else
		printf("Vous avez échoué !")
}