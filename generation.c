/**
* \file generatin.c
* \author KAJAK Rémi
* \version 1.0
* \date 19/03/2018
* \brief Fichier ayant servi à l'élaboration de la fonction de lecture du fichier texte qui contient les nombres générateurs de la matrice principale et la fonction de génération de la matrice solution.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* \def N
* \brief Nombre de lignes de la matrice test
*/
#define N 5

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
			for(i = 1; i <= 2; i++) { // Lecture successive des clés
				ligne = 0;
				colonne = 0;

				while(carac != cle[i]) { // Tant que l'on n'a pas trouvé la clé de départ
					fscanf(fic_gen,"%c",&carac);
				}
				fscanf(fic_gen,"%c",&carac);

				while(carac != cle[i+1]) { // Tant que l'on n'a pas trouvé la clé de fin
					if(carac == ' ' || carac == '\n') {
						fscanf(fic_gen,"%i",&nb_case);
						if(cle[i] == 'H') H[colonne][ligne] = nb_case;
						else if(cle[i] == 'V') V[ligne][colonne] = nb_case;
						colonne++;
					}
					else if(carac == '+') {
						ligne++;
						colonne = 0;
					}
					fscanf(fic_gen,"%c",&carac);
				}
			}
		}
		fscanf(fic_gen,"%c %i",&carac,&num_puz);
	}
	fclose(fic_gen);
}

void init_compteurs_periph(int cptH[N], int cptV[N]) {
	int i;
	
	for(i = 0; i < N; i++) {
		cptH[i] = 0;
		cptV[i] = 0;
	}
}

void gen_solution(int S[N][N], int H[N][N], int V[N][N]) {
	int nbH[N], nbV[N], i, j;
	
	// Dans un premier temps, on dénombre les chiffres présents dans chacune des lignes des matrices périphériques
	init_compteurs_periph(nbH,nbV);
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			if(H[j][i] > 0) nbH[i] = nbH[i] + 1;
			if(V[i][j] > 0) nbV[i] = nbV[i] + 1;
		}
	}
	
	// Ensuite, 
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			
		}
	}
}

void init_matrices(int S[N][N], int H[N][N], int V[N][N]) {
	int i, j;
	
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			S[i][j] = 0;
			H[i][j] = 0;
			V[i][j] = 0;
		}
	}
}

void afficher_matrice(int mat[N][N], char cle) {
	int i, j;
	
	printf("\n");
	if(cle == 'H') {
		printf("Matrice périphérique horizontale :\n");
		for(i = 0; i < N/2; i++) {
			for(j = 0; j < N; j++) printf("%i ",mat[i][j]);
			printf("\n");
		}
		
	}
	else if(cle == 'V') {
		printf("Matrice périphérique verticale :\n");
		for(i = 0; i < N; i++) {
			for(j = 0; j < N/2; j++) printf("%i ",mat[i][j]);
			printf("\n");
		}
	}
	else {
		printf("Matrice solution :\n");
		for(i = 0; i < N; i++) {
			for(j = 0; j < N; j++) printf("%i ",mat[i][j]);
			printf("\n");
		}
	}
}

int main() {
	char *saisie = "nombres_puzzle.txt";
	int matH[N][N], matV[N][N], soluce[N][N];
	
	init_matrices(soluce,matH,matV);
	lecture_fic(saisie,1,matH,matV);
	afficher_matrice(matH,'H');
	afficher_matrice(matV,'V');
	
	gen_solution(soluce,matH,matV);
	afficher_matrice(soluce,'S');
	printf("\n");
}
