/**
* \file generatin.c
* \author KAJAK Rémi
* \version 1.0
* \date 19/03/2018
* \brief Fichier ayant servi à l'élaboration de la fonction de lecture du fichier texte qui contient les nombres générateurs de la matrice principale.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* \def N
* \brief Nombre de lignes de la matrice test
*/
#define N 10

/**
* \fn lecture_fic(char *nom, int niveau)
* \brief Lit un fichier avec un format spécifique et renseigne les nombres contenus dans les matrices adjacentes
* \param nom Nom du fichier texte à analyser
* \param niveau Nombre du puzzle à trouver dans le fichier
* \return Ne retourne aucun résultat
*/
void lecture_fic(char *nom_fic, int niveau, int H[N][N], int V[N][N]) { /* Lecture du fichier contenant les puzzles prédéfinis */
	FILE * fic_gen;
	char cle[4] = "PHVF", carac;
	int ligne, colonne, num_puz, nb_case, i;

	fic_gen = fopen(nom_fic,"r");
	fscanf(fic_gen,"%c %i",&carac,&num_puz);

	while(!feof(fic_gen)) { // Tant que la fin du fichier n'a pas été atteinte
		if(carac == cle[0] && num_puz == niveau) { // Si on trouve le bon niveau de puzzle
			printf("%c %i\n",carac,num_puz);
			for(i = 1; i <= 2; i++) { // Lecture successive des clés
				ligne = 0;
				colonne = 0;

				while(carac != cle[i]) { // Tant que l'on n'a pas trouvé la clé de départ
					fscanf(fic_gen,"%c",&carac);
				}
				printf("%c",carac);
				fscanf(fic_gen,"%c",&carac);

				while(carac != cle[i+1]) { // Tant que l'on n'a pas trouvé la clé de fin
					printf("%c",carac);
					if(carac == ' ' || carac == '\n') {
						fscanf(fic_gen,"%i",&nb_case);
						printf("%i",nb_case);
						if(cle[i] == 'H') H[colonne][ligne] = nb_case;
						else if(cle[i] == 'V') V[ligne][colonne] = nb_case;
						colonne++;
					}
					else if(carac == '+') {
						ligne++;
						printf(" %i",ligne-1);
						printf(" %i",colonne);
						colonne = 0;
					}
					fscanf(fic_gen,"%c",&carac);
				}
				printf("\n\n");
			}
		}
		fscanf(fic_gen,"%c %i",&carac,&num_puz);
	}
	fclose(fic_gen);
	printf("Sortie du fichier\n");
}

void init_matrices(int H[N][N], int V[N][N]) {
	int i, j;

	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			H[i][j] = 0;
			V[i][j] = 0;
		}
	}
}

void afficher_matrice(int mat[N][N], char cle) {
	int i, j;

	if(cle == 'H') {
		printf("Matrice périphérique horizontale :\n");
		for(i = 0; i < N/2; i++) {
			for(j = 0; j < N; j++) printf("%i ",mat[i][j]);
		}
		printf("\n");
	}
	else if(cle == 'V') {
		printf("Matrice périphérique verticale :\n");
		for(i = 0; i < N; i++) {
			for(j = 0; j < N/2; j++) printf("%i ",mat[i][j]);
		}
		printf("\n\n");

	}
	printf("\n\n");
}

int main() {
	char *saisie = "nombres_puzzle.txt";
	int matH[N][N], matV[N][N];

	init_matrices(matH,matV);
	lecture_fic(saisie,2,matH,matV);
	afficher_matrice(matH,'H');
	afficher_matrice(matV,'V');
}
