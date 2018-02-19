#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10
#define M 5
int mat[N][M];

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
