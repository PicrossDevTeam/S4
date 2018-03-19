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
* \def M
* \brief Nombre de colonnes de la matrice test
*/
#define M 5
/**
* \def mat[N][M]
* \brief Matrice test pour l'insertion - non-fonctionnelle
*/
int mat[N][M];

/**
* \fn lecture_fic(char *nom, int niveau)
* \brief Lit un fichier avec un format spécifique et renseigne les nombres contenus dans les matrices adjacentes
* \param nom Nom du fichier texte à analyser
* \param niveau Nombre du puzzle à trouver dans le fichier
* \return Ne retourne aucun résultat
*/
void lecture_fic(char *nom_fic, int niveau) { /* Lecture du fichier contenant les puzzles prédéfinis */
	FILE * fic_gen;
	char cle[4] = "PHVF", carac;
	int ligne, colonne, num_puz, nb_case;
	
	fic_gen = fopen(nom_fic,"r");
	fscanf(fic_gen,"%c %i",&carac,&num_puz);
	
	while(!feof(fic_gen)) { // Tant que la fin du fichier n'a pas été atteinte
		if(carac == cle[0] && num_puz == niveau) { // Si on trouve le bon niveau de puzzle
			printf("%c %i\n",carac,num_puz);
			for(int i = 1; i <= 2; i++) { // Lecture successive des clés
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
						mat[ligne][colonne] = nb_case;
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

int main() {
	char *saisie = "nombres_puzzle.txt";
	
	lecture_fic(saisie,2);
}
