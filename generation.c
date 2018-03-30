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

void afficher_matrice(int mat[N][N], char cle) {
	int i, j;
	
	printf("\n");
	if(cle == 'C') {
		printf("Matrice périphérique horizontale :\n");
		for(i = 0; i < N/2; i++) {
			for(j = 0; j < N; j++) printf("%i ",mat[i][j]);
			printf("\n");
		}
		
	}
	else if(cle == 'L') {
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

/**
* \fn lecture_fic(char *nom, int niveau)
* \brief Lit un fichier avec un format spécifique et renseigne les nombres contenus dans les matrices périphériques.
* \param nom Nom du fichier texte à analyser
* \param niveau Nombre du puzzle à trouver dans le fichier
* \return Ne retourne aucun résultat
*/
void lecture_fic(char *nom_fic, int niveau, int C[N][N], int L[N][N]) { /* Lecture du fichier contenant les puzzles prédéfinis */
	FILE * fic_gen;
	char cle[4] = "PCLF", carac;
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
						if(cle[i] == 'C') C[colonne][ligne] = nb_case;
						else if(cle[i] == 'L') L[ligne][colonne] = nb_case;
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

/**
* \fn adequation_rangee_et_nombres(int S[N][N], int periph[N][N], int cpt[N], int rangee, char type_rangee)
* \brief Lérifie dans la matrice solution, pour une matrice périphérique, un compteur d'indice et une rangée précise donnés, si le remplissage d'une rangée de type "ligne" correspond aux nombres de la rangée de type "colonne" (et inversement).
* \param S La matrice solution dans laquelle on vérifie l'adéquation d'une rangée par rapport à une autre
* \param periph La matrice périphérique qui contient les nombres nécessaires à la vérification
* \param cpt La taille du groupe de nombres vérifié
* \param rangee La rangée de la matrice solution qui va être vérifiée
* \param type_rangee La nature de la rangée (ligne ou colonne)
* \return 1 s'il y a un débordement, 0 si les données correspondent, -1 s'il reste des cases à compléter
*/
int adequation_rangee_et_nombres(int S[N][N], int periph[N][N], int cpt, int rangee, char type_rangee) {
	int i, sortie = 0, sortie_groupe, cpt_verif = 0, liste_taille_groupe[cpt], valeur_nombres = 0;
	
	// Avant toute opération, on initialise la liste de vérification des nombres
	for(i = 0; i < cpt; i++) liste_taille_groupe[i] = 0;
	
	// On parcourt la rangée analysée
	if(type_rangee == 'C') {
		for(i = 0; i < N; i++) {
			if(S[i][rangee] != 0 && S[i][rangee] != 2) {
				sortie_groupe = 0;
				liste_taille_groupe[cpt_verif] = liste_taille_groupe[cpt_verif] + 1;	
			}
			else sortie_groupe = 1;
			
			if(S[i-1][rangee] != 0 && S[i-1][rangee] != 2 && sortie_groupe == 1) cpt_verif++;
		}
		i = 0;
		
		while(i < cpt && sortie == 0) {
			if(liste_taille_groupe[i] < periph[i][rangee]) {
				valeur_nombres = -1;
				sortie = 1;
			}
			else if(liste_taille_groupe[i] > periph[i][rangee]) {
				valeur_nombres = 1;
				sortie = 1;
			}
			i++;
		}
	}
	else if(type_rangee == 'L') {
		for(i = 0; i < N; i++) {
			if(S[rangee][i] != 0 && S[rangee][i] != 2) liste_taille_groupe[cpt_verif] = liste_taille_groupe[cpt_verif] + 1;
			else cpt_verif++;
		}
		i = 0;
		
		while(i < N && sortie == 0) {
			if(liste_taille_groupe[i] < periph[rangee][i]) {
				valeur_nombres = -1;
				sortie = 1;
			}
			else if(liste_taille_groupe[i] > periph[rangee][i]) {
				valeur_nombres = 1;
				sortie = 1;
			}
			i++;
		}
	}
	printf("\nCompteur défaut : %i",cpt);
	printf("\nCompteur verif : %i, Valeur nombres : %i",cpt_verif,valeur_nombres);
	if(cpt_verif < cpt || valeur_nombres == -1) return -1;
	else if(cpt_verif > cpt || valeur_nombres == 1) return 1;
	else if(cpt_verif == cpt || valeur_nombres == 0) return 0;
}

/**
* \fn init_compteurs_periph(int cptC[N], int cptL[N])
* \brief Initialise les compteurs des matrices périphériques. Leur rôle est d'indiquer combien de nombres sont contenus dans chaque rangée (ligne/colonne) de chaque matrice périphérique. Ces compteurs sont utilisés dans la fonction gen_solution(int S[N][N], int C[N][N], int L[N][N]).
* \param cptC Tableau d'indices de la matrice périphérique des colonnes
* \param cptL Tableau d'indices de la matrice périphérique des lignes
* \return Ne retourne aucun résultat
*/
void init_compteurs_periph(int cptC[N], int cptL[N]) {
	int i;
	
	for(i = 0; i < N; i++) {
		cptC[i] = 0;
		cptL[i] = 0;
	}
}

/**
* \fn gen_solution(int S[N][N], int C[N][N], int L[N][N])
* \brief Initialise la matrice solution grâce aux données des matrices périphériques.
* \param S La matrice solution qui va contenir le motif du puzzle
* \param C La matrice périphérique des colonnes (situé en haut de la grille du Picross)
* \param L La matrice périphérique des lignes (situé à gauche de la grille du Picross)
* \return Ne retourne aucun résultat
*/
void gen_solution(int S[N][N], int C[N][N], int L[N][N]) {
	int nbC[N], nbL[N], i, j, k, l, decalage, verif, respect_regles = 0, tour_lignes = 1;
	
	// Dans un premier temps, on dénombre les chiffres présents dans chacune des lignes des matrices périphériques
	init_compteurs_periph(nbC,nbL);
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			if(C[j][i] > 0) nbC[i] = nbC[i] + 1;
			if(L[i][j] > 0) nbL[i] = nbL[i] + 1;
		}
	}
	
	// Initialisation des variables d'incrémentation
	i = 0;
	j = 0;
	
	afficher_matrice(C,'C');
	
	// Ensuite, on boucle la matrice jusqu'à ce que la solution soit correctement générée
	while(respect_regles != 1) {
		if(tour_lignes == 1) {							// On commence par remplir les lignes
			decalage = j;
			
			for(k = 0; k < nbL[i]; k++) {				// Si le nombre relevé est supérieure à 0 (au moins un groupe de case existant)
				if(nbL[k] > 0) {						// Pour chaque nombre de la ligne lue dans la matrice périphérique
					for(l = 0; l < L[i][j]; l++) {		// Pour chaque nombre lu dans la matrice périphérique, on remplit les cases
						S[i][decalage] = 1;
						decalage++;
					}
					decalage++;
				}
			}
			verif = adequation_rangee_et_nombres(S,C,nbC[i],j,'C');
			printf("\nVérification : %i\n\n",verif);
			i++;
			if(verif != -1) j++;
		}
		if(i >= N) respect_regles = 1;
	}
}

void init_matrices(int S[N][N], int C[N][N], int L[N][N]) {
	int i, j;
	
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			S[i][j] = 0;
			C[i][j] = 0;
			L[i][j] = 0;
		}
	}
}

int main() {
	char *saisie = "nombres_puzzle.txt";
	int matC[N][N], matL[N][N], soluce[N][N];
	
	init_matrices(soluce,matC,matL);
	lecture_fic(saisie,1,matC,matL);
	
	gen_solution(soluce,matC,matL);
	afficher_matrice(soluce,'S');
	printf("\n");
}
